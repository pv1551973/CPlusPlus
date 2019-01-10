#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP
#include<string>
#include<array>
#include "constants.hpp"
using std::string;
using std::array;

namespace connector{
        struct duration{
                string from;
                string to;
        };
        void write_fromfile_todb(void);
        void extract_key(array<char,MAX_BUFFER>&);
        void extract_year_values(array<char,MAX_BUFFER>&,string&,string&);
        void adjust_duration(array<char,MAX_BUFFER>&);
        void rem_dup_keys(void);
        void write_fromdb_tofile(void);
        void sort_data(string&);
        void create_output_string(string&, string&);
        void write_output_to_memory(string&);
}

#endif
