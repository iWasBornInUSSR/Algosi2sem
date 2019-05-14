#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <unordered_set>
#include <list>
#include <ctime>
#include "source/UltimateClass.hpp"

using namespace std;
unsigned coolIterSet::code_name = 0;
int main() {
    srand(time(nullptr));
//    coolIterSet As(10);
//    As.showSet();
//    cout << endl;
//    coolIterSet Bs(10);
//    Bs.showSet();
//    cout << endl;
//    (As / Bs).showSet();
//    cout << endl;
//    (~Bs & As).showSet();
//    cout << endl;
//    (As ^ Bs).showSet();
//    cout << endl;
////    (~As).showSet();
////    cout << endl;
//    cout << "Seq" << endl;
//    As.showSeq();
//    Bs.showSeq();
//    As.contact(Bs).showSeq();
//    cout << endl;
//    As.mul(2).showSeq();
//    cout << endl;
//    As.excl(Bs).showSeq();
    /// ~~~~~~~~~~~~~~~~~~
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
    ///~~~~~~~~~~~~~~~~~~~~~~~~~~~
    return 0;
}