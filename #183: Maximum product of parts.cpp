#include <iostream>
#include <vector>
#include <cmath>

int main() {
  // five dummy entries
  std::vector < long long > cache(5, 0);

  #ifndef ORIGINAL
  unsigned int tests = 1;
  std::cin >> tests;
  while (tests--)
    #endif 
    {
      unsigned int limit = 10000;
      std::cin >> limit;

      auto result = cache.back();
      for (unsigned int n = cache.size(); n <= limit; n++) {
        unsigned int k = round(n / 2.718281828);

        // terminating only if n/k has only prime factors 2 and 5
        while (k % 5 == 0)
          k /= 5;
        while (k % 2 == 0)
          k /= 2;

        if (n % k == 0)
          result -= n;
        else
          result += n;

        // cache intermediate results, too (needed for Hackerrank only)
        cache.push_back(result);
      }

      // display result
      std::cout << cache[limit] << std::endl;
    }

  return 0;
}
