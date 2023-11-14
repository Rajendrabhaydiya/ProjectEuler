#include <iostream>

// return true, if x will arrive at 89
bool becomes89(unsigned int x)
{
  do
  {
    // sum of squares of all digits
    unsigned int squareDigitSum = 0;
    auto reduce = x;
    while (reduce > 0)
    {
      auto digit = reduce % 10;
      reduce /= 10;
      squareDigitSum += digit * digit;
    }

    // terminated ?
    if (squareDigitSum == 89)
      return true;
    if (squareDigitSum ==  1)
      return false;

    // not done yet ... next iteration
    x = squareDigitSum;
  } while (true);
}

int main()
{
  unsigned int digits = 7; // 10^7 = 10,000,000
  std::cin >> digits;

  // Hackerrank's result will become quite big, they only want the final number modulo 1000000007
  // (doesn't affect the original problem)
  const unsigned int Modulo = 1000000007;

  // count how many numbers with the same digit sum exist
  // inspired by https://rosettacode.org/wiki/Iterated_digits_squaring

  // initialized with zeros
  unsigned int sums[200*9*9 + 1] = { 0 };

  // single-digit numbers
  for (unsigned int first = 0; first <= 9; first++)
    sums[first * first]++;
  // alternative approach: set sums[0] = 1; and start the new loop with length = 1

  // start with one digit and iteratively add digits
  for (unsigned int length = 2; length <= digits; length++)
    // go through all potential sums (including the most recently added digit)
    for (unsigned int sum = length*9*9; sum > 0; sum--)
      // what sum is it without that most recently added digit ?
      for (unsigned int high = 1; high <= 9; high++)
      {
        // square of the just added digit
        auto square = high * high;
        // this digit can't be part of the current digit sum because it's too big
        if (square > sum)
          break;

        // add count of all numbers without the new digit
        sums[sum] += sums[sum - square];
        // avoid overflows (Hackerrank only)
        sums[sum] %= Modulo;
      }

  // now we know how many numbers sums[x] exist with digit sum x
  // let's check which digit sums will be converted to 89
  unsigned int count89 = 0;
  // check all sums
  for (unsigned int i = 1; i <= digits*9*9; i++)
    if (becomes89(i))
    {
      count89 += sums[i]; // yes, all these numbers turn to 89
      count89 %= Modulo;  // Hackerrank only
    }

  std::cout << count89 << std::endl;
  return 0;
}
