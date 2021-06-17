#include <iostream>

#include "BinaryTreeNode/bintree.h"
#include "Bag/bag6.h"
#include "BalancedTrees/set.h"
#include "Graph/graph.h"

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
    for (int i = 0; i <= 8; i++)
    {
        mySet.insert(i);
    }
    mySet.insert(10);

    for (int i = 11; i <= 24; i++)
    {
        mySet.insert(i);
    }
    mySet.insert(26);
    mySet.insert(28);
    
    for (int i = 31; i <= 35; i++)
    {
        mySet.insert(i);
    }
    mySet.insert(40);
    mySet.insert(50);
    mySet.insert(51);
    
    main_savitch_11::set<int> mySet2;
    mySet2.insert(4);
    mySet2.insert(17);
    mySet2.insert(6);
    mySet2.insert(12);    
    mySet2.insert(19);
    mySet2.insert(22);
    mySet2.insert(18);

    mySet = mySet2;
    mySet.print();
}


void testGraph()
{
    main_savitch_15::graph<int> myGraph;
    myGraph.add_vertex(0);
    myGraph.add_vertex(1);
    myGraph.add_vertex(2);
    myGraph.add_vertex(3);
    myGraph.add_vertex(4);
    myGraph.add_vertex(5);
    myGraph.add_vertex(6);
    
    myGraph.add_edge(0, 1);
    myGraph.add_edge(0, 4);
    myGraph.add_edge(1, 3);
    myGraph.add_edge(2, 0);
    myGraph.add_edge(3, 5);
    myGraph.add_edge(3, 6);
    myGraph.add_edge(6, 1);

    
}

int main()
{
    //testBag();
    //testSet();
    testGraph();
    return 0;
}