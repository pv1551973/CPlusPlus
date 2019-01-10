#ifndef DATA_HPP
#define DATA_HPP
#include<string>
#include<vector>
#include<map>
#include<iostream>
using std::string;
using std::vector;
using std::map;

class unit_data{
        public:
                unit_data()=default;
        public:
                void construct(string&&);
                void operator = (unit_data&);
        public:
                string& get_prod(void);
                string& get_year_orig(void);
                string& get_year_dev(void);
                string& get_val(void);
        private:
                string prod;
                string year_orig;
                string year_dev;
                string val;
};

class data{
        public:
                data()=default;
        public:
                void insert(unit_data&);
                vector<unit_data>& operator [](const string&);
        private:
                map<string,vector<unit_data>> repo;
};
#endif
