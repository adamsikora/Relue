#include <iostream>
#include <iomanip>

#include <fstream>

#include <sstream>

#include <set>
#include <map>
#include <vector>

#include <math.h>

#include "ttmath/ttmath.h"

#include "mtrand.h"

#include "primes.h"
#include "Clipboard.h"
#include "Palindrome.h"

#include "StopWatch.h"

const long long thousand = 1000;
const long long million = thousand * thousand;
const long long billion = thousand * million;

long long treshold = 1000000000000i64;

unsigned long long finalSum = 0;

std::vector<std::string> olds, news;

unsigned getOldNum(std::string str)
{
   unsigned num = 0, lastNum = 0, finalNum = 0;
   for (unsigned i = 0; i < str.size(); i++) {
      lastNum = num;
      switch (str[i]) {
      case 'I': num = 1; break;
      case 'V': num = 5; break;
      case 'X': num = 10; break;
      case 'L': num = 50; break;
      case 'C': num = 100; break;
      case 'D': num = 500; break;
      case 'M': num = 1000; break;
      default: std::cout << "zly string" << std::endl;
      }
      if (i > 0) {
         if (num <= lastNum) {
            finalNum += lastNum;
         }
         else {
            finalNum -= lastNum;
         }
      }
   }
   finalNum += num;
   return finalNum;
}

std::string getProperRoman(unsigned num)
{
   std::string str;
   unsigned digit = (num / 1000) % 10;
   switch (digit) {
   case 0: break;
   case 1: str += "M"; break;
   case 2: str += "MM"; break;
   case 3: str += "MMM"; break;
   case 4: str += "MMMM"; break;
   case 5: str += "MMMMM"; break;
   case 6: str += "MMMMMM"; break;
   case 7: str += "MMMMMMM"; break;
   case 8: str += "MMMMMMMM"; break;
   case 9: str += "MMMMMMMMM"; break;
   }
   digit = (num / 100) % 10;
   switch (digit) {
   case 0: break;
   case 1: str += "C"; break;
   case 2: str += "CC"; break;
   case 3: str += "CCC"; break;
   case 4: str += "CD"; break;
   case 5: str += "D"; break;
   case 6: str += "DC"; break;
   case 7: str += "DCC"; break;
   case 8: str += "DCCC"; break;
   case 9: str += "CM"; break;
   }
   digit = (num / 10) % 10;
   switch (digit) {
   case 0: break;
   case 1: str += "X"; break;
   case 2: str += "XX"; break;
   case 3: str += "XXX"; break;
   case 4: str += "XL"; break;
   case 5: str += "L"; break;
   case 6: str += "LX"; break;
   case 7: str += "LXX"; break;
   case 8: str += "LXXX"; break;
   case 9: str += "XC"; break;
   }
   digit = num % 10;
   switch (digit) {
   case 0: break;
   case 1: str += "I"; break;
   case 2: str += "II"; break;
   case 3: str += "III"; break;
   case 4: str += "IV"; break;
   case 5: str += "V"; break;
   case 6: str += "VI"; break;
   case 7: str += "VII"; break;
   case 8: str += "VIII"; break;
   case 9: str += "IX"; break;
   }

   return str;
}

int main()
{
   StopWatch sw;
   sw.start();

   std::ifstream inputFile;

   inputFile.open("roman.txt", std::ios::in);
   if (!inputFile.is_open())
      std::cout << "chyba pri otevirani inp";

   for (unsigned i = 0; i < 1000; i++) {
      char s[100] = "";
      inputFile.getline(s, 100);
      olds.emplace_back(s);
   }

   inputFile.close();

   //std::cout << olds[3] << getOldNum(olds[3]);

   for (unsigned i = 0; i < 1000; i++) {
      news.emplace_back(getProperRoman(getOldNum(olds[i])));
   }

   for (unsigned i = 0; i < 1000; i++) {
      if (news[i].size() > olds[i].size()){
         std::cout << "bad";
      }
      else {
         finalSum += olds[i].size() - news[i].size();
      }
   }

   for (unsigned i = 0; i < 1000; i++) {
      std::cout << std::setw(16) << olds[i] << std::setw(6) << getOldNum(olds[i]) << std::setw(12) << news[i];
      if (getOldNum(olds[i]) != getOldNum(news[i])) {
         std::cout << "zle";
         std::cin.ignore();
      }
      std::cout << std::endl;
   }

   sw.stop();
   std::cout << std::endl << "Completed in: " << sw.getTotalElapsed() << std::endl;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}