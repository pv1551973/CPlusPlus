#pragma once
#define DBG_TRACE {cout << "At line# " << __LINE__ << " in file " << __FILE__ << endl;}
#define WS " "
#define EQ "="
#define STR(x) #x
#define PRINT(x) {cout << STR(x) << WS << EQ << WS << x << endl;}
