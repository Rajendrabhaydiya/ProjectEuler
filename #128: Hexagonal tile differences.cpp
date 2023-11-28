#include <iostream>
#include <vector>

// standard prime sieve, see my [toolbox](../toolbox/)
// odd prime numbers are marked as "true" in a bitvector
std::vector < bool > sieve;

// return true, if x is a prime number
bool isPrime(unsigned int x) {
  // handle even numbers
  if ((x & 1) == 0)
    return x == 2;

  // lookup for odd numbers
  return sieve[x >> 1];
}

// find all prime numbers from 2 to size
void fillSieve(unsigned int size) {
  // store only odd numbers
  const unsigned int half = size >> 1;

  // allocate memory
  sieve.resize(half, true);
  // 1 is not a prime number
  sieve[0] = false;

  // process all relevant prime factors
  for (unsigned int i = 1; 2 * i * i < half; i++)
    // do we have a prime factor ?
    if (sieve[i]) {
      // mark all its multiples as false
      unsigned int current = 3 * i + 1;
      while (current < half) {
        sieve[current] = false;
        current += 2 * i + 1;
      }
    }
}

int main() {

  unsigned int limit = 80000;
  fillSieve(91200000);

  // [nth number] => [tile]
  std::vector < unsigned long long > found = {
    1,
    2
  };

  // tiles 1 and 2 are the first two tiles because PD(1)=PD(2)=3
  unsigned int numFound = 2;
  // and there are no further tiles below 8 where PD(x)=3
  unsigned long long first = 8;

  // analyze rings until enough numbers are found
  for (unsigned long long ring = 2; numFound < limit; ring++) {
    // difference to previous ring (inside current ring)
    auto incrementFrom = (ring - 1) * 6;
    // difference to next ring (outside current ring)
    auto incrementTo = ring * 6;
    // difference to ring after the next ring
    auto incrementTo2 = (ring + 1) * 6 + incrementTo;

    // difference "incrementTo - 1" appears twice: around first and last tile
    if (!isPrime(incrementTo - 1)) {
      first += incrementTo;
      continue;
    }

    // check first number of a ring
    if (isPrime(incrementTo + 1) && isPrime(incrementTo2 - 1)) {
      numFound++;
      found.push_back(first);
    }

    // check last number of a ring
    if (isPrime(incrementFrom + incrementTo - 1) && isPrime(incrementTo2 - incrementTo - 1)) {
      numFound++;

      auto last = first + incrementTo - 1;
      found.push_back(last);
    }

    // next ring
    first += incrementTo;
  }

  // look up results
  unsigned int tests = 1;
  std::cin >> tests;
  while (tests--) {
    unsigned int index = 2000;
    std::cin >> index;
    std::cout << found[index - 1] << std::endl;
  }

  return 0;
}
