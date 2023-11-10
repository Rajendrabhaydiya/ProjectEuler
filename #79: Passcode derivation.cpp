#include <set>
#include <map>
#include <string>
#include <iostream>

int main()
{
  unsigned int logins = 50; // p079_keylog.txt contains 50 logins

//#define ORIGINAL
#ifndef ORIGINAL
  std::cin >> logins;
#endif

  // read all logged inputs
  // for each digit/letter, store its predecessor
  std::map<char, std::set<char>> previous;
  while (logins--)
  {
    std::string line;
    std::cin >> line;
    // create an empty set for the initial letter (if it doesn't exist yet)
    previous[line[0]];
    // and for the other letters, store their predecessors
    for (unsigned int i = 1; i < line.size(); i++)
      previous[line[i]].insert(line[i - 1]);
  }

  // until we have no characters left ...
  std::string result;
  while (!previous.empty())
  {
    // find lexicographically smallest letter with no predecessor
    auto emptySet = previous.begin();
    while (emptySet != previous.end() && !emptySet->second.empty())
      emptySet++;

    // invalid ?
    if (emptySet == previous.end())
    {
      result = "SMTH WRONG"; // Hackerrank's message if code cannot be decrypted
      break;
    }

    // print letter
    auto current = emptySet->first;
    result += current;

    // that letter won't appear in the keyphrase anymore
    previous.erase(current);

    // remove from the predecessor list of all other letters
    for (auto& p : previous)
      p.second.erase(current);
  }

  // print keyphrase
  std::cout << result << std::endl;
  return 0;
}
