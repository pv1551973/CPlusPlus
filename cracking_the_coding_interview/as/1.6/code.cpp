#include <string>
#include <array>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using std::string;
using std::to_string;
using std::array;
using std::vector;
using std::rand;
using std::cout;
using std::endl;
using std::for_each;

#define NUM_ROWS 5
#define NUM_COLS 5
#define NUM_BYTES_PER_PIXEL 4

#define DBG_TRACE cout << "At line " << __LINE__ << endl;


void set_matrix(vector<array<string, NUM_COLS>>&);
void rotate_90deg_matrix(vector<array<string, NUM_COLS>>&);
void display_matrix(vector<array<string, NUM_COLS>>&);
int generate_random_num_in_range(int, int);

int main (void){
	vector<array<string, NUM_COLS>>matrix(NUM_ROWS);

	set_matrix(matrix);
	display_matrix(matrix);

	rotate_90deg_matrix(matrix);
	display_matrix(matrix);

	return 0;
}

void set_matrix(vector<array<string, NUM_COLS>>& matrix){


	auto row = 0;

	while(row < NUM_ROWS){
		auto col = 0;
		while(col < NUM_COLS){
			string pixel;
			int min = 0;
			int max = 100;
		        for(auto i = 0; i < NUM_BYTES_PER_PIXEL; ++i){
				auto rand_num = generate_random_num_in_range(min, max);
				pixel += to_string(rand_num);
			}	
			matrix[row].at(col) = pixel;
			++col;
		}
		++row;
	}


	return;
}

void rotate_90deg_matrix(vector<array<string, NUM_COLS>>& matrix){

	array<string, NUM_COLS>new_row;
	auto orig_sz = matrix.size();
	auto col_num = 0;
	do{
		auto row_num = orig_sz - 1; 
		auto i = 0;
		while(row_num >= 0 && i < NUM_COLS){
			auto iter = matrix.begin() + row_num;
			new_row[i] = (*iter)[col_num];//NXN matrix
			++i;
			--row_num;
		}
		matrix.push_back(new_row);
	}while(++col_num < NUM_COLS);
	auto iter = matrix.begin();
	size_t i = 0;
	while(i < orig_sz){
		matrix.erase(iter);
		++i;
	}

	return;
}

 void display_matrix(vector<array<string, NUM_COLS>>& matrix){
 	auto row_count = 0;
	 for_each(matrix.begin(), matrix.end(), 
			 [&](array<string, NUM_COLS>& a){
			 	for_each(a.begin(), a.end(), 
						[&](string& s){
							cout << s << " ";
						}
					);
				cout << endl;
				++row_count;
			 }
		 );
	 cout << "============================================="<< endl;	
	 return;
 }

int generate_random_num_in_range(int min, int max){

	return (min + (rand() % (max - min + 1)));
}

