//
// Created by Admin on 05.05.2019.
//

#ifndef LAB5_NEWHASH_HPP
#define LAB5_NEWHASH_HPP

#include <list>
#include <vector>
#include <cstdio>
#include <iostream>
#include <random>
#include <bits/unique_ptr.h>
#include <memory>

using namespace std;

class HashMap {

public:
    typedef unsigned short hashtype;
    typedef vector<list < hashtype> *>
    ptr_list_type;
    HashMap() {
        table.resize(m);
        A = '0';
    }

    explicit HashMap(char i) : A(i) {
        table.resize(m);
        for (hashtype j = 0; j < m; ++j) {
            if (rand() % 2) add(j);
        }
    }

    void add(hashtype val) {
        table.at(hash_function(val)).push_back(val);
        ptr_table.push_back(&table.at(hash_function(val)));
    }

    void add(initializer_list<hashtype> vals) {
        for (auto &i : vals) {
            add(i);
        }
    }

    list<hashtype> get(hashtype key) {
        return table.at(key);
    }

    void printTable();

    void printSequence();

    HashMap operator~() const;

    HashMap operator|(const HashMap &B) const;

    HashMap operator&(const HashMap &) const;

    HashMap operator^(const HashMap &B) const { return (~(*this & B) & (*this | B)); };

    HashMap &operator=(const HashMap &copy) {
        table = copy.table;
        ptr_table = copy.ptr_table;
        return (*this);
    };

    HashMap &concat(HashMap &B);

    HashMap &mul(unsigned int n);

    HashMap &excl(HashMap &);

    friend void whatHave(HashMap &e);

private:
    static const hashtype a = 97;
    static const hashtype b = 11;
    static const hashtype capacity = 26;
    static const hashtype m = capacity * 3;
    static const hashtype MAXINT = 100;
    vector<list<hashtype> > table;
    ptr_list_type ptr_table;

    static hashtype hash_function(hashtype x) {
        return (a * x + b) % m;
    }

    char A;
};

void HashMap::printTable() {

    printf("HashMap %c:\n", A);
    hashtype p = 0;
    for (auto &i : table) {
        p++;
        if (!i.empty()) {
            printf("key - %2d = {", p);
            for (auto j : i) {
                printf("%4d", j);
            }
            printf("  }\n");
        }
    }
}

HashMap HashMap::operator~() const {
    HashMap C;
    for (hashtype i = 0; i < MAXINT; ++i) {
        if (table.at(hash_function(i)).empty())
            C.add(i);
        else {
            bool flag = true;
            for (auto a = table.at(hash_function(i)).begin(); a != table.at(hash_function(i)).end() && flag; a++)
                if (*a == i) flag = false;
            if (flag) C.add(i);
        }
    }


    return C;
}

HashMap HashMap::operator|(const HashMap &B) const {
    // if this == B return C(*this)
    HashMap C(*this);
    bool flag;
    for (hashtype i = 0; i < m; ++i) {
        if (!table.at(i).empty()) {
            for (auto c : B.table.at(i)) {
                flag = true;
                for (auto d : this->table.at(i)) {
                    if (c == d) {
                        flag = false;
                        break;
                    }
                }
                if (flag) C.add(c);
            }
        } else C.table.at(i) = B.table.at(i);
    }
    return C;
}

HashMap HashMap::operator&(const HashMap &B) const {
    HashMap C;
    bool flag;
    for (hashtype i = 0; i < m; ++i) {
        if (!table.at(i).empty() && !B.table.at(i).empty()) {
            for (auto c : B.table.at(i)) {
                flag = false;
                for (auto d : table.at(i)) {
                    if (c == d) {
                        flag = true;
                        break;
                    }
                }
                if (flag) C.add(c);
            }
        }
    }
    return C;
}

void whatHave(HashMap &e) {
    for (HashMap::hashtype i = 0; i < HashMap::m; ++i)
        for (unsigned short &a : e.table.at(i))
            cout << a << " ";
    cout << endl;
}

void HashMap::printSequence() {
    for (auto i = ptr_table.cbegin(); i != ptr_table.cend(); ++i) {
        cout << i.operator*()->front() << " ";
    }
    cout << endl;
}

HashMap &HashMap::concat(HashMap &B) {
    for (auto i : B.ptr_table) {
        add(i->front());
    }
    return *this;
}

HashMap &HashMap::mul(unsigned int n) {

    for (int j = 0; j < n; ++j) {
        for (auto i : ptr_table) {
            add(i->front());
        }
    }
    return *this;
}

HashMap &HashMap::excl(HashMap &B) {
    // экономия времени на обращение???
    // запихать значения в вектор?
    const ptr_list_type ptr_vector_cpy(ptr_table);
    int deletionTimes = 0;
    unsigned long size = ptr_vector_cpy.size() - B.ptr_table.size();
    for (unsigned long i = 0; i < size + 1; ++i) {
        bool flag = true;
        for (unsigned long j = 0; j < B.ptr_table.size(); ++j) {
            if (ptr_vector_cpy.at(i + j)->front() != B.ptr_table.at(j)->front()) {
                flag = false;
                break;
            }
        }
        if (flag) {
            // deleting from Map
            for (auto c : B.ptr_table) {
                table.at(hash_function(c->front())).erase(table.at(hash_function(c->front())).begin());
            }
            ptr_table.erase(ptr_table.cbegin() + i - B.ptr_table.size() * deletionTimes, ptr_table.cbegin()
                                                                                         + i + B.ptr_table.size() -
                                                                                         B.ptr_table.size() *
                                                                                         deletionTimes); // subtract B.ptr_table.size() * deletionTimes
            // becouse ptr_table size less than its copy
            deletionTimes++;
            i = i + B.ptr_table.size() - 1;
        }
    }
    return *this;
}

#endif //LAB5_NEWHASH_HPP
