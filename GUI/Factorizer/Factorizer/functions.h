#pragma once

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <vector>
#include <algorithm>
#include "afxdialogex.h"

typedef unsigned long long ull;

std::vector<std::pair<ull, short>> factorize(ull t); // find the prime factors of t 
std::vector<ull> factors(ull t); // find all factors of t
ull gcd(ull a, ull b); // find the greatest common denominator of a and b
ull power(ull b, int e); // raise b to the power e
std::vector<ull> separate(ull t, int r); // separate the number t into digits (r as radix)
CString currentPath(); // get the directory of the .exe file

#endif  // _FUNCTIONS_H_