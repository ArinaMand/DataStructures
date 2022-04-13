#include "pch.h"
#include "mm.h"
#include <iostream>

using namespace lab618;

struct Cube {
    int a;
    double b;
    std::string name;
    Cube() = default;
    Cube(int a, double b, std::string c) {
        a = a;
        b = b;
        name = c;
    };
};

int main() {
    CMemoryManager<Cube> manager = CMemoryManager<Cube>(8, true);
    printf("Manager reated succesfully\n\r");
    Cube* c;
    Cube* c_1 = nullptr;
    Cube* c_2 = nullptr;
    for (int i = 0; i < 10; ++i) {
        c = manager.newObject();
        if (i == 1) { c_1 = c; };
        if (i == 7) { c_2 = c; };
        c = new Cube(i, i*0.03, "name");
    }
    printf("Manager filled succesfully\n\r");
    bool r = manager.deleteObject(c_1);
    if (r == false) {
        printf("failed delete\n\r");
    }
    else{
        printf("deleted 1st succesfully\n\r");
    }
    r = manager.deleteObject(c_2);
    if (r == false) {
        printf("failed 7th delete\n\r");
    }
    else {
        printf("deleted 7th succesfully\n\r");
    }
    manager.clear();
}