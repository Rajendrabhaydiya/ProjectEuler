#include <iostream>
#include <vector>
#include <string>

// all 22 guesses
typedef std::vector<unsigned char> Sequence;
std::vector<Sequence>     sequences;
// and how many of their digits match the secret number
std::vector<unsigned int> hits;

// a simple pseudo-random number generator, result in 0 .. modulo - 1
// (produces the same result no matter what compiler you have - unlike rand() from math.h)
unsigned int myrand(unsigned int modulo)
{
  static unsigned int seed = 0;
  seed = 1103515245 * seed + 12345;
  return seed % modulo;
}

// replace reference by a new random digit (0..9)
void shuffle(unsigned char& digit)
{
  auto old = digit;
  do
    digit = myrand(10);
  while (digit == old);
}

// a player's guess and how many digits were correct
void add(const std::string& guess, unsigned int matches)
{
  // convert from ASCII to int
  Sequence s;
  for (auto c : guess)
    s.push_back(c - '0');
  sequences.push_back(s);

  hits.push_back(matches);
}

// compute how many digits of the guesses don't match to the currently analyzed number
// a perfect match returns 0, "mismatches" return > 0
unsigned int distance(const Sequence& current)
{
  unsigned int errors = 0;

  for (unsigned int i = 0; i < sequences.size(); i++)
  {
    // count number of matching digits
    unsigned int same = 0;
    for (unsigned int j = 0; j < current.size(); j++)
      if (current[j] == sequences[i][j])
        same++;

    // too many identical digits ?
    if (same > hits[i])
      errors += same - hits[i];
    else // or too few ?
      errors += hits[i] - same;
  }

  return errors;
}

int main()
{
//#define ORIGINAL
#ifdef ORIGINAL
  // guesses of the problem
  add("5616185650518293", 2);
  add("3847439647293047", 1);
  add("5855462940810587", 3);
  add("9742855507068353", 3);
  add("4296849643607543", 3);
  add("3174248439465858", 1);
  add("4513559094146117", 2);
  add("7890971548908067", 3);
  add("8157356344118483", 1);
  add("2615250744386899", 2);
  add("8690095851526254", 3);
  add("6375711915077050", 1);
  add("6913859173121360", 1);
  add("6442889055042768", 2);
  add("2321386104303845", 0);
  add("2326509471271448", 2);
  add("5251583379644322", 2);
  add("1748270476758276", 3);
  add("4895722652190306", 1);
  add("3041631117224635", 3);
  add("1841236454324589", 3);
  add("2659862637316867", 2);
#else
  unsigned int numGuesses;
  std::cin >> numGuesses;
  while (numGuesses--)
  {
    std::string guess;
    unsigned int correct;
    std::cin >> guess >> correct;
    add(guess.c_str(), correct);
  }
#endif

  // initially a purely random guess
  const auto NumDigits = sequences.front().size();
  Sequence current(NumDigits, 0);
  for (auto& x : current)
    shuffle(x);

  // shuffle a random digit when stuck in a local optimum, too
  const auto MaxRoundsWithoutImprovement = 20; // "sweet spot" for my random number generator
  auto quietRounds = 0;

  auto errors   = distance(current);
  auto previous = errors;
  while (errors != 0)
  {
    // replace every digit by a different random number, keep those that minimize the error metric
    for (auto& digit : current)
    {
      // replace by a new random digit
      auto previousDigit = digit;
      do
        shuffle(digit);
      while (digit == previousDigit);

      // compute error metric
      auto modified = distance(current);
      if (modified <= errors)
      {
        // better than before, adjust error level and keep new digit
        errors = modified;
      }
      else
        // mutation is equal or worse, restore old digit
        digit = previousDigit;
    }

    // unchanged score ? we didn't improve on the previous solution ...
    if (errors == previous)
    {
      // stuck too long ? try to escape local optimum
      quietRounds++;
      if (quietRounds == MaxRoundsWithoutImprovement)
      {
        // change a random number
        shuffle(current[myrand(current.size())]);
        errors = distance(current);

        // reset counter
        quietRounds = 0;
      }
    }
    else
    {
      // we got closer to the goal ...
      quietRounds = 0;
      previous = errors;
    }
  }

  // show solution
  for (auto c : current)
    std::cout << int(c);
  std::cout << std::endl;

  return 0;
}
