// FILE: set.h (part of the namespace main_savitch_11)
// TEMPLATE CLASS PROVIDED: set<Item> (a container template class for a set of items)
//
// TYPEDEFS for the set<Item> class:
//  set<Item>::value_type
//      set<Item>::value_type은 set내에 존재하는 item의 데이터 타입이다. 이 타입 정보에는 C++의 내장(built-in) 타입(int, char 등)이나
//      디폴트 생성자, 복사 생성자, 대입(=) 연산자, strict weak ordering을 형성하는 less-than(<) 연산자를 갖는 클래스가 올 수 있다.
//
// CONSTRUCTOR for the set<Item> class:
//  set()
//      Postcondition: set은 비어있다.
//
// MODIFICATION MEMBER FUNCTIONS for the set<Item> class:
//  void clear()
//      Postcondition: set은 비어있다.
//
//  bool insert(const Item& entry)
//      Postcondition: 만약 set 안에 이미 존재하는 값이 entry라면, set에 변동은 없으며 false를 반환한다.
//      그렇지 않다면, entry값은 set에 추가되고 true를 반환한다. 이것은 C++ STL의 set과 약간의 차이가 있다.
//
//  size_t erase(const Item& target)
//      Postcondition: set 안에 target이 존재한다면 그 값을 set에서 삭제하고 1을 반환한다. 그렇지 않다면, set에 변동은 없으며 0을 반환한다.
//
// CONSTANT MEMBER FUNCTIONS for the Set<Item> class:
//  size_t count(const Item& target) const
//      Postcondition: set내에 존재하는 target과 동일한 값의 개수를 반환한다.(set의 경우 그 값은 0 또는 1이다.)
//
//  bool empty() const
//      Postcondition: 비어있는 set이라면 true를 반환하고 그렇지 않다면 false를 반환한다.
//
// VALUE SEMANTICS for the set<Item> class:
//  대입과 복사 생성자는 set<Item> 객체에서 사용될 수 있다.
//
// DYNAMIC MEMORY USAGE by the set<Item> class:
//  동적 메모리가 부족한 경우에는 아래 함수들이 bad_alloc 에러를 던질 수 있다.
//  생성자, insert 함수, 대입(=) 연산자
#ifndef MAIN_SAVITCH_SET_H
#define MAIN_SAVITCH_SET_H

#include <cstdlib> // Provides size_t
#include <iostream>

namespace main_savitch_11
{
    template <typename Item>
    class set
    {
    public:
        // 별칭 선언
        using value_type = Item;

        // 생성자 및 소멸자
        set();
        set(const set<Item> &source);
        ~set();

        // 수정(MODIFICATION)을 위한 멤버 함수
        void operator=(const set &source);
        void clear();
        bool insert(const Item &entry);

        //  TODO: 
        std::size_t erase(const Item &target);

        // 상수(CONST) 멤버 함수
        std::size_t count(const Item &target) const;
        bool empty() const;
        void print(int depth = 0);

    private:
        // 멤버 상수
        static const std::size_t MINIMUM = 1;
        static const std::size_t MAXIMUM = 2 * MINIMUM;

        // 멤버 변수
        std::size_t data_count;
        Item data[MAXIMUM + 1];
        std::size_t child_count;
        set *subset[MAXIMUM + 2];

        // 헬퍼 멤버 함수
        bool is_leaf() const;

        // Precondition: 전체 B-tree는 유효하다.
        // Postcondition: 만약 set 안에 이미 존재하는 값이 entry라면, set에 변동은 없으며 false를 반환한다.
        // Postcondition: If entry was already in the set, then the set is unchanged and the return value is false.
        // 그렇지 않다면, entry값은 set에 추가되고 true를 반환한다. 그리고 현재 set의 root의 entry 개수가 maximum값 보다 
        // 1이 더 큰 경우를 제외한 전체 B-tree는 여전히 유효하다.
        bool loose_insert(const Item &entry);

        //  TODO: 
        bool loose_erase(const Item &target);

        //  TODO: 
        void remove_biggest(Item &removed_entry);

        // Precondition: i는 child_count보다는 작고, subset[i]의 data count가 MAXIMUM + 1인 예외를 제외하고는 전체 B-tree가 유효하다.
        // Postcondition: tree는 재정렬되며 이를 통해 이 set의 root노드가 가지는 entry의 개수가 허용하는 maximum 개수를 초과하는 경우를 
        // 제외하면 전체 B-tree는 유효하다.
        void fix_excess(std::size_t i);

        //  TODO: 
        void fix_shortage(std::size_t i);
    };
}
#endif

#include "set.impl.h"