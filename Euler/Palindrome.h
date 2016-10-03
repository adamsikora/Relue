/*
Adam Sikora
16.2.2014

*/

#ifndef PALINDROME_H
#define PALINDROME_H

inline bool isPalindrome(int number, int digits = -1) {
   std::vector<int> digs;
   int transfer = number;
   while (transfer) {
      digs.push_back(transfer % 10);
      transfer /= 10;
   }

   for (int ipi = 0; ipi < digits; ipi++)
      if (digs[ipi] != digs[digits - 1 - ipi])
         return false;
   return true;
}

long long gcd(long long a, long long b)
{
	if (a == b || b == 0) {
		return a;
	}
	else if (a > b) {
		return gcd(b, a);
	}
	else {
		return gcd(a, b % a);
	}
}

long long factorial(long long f) {
	long long toret = 1;
	for (long long i = 2; i <= f; ++i) {
		toret *= i;
	}
	return toret;
}

long long combinations(long long all, long long taken) {
	if (taken > all) {
		return 0;
	}
	else {
		return factorial(all) / factorial(taken) / factorial(all - taken);
	}
}

#endif //PALINDROME_H