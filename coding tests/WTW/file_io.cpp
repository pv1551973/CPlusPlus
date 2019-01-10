#include "file_io.hpp"
#include "error.hpp"
using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;

        string file_io::inputfilename;
        string file_io::outputfilename;
        array<char,MAX_BUFFER> file_io::buffer;
        vector<array<char,MAX_BUFFER>> file_io::input;
        vector<string> file_io::output;

void file_io::read(void){

        cout << "Enter the name of the file to read from: ";
        cin >> inputfilename;

        ifstream inputfile(inputfilename.c_str());
        
        if(!inputfile.is_open()){
                throw(Error_Code::BAD_FILENAME);
        }
        else{
                //ignore the header row in input text file
                inputfile.ignore(MAX_BUFFER,NEWLINE);
                while(true){
                        if(inputfile.eof()){
                                break;
                        }
                        inputfile.getline(&buffer[0],MAX_BUFFER,NEWLINE);
                        if(buffer.data() == NULL_STRING){
                                continue;
                        }
                        input.push_back(buffer);
                }
                inputfile.close();
        }

        return;
}

void file_io::write(){

                ofstream file_handle;
                outputfilename = OUTPUT_FILE;

                file_handle.open(outputfilename, OUTPUT_MODE);
                
                if(!file_handle.is_open()){
                       throw(Error_Code::BAD_FILE_WRITE);
                }
                for(auto s : output){
                        file_handle << s;
                        file_handle << NEWLINE;
                }
                file_handle.close();

        return;
}
