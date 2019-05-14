#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <ctime>
#include "source/UltimateClass.hpp"
#include "source/newSet.hpp"
using namespace std;
unsigned coolIterSet::code_name = 0;
int main() {
    srand(time(0));
    coolIterSet A(100), B(100), C(100), D(100), E(100);
    for (long j = 1000; j < 100001; j = j * 10) {
        auto begin = clock();
        for (int i = 0; i < j; ++i) {
            coolIterSet F = (A / B / C) ^ D | E;
            F.contact(A).contact(B);
            F.mul(2);
            F.excl(A).excl(B);
        }
        auto end = clock();
        cout << "Time  = " << end - begin << "Numb:" << j << endl;
    }
    A.showSet();
    cout << endl;
    B.showSet();
    cout << endl;
    C.showSet();
    cout << endl;
    D.showSet();
    cout << endl;
    E.showSet();
    cout << endl;
}