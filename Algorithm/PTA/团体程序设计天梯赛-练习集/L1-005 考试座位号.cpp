#include <iostream>
#include <cstring>
// C++�������, ������չ����(��̬����)
#include <vector>
using namespace std;

typedef struct tester {
	// �ĳ�string����, ����ֱ�Ӹ�ֵ
	string id;
	// char id[17];    // ׼��֤��
	int exam_id;       // ������λ��
} retester;
/*
struct [type_name] {
	member_type member_name;
} [variable_name];
*/
/*
C++
typedef member_type type_name
typedef struct [type_name] {
	member_type member_name;
} type_rename;
*/

// ����һ��һά������̬���� int[]
vector<int> vi;
// ����һ����ά������̬���� int [][]
// vector<vector<int>> vii;
// >> �ᱻ���� cin >> i �� >>, ���Ա���
vector< vector<int> > vii;
// ����취������, �����е��鷳, һ��С�ľ�д��,
// �ر���д��ά���ϵ�ʱ��, �������ͺܳ�
// ���԰�һά����������(�������)
typedef vector<int> int_single_array;
vector<int_single_array> int_two_array;

int main() {
	retester rt;
	int n;
	cin >> n;
	// ��Ϊ����Ҫ��, �������ø�������¼��n
	int copy_n = n;
	tester t[n + 1];    // ���������������Ի���λ��, ��ΧΪ 1~N, ������Ҫ��1
	int test_id;        // ��¼�Ի���λ��
	// ��Ϊ�����ò���n, ���Կ���ֱ���������������ݵļ�����
	while(n--) {
		// ��Ϊһ��ʼ����ȷ����λ����, ������Ҫ�����ı�����¼,
        // ��t[0]�պ��ò���, ����������
		cin >> t[0].id >> test_id >> t[0].exam_id;
		// strcpy(t[test_id].id, t[0].id);
		// string���Ϳ���ֱ�Ӹ�ֵ
		t[test_id].id = t[0].id;
		t[test_id].exam_id = t[0].exam_id;
	}
	n = copy_n;
	for(int i = 1; i <= n; i++) {
		// ������printf����鷳, ��Ҫ����c_str����ת�����ַ�����
		//printf("%s %d %d\n", t[i].id.c_str(), i, t[i].exam_id);
	}
	// �ع���Ŀ����
	// �Ѿ��õ�������Ϣ, ��ʱ��ʼ��ѯ
	cin >> n;
	while(n--) {
		cin >> test_id;
		printf("%s %d\n", t[test_id].id.c_str(), t[test_id].exam_id);
	}
}
