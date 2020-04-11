#include <iostream>
using namespace std;

int main()
{
	string decode, encode;
	cin >> decode;
	encode = decode;
	for(int i = 0; i < decode.length(); i++)
    {
    	encode[i] += 3;
		if(encode[i] > 'z')
			encode[i] = 'a' + (encode[i] % 'z') - 1;
    }
    cout << encode;
}
