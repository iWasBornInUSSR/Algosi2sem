//
// Created by Nick on 04.03.2019.
//
#include <list>
#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;
#ifndef LAB2_HASH_H
#define LAB2_HASH_H
class no_element_exception  : public exception{
};
class HashMap{

public:
    typedef unsigned short hashtype;
    HashMap() {
        table.resize(m);
    }
    // % constructor with rand gen? %
    void add(hashtype val){
         table.at(hash_function(val)).push_back(val);
     }
    list<hashtype> get(hashtype key){
         return table.at(key);
     }
     void printTable();
    HashMap operator~() const;

    HashMap operator|(const HashMap &B) const;

    HashMap operator&(const HashMap &) const;

    HashMap operator^(const HashMap &) const;

    HashMap &operator=(const HashMap & copy){table = copy.table; return (*this);};
    friend void whatHave(HashMap &e);
private:
    static const hashtype a = 97;
    static const hashtype b = 11;
    static const hashtype capacity = 26;
    static const hashtype m = capacity * 3;
    vector<list<hashtype> > table;
    hashtype hash_function(hashtype x) {
        return (a * x + b) % m;
    }
    hashtype search(hashtype val) const{
        hashtype key = 0;
        bool  flag = true;
        //error if cant find
        for (hashtype i = 0; i < m && flag; ++i){
            for(auto j : table.at(i))
                if(j == val){
                    key = i;
                    flag = false;
                    break;
                }
        }
        if(flag) throw no_element_exception();
        return key;
    }
};
void HashMap::printTable() {

        hashtype p = 0;
        printf("|----------------- %s --|-------------------- %s -----------\n","keys","values");
        for(auto & i : table){
            cout << " " << p++ << ":";
            for(auto j : i){
                cout << "                                 " << j <<endl;
            }
            printf("|----------------------------|----------------------------------\n");
        }
    }
void whatHave(HashMap &e){
    for (HashMap::hashtype i = 0; i < 100; ++i) {
        try {
            e.search(i);
            cout << i << " ";
        }
        catch(no_element_exception&){
        }
    }
    cout << endl;
}
HashMap HashMap::operator~() const {
    HashMap C;
    for (hashtype i = 0; i < 100; ++i) {
        try {
            search(i);
            }
        catch(no_element_exception&){
            C.add(i);
        }
    }
    return C;
}
#endif //LAB2_HASH_H
