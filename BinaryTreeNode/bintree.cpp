#include <iostream>
#include <iomanip>

#include "bintree.h"

namespace main_savitch_10
{
    template <typename Process, typename BTNode>
    void inorder(Process f, BTNode *node_ptr)
    {
        if (node_ptr != nullptr)
        {
            inorder(f, node_ptr->left());
            f(node_ptr->data());
            inorder(f, node_ptr->right());
        }
    }

    template <typename Process, typename BTNode>
    void postorder(Process f, BTNode *node_ptr)
    {
        if (node_ptr != nullptr)
        {
            postorder(f, node_ptr->left());
            postorder(f, node_ptr->right());
            f(node_ptr->data());
        }
    }

    template <typename Process, typename BTNode>
    void preorder(Process f, BTNode *node_ptr)
    {
        if (node_ptr != nullptr)
        {
            f(node_ptr->data());
            preorder(f, node_ptr->left());
            preorder(f, node_ptr->right());
        }
    }

    template <typename Item, typename SizeType>
    void print(const binary_tree_node<Item> *node_ptr, SizeType depth)
    {
        std::cout << std::setw(4 * depth) << "";
        if (node_ptr == nullptr)
        {
            std::cout << "[Empty]" << std::endl;
        }
        else if (node_ptr->is_leaf())
        {
            std::cout << node_ptr->data();
            std::cout << " [leaf]" << std::endl;
        }
        else
        {
            std::cout << node_ptr->data() << std::endl;
            print(node_ptr->right(), depth + 1);
            print(node_ptr->left(), depth + 1);
        }
    }

    template <typename Item>
    std::size_t tree_size(const binary_tree_node<Item> *node_ptr)
    {
        if (node_ptr == nullptr)
            return 0;
        else
            return 1 + tree_size(node_ptr->left()) + tree_size(node_ptr->right());
    }

    template <class Item>
    void tree_clear(binary_tree_node<Item> *&root_ptr)
    {
        // 1. 왼쪽 서브 트리의 모든 노드들을 힙 영역으로 반환
        // 2. 오른쪽 서브 트리의 모든 노드들을 힙 영역으로 반환
        // 3. 루트 노드를 힙 영역으로 반환
        // 4. root_ptr을 NULL로 변경
        binary_tree_node<Item> *child;
        if (root_ptr != nullptr)
        {
            child = root_ptr->left();
            tree_clear(child);
            child = root_ptr->right();
            tree_clear(child);
            root_ptr = nullptr;
        }
    }

    template <class Item>
    binary_tree_node<Item> *tree_copy(const binary_tree_node<Item> *root_ptr)
    {
        // 1. l_ptr을 왼쪽 서브 트리의 복사본으로 만든다.
        // 2. r_ptr을 오른쪽 서브 트리의 복사본으로 만든다.
        // 3. 새로운 binary_tree_node를 반환한다. (root_ptr->data(), l_ptr, r_ptr)
        binary_tree_node<Item> *l_ptr, r_ptr;

        if (root_ptr == nullptr)
        {
            return nullptr;
        }
        else
        {
            l_ptr = tree_copy(root_ptr->left());
            r_ptr = tree_copy(root_ptr->right());
            return new binary_tree_node<Item>(root_ptr->data(), l_ptr, r_ptr);
        }
    }
}