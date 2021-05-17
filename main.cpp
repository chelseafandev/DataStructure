#include <iostream>

#include "BinaryTreeNode/bintree.h"

int main()
{
    main_savitch_10::binary_tree_node<int> rootNode(100);
    main_savitch_10::binary_tree_node<int> leftNode(200);
    main_savitch_10::binary_tree_node<int> rightNode(300);
    main_savitch_10::binary_tree_node<int> lastNode(400);

    rootNode.set_left(&leftNode);
    rootNode.set_right(&rightNode);
    leftNode.set_left(&lastNode);

    main_savitch_10::print<int, int>(&rootNode, 0);
    return 0;
}