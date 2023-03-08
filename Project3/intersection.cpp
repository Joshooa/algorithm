#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct car {
	int t;
	char w;
	bool outCeck = false; // 교차로 빠져나간 여부 확인
	bool standBy = false; // 교차로 구역에 진입여부 체크
	int outTime = 0;
};

int Time;
vector<car> car_info;
queue<car> car_check;
int section[4]; // A=0, B=1, C=2, D=3
bool escape = false;

int main()
{
	int n;

	cin >> n;

	// 차 정보 입력받아서 교차로 정보 배열에 입력
	for (int i = 0; i < n; i++) {
		car c;
		cin >> c.t >> c.w;
		car_info.push_back(c);
		car_check.push(c);
	}

	// 교차로 상황 시뮬레이션
	while (!car_check.empty()) {

		// 교차로에 차량 진입정보 확인하기
		for (int i = 0; i < n; i++) {
			// 교차로에 차량 진입 시간이 되었다면 구역별로 차량 배치
			if (car_info[i].t == Time && car_info[i].standBy == false) {
				// 교차로 구역별로 이동하기
				if (car_info[i].w == 'A') {
					car_info[i].standBy = true;
					section[0]++;
				}
				else if (car_info[i].w == 'B') {
					car_info[i].standBy = true;
					section[1]++;
				}
				else if (car_info[i].w == 'C') {
					car_info[i].standBy = true;
					section[2]++;
				}
				else if (car_info[i].w == 'D') {
					car_info[i].standBy = true;
					section[3]++;
				}
			}
		} // 차 정보 확인 for문 종료

		bool fullCheck = false;
		int num = 0;
		for (int i = 0; i < 4; i++) {
			if (section[i] != 0) {
				//cout << "section[" << i << "]: " << section[i] << endl;
				num++;
			}
		}
		if (num == 4) fullCheck = true;

		bool A_check = false;
		bool B_check = false;
		bool C_check = false;
		bool D_check = false;

		// 교차로 진입한 차들 중 우측에 차없으면 교차로 나가기
		if (fullCheck == false) {
			for (int i = 0; i < n; i++) {
				if (car_info[i].standBy == true &&
					car_info[i].w == 'A' && car_info[i].outCeck == false && A_check == false) {
					// D구역에 차가 없으면 교차로 나가기
					if (section[3] == 0) {
						car_info[i].outTime = Time;
						car_info[i].outCeck = true;
						car_check.pop();
						A_check = true;
					}
				}
				else if (car_info[i].standBy == true && car_info[i].w == 'B' && car_info[i].outCeck == false && B_check == false) {
					// A구역에 차가 없으면 교차로 나가기
					if (section[0] == 0) {
						car_info[i].outTime = Time;
						car_info[i].outCeck = true;
						car_check.pop();
						B_check = true;
					}
				}
				else if (car_info[i].standBy == true && car_info[i].w == 'C' && car_info[i].outCeck == false && C_check == false) {
					// B구역에 차가 없으면 교차로 나가기
					if (section[1] == 0) {
						car_info[i].outTime = Time;
						car_info[i].outCeck = true;
						car_check.pop();
						C_check = true;
					}
				}
				else if (car_info[i].standBy == true && car_info[i].w == 'D' && car_info[i].outCeck == false && D_check == false) {
					// C구역에 차가 없으면 교차로 나가기
					if (section[2] == 0) {
						car_info[i].outTime = Time;
						car_info[i].outCeck = true;
						car_check.pop();
						D_check = true;
					}
				}
			}
			// 교차로 차 내보낸다음 교차로에있는 차 파악하기
			for (int i = 0; i < n; i++) {
				if (car_info[i].outCeck == true && car_info[i].w == 'A') {
					if (section[0] > 0) section[0]--;
				}
				else if (car_info[i].outCeck == true && car_info[i].w == 'B') {
					if (section[1] > 0) section[1]--;
				}
				else if (car_info[i].outCeck == true && car_info[i].w == 'C') {
					if (section[2] > 0) section[2]--;
				}
				else if (car_info[i].outCeck == true && car_info[i].w == 'D') {
					if (section[3] > 0) section[3]--;
				}
			}
		}
		else if (fullCheck == true) {
			for (int j = 0; j < n; j++) {
				if (car_info[j].outCeck == false) {
					car_info[j].outTime = -1;
					car_check.pop();
				}
			}
		}
		Time++;
	}

	for (int i = 0; i < n; i++) {
		cout << car_info[i].outTime << endl;
	}

	return 0;
}