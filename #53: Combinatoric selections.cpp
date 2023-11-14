#include <vector>
#include <iostream>

int main()
{
  // maximum index n and/or k
  unsigned int       maxN      = 100;
  // what is considered "big" ?
  unsigned long long maxNumber = 1000000;
  std::cin >> maxN >> maxNumber;

  // this will be the displayed result
  unsigned int bigNumbers = 0;

  // setup a 2D array to hold all values
  std::vector<std::vector<unsigned long long>> combinations(maxN + 1);

  // C(n,0) = C(n,n) = 1
  for (unsigned int n = 0; n <= maxN; n++)
  {
    combinations[n].resize(n + 1, 0);
    combinations[n][0] = combinations[n][n] = 1;
  }

  // recursive definition:
  // C(n,k) = C(n-1, k-1) + C(n-1, k)
  for (unsigned int n = 1; n <= maxN; n++)
    for (unsigned int k = 1; k < n; k++)
    {
      auto sum = combinations[n - 1][k - 1] + combinations[n - 1][k];
      // clamp numbers to avoid exceeding 64 bits
      if (sum > maxNumber)
      {
        sum = maxNumber + 1;
        // we found one more big number
        bigNumbers++;
      }

      // store result
      combinations[n][k] = sum;
    }

  std::cout << bigNumbers << std::endl;
  return 0;
}
