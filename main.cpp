#include <iostream>
#include "Morfologia.cpp"

int main() {
    BitmapaExt b(3, 4, 5);
    b(0, 1, 0) = b(0, 2, 2) = b(0, 2, 3) = b(0, 1, 2) = true;
    b(1, 2, 1) = b(1, 2, 2) = b(1, 2, 3) = b(1, 1, 1) = b(2, 1, 2) = true;
    b(2, 2, 1) = b(2, 2, 2) = b(2, 2, 3) = b(2, 1, 1) = true;

    std::cout << "Oryginalna bitmapa:\n" << b << "\n\n";
}