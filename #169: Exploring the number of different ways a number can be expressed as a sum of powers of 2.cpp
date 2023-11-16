#include <iostream>
#include <vector>
#include <string>

// GCC-specific 128 bit integer
typedef unsigned __int128 BigNum;

// brute-force solver, not used anymore
unsigned int solve(unsigned int x, unsigned int minAdd = 1)
{
  if (x == 0)
    return 1;

  unsigned long long result = 0;
  auto current = minAdd;
  while (current <= x)
  {
    // try to remove current 2^k once
    result += solve(x - current, current*2);
    // and twice
    if (x >= 2*current)
      result += solve(x - 2*current, current*2);

    // process 2^(k+1)
    current *= 2;
  }

  return result;
}

// count consecutive zeros in binary representation
std::vector<unsigned int> countZeros(BigNum x)
{
  std::vector<unsigned int> result;

  // right-most 1s don't affect the result, remove them
  while ((x & 1) == 1)
    x >>= 1;

  auto consecutive = 0;
  while (x > 0)
  {
    // look at right-most bit
    if ((x & 1) == 0)
    {
      // once more zero
      consecutive++;
    }
    else
    {
      // runs of consecutive zeros interrupted by a 1
      result.insert(result.begin(), consecutive);
      consecutive = 0;
      // note: consecutive can be zero, too !
    }

    x >>= 1;
  }

  return result;
}

int main()
{
  // can't read anything >= 2^64, must do it via string parsing
  std::string large;
  std::cin >> large;
  BigNum x = 0;
  // digit by digit ...
  for (auto c : large)
    x = x*10 + (c - '0');

  // count consecutive zeros in binary representation
  auto zeros = countZeros(x);

  // compute number of distinct representations
  unsigned long long result = 1;
  unsigned long long sum    = 1;
  for (unsigned int i = 0; i < zeros.size(); i++)
  {
    result += zeros[i] * sum;
    sum    += result;
  }
  std::cout << result << std::endl;
  return 0;
}
