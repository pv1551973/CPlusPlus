#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using std::vector;
using std::for_each;
using std::next;
using std::prev;
using std::cout;
using std::endl;


void print(vector<int>& nums)
{
	for_each(nums.begin(), nums.end(), [](const int& n){
						cout << n << " " ;});
  cout << endl;
	return;
}

void rotate(vector<int>& nums, int k) {
        
        size_t origSz = nums.size();
        size_t rem = origSz - k;

        nums.reserve(nums.size() * 2);
        
        for(size_t count = 0; count < origSz; ++count)
        {
					nums.push_back(*(nums.begin() + count));
				}

        auto iter = nums.end() - k;
        
        for(auto count = 0; count < k; ++count)
        {
					*(nums.begin() + count) = *(iter + count);
				}
        
        if(k > 1)
				{
					nums.erase(prev(nums.end(), -1), prev(nums.end(), -(k + 1)));
				}
				else
				{
					nums.erase(prev(nums.end(), -1));
				}
        
				nums.erase(next(nums.begin(), k), next(nums.begin(), k+rem));

        return;
}

int func() 
{
	vector<int>nums = {1, 2, 3, 4, 5, 6, 7};
	//vector<int>nums = {-1, -100, 3, 99};
	//vector<int>nums = {1, 2, 3, 4, 5, 6};
  //int k = 3;
  //int k = 2;
  int k = 1;
  cout << "Before rotation: " << endl;
  print(nums); 
  rotate(nums, k);
  cout << "After rotation: " << endl;
  print(nums); 
  
	return 0;	
}

int main() {
    auto exit = (int (*)()) &func;
    
    std::cout << exit() << std::endl;
}
