#include <iostream>
#include <vector>

//#define ORIGINAL

// store single digits with lowest digits first
// e.g. 1024 is stored as { 4,2,0,1 }
struct BillionNum : public std::vector<unsigned int>
{
  // must store exactly 9 digits per cell
  static const unsigned int MaxDigit = 1000000000;

  // fill one cell
  BillionNum(unsigned int x)
  {
    push_back(x);
  }

  // add a big number
  void operator+=(const BillionNum& other)
  {
    // this code is a 95% copy of my BigNum class

    // add in-place, make sure it's big enough
    if (size() < other.size())
      resize(other.size(), 0);

    unsigned int carry = 0;
    for (size_t i = 0; i < size(); i++)
    {
      // perform standard addition algorithm
      carry += operator[](i);
      if (i < other.size())
        carry += other[i];
      else
        if (carry == 0)
          return;

      if (carry < MaxDigit)
      {
        // no overflow
        operator[](i) = carry;
        carry         = 0;
      }
      else
      {
        // yes, we have an overflow
        operator[](i) = carry - MaxDigit;
        carry         = 1;
      }
    }

    if (carry > 0)
      push_back(carry);
  }
};

// return true if x is pandigital (1..digits)
bool isPandigital(unsigned int x, unsigned int digits = 9)
{
  unsigned int mask = 0; // zero is not allowed, only 1 to 9
  for (unsigned int i = 0; i < digits; i++)
  {
    // get next digit
    auto current = x % 10;
    if (current == 0 || current > digits)
      return false;

    auto bit = 1 << current;
    // already seen ?
    if ((mask & bit) != 0)
      return false;

    // mark that digit as "used"
    mask |= bit;
    x    /= 10;
  }

  return true;
}

int main()
{
  unsigned int first  = 1; // F_1 = 1
  unsigned int second = 1; // F_2 = 1
  unsigned int digits = 9; // 9-pandigital (1..9)

#ifndef ORIGINAL
  std::cin >> first >> second >> digits;
#endif

  if (first == 1 && digits == 1)
  {
    std::cout << "1" << std::endl;
    return 0;
  }

  unsigned long long Modulo = 1; // 10^digits
  for (unsigned i = 1; i <= digits; i++)
    Modulo *= 10;

  // convert to a simplified BigNum
  BillionNum a = first;
  BillionNum b = second;

  for (unsigned int i = 2; i <= 2000000; i++)
  {
    // analyze the lowest digits
    auto lowest = b.front() % Modulo;
    bool isPanLow = isPandigital(lowest, digits);

    // look at the highest digits
    if (isPanLow)
    {
      unsigned long long highest = b.back();
      // maybe too few digits: use next cells, too
      if (highest < Modulo && b.size() > 1)
        highest = highest * BillionNum::MaxDigit + b[b.size() - 2];

      // too many digits ? shrink until we have the right number of digits
      while (highest >= Modulo)
        highest /= 10;

      // check if pandigital
      if (isPandigital(highest, digits))
      {
        // yes, pandigital on both ends !
        std::cout << i << std::endl;
        return 0;
      }
    }

    // next Fibonacci number
    a += b;
    std::swap(a, b);

    // don't compute all digits:
    // - look at the lowest digits
    // - and look at the highest (incl. some of its neighbors because of carry)
    // => remove those in the middle
    // => my "magic numbers" 10 and 2 were chosen pretty much at random ...
    if (a.size() > 10)
    {
      a.erase(a.begin() + 2);
      b.erase(b.begin() + 2);
    }
  }

  // failed
  std::cout << "no solution" << std::endl;
  return 0;
}
