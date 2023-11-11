#include <iostream>
#include <vector>
#include <string>
#include <set>

// sorted container of valid n-gon strings
std::set<std::string> result;
// size of the n-gon (3,4,5)
unsigned int size;
// sum of all three cells alongs a diagonal/edge
unsigned int tripletSum;

void fillLine(unsigned int pos, std::vector<unsigned int> inner, std::vector<unsigned int> outer, unsigned int used)
{
  // inner ring completely filled, just one cell of the outer ring left
  if (pos == size - 1)
  {
    // check last line
    outer[size - 1] = tripletSum - (inner[0] + inner[size - 1]);
    unsigned int mask = 1 << outer[size - 1];
    if ((used & mask) != 0)
      return;

    // first element of outer ring must be the smallest
    for (auto x : outer)
      if (x < outer[0])
        return;

    // build string
    std::string id;
    for (unsigned int i = 0; i < size; i++)
      id += std::to_string(outer[i]) + std::to_string(inner[i]) + std::to_string(inner[(i + 1) % size]);

    // will be alphabetically ordered
    result.insert(id);
    return;
  }

  // move a number between 1 and 2*size into one of the inner cells of the n-gon
  for (unsigned int i = 1; i <= 2*size; i++)
  {
    // fill a cell of the inner ring
    unsigned int innerMask = 1 << i;
    // is that number still available ?
    if ((innerMask & used) != 0)
      continue;

    // occupy cell
    inner[pos + 1] = i;
    unsigned int nextUsed = used | innerMask;

    // compute the according cell in the outer ring
    outer[pos] = tripletSum - (inner[pos] + i);
    unsigned int outerMask = 1 << outer[pos];
    // is that number still available ?
    if ((nextUsed & outerMask) != 0)
      continue;
    nextUsed |= outerMask;

    // next line
    fillLine(pos + 1, inner, outer, nextUsed);
  }
}

int main()
{
  std::cin >> size >> tripletSum;

  // generate the inner and outer ring
  std::vector<unsigned int> inner(size);
  std::vector<unsigned int> outer(size);
  // a triplet consists of inner[a], inner[(a+1) % (2*a)], outer[a]

  // generate a bitmask of allowed numbers (0 = still available, 1 = already used / disallowed)
  unsigned int allowed = 0;
  for (unsigned int i = 1; i <= 2 * size; i++)
    allowed |= 1 << i;
  allowed = ~allowed;

  // fill first cell of inner ring
  for (unsigned int i = 1; i <= 2*size; i++)
  {
    inner[0] = i;
    // fill remaining cells
    fillLine(0, inner, outer, allowed | (1 << i));
  }

//#define ORIGINAL
#ifdef ORIGINAL
  std::cout << *result.rbegin() << std::endl;
#else
  for (auto r : result)
    std::cout << r << std::endl;
#endif
}
