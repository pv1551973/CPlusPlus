#ifndef TST_CDE_H
#define TST_CDE_H
#include<numeric>
#include<random>
#include<algorithm>
#include<iterator>
#include<fstream>
using std::ios;
using std::ofstream;
using std::vector;
using std::iota;
using std::random_device;
using std::mt19937;
using std::shuffle;

#define FILENAME "DB_file.txt"
#define MAX_ELEMS 100

class xRan{
public:
xRan();
private:
random_device rd;
};//end of class declaration 
#endif
