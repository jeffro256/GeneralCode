#include <iostream>

int main() {
    void** a;

    std::cout << "a: " << a << std::endl;

    a = (void**) 10;

    return 0;
} 
