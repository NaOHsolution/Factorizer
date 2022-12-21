#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define DIRECT_SOURCE false
#define EXTERNAL_SOURCE true
#define PRIME_FACTORS false
#define ALL_FACTORS true

#define DEFAULT_ERROR 0
#define NO_SOURCE 1
#define NO_TYPE 2
#define NO_INPUT 3
#define OUT_OF_RANGE 4
#define NOT_A_NUMBER 5
#define INPUT_ERROR 6
#define OUTPUT_ERROR 7

typedef unsigned long long ull;

ull primes[100] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

struct input {
	bool source;
	ull number;
	string inputDirectory;
	bool type;
	bool output;
	string outputDirectory;

	input() : source(DIRECT_SOURCE), type(PRIME_FACTORS), output(false), number(2ull) {};
};

class emptyInput {};
class syntaxError : public exception {
	int type;

	virtual const char* what() const throw() {
		if (type == NO_SOURCE) return "Syntax error: Cannot find the -d/-e parameter.";
		else if (type == NO_TYPE) return "Syntax error: Cannot find the -p/-f parameter.";
		else if (type == NO_INPUT) return "Syntax error: Cannot find the number or input directory.";
		else return "Syntax error. Please check your input.";
	}

public: 
	syntaxError(int t) : type(t) {};
};
class numberError : public exception {
	int type;

	virtual const char* what() const throw() {
		if (type == NOT_A_NUMBER) return "Number error: The input is not a number.";
		else if (type == OUT_OF_RANGE) return "Number error: The number is out of range.";
		else return "Number error. Please check your input.";
	}

public: 
	numberError(int t) : type(t) {};
};
class exitProgram {};
class help {};
class fileError : public exception {
	int type;
	
	virtual const char* what() const throw() {
		if (type == INPUT_ERROR) return "File error: Cannot open input directory.";
		else if (type == OUTPUT_ERROR) return "File error: Cannot open output directory.";
		else return "File error. Please check your input.";
	}

public:
	fileError(int t) : type(t) {};
};

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

	for (ull i = 1; i <= sqrt(t); ++i) {
		if (t % i == 0) {
			res.push_back(i);
			if (i * i != t) res.push_back(t / i);
		}
	}
	sort(res.begin(), res.end());

	return res;
}

void display() {
	cout << "Factorizer 1.4.1" << endl << "By NaOHsolution" << endl << endl << "Syntax:" << endl << "-d/-e source -p/-f [output]" << endl << endl;
	cout << "Parameters: " << endl;
	cout << "-d/-e \t Where the number(s) comes from. -d stands\n\t for direct input, -e stands for external\n\t source (file)." << endl;
	cout << "source \t What the number(s) is. If the previous\n\t parameter is -d, just enter the number; if\n\t it is -e, enter the directory of the input file." << endl;
	cout << "-p/-f \t What to do with the number(s). -p stands\n\t for factorizing (prime factors), -f stands\n\t for factor finding (all factors)." << endl;
	cout << "[output] Where to put the results. Leave blank to\n\t show them in the console, or enter a output\n\t directory." << endl << endl;
	cout << "Enter \"exit\" to quit the program, or \"help\" to\ndisplay this screen." << endl << endl;
	cout << "\"-d 12345 -p C:\\log.txt \" means factorizing the number\n12345 into its prime factors before putting the results\ninto a file with directory \"C:\\log.txt\"." << endl << endl;
	cout << "Please make sure the number(s) is between 1 and\n18,446,744,073,709,551,615. " << endl << endl;
}

input handleInput(string t) {
	if (t.empty()) throw emptyInput();
	while (t[0] == ' ' && !t.empty()) t.erase(0, 1);
	while (t[t.size() - 1] == ' ' && !t.empty()) t.erase(t.size() - 1, 1);
	if (t.empty()) throw emptyInput();
	if (t == "exit") throw exitProgram();
	if (t == "help") throw help();
	if (t.length() < 6) throw syntaxError(DEFAULT_ERROR);

	t += " ";

	input ret;
	bool hasType = false;
	int index1, index2;
	string buf;
	stringstream s;
	fstream fs;
	ull temp;

	if (t[0] != '-') throw syntaxError(NO_SOURCE);
	switch (t[1]) {
	case 'd':
		ret.source = DIRECT_SOURCE;
		break;
	case 'e':
		ret.source = EXTERNAL_SOURCE;
		break;
	default:
		throw syntaxError(NO_SOURCE);
	}
	for (int i = 2; i < t.size() - 2; ++i) {
		if (t[i] == '-' && t[i + 2] == ' ' && t[i - 1] == ' ') {
			switch (t[i + 1]) {
			case 'p':
				ret.type = PRIME_FACTORS;
				hasType = true;
				index1 = i - 1, index2 = i + 2;
				break;
			case 'f':
				ret.type = ALL_FACTORS;
				hasType = true;
				index1 = i - 1, index2 = i + 2;
				break;
			default:
				continue;
			}
		}
	}
	if (!hasType) throw syntaxError(NO_TYPE);
	if (2 >= index1 - 2) throw syntaxError(NO_INPUT);
	buf = t.substr(2, index1 - 2);
	while (buf[0] == ' ' && buf.size() > 1) buf.erase(0, 1);
	while (buf[buf.size() - 1] == ' ' && buf.size() > 1) buf.erase(buf.size() - 1, 1);
	if (buf == " ") throw syntaxError(NO_INPUT);
	
	if (ret.source == DIRECT_SOURCE) {
		if (buf == "0") throw numberError(OUT_OF_RANGE);
		for (int i = 0; i < buf.size(); ++i) {
			if (buf[i] < '0' || buf[i] > '9') throw numberError(NOT_A_NUMBER);
		}
		s << buf;
		s >> ret.number;
		if (s.fail()) throw numberError(OUT_OF_RANGE);
	}
	else ret.inputDirectory = buf;
	buf = t.substr(index2, t.size() - index2);
	while (buf[0] == ' ' && buf.size() > 1) buf.erase(0, 1);
	while (buf[buf.size() - 1] == ' ' && buf.size() > 1) buf.erase(buf.size() - 1, 1);
	if (buf == " " || buf.empty()) ret.output = false;
	else ret.output = true, ret.outputDirectory = buf;

	if (ret.source == EXTERNAL_SOURCE) {
		fs.open(ret.inputDirectory, ios::in);
		if (!fs.is_open()) throw fileError(INPUT_ERROR);
		fs.close();
	}
	if (ret.output) {
		fs.open(ret.outputDirectory, ios::out);
		if (!fs.is_open()) throw fileError(INPUT_ERROR);
		fs.close();
	}

	return ret;
}

int main() {
	string buf;
	input op;
	int progress;
	vector<pair<ull, short>> resultp;
	vector<ull> resultf;
	vector<ull> numbers;
	fstream fs;

	display();
	
	while (true) {
		cout << "> ";
		getline(cin, buf, '\n');

		try {
			op = handleInput(buf);
		}
		catch (emptyInput) {
			continue;
		}
		catch (exitProgram) {
			return 0;
		}
		catch (help) {
			cout << endl;
			display();
			continue;
		}
		catch (exception& e1) {
			cout << endl << e1.what() << endl << endl;
			continue;
		}

		numbers.clear();
		resultf.clear();
		resultp.clear();
		cout << endl;
		if (op.source == DIRECT_SOURCE) {
			numbers.push_back(op.number);
		}
		else if (op.source == EXTERNAL_SOURCE) {
			fs.open(op.inputDirectory, ios::in);
			while (!fs.eof()) {
				ull t = 0;
				string buf;
				fs >> t;
				if (fs.fail()) {
					fs.clear();
					fs >> buf;
				}
				else if (t != 0) numbers.push_back(t);
			}
			if (numbers.empty()) {
				cout << "There are no numbers in the file." << endl << endl;
				continue;
			}
			fs.close();
			cout << "Read successfully from " << op.inputDirectory << endl << endl;
		}

		progress = 1;
		if (op.type == PRIME_FACTORS) {
			if (op.output == false) {
				for (vector<ull>::iterator itr = numbers.begin(); itr != numbers.end(); ++itr, ++progress) {
					if (*itr != 1) {
						resultp = factorize(*itr);

						cout << *itr << " = ";
						for (vector<pair<ull, short>>::iterator itr2 = resultp.begin(); itr2 != resultp.end(); ++itr2) {
							cout << itr2->first;
							if (itr2->second != 1) cout << " ^ " << itr2->second;
							if (itr2 + 1 != resultp.end()) cout << " x ";
						}
						cout << endl;
						if (resultp.size() == 1 && resultp.begin()->second == 1) cout << *itr << " is prime. (" << progress << "/" << numbers.size() << ")";
						else cout << *itr << " is composite. (" << progress << "/" << numbers.size() << ")";
					}
					else cout << "1 is neither prime nor composite. (" << progress << "/" << numbers.size() << ")";
					cout << endl << endl;
				}
			}
			else if (op.output == true) {
				fs.open(op.outputDirectory, ios::out);
				for (vector<ull>::iterator itr = numbers.begin(); itr != numbers.end(); ++itr, ++progress) {
					if (*itr != 1) {
						resultp = factorize(*itr);

						fs << *itr << " = ";
						for (vector<pair<ull, short>>::iterator itr2 = resultp.begin(); itr2 != resultp.end(); ++itr2) {
							fs << itr2->first;
							if (itr2->second != 1) fs << " ^ " << itr2->second;
							if (itr2 + 1 != resultp.end()) fs << " x ";
						}
						fs << endl;
						if (resultp.size() == 1 && resultp.begin()->second == 1) fs << *itr << " is prime.";
						else fs << *itr << " is composite.";
					}
					else fs << "1 is neither prime nor composite.";
					fs << endl << endl;

					cout << "Completed operation on " << *itr << " (" << progress << "/" << numbers.size() << ")." << endl;
				}
				cout << endl << "File ready at " << op.outputDirectory << "." << endl << endl;
				fs.close();
			}
		}
		else if (op.type == ALL_FACTORS) {
			if (op.output == false) {
				for (vector<ull>::iterator itr = numbers.begin(); itr != numbers.end(); ++itr, ++progress) {
					resultf = factors(*itr);

					cout << "Factors of " << *itr << ": " << endl;
					for (vector<ull>::iterator itr2 = resultf.begin(); itr2 != resultf.end(); ++itr2) {
						cout << *itr2;
						if (itr2 + 1 != resultf.end()) cout << ", ";
					}
					cout << endl;
					if (*itr == 1) cout << "1 is neither prime nor composite. (" << progress << "/" << numbers.size() << ")";
					else if (resultf.size() == 2) cout << *itr << " is prime. (" << progress << "/" << numbers.size() << ")";
					else cout << *itr << " is composite. (" << progress << "/" << numbers.size() << ")";
					cout << endl << endl;
				}
			}
			else if (op.output == true) {
				fs.open(op.outputDirectory, ios::out);
				for (vector<ull>::iterator itr = numbers.begin(); itr != numbers.end(); ++itr, ++progress) {
					resultf = factors(*itr);

					fs << "Factors of " << *itr << ": " << endl;
					for (vector<ull>::iterator itr2 = resultf.begin(); itr2 != resultf.end(); ++itr2) {
						fs << *itr2;
						if (itr2 + 1 != resultf.end()) fs << ", ";
					}
					fs << endl;
					if (*itr == 1) fs << "1 is neither prime nor composite.";
					else if (resultf.size() == 2) fs << *itr << " is prime.";
					else fs << *itr << " is composite.";
					fs << endl << endl;

					cout << "Completed operation on " << *itr << " (" << progress << "/" << numbers.size() << ")." << endl;
				}
				cout << endl << "File ready at " << op.outputDirectory << "." << endl << endl;
				fs.close();
			}
		}
	}
	
	return 0;
}