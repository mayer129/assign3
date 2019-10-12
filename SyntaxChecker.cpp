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
  ifstream textFile(fileName); //opens filepath

  while (true)
  {
    GenStack<char> s;

    string line = "";
    int lineCount = 0;

    while (getline(textFile, line)) //iterates through each line in file
    {
      lineCount++;
      for(int i = 0; i < line.size(); ++i) //iterates through each char in line
      {
        char lineChar  = line[i];

 //if it may be a comment or multiline ending
        if (lineChar == '/')
        {
          if (i > 0) //so we can check previous char
          {
            if (line[i - 1] == '/') //if comment
            {
              if (!s.isEmpty()) //and stack not empty
              {                       //change this
                if (s.peek() == '\"' || s.peek() == '\'' || s.peek() == '*') //check for other excemptions
                  continue;
              }
              break; //if comment, break line
            }
            if (line[i - 1] == '*')
            {
              if (!s.isEmpty())
              {
                if (s.peek() == '*')
                {
                  s.pop();
                  continue;
                }
              }
            }
          }
          else //if no previous, continue
            continue;
        }

//if it may be a multiline comment beginning
        if (lineChar == '*')
        {
          if (i > 0) //so we can check previous char
          {
            if (line[i - 1] == '/') //if multiline comment
            {
              if (!s.isEmpty()) //and stack not empty
              {
                if (s.peek() == '\"' || s.peek() == '\'' || s.peek() == '*') //check for other excemptions
                  continue;
                else
                {
                  s.push(lineChar);
                  continue;
                }
              }
              else //if stack empty, add multiline comment, continue;
              {
                s.push(lineChar);
                continue;
              }
            }
          }
          else //if no previous char, continue
            continue;
        }

//if it may be a single or double quote
        if (lineChar == '\"' || lineChar == '\'')
        {
          if (!s.isEmpty()) //and stack not empty
          {
            if (s.peek() == lineChar) //if stack also holds single or double quote
            {
              if (i > 0) //so we can check previous char for string literal
              {
                if (line[i - 1] == '\\') //if previous char is string literal, continue
                {
                  int j = i - 1;
                  int count = 0;
                  while (line[j] == '\\' && j > -1)
                  {
                    count++;
                    j--;
                  }
                  if (count % 2 != 0) //if you have an even number of string literals it should not invalidated anything after it.
                    continue;
                  else //if you have an odd number of string literals, it should be added
                  {
                    s.pop();
                    continue;
                  }
                }
                else //if lineChar == char on stack, and i > 0, pop char from stack
                {
                  s.pop();
                  continue;
                }
              }
            }
            else if (s.peek() == '*' || s.peek() == '\"' && lineChar == '\'' || s.peek() == '\'' && lineChar == '\"') //check for other excemptions
              continue; //checks to make sure " and ' dont get added to the stack if their opposite is already there
            else //if they do match, and !i > 1, push
            {
              s.push(lineChar);
              continue;
            }
          }
          else //if stack empty, add single or double quote, continue
          {
            s.push(lineChar);
            continue;
          }
        }

//checks for stack holding excemption symbols. if it does, simply iterate as it shouldnt count anything within comments or quotes
        if (!s.isEmpty())
          if (s.peek() == '\"' || s.peek() == '\'' || s.peek() == '*')
            continue;


        if (lineChar == '{' || lineChar == '(' || lineChar == '[') //if open syntax, add to stack
          s.push(lineChar);
        else if (lineChar == '}' || lineChar == ')' || lineChar == ']') //if closed syntax
        {
          if (s.isEmpty()) //if no previous syntax, throw error
          {
            cout << "Line " << lineCount << ": expected " << getCharVal(lineChar) << " and found " << lineChar << endl;
            textFile.close();
            return;
          }
          else
          {
            if (getCharVal(lineChar) == s.peek()) //if they are same, remove from stack
              s.pop();
            else //if they aren't same, throw error
            {
              cout << "Line " << lineCount << ": expected " << getCharVal(s.peek()) << " and found " << lineChar << endl;
              textFile.close();
              return;
            }
          }
        }
      }
    }
      if (!s.isEmpty()) //if at end of file and stack isn't empty, throw error
      {
        cout << "Reached end of file: missing " << getCharVal(s.peek()) << endl;
        textFile.close();
        return;
      }

    string cont = "";
    fileName = "";
    cout << "Delimiter Syntax Valid. Would you like to analyze another file? (y/n)" << endl; //if syntax valid, prompt for input
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

char SyntaxChecker::getCharVal(char d) //this just checks whether the syntax goes with its corresponding symbol
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
