#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include "source/UltimateClass.hpp"

using namespace std;

int main() {
//    newList A = {1, 2,10, 7, 5,6};
//    newList B = {6,5,7, 3,5,1};
//    (A ^ B).showMap();
//    (A | B).showMap();
//    (A & B).showMap();
//    (~A).showMap();
    srand(time(0));
    newList A(100), B(100), C(100), D(100), E(100);
    for (long j = 1000; j < 100001; j = j * 10) {
        auto begin = clock();
        for (int i = 0; i < j; ++i) {
            newList F = (A / B / C) ^ D | E;
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