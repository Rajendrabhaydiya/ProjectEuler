#include <iostream>
#include <vector>

int main()
{
  // compute the first 10001 primes
  std::vector<unsigned int> primes;
  primes.reserve(10001);
  primes.push_back(2);
  for (unsigned int x = 3; primes.size() <= 10000; x += 2)
  {
    bool isPrime = true;
    for (auto p : primes)
    {
      // found a divisor ? => abort
      if (x % p == 0)
      {
        isPrime = false;
        break;
      }

      // no larger prime factors possible ?
      if (p*p > x)
        break;
    }

    // yes, we have a new prime
    if (isPrime)
      primes.push_back(x);
  }

  // processing all test cases is now just a plain lookup
  unsigned int tests;
  std::cin >> tests;
  while (tests--)
  {
      unsigned int x;
      std::cin >> x;
      // just look up the x-th prime
      // with a little twist: vector's index is zero-based, therefore "off by one"
      x--;

      if (x < primes.size())
        std::cout << primes[x] << std::endl;
      else
        std::cout << "ERROR" << std::endl;
  }
  return 0;
}
