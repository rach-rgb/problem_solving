#include <iostream>
using namespace std;

// 1, 3, 6, 10, 15, 21 ...

int main() {
	int A, B;
	cin >> A >> B;

	int val = 1, cur = 1, sum = 0;
	while (1) {
		if (cur < A) {

		}
		else if ((A <= cur) && (cur <= B)) {
			sum += val * (cur - A + 1);
			A = cur + 1;
		}
		else if (B < cur) {
			sum += val * (B - A + 1);
			break;
		}

		val++;
		cur += val;
	}

	cout << sum << endl;

	return 0;
}
