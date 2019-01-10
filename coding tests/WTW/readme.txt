This program has been designed in terms of the following three modules:

* file_io module for file input/output
* data module for representation of data in memory
* connector module that bridges the above two modules

The UI is very minimal as can be in the absence of corresponding libraries; the program has been coded and compiled on the Unix-like environment provided by MacOS, and compiled using gcc version 4.2.1:

g++ -ggdb -pedantic-errors -std=c++14 -Wall connector.cpp data.cpp file_io.cpp main.cpp

The input data has been read from the file sample.txt and the output data written to the file output.txt.
