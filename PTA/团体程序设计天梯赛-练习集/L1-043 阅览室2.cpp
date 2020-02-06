#include <iostream>
using namespace std;
const int MaxN = 1e3 + 1;

int timeToStamp(int h, int m) {
  return h * 60 + m;
}

int main() {
  int n;
  scanf("%d", &n);

  int id;
  char key;
  int h, m;

  int t[MaxN] = { 0 };
  bool b[MaxN] = { false };
  int count = 0;
  double time = 0;

  while(n) {
    scanf("%d %c %d:%d", &id, &key, &h, &m);
    if(id == 0) {
      for(int i = 0; i < MaxN; i++) t[i] = 0;
      for(int i = 0; i < MaxN; i++) b[i] = false;
      printf("%d ", count);
      printf("%d\n", (count == 0 ? 0 : (int)(time / count + 0.5f)));
      --n;
      count = time = 0;
      continue;
    }

    if(key == 'S') {
      t[id] = timeToStamp(h, m);
      b[id] = true;
    } else if(key == 'E') {
      if(b[id] == false) continue;
      ++count;
      time += timeToStamp(h, m) - t[id];
      b[id] = false;
    }

  }
}
