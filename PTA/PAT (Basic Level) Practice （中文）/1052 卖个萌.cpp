#include <iostream>
#include <vector>
using namespace std;

void get_face(string s, vector<string> & face) {
	face.clear();
	int start;
	int len = s.length();
	for(int i = 0; i < len; i++) {
		if(s[i] == '[')
			start = i + 1;
		else if(s[i] == ']') {
			// cout << start << ' ' << i << endl;
			face.push_back(s.substr(start, i - start));
		}
	}
}

void print_face(vector<string> face) {
	cout << face.size() << endl;
	for(int i = 0; i < face.size(); i++) {
		if(i > 0) cout << "    ";
		cout << face[i];
	}
	cout << endl;
}

int main() {
	string a, b, c;
	getline(cin, a);
	getline(cin, b);
	getline(cin, c);
//	cout << a << endl << b << endl << c << endl;
	vector< vector<string> > face(3);
	get_face(a, face[0]); // hand
	get_face(b, face[1]); // eye
	get_face(c, face[2]); // mouth
//	print_face(face[0]);
//	print_face(face[1]);
//	print_face(face[2]);
	int n;
	cin >> n;
	int q, w, e, r, t; // left_hand, left_eye, mouth, right_eye, right_hand
	for(int i = 0; i < n; i++) {
		cin >> q >> w >> e >> r >> t;
		if(
			q <= 0 || w <= 0 || e <= 0 || r <= 0 || t <= 0
			|| q > face[0].size() || w > face[1].size() || e > face[2].size()
			|| r > face[1].size() || t > face[0].size()
		) {
			printf("Are you kidding me? @\\/@\n");
		} else {
			printf(
				"%s(%s%s%s)%s\n",
				face[0][q - 1].c_str(),
				face[1][w - 1].c_str(),
				face[2][e - 1].c_str(),
				face[1][r - 1].c_str(),
				face[0][t - 1].c_str()
			);
		}
	}
}
