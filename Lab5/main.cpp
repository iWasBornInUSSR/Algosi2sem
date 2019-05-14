#include <iostream>
#include <vector>
#include "source/newHash.hpp"

using namespace std;

// TODO: shared_ptr<> vs common ptr?
//  --указатель на лист или на элемент?
//  -- new copy constructor
//  -- недостаток способа - если в хэш - таблице на ключ приходиться больше 1 разного значения, то не работает
//  -- открытая адресация??
//  -- problem with copy constructor and =
int main() {
    HashMap A, C;
    A.add({1, 2, 3, 5, 2, 3, 12, 5, 16, 1, 7, 3, 1, 5, 3, 71, 2, 3, 4, 2, 6, 2, 3});
    C.add({2, 3});
    HashMap B(A);
    A = A & C;
    A.printSequence();
    B.printSequence();
}