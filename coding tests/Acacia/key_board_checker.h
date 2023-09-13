#ifndef KEY_BOARD_CHECKER_H
#define KEY_BOARD_CHECKER_H

#include <array>
#include <vector>
#include <string>
#include <map>
#include <set>

using std::array;
using std::vector;
using std::string;
using std::map;
using std::set;

class key_board;

class key_board_checker{

public:
key_board_checker(const key_board& rkb);
~key_board_checker()=default;

protected:

private:
key_board_checker(const key_board_checker&)=delete;
key_board_checker& operator=(const key_board_checker&)=delete;

private:
//static const unsigned short maxletters  = 52;
static const unsigned short maxletters  = 128;
static array<bool,maxletters> alphabet;

private:
//housekeeping
mutable map<string,vector<string>>final;

private:
static const unsigned short numalnumidx = 18;
static array<char,numalnumidx> alnum;

private:
const key_board& rkb;

private:
void initialize_vowels ();
void check_keyboard () const;
bool check_if_vowel(char) const;
void step1 () const; 
void step2 (const vector<string>&) const; 
void step3 (const vector<string>&, string&) const; 
void step4 (const string&, const vector<string>&) const; 

//debugging
#ifdef DBG_TRACE
private:
void print_vs(const vector<string>&) const; 
void print_strset(const set<string>&) const; 
void print_str(const string&) const; 
void print_idx_str(unsigned short, const string&) const; 
#endif

};

#include "key_board.h"

#endif
