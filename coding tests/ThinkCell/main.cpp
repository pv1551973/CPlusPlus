#include "code.hpp"
#include<exception>
using std::exception;


int main(){

    try{

        IntervalMapTest();
    }
    catch(exception e){

        cout << "Standard Exception " << e.what() << " caught" << endl;
    }
    catch(error e)
    {
        cout << "Exception error " << as_integer(e) << " caught" << endl;

    }
    catch(...){

        cout << "Unknown exception caught" << endl;
    }

    return(0);
}

