#include <conio.h>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

ull number;
vector<pair<ull, short>> result;

int main() {
	cout << "Enter the number to be factorized: ";
	cin >> number;

	ull t = number;
	short cnt;
	for (ull i = 2; i <= t; ++i) {
		if (t % i == 0) {
			cnt = 0;
			while (t % i == 0) t /= i, ++cnt;
			result.push_back(pair<ull, short>(i, cnt));
		}
	}

	if (number != 1) cout << endl << number << " = ";
	for (vector<pair<ull, short>>::iterator itr = result.begin(); itr != result.end(); ++itr) {
		if (itr->second == 1) cout << itr->first;
		else cout << itr->first << " ^ " << itr->second;
		if (itr + 1 != result.end()) cout << " x ";
	}
	if (number == 1) cout << endl << "1 is neither prime nor composite.";
	else if (result.size() == 1) cout << endl << number << " is prime.";
	else cout << endl << number << " is composite.";

	cout << endl << endl << "Press any key to exit...";
	while (!_kbhit());
	return 0;
}