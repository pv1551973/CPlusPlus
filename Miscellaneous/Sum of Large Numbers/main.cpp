
#include "code.hpp"
using std::cin;
using std::endl;

int main (){
    
    string num1, num2;
    cout << "Enter the numbers (double values would be truncated):";
    cin >> num1 >> num2;

    addNums obj(num1,num2);

    obj.print_sum();

    return 0;
}
