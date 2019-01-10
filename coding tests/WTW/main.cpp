#include "file_io.hpp"
#include "data.hpp"
#include "connector.hpp"
#include "error.hpp"
using std::cout;

unit_data obj_udata;
data obj_data;
vector<string> keys;
connector::duration from_to;

int main(){
        try{
                from_to.from = ZERO_STRING;
                from_to.to = ZERO_STRING;
                file_io::read();
                connector::write_fromfile_todb();
                connector::write_fromdb_tofile();

                cout << "Data Successfully Written to " << OUTPUT_FILE << NEWLINE;
                cout << "Program Ends Successfully" << NEWLINE; 
        }
        catch(Error_Code e){
                switch(e){
                        case Error_Code::BAD_FILENAME:
                                cout << "Invalid Input File" << NEWLINE;
                                break;
                        case Error_Code::BAD_INPUT:
                                cout << "Invalid Data in Input File" << NEWLINE;
                                break;
                        case Error_Code::BAD_FILE_WRITE:
                                cout << "Unable to Create File on Disk" << NEWLINE;
                                break;
                        default:
                                break;
                }
        }

        return 0;
}
