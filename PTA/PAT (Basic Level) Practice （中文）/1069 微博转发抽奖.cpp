#include <iostream>
#include <vector>
#include <map>
using namespace std;

void print_forwarder(vector<string> f) {
	cout << "----" << endl;
	int len = f.size();
	for(int i = 0; i < len; i++) {
		cout << f[i] << endl;
	}
	cout << "----" << endl;
}
int main() {
	int m, n, s;
	cin >> m >> n >> s;
	if(m - s < 0)
		cout << "Keep going..." << endl;
    else {
		s--;
		// Filter
		string tmp;
		for(int i = 0; i < s; i++) {
			cin >> tmp;
		}
		// Start Collect
		m -= s;
    	vector<string> fer(m);
		for(int i = 0; i < m; i++)
			cin >> fer[i];
//		print_forwarder(fer);
		map<string, bool> is_lucky;
		for(int i = 0; i < m; i += n) {
			while(i < m && is_lucky.count(fer[i]) > 0)
				i++;
			if(i == m) break;
			is_lucky[fer[i]] = true;
			cout << fer[i] << endl;
		}
	}
	
}
