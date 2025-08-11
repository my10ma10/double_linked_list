#include <iostream>
#include "list.hpp"

int main() {
    try {
        // List<int> list;
        // list = std::move(old_list);

        // for (List<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        //     std::cout << *it << std::endl;
            
        // }
        List<int> list = {-4, 4, 1, 0, -3, 18, 5};

        list.sort();
        for (auto it = list.begin(); it != list.end(); ++it) {
            std::cout << *it << std::endl;
        }
        
        list.reverse();        
        for (auto it = list.begin(); it != list.end(); ++it) {
            std::cout << *it << std::endl;
        }
        std::cout << "size = " << list.size() << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << "Exception\n";
        std::cout << ex.what() << std::endl;
    }
    
    return 0;
}