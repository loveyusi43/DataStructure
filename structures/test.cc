#include <iostream>

#include "array_list.hpp"

int main(void) {
    ArrayList<char> letter;
    letter.Insert(0, 'd');
    letter.Insert(0, 'c');
    letter.Insert(0, 'b');
    letter.Insert(0, 'a');

    std::cout << letter.Empty() << std::endl;

    std::cout << letter.Size() << std::endl;

    std::cout << letter.Get(0) << std::endl;
    std::cout << letter.Get(2) << std::endl;
    std::cout << letter.Get(6) << std::endl;
    std::cout << letter.Get(0) << std::endl;

    std::cout << letter.IndexOf('a') << std::endl;
    std::cout << letter.IndexOf('c') << std::endl;
    std::cout << letter.IndexOf('q') << std::endl;

    letter.Erase(0);
    letter.Erase(2);
    letter.Erase(3);

    letter.Insert(0, 'e');
    letter.Insert(2, 'f');
    letter.Insert(3, 'g');
    letter.Insert(4, 'h');
    letter.Insert(6, 'h');
    letter.Insert(-3, 'h');

    return 0;
}