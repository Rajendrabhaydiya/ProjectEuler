#include <iostream>

// return true if x is a bouncy number
bool isBouncy(unsigned long long x)
{
  // figure out whether x is monotonic ascending or descending
  // it's bouncy if neither ascending nor descending
  bool ascending  = true;
  bool descending = true;

  // initial digit (the right-most digit)
  auto previous = x % 10;
  x /= 10;

  // still digits left ?
  while (x > 0)
  {
    // current digit
    auto current = x % 10;

    // compare two digits
    descending &= previous >= current;
    ascending  &= previous <= current;

    // bouncy ?
    if (!ascending && !descending)
      return true;

    // keep going ...
    x /= 10;
    previous = current;
  }

  // not bouncy (either ascending, descending or all digits are equal)
  return false;
}


int main()
{
  unsigned int tests = 1;
  std::cin >> tests;

  while (tests--)
  {
    // original problem: 99%
    unsigned long long p =  99;
    unsigned long long q = 100;
    std::cin >> p >> q;

    // brute-force ...
    unsigned long long current   = 100; // no bouncy numbers below 100
    unsigned long long numBouncy =   0;
    do
    {
      // check next number if bouncy
      current++;
      if (isBouncy(current))
        numBouncy++;
    } while (numBouncy * q < current * p); // same as numBouncy/current == p/q (=99%)

    // print result
    std::cout << current << std::endl;
  }

  return 0;
}
