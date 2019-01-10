                 About the Program Design
                 ------------------------
The notion of a sampler has been assumed to be meaningless, in the absence 
of the notion of a database to extract sample values from. Accordingly,
the constructor for the sampler object would take two arguments, viz.,
the database name in addition to the sampling frequency highlighted in
the problem statement.
The database has been conceived of as a class object, while the sampler has
been conceived of as a template class object. The assumption was that
in a multi-threaded environment, this would enable a unique instance
 of the sampler object being run from a different thread, in order to
extract possibly varied samples from a given database. 
Likewise, a receptacle of utitlity functions has been created in 
another class template object func_objs, which in addition to enabling 
multi-threaded access, also lends extensibility to the notion of
such a utility object.
The try-catch framework has been included as a basic mechanism for 
error recovery, and has not been elaborated on in terms of its 
implementation.

              About the Test Program Design
              -----------------------------
The logic adopted writes a shuffled repository of sequential integers
within a specified custom range, to a database file "DB_file.txt" created 
on the disk.
The test program needs to be run witin the same directory before the 
database sampler program; thus path extended filenames have been 
discouraged for the database file owing to reasons of simplicity.
Even though the test program has been based on integer database, the
database sampler program has been designed to work with database of any
given type.
The source files pertaining to the test program have been distinguished
by means of the "test_" prrefix to the file name. 

             About Program Compilation
             -------------------------
The following command was used to complile and link both the programs:
g++ -ggdb -Wall -std=c++11 <file names>
The program was coded, compiled and tested on macOS High Sierra 
Version 10.13.2. 
