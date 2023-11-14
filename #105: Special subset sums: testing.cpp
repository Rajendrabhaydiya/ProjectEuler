#include <iostream>
#include <vector>

typedef std::vector<unsigned int> Sequence;

// return true if sequence is special
bool check(const Sequence& sequence)
{
  // sum of all elements
  unsigned int fullSum = 0;
  for (auto x : sequence)
    fullSum += x;

  // mark each generated sum as true, no collisions allowed
  std::vector<bool> sums(fullSum + 1, false);

  // track the lowest and highest sum for each subset size
  std::vector<unsigned int> maxSum(sequence.size() + 1, 0);
  std::vector<unsigned int> minSum(sequence.size() + 1, fullSum + 1);
  minSum[0] = maxSum[0] = 0; // empty set

  unsigned int fullMask = (1 << sequence.size()) - 1;

  // 2^elements iterations (actually, I ignore the empty set)
  for (unsigned int mask = 1; mask <= fullMask; mask++)
  {
    unsigned int sum  = 0;
    unsigned int size = 0;
    for (unsigned int element = 0; element < sequence.size(); element++)
    {
      // use that element ?
      unsigned int bit = 1 << element;
      if ((mask & bit) == 0)
        continue;

      sum += sequence[element];
      // count subset size
      size++;
    }

    // two subsets share the same sum ?
    if (sums[sum])
      return false;
    sums[sum] = true;

    // adjust lowest and highest sum of current subset
    if (minSum[size] > sum)
      minSum[size] = sum;
    if (maxSum[size] < sum)
      maxSum[size] = sum;
  }

  // make sure that no set will fewer elements has a higher sum
  for (size_t i = 1; i < sequence.size(); i++)
    if (maxSum[i] > minSum[i + 1])
      return false;

  // yes, have another solution
  return true;
}

#ifdef ORIGINAL

// convert a line of Project Euler's format into a sequence
Sequence readLine()
{
  Sequence result;
  while (true)
  {
    result.push_back(0);

    char oneByte = 0;
    while (true)
    {
      oneByte = std::cin.get();

      // end of file ?
      if (!std::cin)
        return result;

      // not a digit ?
      if (oneByte < '0' || oneByte > '9')
        break;

      // append digit
      result.back() *= 10;
      result.back() += oneByte - '0';
    }

    // end of line
    if (oneByte != ',')
      break;
  }
  return result;
}

#else

// convert a line of Project Euler's format into a sequence
Sequence readLine()
{
  // read number elements
  unsigned int size;
  std::cin >> size;

  // read elements
  Sequence result(size);
  for (auto& x : result)
    std::cin >> x;

  return result;
}

#endif

int main()
{
  unsigned int tests = 100;
#ifdef ORIGINAL
  unsigned int sum = 0;
#else
  std::cin >> tests;
#endif

  while (tests--)
  {
    auto sequence = readLine();

#ifdef ORIGINAL
    // special ?
    if (check(sequence))
      // yes !
      for (auto x : sequence)
        sum += x;
#else
    // special ?
    if (sequence.size() < 30) // 2^30 has already one billion subsets ...
      std::cout << (check(sequence) ? "YES" : "NO") << std::endl;
    else
      std::cout << "NO" << std::endl; // just make a guess
#endif
  }

#ifdef ORIGINAL
  std::cout << sum << std::endl;
#endif

  return 0;
}
