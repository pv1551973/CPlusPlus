#ifndef DEBUG_HPP
#define DEBUG_HPP
#define PRNT_LN_NUM (cout << "At line " << __LINE__ << " " << "in file " << __FILE__<< endl);
#define EXIT_PROGRAM_NOW {\
                          atexit(report);\
                          exit(EXIT_FAILURE);\
                         }
#include <cstdlib>
using std::exit;
using std::atexit;

//variable for loop count
extern int loop_count;
//exit handler
extern void report();
#endif
