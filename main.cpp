#include "GenStack.h"
#include "SyntaxChecker.h"
#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char** argv)
{
  if (argc != 2) //checking if filepath was entered. If no filepath given, program ends
  {
    cout << "Please run again and include the filepath" << endl;
    return 0;
  }

  ifstream textFile(argv[1]);

  if (textFile.is_open() && textFile.good())
  {
    textFile.close();
    SyntaxChecker sc(argv[1]);
  }
  else
    cout << "Unable to open file" << endl;

  return 0;
}
