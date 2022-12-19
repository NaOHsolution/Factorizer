#include <conio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

ull number;
vector<pair<ull, short>> result;

int main() {
	ull t;
	short cnt;
	string buf;
	stringstream m;

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

		t = number;
		result.clear();
		if (number != 1) {
			for (ull i = 2; i <= t; ++i) {
				if (t % i == 0) {
					cnt = 0;
					while (t % i == 0) t /= i, ++cnt;
					result.push_back(pair<ull, short>(i, cnt));
				}
			}

			cout << endl << number << " = ";
			for (vector<pair<ull, short>>::iterator itr = result.begin(); itr != result.end(); ++itr) {
				if (itr->second == 1) cout << itr->first;
				else cout << itr->first << " ^ " << itr->second;
				if (itr + 1 != result.end()) cout << " x ";
			}
			cout << endl;
			if (result.size() == 1) cout << number << " is prime.";
			else cout << number << " is composite.";
		}
		else cout << endl << "1 is neither prime nor composite.";
		cout << endl << endl;
	}
	
	return 0;
}