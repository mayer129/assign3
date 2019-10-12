#include <iostream>
#include <cstdlib>
#include <iostream>

using namespace std;

template <class T>
class GenStack
{
public:
  GenStack(int maxSize = 128);
  ~GenStack();

  void push(T d);
  T pop();
  T peek();

  bool isEmpty();
  bool isFull();

  int top;
  int size;

  T* myArray;
};

template <class T>
GenStack<T>::GenStack(int maxSize)
{
  myArray = new T[maxSize];
  size = maxSize;
  top = -1;
}

template <class T>
GenStack<T>::~GenStack()
{
  delete[] myArray;
}

template <class T>
void GenStack<T>::push(T d)
{
  if (isFull())
  {
    int newSize = size * 2;
    T* temp = new T[newSize];
    for (int i = 0; i < size; ++i)
    {
      temp[i] = myArray[i];
    }
    delete[] myArray;
    myArray = temp;
    size = newSize;
  }
  myArray[++top] = d;
}

template <class T>
T GenStack<T>::pop()
{
  if (isEmpty())
  {
    cerr << "Unable to pop empty stack" << endl;
    exit(EXIT_FAILURE);
  }
  return myArray[top--];
}

template <class T>
T GenStack<T>::peek()
{
  if (isEmpty())
  {
    cerr << "Unable to peek empty stack" << endl;
    exit(EXIT_FAILURE);
  }
  return myArray[top];
}

template <class T>
bool GenStack<T>::isFull()
{
  return (top == size - 1);
}

template <class T>
bool GenStack<T>::isEmpty()
{
  return (top == -1);
}
