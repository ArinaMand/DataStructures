#include <iostream>
#include "../../list.h"
using namespace lab618;

int main()
{
    struct Cube {
        float side;
        int color;
        Cube(float s, int c) {
            side = s;
            color = c;
        }
    };

    //-------Test Constructors
    CSingleLinkedList<int> list = CSingleLinkedList<int>();
    CSingleLinkedList<std::string> string_list = CSingleLinkedList<std::string>();
    CSingleLinkedList<Cube> cube_list = CSingleLinkedList<Cube>();


    CSingleLinkedList<int>::CIterator iter = CSingleLinkedList<int>::CIterator::CIterator();
    CSingleLinkedList<std::string>::CIterator str_iter = CSingleLinkedList<std::string>::CIterator::CIterator();
    CSingleLinkedList<Cube>::CIterator cube_iter = CSingleLinkedList<Cube>::CIterator::CIterator();

    //CSingleLinkedList<int> dub_list = CSingleLinkedList<int>(iter);
    int data = 10;
    int data2 = 20;
    int data3 = 30;
    int data4 = 40;
    std::string str_data = "hello!";
    Cube cube_data = Cube(1.5, 4);

    //------Test getSize, pushBack, pushFront, popBack

    int int_size = list.getSize();//assert size = 0
    list.pushBack(data);
    int_size = list.getSize(); //assert size = 1
    list.pushBack(data);  //assert getSize==2
    int gotten_data = list.popFront();//assert gotten_data = data
    int_size = list.getSize();//assert size=1
    
    list.pushBack(data3);
    list.pushBack(data2);
    //assert list.popfront = data
    list.pushFront(data4);
    list.pushFront(data2);
    //assert getSize == 4
    gotten_data = list.popFront();
    //assert g_d=data2

    //size=3, list = data2, data3, data, data4

    //--------Testing iterators

    //assert iter.isValid() == false
    iter = list.begin();
    //assert iter.isValid() == true
    gotten_data = iter.getData();
    //assert gd = data2
    gotten_data = *iter;
    //assert gd = data2
    CSingleLinkedList<int>::CIterator dub_iter = list.begin();
    dub_iter++;
    //assert dub_iter->data3
    dub_iter++; // point on data

    CSingleLinkedList<int>::CIterator third_iter = CSingleLinkedList<int>::CIterator::CIterator(dub_iter);
    gotten_data = third_iter.getData(); //assert ==data
    dub_iter++;//point on data4
    third_iter = CSingleLinkedList<int>::CIterator::CIterator(dub_iter.getLeaf());
    //assert third_iter = data4

    // iter->data2, dub_iter->data4, third_iter->data4

    bool are_equal = iter != dub_iter;
    //assert ==true
    dub_iter = iter;
    //assert dub_iter!=iter == false
    dub_iter.setLeaf(third_iter.getLeaf());
    //assert dub_iter.getData() = data4
    iter++;
    dub_iter.setLeaf(iter.getLeaf());
    //assert dub_iter != iter = false
}

