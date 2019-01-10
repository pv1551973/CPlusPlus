#ifndef FILE_IO_HPP
#define FILE_IO_HPP
#include<string>
#include<array>
#include<vector>
#include<fstream>
#include<iostream>
#include "constants.hpp"
using std::string;
using std::array;
using std::vector;

namespace file_io{
        
        void read(void);
        void write(void);
        extern string inputfilename;
        extern string outputfilename;
        extern array<char,MAX_BUFFER> buffer;
        extern vector<array<char,MAX_BUFFER>> input;
        extern vector<string> output;
}
#endif
