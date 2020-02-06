#include <iostream>
#include <vector>
using namespace std;
typedef struct
{
  int teams;
  int players;
} school;
int main() {
  int n;
  cin >> n;
  vector<school> m(n);
  for(int i = 0; i < n; i++) {
    cin >> m[i].teams;
  	m[i].players = 0;
  }

  vector<int> x(0);

  int finish = 0;
  for(int i = 0; i < m.size(); ) {
    if(m[i].teams * 10 > m[i].players) {
      x.push_back(i + 1);
      cout << "[" << i + 1 <<"]" << m[i].players << endl;
      if(++m[i].players == m[i].teams * 10) ++finish;
    }

    if(++i == m.size()) i = 0;
    if(finish == m.size() - 1) break;
  }

  return 0;
  int flag = 0;
  for(int i = 0; i < x.size(); i++) {
	cout << x[i];
	if(++flag % 10 == 0) cout << endl;
	else cout << ' ';
  }
  

  for(int i = 0; i < m.size(); i++) {
    if(m[i].players >= m[i].teams * 10) continue;
    if(m.size() == 1) x.push_back(0);
    while(m[i].players < m[i].teams * 10) {
      x.push_back(i + 1);
      x.push_back(0);
      ++m[i].players;
    }
  }

  for(int i = 0; i < m.size(); ++i) {
    cout << "#" << i + 1 << endl;
    m[i].players = 0;
    for(int j = 0; j < x.size(); ++j) {
      if(x[j] != i + 1) continue;
      cout << j + 1;
      if(++m[i].players % 10 == 0) {
        if(m[i].players < m[i].teams * 10)
          cout << endl;
      } else {
        cout << " ";
      }
    }
    if(i + 1 != m.size()) cout << endl;
  }

  return 0;
}
