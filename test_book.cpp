#include "book.h"
#include <iostream>

int main() {
    Book b("Data Abstraction & Problem Solving with C++", 79.99, 20,
           "978-013292372-9", "Carrano and Henry");
    std::cout << b.displayString() << "\n";
    return 0;
}