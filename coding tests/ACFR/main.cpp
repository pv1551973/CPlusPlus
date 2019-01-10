#include "database.hpp"
#include "sampler.hpp"
#include "error.hpp"
//crude, in order to evoke exit()
#include<stdlib.h>

int main ()
{
 string filename;
 double frequency;
 try{
 cout << "Enter DB File Name (must be in current directory; Unix file naming conventions apply):";
 cin >> filename; 
 string backslash("/");

if(!(
     string::npos == filename.find(backslash)
    )
  ){//if block 1
error e(error_code::invalid_filename);
throw e;
}//end of if block 1 

 cout << "\n";
 cout << "Enter the sampling frequency (must be in the range 0-1):";
 cin >> frequency;
if(0 > frequency || frequency > 1.0){//if block 2 
error e(error_code::invalid_range); 
throw e;
}//end of if block 2 

 cout << "\n";

//initialize the database object
database db(filename);

//initialize the sampler object
sampler<database> s_engine(db, frequency);
//generate sample of database
s_engine.generate_sample();
cout << "\n";
return 0;
}//end of try block

catch(error e){
switch(e.get()){
case error_code::invalid_filename:
cout << "Invalid File Format Entered.\n";
//just a crude place holder for more 
//effective error handling
cout << "Program Would Exit Now.\n";
exit(EXIT_FAILURE);
break;
case error_code::invalid_range:
cout << "Invalid Frequency Range Entered.\n";
//just a crude place holder for more 
//effective error handling
cout << "Program Would Exit Now.\n";
exit(EXIT_FAILURE);
break;
case error_code::out_of_bound_index:
cout << "Container Indexed using Out of Bound Value.\n";
//just a crude place holder for more 
//effective error handling
cout << "Program Would Exit Now.\n";
exit(EXIT_FAILURE);
break;
default:
break;
}//end of switch
}//end of catch error

catch(...){
cout << "Unknown Error Encountered.\n";
//just a crude place holder for more 
//effective error handling
cout << "Program Would Exit Now.\n";
exit(EXIT_FAILURE);
}//end of catch all
}//end of main


