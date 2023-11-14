#include <iostream>
#include <vector>

// maximum denominator
unsigned int maxD = 12000;

// algorithm I:
// count mediants between 1/fromD and 1/toD using recursion
unsigned int recursion(unsigned int fromD, unsigned int toD)
{
  auto mediantD = fromD + toD;
  // denominator too big ?
  if (mediantD > maxD)
    return 0;

  // recursion
  return 1 + recursion(fromD, mediantD) + recursion(mediantD, toD);
}

// algorithm II:
// iteratively enumerate all denominators
unsigned int iteration(unsigned int fromD, unsigned int toD)
{
  // find denominator of closest mediant of "from"
  // initial mediant
  auto d = fromD + toD;
  // is there a mediant closer to fromD ?
  while (d + fromD <= maxD)
    d += fromD;

  // if prevD and d are denominators of adjacent fractions prevN/prevD and n/d
  // then the next denominator is nextD = maxD - (maxD + prevD) % d
  auto prevD = fromD;

  unsigned int count = 0;
  // until we reach the final denominator
  while (d != toD)
  {
    // find next denominator
    auto nextD = maxD - (maxD + prevD) % d;

    // shift denominators, the current becomes the previous
    prevD = d;
    d = nextD;

    count++;
  }

  return count;
}

// algorithm III:
// return numbers of irreducible fractions a/b < n/d where b is less than maxD
unsigned int rank(unsigned int n, unsigned int d)
{
  // algorithm from "Computer Order Statistics in the Farey Sequence" by C. & M. Patrascu
  // http://people.csail.mit.edu/mip/papers/farey/talk.pdf
  std::vector<unsigned int> data(maxD + 1);
  for (unsigned int i = 0; i < data.size(); i++)
    data[i] = i * n / d; // n is always 1 but I wanted to keep the original algorithm

  // remove all multiples of 2*i, 3*i, 4*i, ...
  // similar to a prime sieve
  for (unsigned int i = 1; i < data.size(); i++)
    for (unsigned int j = 2*i; j < data.size(); j += i)
      data[j] -= data[i];

  // return sum of all elements
  unsigned int sum = 0;
  for (auto x : data)
    sum += x;
  return sum;
}

int main()
{
  // denominators are abbreviated D
  unsigned int toD = 2; // which means 1/2 (original problem)

//#define ORIGINAL
#ifndef ORIGINAL
  std::cin >> toD >> maxD;
#endif

  // the algorithm search from 1/fromD to 1/toD
  auto fromD = toD + 1;

  // algorithm 1
  //std::cout << recursion(fromD, toD) << std::endl;
  // algorithm 2
  //std::cout << iteration(fromD, toD) << std::endl;
  // algorithm 3
  auto result = rank(1, toD) - rank(1, fromD) - 1;
  std::cout << result << std::endl;

  return 0;
}
