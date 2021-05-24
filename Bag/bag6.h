// FILE: bag6.h (part of the namespace main_savitch_10)
// TEMPLATE CLASS PROVIDED: bag<Item> (a container template class for a collection of items)
//
// TYPEDEFS for the bag<Item> class:
//  bag<Item>::value_type
//      bag<Item>::value_type은 bag내에 존재하는 item의 데이터 타입이다. 이 타입 정보에는 C++의 내장(built-in) 타입(int, char 등)이나
//      디폴트 생성자, 복사 생성자, 대입(=) 연산자, strict weak ordering을 형성하는 less-than(<) 연산자를 갖는 클래스가 올 수 있다.
//  bag<Item>::size_type
//      bag<Item>::size_type은 bag 안에 몇개의 item이 존재하는지를 추적하기 위해 사용하는 다양한 변수들의 타입이다.
//
// CONSTRUCTOR for the bag<Item> class:
//  bag( )
//      Postcondition: bag은 비어 있는 상태이다.
//
// MODIFICATION MEMBER FUNCTIONS for the bag<Item> class:
//  size_type erase(const Item& target)
//      Postcondition: bag에 존재하는 모든 target값이 삭제된다. 반환 값은 삭제된 target의 개수이며 0이 될 수 있다.
//
//  bool erase_one(const Item& target)
//      Postcondition: 만약 bag에 target이 존재한다면 bag에서 하나의 target을 삭제한다. 그렇지 않다면 bag에는 변화가 없다.
//      반환 값 true는 target 하나를 삭제하였다는 것을 의미하고 false는 삭제한게 없다는 것을 의미힌다.
//
//  void insert(const Item& entry)
//      Postcondition: bag에 새로운 entry가 추가된다.
//
//  void operator +=(const bag& addend)
//      Postcondition: addend의 각각의 item들이 이 bag에 추가된다.
//
// CONSTANT MEMBER FUNCTIONS for the bag<Item> class:
//  size_type size( ) const
//      Postcondition: 반환 값은 bag에 존재하는 모든 item의 개수이다.
//
//  size_type count(const Item& target) const
//      Postcondition: 반환 값은 bag에 존재하는 target의 개수이다.
//
// NONMEMBER FUNCTIONS for the bag class:
//  bag operator +(const bag& b1, const bag& b2)
//      Postcondition: b1와 b2를 합한 bag을 반환한다.
//
// VALUE SEMANTICS for the bag class:
//  대입과 복사 생성자는 bag 객체에서 사용될 수 있다.
// DYNAMIC MEMORY USAGE by the bag:
//  동적 메모리가 부족한 경우에는 아래 함수들이 bad_alloc 에러를 던질 수 있다.
//  생성자, insert 함수, 합(+=, +) 연산자, 대입(=) 연산자
#ifndef BAG6_H
#define BAG6_H

#include <iostream>
#include <cstdlib>
#include <syslog.h>

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
            syslog(LOG_LOCAL0, "%s", "bag constructor called!");
            root_ptr = nullptr;
        }

        bag(const bag &source)
        {
            syslog(LOG_LOCAL0, "%s", "bag copy constructor called!");
            root_ptr = tree_copy(source.root_ptr);
        }

        ~bag()
        {
            syslog(LOG_LOCAL0, "%s", "bag destructor called!");
            tree_clear(root_ptr);
        }

        // 수정(MODIFICATION)을 위한 멤버 함수
        size_type erase(const Item &target)
        {
            int nRet = 0;

            while (1)
            {
                if (!erase_one(target))
                    break;

                nRet++;
            }

            return nRet;
        }

        bool erase_one(const Item &target)
        {
            return bst_remove(root_ptr, target);
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
            syslog(LOG_LOCAL0, "%s", "bag operator+= called!");
            binary_tree_node<Item> *addroot_ptr;

            if(root_ptr == addend.root_ptr)
            {
                addroot_ptr = tree_copy(addend.root_ptr);
                insert_all(addroot_ptr);
                tree_clear(addroot_ptr);
            }
            else
            {
                insert_all(addend.root_ptr);
            }
        }

        void operator=(const bag &source)
        {
            syslog(LOG_LOCAL0, "%s", "bag operator= called!");
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
            int nRet = 0;
            binary_tree_node<Item> *cursor = root_ptr;
            while (cursor != nullptr)
            {
                if (cursor->data() == target)
                {
                    nRet++;
                    cursor = cursor->left();
                }
                else if (cursor->data() > target)
                {
                    cursor = cursor->left();
                }
                else
                {
                    cursor = cursor->right();
                }
            }

            return nRet;
        }

        void printBag()
        {
            print(root_ptr, 0);
        }

    private:
        binary_tree_node<Item> *root_ptr; // 이진 탐색 트리의 root pointer

        // Precondition: root_ptr은 이진 탐색 트리의 root pointer 이다. (비어있는 트리의 경우 이 값이 NULL이 될 수 있다.)
        // Postcondition: target이 트리에 존재한다면 그 값을 삭제하고, root_ptr은 새로운 (작아진)이진 탐색 트리를 가리킨다.
        // 그리고 함수는 true를 반환한다. 그렇지 않다면, tree에 변화는 없고 함수는 false를 반환한다.
        bool bst_remove(binary_tree_node<Item> *&root_ptr, const Item &target)
        {
            if (root_ptr == nullptr)
            {
                return false;
            }
            else
            {
                if (root_ptr->data() > target)
                {
                    bst_remove(root_ptr->left(), target);
                }
                else if (root_ptr->data() < target)
                {
                    bst_remove(root_ptr->right(), target);
                }
                else
                {
                    if (root_ptr->left() == nullptr)
                    {
                        // 루트 노드에 왼쪽 자식 노드가 존재하지 않는 경우
                        binary_tree_node<Item> *tmp_ptr = root_ptr;
                        root_ptr = root_ptr->right();
                        delete tmp_ptr;
                        return true;
                    }
                    else
                    {
                        // 루트 노드에 왼쪽 자식 노드가 존재하는 경우(왼쪽 서브 트리에서 가장 큰 값을 찾아서 그 값을 루트 노드로 올림)
                        Item swapData;
                        bst_remove_max(root_ptr->left(), swapData);
                        root_ptr->set_data(swapData);
                        return true;
                    }
                }
            }
        }

        // Precondition: root_ptr은 비어있지 않은 이진 탐색 트리의 root pointer 이다.
        // Postcondition: 이진 탐색 트리의 가장 큰 값이 제거되고, root_ptr은 새로운 (작아진)이진 탐색 트리를 가리킨다.
        // reference 타입인 인자 removed는 삭제되는 값으로 설정한다.
        void bst_remove_max(binary_tree_node<Item> *&root_ptr, Item &removed)
        {
            if (root_ptr->right() == nullptr)
            {
                // 오른쪽 자식 노드가 없는 경우에는 루트 노드가 가장 큰 노드이다
                removed = root_ptr->data();
                binary_tree_node<Item> *tmp_ptr = root_ptr;
                root_ptr = root_ptr->left();
                delete tmp_ptr;
            }
            else
            {
                // 오른쪽 자식 노드가 있는 경우에는 오른쪽 서브 트리를 기준으로 다시 가장 큰 값을 찾는다
                bst_remove_max(root_ptr->right(), removed);
            }
        }

        // Precondition: addroot_ptr은 이 메소드를 활성화한 bag객체의 이진 탐색 트리로부터 분리된 이진 탐색 트리의 root pointer이다.
        // Postcondition: addroot_ptr의 이진 탐색 트리에 존재하는 모든 item은 이 메소드를 활성화한 bag객체의 이진 탐색 트리에 추가된다.
        void insert_all(const binary_tree_node<Item> *addroot_ptr)
        {
            // pre-order나 post-order를 사용하라(in-order는 Unbalanced Tree를 발생시킴)
            if(addroot_ptr != nullptr)
            {
                insert(addroot_ptr->data());
                insert_all(addroot_ptr->left());
                insert_all(addroot_ptr->right());
            }
        }
    };

    // bag<Item>클래스에서 활용되는 비멤버 함수
    template <typename Item>
    bag<Item> operator+(const bag<Item> &b1, const bag<Item> &b2)
    {
        syslog(LOG_LOCAL0, "%s", "bag operator+ called!");
        bag<Item> result = b1;
        result += b2;
        return result;
    }
}

#endif