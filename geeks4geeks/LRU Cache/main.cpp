#include "code.hpp"
#include <exception>
#include <array>

using std::ofstream;
using std::exception;
using std::array;

#define MAX_SIZE 25

int main (void){

   array<int,MAX_SIZE> a;
   a.fill(-1);

   try{
      string filename = "example.txt";
      ofstream filehandle;
      filehandle.open(filename);
      if(!filehandle.is_open()){
         error e(error_code::BAD_FILE_OPEN, "Unable to create/open file on disk");
         throw e;
      }
      filehandle << "4" << endl;
      filehandle << "5" << endl;
      filehandle << "14" << endl;
      filehandle << "SET 1 2 SET 3 4 SET 4 5 SET 5 6 SET 6 7 SET 7 8 SET 8 9 GET 1 GET 3 GET 4 GET 5 GET 6 GET 7 GET 8" << endl;
      filehandle << "2" << endl;
      filehandle << "6" << endl;
      filehandle << "SET 1 2 SET 3 4 SET 4 5 SET 5 6 GET 3 GET 5" << endl;
      filehandle << "2" << endl;
      filehandle << "2" << endl;
      filehandle << "SET 1 2 GET 1" << endl;
      filehandle << "2" << endl;
      filehandle << "7" << endl;
      filehandle << "SET 1 2 SET 2 3 SET 1 5 SET 4 5 SET 6 7 GET 4 GET 1" << endl;

      filehandle.close();
      cache<array<int,MAX_SIZE>> c(filename, a);
   }
   catch(const exception& e){
      cout << "Runtime error: " ;
      cout << e.what() << endl;
   }
   catch(const error& e){
      cout << "Runtime error: " ;
      cout << e.what() << endl;
   }
   catch(...){
      cout << "Unidentified runtime error" << endl;
   }

   return 0;
}
