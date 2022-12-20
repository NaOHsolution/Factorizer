#include <conio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

ull primes[100] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

vector<pair<ull, short>> factorize(ull t) {
	vector<pair<ull, short>> res;
	short cnt = 0;
	
	for (int i = 0; i < 25; ++i) {
		ull p = primes[i];
		if (t % p == 0) {
			cnt = 0;
			while (t % p == 0) t /= p, ++cnt;
			res.push_back(pair<ull, short>(p, cnt));
		}
		if (t == 1) return res;
	}
	ull f = 102, dest = t / 97;
	while (f - 1 <= dest) {
		if (t % (f - 1) == 0) {
			cnt = 0;
			while (t % (f - 1) == 0) t /= (f - 1), ++cnt;
			res.push_back(pair<ull, short>(f - 1, cnt));
			dest = t / (f - 1);
		}
		if (t % (f + 1) == 0) {
			cnt = 0;
			while (t % (f + 1) == 0) t /= (f + 1), ++cnt;
			res.push_back(pair<ull, short>(f + 1, cnt));
			dest = t / (f + 1);
		}

		f += 6;
	}

	if (t != 1) res.push_back(pair<ull, short>(t, 1));
	return res;
}

vector<ull> factors(ull t) {
	vector<ull> res;
	res.push_back(1ull);

	for (ull i = 2; i <= t; ++i) {
		if (t % i == 0) res.push_back(i);
	}

	return res;
}

int main() {
	ull number;
	char op;
	string buf;
	stringstream m;
	
	while (true) {
		m.clear();
		m.str("");
		cout << "Enter the number (0 to exit):" << endl << "> ";
		getline(cin, buf, '\n');
		m << buf;
		m >> number;
		if (m.fail()) {
			cout << endl << "Invalid input." << endl << endl;
			continue;
		}
		if (number == 0) break;
		m.clear();
		m.str("");
		cout << endl << "Select an operation: " << endl << "[p] Factorize the number into its prime factors" << endl << "[f] Find out all of the number's factors" << endl << "> ";
		getline(cin, buf, '\n');
		m << buf;
		m >> op;
		if (m.fail() || (op != 'p' && op != 'f')) {
			cout << endl << "Invalid input." << endl << endl;
			continue;
		}

		switch (op) {
		case 'p':
			if (number != 1) {
				vector<pair<ull, short>> result = factorize(number);

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

			break;
		case 'f':
			vector<ull> result = factors(number);

			cout << endl << "Factors: ";
			for (vector<ull>::iterator itr = result.begin(); itr != result.end(); ++itr) {
				cout << *itr;
				if (itr + 1 != result.end()) cout << ", ";
			}
			cout << endl;
			if (result.size() == 1) cout << "1 is neither prime nor composite.";
			else if (result.size() == 2) cout << number << " is prime.";
			else cout << number << " is composite.";

			break;
		}
		
		cout << endl << endl;
	}
	
	return 0;
}