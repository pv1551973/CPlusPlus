#ifndef KEY_SEQUENCES_H
#define KEY_SEQUENCES_H

#include <set>
#include <map>
#include <string>

using std::set;
using std::map;
using std::string;

class key_board;
class key_board_checker;

class key_sequences{

friend class key_board;
friend class key_board_checker;

public:
key_sequences();
~key_sequences() = default;

protected:

private:
key_sequences (const key_sequences&) = delete;
key_sequences& operator = (const key_sequences&) = delete;

private:
 map<string,set<string>>matrix;
 map<char,set<string>>indices;
 void initialize_matrix_indices();
 
};

#include "key_board.h"
#include "key_board_checker.h"

#endif
