#include "pch.h"
#include "functions.h"

// 48719827982179811

const ull primes[100] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

std::vector<std::pair<ull, short>> factorize(ull t, bool external, std::wstring path) {
	std::vector<std::pair<ull, short>> res;
	std::wfstream fs;
	std::wstringstream buf1;
	std::wstring buf2;
	ull p = 97; // I don't understand why I need to initialize this
	short cnt = 0;
	
	if (external) {
		fs.open(path, std::ios::in);
		while (!fs.eof()) {
			buf1.clear();
			buf1.str(L"");
			fs >> buf2;
			buf1 << buf2;
			buf1 >> p;
			if (t % p == 0) {
				cnt = 0;
				while (t % p == 0) t /= p, ++cnt;
				res.push_back(std::pair<ull, short>(p, cnt));
			}
			if (t == 1) {
				fs.close();
				return res;
			}
		}
		fs.close();
	}
	else {
		for (int i = 0; i < 25; ++i) {
			p = primes[i];
			if (t % p == 0) {
				cnt = 0;
				while (t % p == 0) t /= p, ++cnt;
				res.push_back(std::pair<ull, short>(p, cnt));
			}
			if (t == 1) return res;
		}
	}
	ull f = 102, dest = t / p;
	while (f - 1 <= dest) {
		if (t % (f - 1) == 0) {
			cnt = 0;
			while (t % (f - 1) == 0) t /= (f - 1), ++cnt;
			res.push_back(std::pair<ull, short>(f - 1, cnt));
			dest = t / (f - 1);
		}
		if (t % (f + 1) == 0) {
			cnt = 0;
			while (t % (f + 1) == 0) t /= (f + 1), ++cnt;
			res.push_back(std::pair<ull, short>(f + 1, cnt));
			dest = t / (f + 1);
		}

		f += 6;
	}

	if (t != 1) res.push_back(std::pair<ull, short>(t, 1));
	return res;
}

std::vector<ull> factors(ull t) {
	std::vector<ull> res;

	for (ull i = 1; i <= sqrt(t); ++i) {
		if (t % i == 0) {
			res.push_back(i);
			if (i * i != t) res.push_back(t / i);
		}
	}
	std::sort(res.begin(), res.end());

	return res;
}

ull gcd(ull a, ull b) {
	ull smallNum = (a > b ? b : a), bigNum = (a > b ? a : b);
	if (bigNum % smallNum == 0) return smallNum;
	return gcd(smallNum, bigNum % smallNum);
}

ull power(ull b, int e) {
	ull ret = 1;
	for (int i = 0; i < e; ++i) ret *= b;
	return ret;
}

std::vector<ull> separate(ull t, int r) {
	std::vector<ull> ret;
	while (t != 0) {
		ret.push_back(t % r);
		t /= r;
	}
	return ret;
}

CString currentPath() {
	CString ret;
	TCHAR buf1[MAX_PATH + 1];

	GetModuleFileName(NULL, buf1, MAX_PATH);
	(_tcsrchr(buf1, _T('\\')))[1] = 0;
	ret = buf1;

	return ret;
}

ull toDec(std::vector<ull> n, int r) {
	ull res = 0;
	int e = 0;

	for (std::vector<ull>::reverse_iterator itr = n.rbegin(); itr != n.rend(); ++itr, ++e) res += *itr * power(r, e);

	return res;
}

std::vector<ull> fromDec(ull n, int r) {
	std::vector<ull> t, res;

	while (n != 0) {
		t.push_back(n % r);
		n /= r;
	}
	for (std::vector<ull>::reverse_iterator itr = t.rbegin(); itr != t.rend(); ++itr) res.push_back(*itr);

	return res;
}

std::vector<ull> convert(std::vector<ull> n, int from, int to) {
	return fromDec(toDec(n, from), to);
}
