
#ifndef CODE_HPP
#define CODE_HPP
#include <iostream>
#include <string>
#include <vector>
#include<bitset>
#include<cassert>
using std::string;
using std::vector;
using std::to_string;
using std::bitset;
using std::cout;
using std::endl;

#define LINE (cout << "At line " << __LINE__ << endl);

class addNums{
    public:
        addNums(string&, string&);
        ~addNums();
        void print_sum();
    private:
        string& num1;
        string& num2;
        vector<char> sum;
    private:
        //string to store
        //the difference
        //in the case of 
        //two numbers with
        //unequal decimal
        //positions
        string diff_string;
        int carry;
};

addNums::addNums(string& a, string& b):num1(a), num2(b){

    string::reverse_iterator iter1 = num1.rbegin();
    string::reverse_iterator iter2 = num2.rbegin();

    auto count = 0;

    //denotes whether the two
    //nummbers are unequal in
    //their number of decimal
    //positions, and if so
    //which is the larger of
    //the two numbers
    bitset<2> flag_larger_num;

    auto sz  = (num1.size() == num2.size()) 
        ?
        (
         flag_larger_num.reset(0),
         flag_larger_num.reset(1),
         num1.size()
        )
        :
        (num1.size() < num2.size())
        ?
        (
        flag_larger_num.set(1),
        flag_larger_num.reset(0),
        num1.size() 
        )
        : 
        (
        flag_larger_num.set(0),
        flag_larger_num.reset(1),
        num2.size()
        );

    if(1 == flag_larger_num.to_ulong()){

        //LINE

        string reverse_num1;

        auto rev_iter_num1 =  num1.crbegin();

        while(rev_iter_num1 != num1.crend()){
            reverse_num1.push_back(*rev_iter_num1);
            ++rev_iter_num1;
        }
        

        //for(auto i = sz; i < num1.size(); ++i){

            //diff_string.push_back(num1[i]);
        //}

        for(auto i = sz; i < num1.size(); ++i){

            diff_string.push_back(reverse_num1[i]);
        }

        //LINE
        //cout << "diff_string:" << diff_string << endl;

    }
    else if(2 == flag_larger_num.to_ulong()){

        //LINE

        string reverse_num2;

        auto rev_iter_num2 =  num2.crbegin();

        while(rev_iter_num2 != num2.crend()){

            reverse_num2 += *rev_iter_num2;
            ++rev_iter_num2;
        }

        //for(auto i = sz; i < num2.size(); ++i){

            //diff_string.push_back(num2[i]);
        //}

        for(auto i = sz; i < num2.size(); ++i){

            diff_string.push_back(reverse_num2[i]);
        }

        //LINE
        //cout << "diff_string:" << diff_string << endl;

    }

    do{
        //LINE
        
        switch(count){
            default:
                {
                    //LINE
                    auto s = to_string( (*iter1 - '0') + (*iter2 - '0') + carry );
                    if(2 == s.size()){
                       carry = s[0] - '0'; 
                    }
                    else{
                          carry = 0;
                    }
                    sum.push_back(s[s.size() - 1]);

                    ++iter1;
                    ++iter2;
                    break;
                }//end of default:

                //LINE
        }//end of switch()

        //LINE
        
    }while(++count < sz);

    //LINE
}

addNums::~addNums(){ }

void addNums::print_sum(){

    //LINE

        //cout << "diff_string:" << diff_string << endl;
        //cout << "carry:" << carry << endl;
        //cout << "sum.size():" << sum.size() << endl;

    //lambda defintion

    auto print = [&] (vector<char>& v, string& diff_string, int carry){

        //LINE

        string s1, s2, result;

        auto crIter = v.crbegin();

        do{
            s1 += *crIter;

        }while(++crIter != v.crend());

        //any remaining carry has to be 
        //acoounted for here

        if(carry){

            //LINE
            //cout << "carry:" << carry << endl;

            string tmp_string;

            //diff_string is already reversed
            //due to push_back(),
            //i.e., 12 would come across as
            //21
            //so we can read diff_string in
            //its natural order

            //cout << "diff_string:" << diff_string << endl;

            string::iterator It = diff_string.begin();

            auto count = 0;

            do{

                //LINE

                //cout << "count:" << count << endl;
                //cout << "*It:" << *It << endl;
                //cout << "carry:" << carry << endl;
                
                auto s = to_string((*It - '0') + carry);

                //cout << "s:" << s << endl;
                if(2 == s.size()){
                    //LINE
                    carry = s[0] - '0';
                    tmp_string.push_back(s[1]);
                }
                else{
                    //LINE
                    tmp_string.push_back(s[0]);
                    carry = 0;
                }

                //cout << "tmp_string:" << tmp_string << endl;

                ++count;

                //LINE

            }while(carry 
                    &&
                    ++It != diff_string.end()
                  );

            //cout << "tmp_string:" << tmp_string << endl;

            //LINE

            //here we need to accout for
            //the possibility that tmp_string
            //represents fewer decimal positions
            //than diff_string
            //note that diff_string is reversed
            //whereas tmp_string does undo this
            //reversion during its formation
            //so the following code to be 
            //written in accordance with that logic

            string rev_diff_string;
            It = diff_string.begin(); 

            //LINE

            while(It != diff_string.end()){

                    rev_diff_string.push_back(*It);
                    ++It;
            }

            //LINE

            diff_string = rev_diff_string;

            diff_string.replace(0, tmp_string.size(), tmp_string);

            //push back any remaning carry
            //to diff_string
            if(carry){
                //LINE
                //can do a (char)int conversion
                //safely since the value of carry
                //would always be 1

                //cout << "carry:" << carry << endl;

                auto s = to_string(carry);

                //cout << "s:" << s << endl;


                //diff_string.push_back((char)carry);
                //diff_string.push_back(static_cast<char>(carry));
                diff_string.push_back(s[0]);
                
                carry = 0;

                //cout << "diff_string:" << diff_string << endl;
            }

        }


        crIter = diff_string.crbegin();

        do{
            if(crIter == diff_string.crend()){
                break;
            }
            s2 += *crIter;

        }while(++crIter != diff_string.crend());

        result = s2 + s1;

        cout << "The sum of the two numbers is ";
        cout << result;
        cout << endl;
    };

    print(sum, diff_string, carry);

    //LINE
}

#endif
