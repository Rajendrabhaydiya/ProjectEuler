#include <iostream>

int main()
{
  unsigned int tests;
  std::cin >> tests;
  while (tests--)
  {
    unsigned long long x;
    std::cin >> x;

    unsigned long long sum        = 0; // 1   + 2   + ...
    unsigned long long sumSquared = 0; // 1^2 + 2^2 + ...

    for (unsigned long long i = 1; i <= x; i++)
    {
      sum        += i;
      sumSquared += i*i;
    }
    // chances are that your compiler (partially) unrolls this simple loop

    // actually we don't need a loop for the sum (and the sum of squares)
    // => see "Alternative" section above

    // we had (1+2+...) instead of (1+2+...)^2
    unsigned long long squaredSum = sum * sum;
    std::cout << (squaredSum - sumSquared) << std::endl;
  }
  return 0;
}
