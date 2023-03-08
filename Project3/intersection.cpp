#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct car {
	int t;
	char w;
	bool outCeck = false; // ������ �������� ���� Ȯ��
	bool standBy = false; // ������ ������ ���Կ��� üũ
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

	// �� ���� �Է¹޾Ƽ� ������ ���� �迭�� �Է�
	for (int i = 0; i < n; i++) {
		car c;
		cin >> c.t >> c.w;
		car_info.push_back(c);
		car_check.push(c);
	}

	// ������ ��Ȳ �ùķ��̼�
	while (!car_check.empty()) {

		// �����ο� ���� �������� Ȯ���ϱ�
		for (int i = 0; i < n; i++) {
			// �����ο� ���� ���� �ð��� �Ǿ��ٸ� �������� ���� ��ġ
			if (car_info[i].t == Time && car_info[i].standBy == false) {
				// ������ �������� �̵��ϱ�
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

		// ������ ������ ���� �� ������ �������� ������ ������
		if (fullCheck == false) {
			for (int i = 0; i < n; i++) {
				if (car_info[i].standBy == true &&
					car_info[i].w == 'A' && car_info[i].outCeck == false && A_check == false) {
					// D������ ���� ������ ������ ������
					if (section[3] == 0) {
						car_info[i].outTime = Time;
						car_info[i].outCeck = true;
						car_check.pop();
						A_check = true;
					}
				}
				else if (car_info[i].standBy == true && car_info[i].w == 'B' && car_info[i].outCeck == false && B_check == false) {
					// A������ ���� ������ ������ ������
					if (section[0] == 0) {
						car_info[i].outTime = Time;
						car_info[i].outCeck = true;
						car_check.pop();
						B_check = true;
					}
				}
				else if (car_info[i].standBy == true && car_info[i].w == 'C' && car_info[i].outCeck == false && C_check == false) {
					// B������ ���� ������ ������ ������
					if (section[1] == 0) {
						car_info[i].outTime = Time;
						car_info[i].outCeck = true;
						car_check.pop();
						C_check = true;
					}
				}
				else if (car_info[i].standBy == true && car_info[i].w == 'D' && car_info[i].outCeck == false && D_check == false) {
					// C������ ���� ������ ������ ������
					if (section[2] == 0) {
						car_info[i].outTime = Time;
						car_info[i].outCeck = true;
						car_check.pop();
						D_check = true;
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