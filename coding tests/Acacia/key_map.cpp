#include "key_map.h"

key_map::key_map(){

 initialize_matrix();

}

void key_map::initialize_matrix(){

 matrix['A'].insert('H');
 matrix['A'].insert('L');

 matrix['B'].insert('I');
 matrix['B'].insert('K');
 matrix['B'].insert('M');

 matrix['C'].insert('F');
 matrix['C'].insert('J');
 matrix['C'].insert('L');
 matrix['C'].insert('N');

 matrix['D'].insert('G');
 matrix['D'].insert('M');
 matrix['D'].insert('O');

 matrix['E'].insert('H');
 matrix['E'].insert('N');

 matrix['F'].insert('1');
 matrix['F'].insert('C');
 matrix['F'].insert('M');

 matrix['G'].insert('2');
 matrix['G'].insert('D');
 matrix['G'].insert('N');

 matrix['H'].insert('1');
 matrix['H'].insert('3');
 matrix['H'].insert('K');
 matrix['H'].insert('O');

 matrix['I'].insert('2');
 matrix['I'].insert('B');
 matrix['I'].insert('L');

 matrix['J'].insert('3');
 matrix['J'].insert('C');
 matrix['J'].insert('M');

 matrix['K'].insert('2');
 matrix['K'].insert('B');
 matrix['K'].insert('H');

 matrix['L'].insert('3');
 matrix['L'].insert('A');
 matrix['L'].insert('C');
 matrix['L'].insert('I');

 matrix['M'].insert('B');
 matrix['M'].insert('D');
 matrix['M'].insert('F');
 matrix['M'].insert('J');

 matrix['N'].insert('1');
 matrix['N'].insert('C');
 matrix['N'].insert('E');
 matrix['N'].insert('G');

 matrix['O'].insert('2');
 matrix['O'].insert('D');
 matrix['O'].insert('H');

 matrix['1'].insert('H');
 matrix['1'].insert('N');

 matrix['2'].insert('G');
 matrix['2'].insert('I');

 matrix['3'].insert('H');
 matrix['3'].insert('L');

}
