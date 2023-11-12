#include <string>
#include <iostream>

typedef unsigned int Board[9][9];
const unsigned int Empty = 0;

// find the first solution and store it in board
bool solve(Board& board)
{
  for (unsigned int y = 0; y < 9; y++)
    for (unsigned int x = 0; x < 9; x++)
    {
      // already solved cell ?
      if (board[x][y] != Empty)
        continue;

      // track which numbers could be placed in the current cell
      bool available[9+1] = { false,  true, true, true, true, true, true, true, true, true };
      // note: available[0] is a dummy entry, the program only uses available[1..9]

      // same row and column
      for (unsigned int i = 0; i < 9; i++)
      {
        if (board[i][y] != Empty)
          available[board[i][y]] = false;
        if (board[x][i] != Empty)
          available[board[x][i]] = false;
      }
      // same region (3x3 area)
      unsigned int rx = (x / 3) * 3;
      unsigned int ry = (y / 3) * 3;
      for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 3; j++)
          if (board[i + rx][j + ry] != Empty)
            available[board[i + rx][j + ry]] = false;

      // try all still available numbers
      for (unsigned int i = 1; i <= 9; i++)
        if (available[i])
        {
          board[x][y] = i;
          if (solve(board))
            return true;
        }
      // all failed, restore old board
      board[x][y] = Empty;
      return false;
    }

  // solved it
  return true;
}

int main()
{
//#define ORIGINAL
#ifdef ORIGINAL
  unsigned int tests = 50;
  unsigned int sum   =  0;
#else
  unsigned int tests =  1;
#endif

  while (tests--)
  {
#ifdef ORIGINAL
    // skip labels "GRID xy"
    std::string dummy;
    std::cin >> dummy >> dummy;
#endif

    // read board
    Board board;
    for (unsigned int y = 0; y < 9; y++)
    {
      std::string line;
      std::cin >> line;
      for (unsigned int x = 0; x < 9; x++)
        board[x][y] = line[x] - '0';
    }

    // and replace all zeros (=Empty) with proper digits
    solve(board);

#ifdef ORIGINAL
    // the first the cells
    sum += 100 * board[0][0] + 10 * board[1][0] + board[2][0];
#else
    // print full solution
    for (unsigned int y = 0; y < 9; y++)
    {
      for (unsigned int x = 0; x < 9; x++)
        std::cout << board[x][y];
      std::cout << std::endl;
    }
#endif
  }

#ifdef ORIGINAL
  std::cout << sum;
#endif

  return 0;
}
