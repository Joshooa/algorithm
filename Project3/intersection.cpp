#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct car {
	int t=-1;
	char w='Z';
	bool outCeck = false; // ������ �������� ���� Ȯ��
	bool standBy = false; // ������ ������ ���Կ��� üũ
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

	// index�� 1���� �����ϱ����� ���̵����� ����
	car d;
	car_info.push_back(d);

	// �� ���� �Է¹޾Ƽ� ������ ���� �迭�� �Է�
	for (int i = 1; i <= n; i++) {
		car c;
		cin >> c.t >> c.w;
		car_info.push_back(c);
		car_check.push(c);
	}

	// n���� �ε��� �÷��ֱ�
	car_info.push_back(d);

	// ������ ��Ȳ �ùķ��̼�
	while (!car_check.empty()) {

		// �����ο� ���� �������� Ȯ���ϱ�
		for (int i = 1; i <= n; i++) {
			// �����ο� ���� ���� �ð��� ���ٸ� �����ο� ���Խ����ֱ�
			if (car_info[i].standBy == false && car_info[i].t == car_info[i+1].t) {
				// ������ �������� �̵��ϱ�
				if (car_info[i].w == 'A') {
					car_info[i].standBy = true;
					section[0]++;
					inSec.push(car_info[i]); // ������ �����ϱ�
				}
				else if (car_info[i].w == 'B') {
					car_info[i].standBy = true;
					section[1]++;
					inSec.push(car_info[i]); // ������ �����ϱ�
				}
				else if (car_info[i].w == 'C') {
					car_info[i].standBy = true;
					section[2]++;
					inSec.push(car_info[i]); // ������ �����ϱ�
				}
				else if (car_info[i].w == 'D') {
					car_info[i].standBy = true;
					section[3]++;
					inSec.push(car_info[i]); // ������ �����ϱ�
				}
			}
		} // �� ���� Ȯ�� for�� ����

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

		// ������ ������ ���� �� ������ �������� ������ ������
		if (fullCheck == false) {
			while (!inSec.empty()) {
				// ������ ���� ���� ������ ���Խð��� �ùķ��̼� �ð����� ���
				if (init_time == false) {
					cur_time = inSec.front().t;
					init_time = true;
				}

				for (int i = 0; i < n; i++) {
					if (car_info[i].standBy == true &&
						car_info[i].w == 'A' && car_info[i].outCeck == false && A_check == false) {
						// D������ ���� ������ ������ ������
						if (section[3] == 0) {
							car_info[i].outTime = cur_time;
							car_info[i].outCeck = true;
							car_check.pop();
							A_check = true;
							inSec.pop();
						}
					}
					else if (car_info[i].standBy == true && car_info[i].w == 'B' && car_info[i].outCeck == false && B_check == false) {
						// A������ ���� ������ ������ ������
						if (section[0] == 0) {
							car_info[i].outTime = cur_time;
							car_info[i].outCeck = true;
							car_check.pop();
							B_check = true;
							inSec.pop();
						}
					}
					else if (car_info[i].standBy == true && car_info[i].w == 'C' && car_info[i].outCeck == false && C_check == false) {
						// B������ ���� ������ ������ ������
						if (section[1] == 0) {
							car_info[i].outTime = cur_time;
							car_info[i].outCeck = true;
							car_check.pop();
							C_check = true;
							inSec.pop();
						}
					}
					else if (car_info[i].standBy == true && car_info[i].w == 'D' && car_info[i].outCeck == false && D_check == false) {
						// C������ ���� ������ ������ ������
						if (section[2] == 0) {
							car_info[i].outTime = cur_time;
							car_info[i].outCeck = true;
							car_check.pop();
							D_check = true;
							inSec.pop();
						}
					}
				}
				// ������ �� ���������� �����ο��ִ� �� �ľ��ϱ�
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

				// ���� �������� ���� �����ο� �����ϴ� ���� Ȯ��
				for (int i = 0; i < n; i++) {
					if (cur_time == car_info[i].t && car_info[i].standBy == false) {
						if (car_info[i].w == 'A') {
							car_info[i].standBy = true;
							section[0]++;
							inSec.push(car_info[i]); // ������ �����ϱ�
						}
						else if (car_info[i].w == 'B') {
							car_info[i].standBy = true;
							section[1]++;
							inSec.push(car_info[i]); // ������ �����ϱ�
						}
						else if (car_info[i].w == 'C') {
							car_info[i].standBy = true;
							section[2]++;
							inSec.push(car_info[i]); // ������ �����ϱ�
						}
						else if (car_info[i].w == 'D') {
							car_info[i].standBy = true;
							section[3]++;
							inSec.push(car_info[i]); // ������ �����ϱ�
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