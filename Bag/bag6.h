// FILE: bag6.h (part of the namespace main_savitch_10)
// TEMPLATE CLASS PROVIDED: bag<Item> (a container template class for a collection of items)
//
//
// TYPEDEFS for the bag<Item> class:
//  bag<Item>::value_type
//      bag<Item>::value_type is the data type of the items in the bag. It may be any of the
//      C++ built-in types (int, char, etc.), or a class with a default constructor, a copy
//      constructor, an assignment operator, and a less-than operator forming a strict
//      weak ordering.
//
//  bag<Item>::size_type
//      bag<Item>::size_type is the data type of any variable that keeps track of how many
//      items are in a bag.
//
// CONSTRUCTOR for the bag<Item> class:
//  bag( )
//      Postcondition: The bag is empty.
//
// MODIFICATION MEMBER FUNCTIONS for the bag<Item> class:
//  size_type erase(const Item& target)
//      Postcondition: All copies of target have been removed from the bag. The return value
//      is the number of copies removed (which could be zero).
//
//  bool erase_one(const Item& target)
//      Postcondition: If target was in the bag, then one copy of target has been removed from
//      the bag; otherwise the bag is unchanged. A true return value indicates that one copy
//      was removed; false indicates that nothing was removed.
//
//  void insert(const Item& entry)
//      Postcondition: A new copy of entry has been inserted into the bag.
//
//  void operator +=(const bag& addend)
//      Postcondition: Each item in addend has been added to this bag.
//
// CONSTANT MEMBER FUNCTIONS for the bag<Item> class:
//  size_type size( ) const
//      Postcondition: Return value is the total number of items in the bag.
//
//  size_type count(const Item& target) const
//      Postcondition: Return value is number of times target is in the bag.
//
// NONMEMBER FUNCTIONS for the bag class:
//  bag operator +(const bag& b1, const bag& b2)
//      Postcondition: The bag returned is the union of b1 and b2.
//
// VALUE SEMANTICS for the bag class:
//  Assignments and the copy constructor may be used with bag objects.
// DYNAMIC MEMORY USAGE by the bag:
//  If there is insufficient dynamic memory, then the following functions throw bad_alloc:
//  the constructors, insert, operator +=, operator +, and the assignment operator.
#ifndef BAG6_H
#define BAG6_H

#include <iostream>
#include <cstdlib>

#include "bintree.h"

namespace main_savitch_10
{
    template <typename Item>
    class bag
    {
    public:
        // 별칭 선언
        using size_type = std::size_t;
        using value_type = Item;

        // 생성자 및 소멸자
        bag()
        {
            std::cout << "constructor called!" << std::endl;
            root_ptr = nullptr;
        }

        bag(const bag &source)
        {
            std::cout << "copy constructor called!" << std::endl;
            root_ptr = tree_copy(source.root_ptr);
        }

        ~bag()
        {
            std::cout << "destructor called!" << std::endl;
            tree_clear(root_ptr);
        }

        // 수정(MODIFICATION)을 위한 멤버 함수
        size_type erase(const Item &target)
        {
        }

        bool erase_one(const Item &target)
        {
        }

        void insert(const Item &entry)
        {
            binary_tree_node<Item> *cursor = nullptr;

            if (root_ptr == nullptr)
            {
                root_ptr = new binary_tree_node<Item>(entry);
                return;
            }
            else
            {
                cursor = root_ptr;
                while (1)
                {
                    if (cursor->data() >= entry)
                    {
                        if (cursor->left() == nullptr)
                        {
                            cursor->left() = new binary_tree_node<Item>(entry);
                            break;
                        }
                        else
                        {
                            cursor = cursor->left();
                            continue;
                        }
                    }
                    else
                    {
                        if (cursor->right() == nullptr)
                        {
                            cursor->right() = new binary_tree_node<Item>(entry);
                            break;
                        }
                        else
                        {
                            cursor = cursor->right();
                            continue;
                        }
                    }
                }
            }
        }

        void operator+=(const bag &addend)
        {
        }

        void operator=(const bag &source)
        {
            std::cout << "operator= called!" << std::endl;
            if (root_ptr == source.root_ptr)
                return;

            tree_clear(root_ptr);
            root_ptr = tree_copy(source.root_ptr);
        }

        // 상수(CONST) 멤버 함수
        size_type size() const
        {
            return tree_size(root_ptr);
        }

        size_type count(const Item &target) const
        {
        }

    private:
        binary_tree_node<Item> *root_ptr; // 이진 탐색 트리의 root pointer
    };

    // bag<Item>클래스에서 활용되는 비멤버 함수
    template <typename Item>
    bag<Item> operator+(const bag<Item> &b1, const bag<Item> &b2)
    {
    }
}

#endif