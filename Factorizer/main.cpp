#include <conio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

vector<pair<ull, short>> factorize(ull t) {
	vector<pair<ull, short>> res;
	short cnt = 0;
	
	if (t % 2 == 0) { // 2
		cnt = 0;
		while (t % 2 == 0) t /= 2, ++cnt;
		res.push_back(pair<ull, short>(2, cnt));
	}
	if (t == 1) return res;
	else if (t % 3 == 0) { // 3
		cnt = 0;
		while (t % 3 == 0) t /= 3, ++cnt;
		res.push_back(pair<ull, short>(3, cnt));
	}
	if (t == 1) return res;
	else { // the rest
		ull f = 6;
		while (f - 1 <= t) {
			if (t % (f - 1) == 0) {
				cnt = 0;
				while (t % (f - 1) == 0) t /= (f - 1), ++cnt;
				res.push_back(pair<ull, short>(f - 1, cnt));
			}
			if (t % (f + 1) == 0) {
				cnt = 0;
				while (t % (f + 1) == 0) t /= (f + 1), ++cnt;
				res.push_back(pair<ull, short>(f + 1, cnt));
			}

			f += 6;
		}
	}

	return res;
}

int main() {
	ull number;
	string buf;
	stringstream m;
	vector<pair<ull, short>> result;

	while (true) {
		m.clear();
		m.str("");

		cout << "Enter the number to be factorized (0 to exit): ";
		getline(cin, buf, '\n');
		m << buf;
		m >> number;
		if (m.fail()) {
			cout << endl << "Invalid input." << endl << endl;
			continue;
		}

		if (number == 0) break;
		if (number != 1) {
			result = factorize(number);

			cout << endl << number << " = ";
			for (vector<pair<ull, short>>::iterator itr = result.begin(); itr != result.end(); ++itr) {
				if (itr->second == 1) cout << itr->first;
				else cout << itr->first << " ^ " << itr->second;
				if (itr + 1 != result.end()) cout << " x ";
			}
			cout << endl;
			if (result.size() == 1 && result.begin()->second == 1) cout << number << " is prime.";
			else cout << number << " is composite.";
		}
		else cout << endl << "1 is neither prime nor composite.";
		cout << endl << endl;
	}
	
	return 0;
}