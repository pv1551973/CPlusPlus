#include <string>
#include <ios>
#include <array>
#include <random>
#include <map>
#include <vector>
#include <iterator>
#include <iostream>

using std::string;
using std::boolalpha;
using std::array;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::map;
using std::next;
using std::cout;
using std::endl;

void make_random_string(string& s, const size_t len)
{
  if(len > 25)
  {
    return;
  }
  constexpr unsigned short num_letters = 26;
  constexpr unsigned short low = 0;
  constexpr unsigned short high = 25;
  array<char,num_letters>alphabets = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<>dist(low,high);
  
  for(size_t count = 0; count < len; ++count)
  {
    auto idx = dist(gen);
    s += alphabets.at(idx);
  }

  return;
}

bool makePalindrome(string s)
{
  auto s_sz = s.size();
  static auto count = 0;

  if(2 == count)
  {
    if(1 == s_sz)
    {
      return true;
    }
    return false;
  }
  if((2 >= s_sz) && !count)
  {
    return true;
  }
  if(s[0] != s[s_sz - 1])
  {
    s[s_sz - 1] = s[0];
    ++count;
  }

  if(3 <= s_sz)
  {
    return(makePalindrome(s.substr(1, s_sz - 2))); 
  }
  else
  {
    return true;
  }
  return false;
}

void print(bool result)
{
  cout << boolalpha << result << endl;

  return;
}

int func() 
{
  //string s = "abcdba";
  //string s = "zbcfedcba";
  //string s = "bbba";
  //string s = "ltifo";
  //string s = "zhak";
  //string s = "zznzk";
  //string s = "qmmhhp";
  string s = "aaa";
  //string s;
  //constexpr size_t sz = 5;
  
  //make_random_string(s, sz);
  
  #ifdef DBG
  cout << "random string: " << s << endl;
  #endif

  print(makePalindrome(s));
  
	return 0;	
}

int main() {
    auto exit = (int (*)()) &func;
    
    std::cout << exit() << std::endl;
}
