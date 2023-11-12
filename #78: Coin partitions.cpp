#include <iostream>
#include <vector>

int main()
{
  // store result (modulo 10^6 or 10^9 + 7)
  std::vector<unsigned long long> partitions;
  // degenerated case, there's one partition for an empty pile
  partitions.push_back(1);

//#define ORIGINAL
#ifdef ORIGINAL
  const long long modulo =    1000000; // 10^6
#else
  const long long modulo = 1000000007; // 10^9 + 7

  unsigned int tests = 1;
  std::cin >> tests;
  while (tests--)
#endif

  {
    unsigned int limit = 100000; // the solution is < 100000, program ab
#ifndef ORIGINAL
    std::cin >> limit;
#endif

    // fill cache
    for (unsigned int n = partitions.size(); n <= limit; n++)
    {
      // sum according to Euler's formula
      long long sum = 0;

      // all pentagonal numbers where pentagonal(i) <= n
      for (unsigned int i = 0; ; i++) // abort inside loop
      {
        // generate alternating numbers +1,-1,+2,-2,+3,-3,...
        int alternate = 1 + (i / 2); // generate the digit 1,1,2,2,3,3,...
        if (i % 2 == 1)
          alternate = -alternate;    // flip the sign for every second number

        // pentagonal index, "how far we go back" in partitions[]
        unsigned int offset = alternate * (3 * alternate - 1) / 2;
        // can't go back that far ? (array index would be negative)
        if (n < offset)
          break;

        // add two terms, subtract two terms, add two terms, subtract two terms, ...
        if (i % 4 < 2)
          sum += partitions[n - offset]; // i % 4 = { 0, 1 }
        else
          sum -= partitions[n - offset]; // i % 4 = { 2, 3 }

        // only the last digits are relevant
        sum %= modulo;

      }

      // note: sum can be temporarily negative
      if (sum < 0)
        sum += modulo;

#ifdef ORIGINAL
      // "divisible by one million" => sum % 1000000 == 0
      // last 6 digits (modulo was 10^6) are zero
      if (sum == 0)
        break;
#endif

      partitions.push_back(sum);
    }

    // print (cached) result
#ifdef ORIGINAL
    std::cout << partitions.size() << std::endl;
#else
    std::cout << partitions[limit] << std::endl;
#endif
  }

  return 0;
}
