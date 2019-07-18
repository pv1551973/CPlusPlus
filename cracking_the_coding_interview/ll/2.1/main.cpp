#include "code.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
using std::string;
using std::cout;
using std::endl;
using std::vector;

void load_menu(void);
void rectify_menu (void);
void reverse_menu (void);
void print_menu(void);

list<node<string>>menu;
vector<string>menu_items{"pasta", "cake", "pizza", "soup", "muffin", "chai", "cake", "pie", "croissant", "coffee", "danish"};

int main (void){
    load_menu();
    print_menu();

    rectify_menu();
    print_menu();

    reverse_menu();
    print_menu();

    return 0;
}

void load_menu (void){
    auto num_menu_items = menu_items.size();

for(size_t i = 0; i < num_menu_items; ++i){
    switch(i){
        case 0:
            {
                auto menu_item = make_shared<node<string>>(menu_items[i]);
                menu_item->set_next(NULL);
                menu.set_head(menu_item);
            }
            break;
        default:
            {
                auto menu_item = make_shared<node<string>>(menu_items[i]);
                menu_item->set_next(NULL);

                auto m = menu.get_head();

                while(m->get_next()){
                     m = m->get_next();
                }

                m->set_next(menu_item);
            }
            break;
    }
}

    return;
}

void rectify_menu (void){

    size_t num_menu_items = menu.size(); 
    assert(num_menu_items == menu_items.size()); 
    size_t i = 0;

    do{
        auto item_i = menu[i]->get_data();
        for(size_t j = i + 1; j < num_menu_items; ++ j){
            auto item_j = menu[j]->get_data();
           if(item_i == item_j){
               num_menu_items = menu.remove(j);
           }
       }
    }while(++i <= num_menu_items - 1); 

    return;
}

void print_menu (void){
    auto h = menu.get_head();
    do{
        cout << h->get_data() << endl;
    }while(h = h->get_next());
    cout << endl;

    return;
}

void reverse_menu (void){
    menu.reverse();

    return;
}
