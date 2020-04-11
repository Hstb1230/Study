#include <iostream>
#include <cmath>
using namespace std;

bool is_leap_year(int year = 2020)
{
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

double ceil(double number, int len)
{
	number *= pow(10, len);
	return ceil(number) / pow(10, len);
}

void print_double(double number, int high_len = 0, int low_len = 0)
{
	int high = (int)number,
		low = (int)(fmod(number, 1) * pow(10, low_len));
	printf("%*d", high_len, high);
	if(low_len > 0)
	{
		printf(".");
		printf("%0*d", low_len, low);
	}
}

int main()
{
	int year, month, min_repay; double bill;
	cin >> year >> month >> min_repay >> bill;
	double bill_rate = 10 * 0.01, interest_rate = 0.05 * 0.01;
	// year和month是指账单产生的时间, 并不是第一次结算时间
	if(++month > 12)
	{
		month = 1;
		year++;
	}
	int month_size[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(is_leap_year(year))
		month_size[1] = 29;
	else
		month_size[1] = 28;
	double cost, interest = 0;
	double cost_sum = 0, interest_sum = 0;
	int flag_first_month = 0;
	int repay_month = 0;
	while(bill > 0)
	{
		repay_month++;
		// 花呗最低还款也会计算首月消费账单的利息
		// 如上月花了1663, 但最低还款会变成169.3, 多了3.3的利息
		// 也许是手续费, 但并不重要, 都是坑钱就对了
		if(flag_first_month++ > 0)
			interest = ceil(month_size[month] * interest_rate * bill, 2);
		bill += interest;
		cost = ceil(bill_rate * bill, 2);
		if(++month > 12)
		{
			month = 1;
			year++;
			month_size[2] = is_leap_year(year) ? 29 : 28;
		}
		if(cost <= min_repay)
			cost = min_repay;
		if(cost > bill)
			cost = bill;
		bill -= cost;
		// 假设会多还款, (喜欢把剩余账单留成整百)
		cost += fmod(bill, 100);
		bill -= fmod(bill, 100);
		
		printf("还款: ");
		print_double(cost, 3, 2);
		printf(" ( 利息: ");
		print_double(interest, 3, 2);
		printf(" ) , ");
		printf("剩余金额: ");
		print_double(bill, 4, 2);
		printf("\n");
		cost_sum += cost;
		interest_sum += interest;
	}
	printf("还款次数: %d , ", repay_month);
	printf("总还款: ");
	print_double(cost_sum, 4, 2);
	printf(" ( 利息: ");
	print_double(interest_sum, 3, 2);
	printf(" )\n");
}
