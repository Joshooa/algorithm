#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct car {
	int t=-1;
	char w='Z';
	bool outCeck = false; // 교차로 빠져나간 여부 확인
	bool standBy = false; // 교차로 구역에 진입여부 체크
	int outTime = 0;
};

int Time;
vector<car> car_info;
queue<car> car_check;
queue<car> inSec;
int section[4]; // A=0, B=1, C=2, D=3
bool escape = false;

int main()
{
	int n;

	cin >> n;

	// index를 1부터 시작하기위한 더미데이터 삽입
	car d;
	car_info.push_back(d);

	// 차 정보 입력받아서 교차로 정보 배열에 입력
	for (int i = 1; i <= n; i++) {
		car c;
		cin >> c.t >> c.w;
		car_info.push_back(c);
		car_check.push(c);
	}

	// n까지 인덱스 늘려주기
	car_info.push_back(d);

	// 교차로 상황 시뮬레이션
	while (!car_check.empty()) {

		// 교차로에 차량 진입정보 확인하기
		for (int i = 1; i <= n; i++) {
			// 교차로에 차량 진입 시간이 같다면 교차로에 진입시켜주기
			if (car_info[i].standBy == false && car_info[i].t == car_info[i+1].t) {
				// 교차로 구역별로 이동하기
				if (car_info[i].w == 'A') {
					car_info[i].standBy = true;
					section[0]++;
					inSec.push(car_info[i]); // 교차로 진입하기
				}
				else if (car_info[i].w == 'B') {
					car_info[i].standBy = true;
					section[1]++;
					inSec.push(car_info[i]); // 교차로 진입하기
				}
				else if (car_info[i].w == 'C') {
					car_info[i].standBy = true;
					section[2]++;
					inSec.push(car_info[i]); // 교차로 진입하기
				}
				else if (car_info[i].w == 'D') {
					car_info[i].standBy = true;
					section[3]++;
					inSec.push(car_info[i]); // 교차로 진입하기
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
		
		bool init_time = false;
		int cur_time = 0;

		// 교차로 진입한 차들 중 우측에 차없으면 교차로 나가기
		if (fullCheck == false) {
			while (!inSec.empty()) {
				// 교차로 최초 진입 차량의 진입시간을 시뮬레이션 시간으로 사용
				if (init_time == false) {
					cur_time = inSec.front().t;
					init_time = true;
				}

				for (int i = 0; i < n; i++) {
					if (car_info[i].standBy == true &&
						car_info[i].w == 'A' && car_info[i].outCeck == false && A_check == false) {
						// D구역에 차가 없으면 교차로 나가기
						if (section[3] == 0) {
							car_info[i].outTime = cur_time;
							car_info[i].outCeck = true;
							car_check.pop();
							A_check = true;
							inSec.pop();
						}
					}
					else if (car_info[i].standBy == true && car_info[i].w == 'B' && car_info[i].outCeck == false && B_check == false) {
						// A구역에 차가 없으면 교차로 나가기
						if (section[0] == 0) {
							car_info[i].outTime = cur_time;
							car_info[i].outCeck = true;
							car_check.pop();
							B_check = true;
							inSec.pop();
						}
					}
					else if (car_info[i].standBy == true && car_info[i].w == 'C' && car_info[i].outCeck == false && C_check == false) {
						// B구역에 차가 없으면 교차로 나가기
						if (section[1] == 0) {
							car_info[i].outTime = cur_time;
							car_info[i].outCeck = true;
							car_check.pop();
							C_check = true;
							inSec.pop();
						}
					}
					else if (car_info[i].standBy == true && car_info[i].w == 'D' && car_info[i].outCeck == false && D_check == false) {
						// C구역에 차가 없으면 교차로 나가기
						if (section[2] == 0) {
							car_info[i].outTime = cur_time;
							car_info[i].outCeck = true;
							car_check.pop();
							D_check = true;
							inSec.pop();
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
				cur_time++;

				// 차량 내보내고 다음 교차로에 진입하는 차량 확인
				for (int i = 0; i < n; i++) {
					if (cur_time == car_info[i].t && car_info[i].standBy == false) {
						if (car_info[i].w == 'A') {
							car_info[i].standBy = true;
							section[0]++;
							inSec.push(car_info[i]); // 교차로 진입하기
						}
						else if (car_info[i].w == 'B') {
							car_info[i].standBy = true;
							section[1]++;
							inSec.push(car_info[i]); // 교차로 진입하기
						}
						else if (car_info[i].w == 'C') {
							car_info[i].standBy = true;
							section[2]++;
							inSec.push(car_info[i]); // 교차로 진입하기
						}
						else if (car_info[i].w == 'D') {
							car_info[i].standBy = true;
							section[3]++;
							inSec.push(car_info[i]); // 교차로 진입하기
						}
					}
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
	}

	for (int i = 0; i < n; i++) {
		cout << car_info[i].outTime << endl;
	}

	return 0;
}