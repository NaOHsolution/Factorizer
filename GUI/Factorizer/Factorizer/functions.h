#pragma once

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <fstream>
#include <sstream>
#include <locale>
#include <vector>
#include <algorithm>
#include "afxdialogex.h"

typedef unsigned long long ull;

std::vector<std::pair<ull, short>> factorize(ull t, bool external, std::wstring path); // find the prime factors of t 
std::vector<ull> factors(ull t); // find all factors of t
ull gcd(ull a, ull b); // find the greatest common denominator of a and b
ull power(ull b, int e); // raise b to the power e
std::vector<ull> separate(ull t, int r); // separate the number t into digits (r as radix)
CString currentPath(); // get the directory of the .exe file
ull toDec(std::vector<ull> n, int r); // convert a number n with radix r to a decimal
std::vector<ull> fromDec(ull n, int r); // convert a decimal n to a number with radix r
std::vector<ull> convert(std::vector<ull> n, int from, int to); // convert a number n from a radix to another radix

#endif  // _FUNCTIONS_H_