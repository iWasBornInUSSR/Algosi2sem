#include <iostream>
#include "source/Hash.h"
int main() {
    HashMap A('A'),B('B'),C('C'),D('D'),E('E');
    HashMap F = ((A & ~B) & ~C) ^ D | E;
    A.printTable();
    B.printTable();
    C.printTable();
    D.printTable();
    E.printTable();
    F.printTable();
    return 0;
}