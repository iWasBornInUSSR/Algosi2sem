//
// Created by Nick on 04.03.2019.
//
#include <list>
#include <vector>
#include <cstdio>
#include <iostream>
#include <random>

using namespace std;
#ifndef LAB2_HASH_H
#define LAB2_HASH_H
std::random_device dev;
std::mt19937 engine(dev());
class no_element_exception  : public exception{
};
class HashMap{

public:
    ///sort list????
    typedef unsigned short hashtype;
    HashMap() {
        table.resize(m);
        A = '0';
    }
    explicit HashMap(char i) : A(i) {
        table.resize(m);
        std::uniform_int_distribution<hashtype> uid(0, 101);
        for (int j = 0; j < m; ++j) {
          if(engine() % 3 == 1)  add(uid(engine));
        }
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

    HashMap operator^(const HashMap &B) const { return (~(*this & B) & (*this | B));};

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
    char A;
};
void HashMap::printTable() {

    printf("HashMap %c:\n",A);
        hashtype p = 0;
        for(auto & i : table){
            p++;
            if(!i.empty()){
            printf("key - %2d = {",p);
            for(auto j : i) {
                printf("%4d", j);
            }
            printf("  }\n");
            }
        }
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
HashMap HashMap::operator|(const HashMap &B) const {
    // if this == B return C(*this)
    HashMap C(*this);
    bool flag;
    for (hashtype i = 0; i < m; ++i) {
        if(table.at(i) != B.table.at(i)) {
            for (auto c : B.table.at(i)) {
                flag = true;
                for (auto d : this->table.at(i)) {
                    if (c == d) {
                    flag = false;
                        break;
                    }
                }
                if(flag) C.add(c);
            }
        }
    }
    return C;
}
HashMap HashMap::operator&(const HashMap &B) const {
    HashMap C;
    bool flag;
    for (hashtype i = 0; i < m; ++i) {
            for (auto c : B.table.at(i)) {
                flag = false;
                for (auto d : this->table.at(i)) {
                    if (c == d) {
                        flag = true;
                        break;
                    }
                }
                if(flag) C.add(c);
            }
    }
    return C;
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
#endif //LAB2_HASH_H
