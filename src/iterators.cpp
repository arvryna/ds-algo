#include <forward_list>
#include <iostream>

// This code will reverse a forward_list data
// forward_list is build by a singly linked list
template <typename vt>
class reverse_forward_list {
public:
    static void reverse(std::forward_list<vt>& list) {
        if(list.begin() == list.end()){
            return;
        }
        typename std::forward_list<vt>::iterator begin = list.begin();
        size_t counter = 0;
        for(auto i : list){
            list.emplace_front(i);
            if (counter == 0) {
                begin = list.begin();
            }
            counter++;
        }
        list.erase_after(begin, list.end());
    }
};