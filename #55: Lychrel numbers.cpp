#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

//#define ORIGINAL

// a sequence of digits, lowest digits first, e.g. 3401 = { 1, 0, 4, 3 }
typedef std::vector<unsigned int> BigNumber;

// count all numbers converging to BigNumber
std::map<BigNumber, unsigned int> finalNumber;

// return true if x is a Lychrel number, stop after maxIterations (and return true if "indecisive")
bool isLychrel(unsigned int x, unsigned int maxIterations)
{
  // split integer into its digit, store each digit in a separate cell
  BigNumber number;
  while (x > 0)
  {
    number.push_back(x % 10);
    x /= 10;
  }

  // try to find a palindrome in the first 60 iterations
  for (unsigned int iteration = 0; iteration < maxIterations; iteration++)
  {
    auto reverse = number;
    std::reverse(reverse.begin(), reverse.end());

    // check if palindrome
#ifdef ORIGINAL
    if (iteration > 0) // originally, the initial number is allowed to be a palindrome
#endif
    // no, can't be a Lychrel number
    if (number == reverse)
    {
      finalNumber[number]++;
      return false;
    }

    // add the reverse
    auto sum = number;
    unsigned int carry = 0;
    for (size_t digit = 0; digit < number.size(); digit++)
    {
      // get digit "from the other end"
      sum[digit] += reverse[digit] + carry;

      // overflow ?
      if (sum[digit] >= 10)
      {
        sum[digit] -= 10;
        carry = 1;
      }
      else
      {
        // add one more digit
        carry = 0;
      }
    }
    if (carry > 0)
      sum.push_back(carry);

    number = std::move(sum);
  }

  // yes, we have a Lychrel number
  return true;
}

int main()
{
  // consider a number to be a Lychrel number if no palindrome after that many iterations
#ifdef ORIGINAL
  unsigned int iterations = 50;
#else
  unsigned int iterations = 60;
#endif

  unsigned int maxNumber = 10000;
  std::cin >> maxNumber;

  // count all Lychrel number
  unsigned int count = 0;
  for (unsigned int i = 0; i <= maxNumber; i++)
    if (isLychrel(i, iterations))
      count++;

#ifdef ORIGINAL
  std::cout << count << std::endl;

#else

  unsigned int bestCount = 0;
  BigNumber    bestNumber;
  // find number most converged to
  for (auto f : finalNumber)
    if (bestCount < f.second)
    {
      bestCount  = f.second;
      bestNumber = f.first;
    }

  // print single digits, highest digits first (they were stored last in BigNumber)
  std::reverse(bestNumber.begin(), bestNumber.end());
  for (auto digit : bestNumber)
    std::cout << digit;
  std::cout << " " << bestCount << std::endl;
#endif

  return 0;
}
