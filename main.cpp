#include <iostream>

#include "BinaryTreeNode/bintree.h"
#include "Bag/bag6.h"
#include "BalancedTrees/set.h"

void testBag()
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
    std::cout << "========================================" << std::endl;

    int target = 10;
    std::cout << "count(" << target << ") = " << myBag3.count(target) << std::endl;
    target = 3;
    std::cout << "count(" << target << ") = " << myBag3.count(target) << std::endl;
    target = 53;
    std::cout << "count(" << target << ") = " << myBag3.count(target) << std::endl;
    std::cout << "========================================" << std::endl;

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
    std::cout << "========================================" << std::endl;

    target = 53;
    std::cout << "erase(" << target << ") = " << myBag3.erase(target) << std::endl;
    myBag3.printBag();
    std::cout << "========================================" << std::endl;

    main_savitch_10::bag<int> myBagSum;
    myBagSum = myBag2 + myBag3;
    myBagSum.printBag();
    std::cout << "========================================" << std::endl;

    myBag += myBag;
    myBag.printBag();
}

void testSet()
{
    main_savitch_11::set<int> mySet;
    mySet.insert(4);
    mySet.insert(17);
    mySet.insert(6);
    mySet.insert(12);
    mySet.insert(19);
    mySet.insert(22);
    
    mySet.insert(18);
    mySet.printData();
}

int main()
{
    //testBag();
    testSet();
    return 0;
}