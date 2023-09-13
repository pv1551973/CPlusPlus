#ifndef KEY_BOARD_H
#define KEY_BOARD_H


#include <set>
#include <map>
#include <string>
#include <vector>
#include <memory>

using std::set;
using std::map;
using std::string;
using std::vector;
using std::unique_ptr;
using mapIter = map<char,set<string>>::iterator;
using setIter = set<string>::iterator;

class key_map;
class key_sequences;
class key_board_checker;

class key_board{

friend class key_board_checker;

private:
struct PrivateTag{};

private:
unique_ptr<key_map>keymPtr;
unique_ptr<key_sequences>keysqPtr;

public:
static const key_board& get_instance(); 
key_board(PrivateTag);
~key_board() = default;

private:
void display() const;
void alternate_display() const;
 
protected:
static bool has_instance;

private:
key_board (const key_board&) = delete;
key_board& operator = (const key_board&) = delete;

private:
static unique_ptr<key_board> keyboardPtr;

private:
map<char,vector<vector<string>>>matrix;

private:
void initialize_matrix();
void loop (mapIter, setIter, setIter);
void loop_again (mapIter,setIter);

private:
//housekeeping
mapIter currIter;
unsigned short ticker;

private:
//debugging
#ifdef DBG_TRACE
void print_string(const string&);
void print_vector_of_strings(const vector<string>&);
void print_map_of_set_of_strings(const map<char,set<string>>&);
void print_set_iterator_dereference(setIter);
#endif

};

#include "key_map.h"
#include "key_sequences.h"
#include "key_board_checker.h"

#endif
