#include <iostream>

using namespace std;

class SyntaxChecker
{
public:
  SyntaxChecker();
  SyntaxChecker(string filePath);
  ~SyntaxChecker();

  char getCharVal(char d);
};
