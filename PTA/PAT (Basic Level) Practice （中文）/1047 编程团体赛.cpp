#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int team[1001] = {0};
	int team_id, team_member, member_score;
	for(int i = 0; i < n; i++) {
		cin >> team_id >> team_member >> member_score;
		team[team_id] += member_score;
	}
	int max_team = 1;
	for(int i = 2; i < 1001; i++) {
		if(team[i] > team[max_team])
			max_team = i;
	}
	printf("%d %d\n", max_team, team[max_team]);
}
