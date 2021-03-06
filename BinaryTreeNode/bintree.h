// FILE: bintree.h (part of the namespace main_savitch_10)
// PROVIDES: A template class for a node in a binary tree and functions for
// manipulating binary trees. The template parameter is the type of data in each node.
//
// TYPEDEF for the binary_tree_node<Item> template class:
// 트리의 노드들은 데이터와 그들의 자식 노드를 가리키는 포인터를 포함하고 있다.
// 데이터의 타입 정보(binary_tree_node<Item>::value_type)는 템플릿 파라미터로 부터 넘어오게 된다.
// 여기서 타입 정보에는 C++의 내장(built-in) 타입(int, char 등)이나 디폴트 생성자와 대입 연산자(=)를 갖는 클래스가 올 수 있다.
//
// CONSTRUCTOR for the binary_tree_node<Item> class:
//  binary_tree_node(
//      const Item& init_data = Item( ),
//      binary_tree_node<Item>* init_left = nullptr,
//      binary_tree_node<Item>* init_right = nullptr
//  )
// Postcondition: 새롭게 생성된 노드는 init_data와 동일한 값을 데이터로 갖게되며,
// 자식 노드의 포인터는 init_left와 init_right와 동일한 값을 갖는다.
//
// MEMBER FUNCTIONS for the binary_tree_node<Item> class:
//  const Item& data( ) const <---- const 버전
//  and
//  Item& data( )             <---- non-const 버전
//      Postcondition: 리턴 값은 binary_tree_node 데이터의 레퍼런스 타입이다.
//
//  const binary_tree_node* left( ) const   <---- const 버전
//  and
//  binary_tree_node* left( )
//  and
//  const binary_tree_node* right( ) const  <---- non-const 버전
//  and
//  binary_tree_node* right( )
//      Postcondition: 리턴 값은 왼쪽 혹은 오른쪽 자식 노드의 포인터다.(자식 노드가 존재하지 않는 다면 NULL값이 될 수 있다.)
//
//  void set_data(const Item& new_data)
//      Postcondition: binary_tree_node는 인자로 넘어온 new data를 포함하게된다.
//
//  void set_left(binary_tree_node* new_link)
//  and
//  void set_right(binary-tree_node* new_link)
//      Postcondition: binary_tree_node는 자식 노드를 가리키는 새로운 링크를 갖게 된다.
//
//  bool is_leaf( )
//      Postcondition: 현재 노드가 leaf 노드라면 true를 반환하고, 그렇지 않다면 false를 반환한다.
//
// NONMEMBER FUNCTIONS to maniplulate binary tree nodes:
//  template <class Process, class BTNode>
//  void inorder(Process f, BTNode* node_ptr)
//      Precondition: node_ptr은 이진 트리 내의 노드를 가리키는 포인터다. (node_ptr이 빈 이진 트리를 가리키는 경우 NULL값이 될 수 있다.)
//      Postcondition: node_ptr이 NULL이 아닌 경우, 함수 f는 *node_ptr의 내용과 그것의 모든 자식 노드에 in-order 순회를 사용하여 적용된다.
//      BTNode는 binary_tree_node 이거나 상수 이진 트리 노드일 수 있다. Process는 Item 타입 1개를 파라미터로 갖고 호출이 되는 함수 f의 타입을 나타낸다.
//
//  template <class Process, class BTNode>
//  void postorder(Process f, BTNode* node_ptr)
//      Same as the in-order function, except with a post-order traversal.
//
//  template <class Process, class BTNode>
//  void preorder(Process f, BTNode* node_ptr)
//      Same as the in-order function, except with a pre-order traversal.
//
//  template <class Item, class SizeType>
//  void print(const binary_tree_node<Item>* node_ptr, SizeType depth)
//      Precondition: node_ptr은 이진 트리 내의 노드를 가리키는 포인터다. (node_ptr이 빈 이진 트리를 가리키는 경우 NULL값이 될 수 있다.)
//      만약 포인터의 값이 NULL이 아니라면, depth는 node_ptr가 가리키는 노드의 depth를 의미한다.
//      Postcondition: *node_ptr과 그것의 모든 자식 노드들은 << operator를 활용한 cout으로 표현된다. 각각의 노드는 그들의 depth의 4배만큼 들여쓰도록 한다.
//
//  template <class Item>
//  void tree_clear(binary_tree_node<Item>*& root_ptr)
//      Precondition: root_ptr은 이진 트리의 root 노드를 가리키는 포인터다. (node_ptr이 빈 이진 트리를 가리키는 경우 NULL값이 될 수 있다.)
//      Postcondition: root 노드와 그 하위에 존재하는 모든 노드는 힙 영역에 반환되고, root_ptr에는 NULL값을 대입한다.
//
//  template <class Item>
//  binary_tree_node<Item>* tree_copy(const binary_tree_node<Item>* root_ptr)
//      Precondition: root_ptr은 이진 트리의 root 노드를 가리키는 포인터다. (node_ptr이 빈 이진 트리를 가리키는 경우 NULL값이 될 수 있다.)
//      Postcondition: 이진 트리의 복사가 이루어지고, 복사본의 root를 가리키는 포인터가 반환된다.
//
//  template <class Item>
//  size_t tree_size(const binary_tree_node<Item>* node_ptr)
//      Precondition: node_ptr은 이진 트리 내의 노드를 가리키는 포인터다. (node_ptr이 빈 이진 트리를 가리키는 경우 NULL값이 될 수 있다.)
//      Postcondition: 트리내에 존재하는 노드의 수를 반환한다.
#ifndef BINTREE_H
#define BINTREE_H

#include <cstdlib>
#include <iomanip>
#include <iostream>

namespace main_savitch_10
{
    template <typename Item>
    class binary_tree_node
    {
    public:
        // 별칭 선언
        using value_type = Item;
        
        binary_tree_node(const Item &init_data = Item(), binary_tree_node *init_left = nullptr, binary_tree_node *init_right = nullptr);

        Item &data();
        binary_tree_node *&left();
        binary_tree_node *&right();
        void set_data(const Item &new_data);
        void set_left(binary_tree_node *new_left);
        void set_right(binary_tree_node *new_right);

        const Item &data() const;
        const binary_tree_node *left() const;
        const binary_tree_node *right() const;
        bool is_leaf() const;
        
    private:
        Item data_field;
        binary_tree_node *left_field;
        binary_tree_node *right_field;
    };

    // binary_tree_node<Item>에서 활용되는 비멤버 함수
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
            delete root_ptr;
            root_ptr = nullptr;
        }
    }

    template <class Item>
    binary_tree_node<Item> *tree_copy(const binary_tree_node<Item> *root_ptr)
    {
        // 1. l_ptr을 왼쪽 서브 트리의 복사본으로 만든다.
        // 2. r_ptr을 오른쪽 서브 트리의 복사본으로 만든다.
        // 3. 새로운 binary_tree_node를 반환한다. (root_ptr->data(), l_ptr, r_ptr)
        binary_tree_node<Item> *l_ptr = nullptr;
        binary_tree_node<Item> *r_ptr = nullptr;

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
#endif

#include "bintree.impl.h"