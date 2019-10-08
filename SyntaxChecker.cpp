#include "SyntaxChecker.h"
#include "GenStack.h"
#include <iostream>
#include <fstream>

using namespace std;

SyntaxChecker::SyntaxChecker()
{

}

SyntaxChecker::SyntaxChecker(string filePath)
{
  string fileName = filePath;
  ifstream textFile(fileName);
  while (true)
  {
    GenStack<char> s;

    string line = "";
    int lineCount = 0;

    while (getline(textFile, line))
    {
      lineCount++;
      for(int i = 0; i < line.size(); ++i)
      {
        char lineChar  = line[i];
        if (lineChar == '{' || lineChar == '(' || lineChar == '[')
          s.push(lineChar);
        if (lineChar == '}' || lineChar == ')' || lineChar == ']')
        {
          if (s.isEmpty())
          {
            cout << "Line " << lineCount << ": expected " << getCharVal(lineChar) << " and found " << lineChar << endl;
            return;
          }
          else
          {
            if (getCharVal(lineChar) == s.peek())
              s.pop();
            else
            {
              cout << "Line " << lineCount << ": expected " << getCharVal(s.peek()) << " and found " << lineChar << endl;
              return;
            }
          }
        }
      }
    }
      if (!s.isEmpty())
      {
        cout << "Reached end of file: missing " << getCharVal(s.peek()) << endl;
        return;
      }

    string cont = "";
    fileName = "";
    cout << "Delimiter Syntax Valid. Would you like to analyze another file? (y/n)" << endl;
    cin >> cont;
    if (cont != "y" && cont != "Y") //if no, breaks out of while loop
      break;

    cout << "What is the name of the next file?" << endl; //takes name of next file and while loop continues
    cin >> fileName;
    textFile.close();
    textFile.clear();
    textFile.open(fileName);
  }
  textFile.close();
}

SyntaxChecker::~SyntaxChecker()
{

}

char SyntaxChecker::getCharVal(char d)
{
  char val = '?';
  switch (d)
  {
    case '{': val = '}';
      break;
    case '}': val = '{';
      break;
    case '(': val = ')';
      break;
    case ')': val = '(';
      break;
    case '[': val = ']';
      break;
    case ']': val = '[';
      break;
    default: val = '!';
  }
  return val;
}
