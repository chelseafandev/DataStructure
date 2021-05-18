#include <iostream>

#include "BinaryTreeNode/bintree.h"
#include "Bag/bag6.h"

int main()
{
    main_savitch_10::bag<int> myBag; // constructor called
    myBag.insert(45);
    myBag.insert(9);
    myBag.insert(3);
    myBag.insert(17);
    myBag.insert(53);
    myBag.insert(53);
    myBag.insert(54);
    myBag.insert(16);
    myBag.insert(52);
    
    main_savitch_10::bag<int> myBag2 = myBag; // copy constructor called
    main_savitch_10::bag<int> myBag3; // constructor called
    myBag3 = myBag; // operator= called
    return 0;
}