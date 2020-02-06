#include <iostream>
#include <map>
using namespace std;
// typedef的另一个作用
// <>中间是类型名, 不能多行
typedef struct {
  string id;
  int kaoshi;
} info;
map<int, info> m;
int main() {
  int n;
  cin >> n;
  string id;
  int shiji;
  int kaoshi;
  while(n--) {
    cin >> id >> shiji >> kaoshi;
    m[shiji].id = id;
    m[shiji].kaoshi = kaoshi;
  }

  int M;
  cin >> M;
  int cha;
  while(M--) {
    cin >> cha;
    cout << m[cha].id << ' ' << m[cha].kaoshi << endl;
  }
}
