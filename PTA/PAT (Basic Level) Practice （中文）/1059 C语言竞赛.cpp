#include <iostream>
#include <memory.h>
using namespace std;

bool is_prime[10000];

void generate_prime(int n = 10000) {
	memset(is_prime, true, sizeof(is_prime));
	int prime[10000] = {0};
	int t = 0;
	int end = n / 2;
	for(int i = 2; i <= end; i++) {
		if(is_prime[i])
			prime[t++] = i;
		for(int j = 0; j < t && i * prime[j] <= n; j++) {
			is_prime[i * prime[j]] = false;
			if(i % prime[j] == 0) break;
		}
	}
}

void print_prime() {
	for(int i = 2; i < 10000; i++) {
		if(is_prime[i])
			printf(" %d", i);
	}
	printf("\n");
}

int main() {
	generate_prime();
	int id[10000] = {0};
	int n, input, first;
	scanf("%d", &n);
	scanf("%d", &first);
	id[first] = 1;
	for(int i = 2; i <= n; i++) {
		scanf("%d", &input);
		id[input] = i;
	}
	int k;
	scanf("%d", &k);
	for(int i = 0; i < k; i++) {
		scanf("%d", &input);
		if(id[input] == 0)
			printf("%04d: Are you kidding?\n", input);
		else if(id[input] == -1)
			printf("%04d: Checked\n", input);
		else {
			if(input == first)
				printf("%04d: Mystery Award\n", input);
			else if(is_prime[id[input]])
				printf("%04d: Minion\n", input);
			else
				printf("%04d: Chocolate\n", input);
			id[input] = -1;
		}
	}
}
