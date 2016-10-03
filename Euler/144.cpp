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

class Coord
{
public:
   Coord(double x, double y) : x(x), y(y) {}
   double x, y;
};

class Vector
{
public:
   Vector(double x, double y) : x(x), y(y) {}
   double x, y;
   void normalize() { double abs = sqrt(x*x + y*y); x /= abs; y /= abs; }
};

void reflect(Vector& vect, Coord pos)
{
   Vector plane(1.0, -4 * pos.x / pos.y);
   plane.normalize();
   Vector old = vect;
   double scal = old.x*plane.x + old.y*plane.y;
   plane.x *= 2*scal;
   plane.y *= 2*scal;
   vect.x = plane.x - old.x;
   vect.y = plane.y - old.y;
   vect.normalize();
}

void travel(Vector vect, Coord& pos)
{
   double h = 100.0;

   for (int i = 0; i < 30; i++) {
      int j = 1;
      while (j < 11) {
         if (4 * (pos.x + vect.x*j*h) * (pos.x + vect.x*j*h) + (pos.y + vect.y*j*h) * (pos.y + vect.y*j*h) > 100) {
            pos.x += (j - 1)*h*vect.x;
            pos.y += (j - 1)*h*vect.y;
            break;
         }
         j++;
      }
      h /= 10.0;
   }
}

int main()
{
   StopWatch sw;
   sw.start();

   Coord pos(1.4, -9.6);
   Vector vect(1.4, -19.7);
   vect.normalize();
   long long bounces = 0;
   while (!(abs(pos.x) < 0.01 && pos.y > 0.0)) {
      reflect(vect, pos);
      travel(vect, pos);
      bounces++;
      if (bounces % 1000000 == 0) std::cout << bounces << std::endl;
   }

   finalSum = bounces;

   std::stringstream answer;
   answer << finalSum;
   std::cout << "Answer is: " << answer.str() << std::endl;
   ClipboardIt(answer.str());
   std::cin.ignore();
   return EXIT_SUCCESS;
}