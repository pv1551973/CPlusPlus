#ifndef KEY_MAP_H
#define KEY_MAP_H

#include <set>
#include <map>

class key_board;

using std::set;
using std::map;

class key_map{

friend class key_board;

public:
 key_map();
 ~key_map() = default;

protected:

private:
key_map (const key_map&) = delete;
key_map& operator = (const key_map&) = delete;

private:
 map<char,set<char>>matrix;
 void initialize_matrix();

};

#include "key_board.h"

#endif
