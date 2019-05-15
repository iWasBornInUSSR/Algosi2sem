#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <ctime>
#include "source/UltimateClass.hpp"
#include "source/newSet.hpp"
using namespace std;
unsigned coolIterSet::code_name = 0;
unsigned newList::code_name = 0;
int main() {
    srand(time(0));
/*    newList A(100), B(100), C(100), D(100), E(100);
    for (long j = 1000; j < 100001; j = j * 10) {
        auto begin = clock();
        for (int i = 0; i < j; ++i) {
            newList F = (A / B / C) ^ D | E;
            F.contact(A).contact(B);
            F.mul(2);
            F.excl(A).excl(B);
        }
        auto end = clock();
        cout << "Time  = " << end - begin << "Numb: " << j << endl;
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
    */
    coolIterSet As(10);
    cout << "As:"<<endl;
    As.showSet();
    coolIterSet Bs(10);
    cout << "Bs:"<<endl;
    Bs.showSet();
/*    cout << "/: "<< endl;
    (As / Bs).showSet();
    cout << "^: "<< endl;
    (As ^ Bs).showSet();
    cout << "&: "<< endl;
    (As & Bs).showSet();
    cout << "|: "<< endl;
    (As | Bs).showSet();
    cout << "Seq:" << endl;*/
  /*  cout << "As:"<<endl;
    As.showSeq();
    cout << "Bs:"<<endl;
    Bs.showSeq();*/
    cout << "A contact B: "<< endl;
    As.contact(Bs).showSeq();
    cout << "mul A twice: "<< endl;
    As.mul(2).showSeq();
    cout << "A excl B: "<< endl;
    As.excl(Bs).showSeq();
    newList A(30), B(30), C(30), D(30), E(30);
    A.showSet();
    B.showSet();
    C.showSet();
    D.showSet();
    E.showSet();
    newList F = A / B;
    cout << "0 / 1" << endl;
    F.showSet();
    cout << "0 / 1 / 2" << endl;
    F = F / C;
    F.showSet();
    F = F ^ D;
    cout << "0 / 1 / 2 ^ 3" << endl;
    F.showSet();
    cout << "0 / 1 / 2 ^ 3 | 4" << endl;
    F = F | E;
    F.showSet();


}