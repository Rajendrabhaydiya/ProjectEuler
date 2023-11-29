#include <iostream>
#include <vector>
#include <map>

//#define ORIGINAL

// a single addition chain
typedef std::vector<unsigned int> Chain;

// iterative depth-first search of Brauer sequence
bool search(Chain& chain, unsigned int exponent, unsigned int maxDepth)
{
  // too deep ?
  if (chain.size() > maxDepth)
    return false;

  auto last = chain.back();
  for (size_t i = 0; i < chain.size(); i++)
  {
    //auto sum = chain[i] + last;
    auto sum = chain[chain.size() - 1 - i] + last; // try high exponents first => about twice as fast
    if (sum == exponent)
      return true;

    chain.push_back(sum);
    if (search(chain, exponent, maxDepth))
      return true;

    chain.pop_back();
  }

  return false;
}

// increase depth until a solution is found
Chain findChain(unsigned int exponent)
{
  // cached ? (needed for Hackerrank only)
  static std::map<unsigned int, Chain> cache;
  auto lookup = cache.find(exponent);
  if (lookup != cache.end())
    return lookup->second;

  // start iterative search
  Chain chain;
  unsigned int depth = 1;
  while (true)
  {
    // reset chain
    chain = { 1 };
    // a start search
    if (search(chain, exponent, depth))
      break;

    // failed, allow to go one step deeper
    depth++;
  }

  cache[exponent] = chain;
  return chain;
}

// print a single chain in Hackerrank format
void print(const Chain& chain)
{
  // number of multiplications
  std::cout << (chain.size() - 1) << std::endl;
  // print each multiplication
  for (size_t i = 1; i < chain.size(); i++)
  {
    // involved exponents
    auto sum  = chain[i];
    auto add1 = chain[i - 1];
    auto add2 = sum - add1;

    std::cout << "n";
    if (add1 > 1)
      std::cout << "^" << add1;
    std::cout << " * n";
    if (add2 > 1)
      std::cout << "^" << add2;
    std::cout << " = n^" << sum << std::endl;
  }
}

int main()
{
#ifdef ORIGINAL

  unsigned int sum = 0;
  // find all chains 2..200
  for (unsigned int exponent = 2; exponent <= 200; exponent++)
  {
    auto chain = findChain(exponent);
    // sum of all chains' lengths
    sum += chain.size();
  }
  std::cout << sum << std::endl;

#else

  unsigned int tests;
  std::cin >> tests;
  while (tests--)
  {
    unsigned int exponent;
    std::cin >> exponent;

    // compute one chain (there might be different chains of the same length)
    auto chain = findChain(exponent);
    // append the exponent, which is not part of the chain yet
    chain.push_back(exponent);
    // and display
    print(chain);
  }

#endif

  return 0;
}
