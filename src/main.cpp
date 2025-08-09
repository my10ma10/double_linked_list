#include <iostream>
#include "list.hpp"

int main() {
    try {
        List<int> list = {1, 2, -2, 4, 0, -6};
        // List<int> list;
        // list = std::move(old_list);

        // for (List<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        //     std::cout << *it << std::endl;
            
        // }
        list.pop_back();
        list.pop_back();
        list.push_back(2);
        
        for (auto it = list.begin(); it != list.end(); ++it) {
            std::cout << *it << std::endl;
        }
        std::cout << "size = " << list.size() << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    
    return 0;
}