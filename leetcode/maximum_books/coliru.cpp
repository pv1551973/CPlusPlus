#include<vector>
#include<iterator>
#include<iostream>

using std::vector;
using std::next;
using std::distance;
using std::cout;
using std::endl;

long long maximumBooks(vector<int>& books)
{
  auto idx = -1;
  auto maxIdx = -1;
  long long maxVal = -1;
  auto totalBooks = books.size();
  //log of book shelves already touched
  static vector<bool>log(totalBooks, false);

  //find the maximum value with the corresponding
  //index
  for(auto& i : books)
  {
    ++idx;
    if(i > maxVal)
    {
      //check if the shelf has been 
      //touched already
      if(log[idx])
      {
        //we can't touch it anymore
        continue;
      }
      else
      {
        maxVal = i;
        maxIdx = idx; 
      }
    }
  }

  //make sure to take only allowed
  //number of books from the current shelf
  if((0 <= maxIdx) && ((decltype(totalBooks))maxIdx < (totalBooks - 1))) 
  {
    auto iterMaxIdx = books.begin() + maxIdx;
    auto iterMinShelfIdx = next(iterMaxIdx,1);

    if(*iterMinShelfIdx < *iterMaxIdx)
    {
      maxVal = *iterMinShelfIdx - 1;
    }

    //mark the shelf as touched
    log[maxIdx] = true;

    if(0 < maxVal)
    {
      return (maxVal + maximumBooks(books));
    }
    else
    {
      return (maximumBooks(books));
    }
  }
  else if((decltype(totalBooks))maxIdx == (totalBooks - 1))
  {
    //mark the shelf as touched
    log[maxIdx] = true;
    return (maxVal + maximumBooks(books));
  }

  return 0;
}

void print(long long num)
{
  cout << "maximum books: " << num << endl;

  return;
}

int func() 
{
  //vector<int>books = {8,5,2,7,9}; 
  vector<int>books = {7,0,3,4,5}; 
  //vector<int>books = {8,2,3,7,3,4,0,1,4,3}; 
  print(maximumBooks(books));
	return 0;	
}

int main() {
    auto exit = (int (*)()) &func;
    
    std::cout << exit() << std::endl;
}
