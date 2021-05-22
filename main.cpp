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
    //myBag.insert(16);
    //myBag.insert(52);

    main_savitch_10::bag<int> myBag2 = myBag; // copy constructor called
    main_savitch_10::bag<int> myBag3;         // constructor called
    myBag3 = myBag;                           // operator= called

    myBag3.printBag();

    int target = 10;
    std::cout << "count(" << target << ") = " << myBag3.count(target) << std::endl;
    target = 3;
    std::cout << "count(" << target << ") = " << myBag3.count(target) << std::endl;
    target = 53;
    std::cout << "count(" << target << ") = " << myBag3.count(target) << std::endl;

    target = 53;
    if (myBag3.erase_one(target))
    {
        std::cout << "erase_one(" << target << ") is true" << std::endl;
        myBag3.printBag();
    }
    else
    {
        std::cout << "erase_one(" << target << ") is false" << std::endl;
        myBag3.printBag();
    }

    target = 53;
    std::cout << "erase(" << target << ") = " << myBag3.erase(target) << std::endl;
    myBag3.printBag();

    return 0;
}