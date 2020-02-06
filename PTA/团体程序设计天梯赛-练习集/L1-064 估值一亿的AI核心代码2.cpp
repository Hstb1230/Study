#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void string_replace(string & str, string find, string rep) {
  size_t pos = 0;
  while((pos = str.find(find, pos)) != string::npos) {
    str.replace(pos, find.length(), rep);
  }
}

void str_tolower(string & str, char except = '\0') {
  size_t end = str.length();
  for(int i = 0; i < end; ++i) {
    if(str[i] >= 'A' && str[i] <= 'Z' && str[i] != except) {
      str[i] = (str[i] - 'A') + 'a';
    }
  }
}

void cut_string_to_array(string str, vector<string> flag, vector<string> & result) {
  result.clear();
  size_t pos = 0;
  size_t min_pos, tmp_pos;
  string find_flag;

  while(pos < str.length()) {
    min_pos = string::npos;

    for(auto i : flag) {
      if((tmp_pos = str.find(i, pos)) < min_pos) {
        min_pos = tmp_pos;
        find_flag = i;
      }
    }

    if(pos < min_pos)
      result.push_back(str.substr(pos, min_pos - pos));
    cout << pos << ' ' << min_pos << ' ' << find_flag << ' ' << str.substr(pos, min_pos - pos) << ".." << endl;
    pos = min_pos + find_flag.length();

    // 没有一个分割符了
    if(min_pos == string::npos) break;
    result.push_back(find_flag);
  }
}

int main() {
  int n;
  cin >> n;
  string s;
  getline(cin, s);
  vector<string> flag = {" ", ",", "!", "?", "'", ".", ";"};
  vector<string> res;
  while(n--) {
    getline(cin, s);
    cout << s << endl;
//    因为题目要求 I 不转，所以这边用自定义函数
//    但其实可以先都转，然后再用函数把i大写
//    transform(s.begin(), s.end(), s.begin(), ::tolower);
//    实际并不行
    str_tolower(s, 'I');
    cut_string_to_array(s, flag, res);

    for(int i = 0; i < res.size(); ++i) {
      if(res[i] == " ") {
        if(i == 0 || i + 1 == res.size()) {
          res.erase(res.begin() + i, res.begin() + i + 1);
          --i;
          continue;
        } else {
          if(find(flag.begin(), flag.end(), res[i + 1]) != flag.end()) {
            res.erase(res.begin() + i, res.begin() + i + 1);
            --i;
            continue;
          }
        }

      } else if(res[i] == "?") {
        res[i] = "!";
      }
      //cout << res[i];
    }
    //cout << endl;

    for(int i = 0; i < res.size(); ++i) {
      if(res[i] == "I" || res[i] == "me") {
        res[i] = "you";
      } else if(i + 2 <= res.size()) {
        if(res[i] == "can" && res[i + 2] == "you") {
          res[i] = "I";
          res[i + 2] = "can";
          i += 3;
        } else if(res[i] == "could" && res[i + 2] == "you") {
          res[i] = "I";
          res[i + 2] = "could";
          i += 3;
        }
      }
    }
    
    cout << "AI: ";
    for(int i = 0; i < res.size(); ++i) {
      cout << res[i];
    }
    cout << '|';
    cout << endl;
  }
}
