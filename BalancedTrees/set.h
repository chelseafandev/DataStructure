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
        set()
        {
            //std::cout << "Constructor!" << std::endl;
            data_count = 0;
            child_count = 0;
        }

        set(const set<Item> &source)
        {
            //std::cout << "Copy Constructor!" << std::endl;
            data_count = source.data_count;
            for (int i = 0; i < data_count; i++)
            {
                data[i] = source.data[i];
            }
            child_count = source.child_count;
            for (int i = 0; i < child_count; i++)
            {
                subset[i] = source.subset[i];
            }
        }

        ~set()
        {
            //std::cout << "Destructor!" << std::endl;
            clear();
        }

        // 수정(MODIFICATION)을 위한 멤버 함수
        void operator=(const set &source)
        {
            //std::cout << "operator= called!" << std::endl;
            clear();
            data_count = source.data_count;
            for (int i = 0; i < data_count; i++)
            {
                data[i] = source.data[i];
            }
            child_count = source.child_count;
            for (int i = 0; i < child_count; i++)
            {
                subset[i] = source.subset[i];
            }
        }
        
        void clear()
        {
            data_count = 0;
            child_count = 0;
            for (int i = 0; i < child_count; i++)
            {
                subset[i]->clear();
                delete subset[i];
                subset[i] = nullptr;
            }
        }

        bool insert(const Item &entry)
        {
            // loose_insert 함수를 통해서 인자로 넘어오는 entry가 추가될 leaf 노드를 찾음.
            // 이 leaf 노드는 예외적으로 maximum보다 하나 더 많은 entry 개수를 가질 수 있으며,
            // 이 예외는 fix_excess라는 함수를 통해 처리하게 됨.
            if (!loose_insert(entry))
            {
                std::cout << "loose_insert failed!" << std::endl;
                return false;
            }

            // loose_insert를 재귀적으로 호출하여 최상위 root에 까지 도달한 다음에도
            // root 노드의 entry개수가 maximum을 초과할 수 있음. 아래는 이를 처리하기 위한 로직임.
            if (data_count > MAXIMUM)
            {
                // 기존의 root 노드를 복사
                set<Item> *tmp = new set<Item>();
                *tmp = *this;
                
                // root 노드 초기화 이후, 복사해둔 노드를 subset으로 추가 
                clear();                
                child_count = 1;
                subset[0] = tmp;

                // subset으로 추가된 기존의 root 노드에 대한 fix_excess 함수 처리
                fix_excess(0);
            }
            return true;
        }

        std::size_t erase(const Item &target)
        {
        }

        // 상수(CONST) 멤버 함수
        std::size_t count(const Item &target) const
        {
            int nSubSetIdx = -1;
            for (int i = 0; i < data_count; i++)
            {
                if (data[i] > target)
                {
                    nSubSetIdx = i;
                    break;
                }
            }

            if (nSubSetIdx == -1)
            {
                nSubSetIdx = data_count;
            }

            // 1) root에 target이 존재하는 경우
            // 주의! Item 타입에 == operator가 정의되지 않은 경우를 고려해야함. 아래와 같은 조건으로 equal 조건을 대신할 수 있음.
            if ((nSubSetIdx < data_count) && !(data[nSubSetIdx] > target))
            {
                return 1;
            }
            else if (is_leaf())
            {
                // 2) root에 자식이 없는 경우
                return 0;
            }

            return subset[nSubSetIdx]->count(target);
        }

        bool empty() const { return data_count == 0; }

        void print(int depth = 0)
        {
            std::cout << std::setw(4 * depth) << "";
            if (is_leaf())
            {
                std::cout << "[";
                for (int i = 0; i < data_count; i++)
                {
                    if(i == data_count - 1)
                    {
                        std::cout << data[i];
                    }
                    else
                    {
                        std::cout << data[i] << " ";
                    }
                }
                std::cout << "]"; 
                std::cout << " [leaf]" << std::endl;
            }
            else
            {
                std::cout << "[";
                for (int i = 0; i < data_count; i++)
                {
                    if(i == data_count - 1)
                    {
                        std::cout << data[i];
                    }
                    else
                    {
                        std::cout << data[i] << " ";
                    }
                }
                std::cout << "]" << std::endl;
                for (int i = child_count-1; i >= 0; i--)
                {
                   subset[i]->print(depth + 1);
                }
            }
        }

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
        bool is_leaf() const { return child_count == 0; }

        // Precondition: 전체 B-tree는 유효하다.
        // Postcondition: 만약 set 안에 이미 존재하는 값이 entry라면, set에 변동은 없으며 false를 반환한다.
        // Postcondition: If entry was already in the set, then the set is unchanged and the return value is false.
        // 그렇지 않다면, entry값은 set에 추가되고 true를 반환한다. 그리고 현재 set의 root의 entry 개수가 maximum값 보다 
        // 1이 더 큰 경우를 제외한 전체 B-tree는 여전히 유효하다.
        bool loose_insert(const Item &entry)
        {
            // 새롭게 추가 될 entry의 값을 통해 어떠한 subset에 포함이 되어야하는지 결정(subset의 인덱스 값)
            // entry의 값을 현재 노드의 data 값들과 비교해 나감
            int nSubSetIdx = -1;
            for (int i = 0; i < data_count; i++)
            {
                if (data[i] > entry)
                {
                    nSubSetIdx = i;
                    break;
                }
            }
            
            if (nSubSetIdx == -1)
            {
                nSubSetIdx = data_count;
            }
            
            if ((nSubSetIdx < data_count) && !(data[nSubSetIdx] > entry))
            {
                // root에 추가하려는 entry가 이미 존재하는 경우
                return false;
            }
            else if (is_leaf())
            {
                // leaf 노드인 경우 위에서 구한 subset의 인덱스 값을 이용하여 entry값을 data 배열에 추가.
                // entry를 추가하더라도 data 배열은 오름차순으로 정렬이 유지되어야함.

                // data 배열이 empty인 경우
                if (data_count == 0)
                {
                    data[0] = entry;
                    data_count++;
                    return true;
                }

                // 정렬 수행
                bool isFound = false;
                Item prev;
                data_count++;
                for (int i = 0; i < data_count; i++)
                {
                    if (!isFound)
                    {
                        if (data[i] > entry)
                        {
                            isFound = true;
                            prev = data[i];
                            data[i] = entry;
                        }

                        if (i == data_count - 1)
                        {
                            data[i] = entry;
                        }
                    }
                    else
                    {
                        Item tmp = prev;
                        prev = data[i];
                        data[i] = tmp;
                    }
                }

                return true;
            }
            else
            {
                // leaf 노드가 아닌 경우는 loose_insert 함수 재귀 호출
                bool nRet = subset[nSubSetIdx]->loose_insert(entry);
                if (nRet)
                {
                    // loose_insert를 통해 leaf 노드에 값이 추가됐다면, leaf 노드의 data_count가 maximum을 초과하는 이슈를 해결해야함.
                    if (subset[nSubSetIdx]->data_count > MAXIMUM)
                        fix_excess(nSubSetIdx);

                    return true;
                }
            }

            return false;
        }

        bool loose_erase(const Item &target)
        {
        }

        void remove_biggest(Item &removed_entry)
        {
        }

        // Precondition: i는 child_count보다는 작고, subset[i]의 data count가 MAXIMUM + 1인 예외를 제외하고는 전체 B-tree가 유효하다.
        // Postcondition: tree는 재정렬되며 이를 통해 이 set의 root노드가 가지는 entry의 개수가 허용하는 maximum 개수를 초과하는 경우를 
        // 제외하면 전체 B-tree는 유효하다.
        void fix_excess(std::size_t i)
        {
            // maximum 개수를 초과한 data 배열에서 위쪽 노드로 올려보내는 값은 중간에 위치한 값임.
            int midIdx = subset[i]->data_count / 2;

            // maximum 개수를 초과한 subset data 배열의 중간 값을 현재 노드의 data 배열에 저장하고
            data[i] = subset[i]->data[midIdx];
            data_count++;

            // subset 쪼개기(오른쪽) - 새로운 set을 만들어서 data 및 subset 붙이기
            set<Item> *added = new set<Item>();
            int newIdx = 0;
            for (int idx = midIdx + 1; idx < subset[i]->data_count; idx++)
            {
                added->data_count++;
                added->data[newIdx] = subset[i]->data[idx];
                newIdx++;
            }
            child_count++;;
            subset[child_count - 1] = added;

            // subset 쪼개기(왼쪽) - 기존 subset 활용하기(count값만 변경)
            subset[i]->data_count = midIdx;

            // 분할된 subset의 subset 붙이기
            if(subset[i]->child_count != 0)
            {
                // 분할된 왼쪽 subset에 subset 붙이기
                int leftSosCnt = subset[i]->data_count + 1;
                subset[i]->child_count = leftSosCnt;

                // 분할된 오른쪽 subset에 subset 붙이기
                int rightSosCnt = subset[child_count - 1]->data_count + 1;
                for (int j = 0, idx = leftSosCnt; idx < rightSosCnt + leftSosCnt; j++, idx++)
                {
                    subset[child_count - 1]->subset[j] = subset[i]->subset[idx];
                    (subset[child_count - 1]->child_count)++;
                }
            }
        }

        void fix_shortage(std::size_t i)
        {
        }
    };
}
#endif