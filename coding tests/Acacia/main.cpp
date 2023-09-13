#include "key_board.h"
#include "key_board_checker.h"

int main (){
 auto const& kbr = key_board::get_instance();
 key_board_checker kbc(kbr);
 return 0;
}
