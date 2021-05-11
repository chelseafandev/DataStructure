#include "set.h"

#include <algorithm>

namespace main_savitch_11
{
    template <typename Item>
    set<Item>::set(const set<Item>& source)
    {
        std::cout << "Copy Constructor!" << std::endl;

        //std::size_t data_count;
        //Item data[MAXIMUM + 1];
        //std::size_t child_count;
        //set *subset[MAXIMUM + 2];
        data_count = source.data_count;
        // data = source.data;
        child_count = source.child_count;
        subset = source.subset;
    }

    template <typename Item>
    std::size_t set<Item>::count(const Item& target) const
    {
        int nSubSetIdx = -1;
        for(int i = 0; i < data_count; i++)
        {
            if(data[i] > target)
            {
                nSubSetIdx = i;
                break;
            }
        }

        if(nSubSetIdx == -1)
        {
            nSubSetIdx = data_count;
        }
        
        // 1) root에 target이 존재하는 경우
        // 주의! Item 타입에 == operator가 정의되지 않은 경우를 고려해야함. 아래와 같은 조건으로 equal 조건을 대신할 수 있음.
        if( (nSubSetIdx < data_count) && !(data[nSubSetIdx] > target) )
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

    template <typename Item>
    bool set<Item>::insert(const Item& entry)
    {
        if(!loose_insert(entry))
        {
            return false;
        }
        
        // 최상위 root에서 fix_excess 처리
        if(data_count > MAXIMUM)
        {
            
        }

        return true;
    }

    // Precondition: The entire B-tree is valid.
    // Postcondition: If entry was already in the set, then the set is unchanged and the return value is false.
    // Otherwise, the entry has been added to the set, the return value is true, and the entire B-tree is still
    // valid EXCEPT that the number of entries in the root of this set might be one more than the allowed maximum.
    template <typename Item>
    bool set<Item>::loose_insert(const Item& entry)
    {
        int nSubSetIdx = -1;
        for(int i = 0; i < data_count; i++)
        {
            if(data[i] > entry)
            {
                nSubSetIdx = i;
                break;
            }
        }

        if(nSubSetIdx == -1)
        {
            nSubSetIdx = data_count;
        }

        // root에 추가하려는 entry가 이미 존재하는 경우
        if( (nSubSetIdx < data_count) && !(data[nSubSetIdx] > entry) )
        {
            return false;
        }
        else if(is_leaf())
        {
            data[nSubSetIdx] = entry;
            data_count++;
            std::sort(data, data + data_count);
            return true;
        }
        else
        {
            bool nRet = subset[nSubSetIdx]->loose_insert(entry);
            if(nRet)
            {
                if(subset[nSubSetIdx]->data_count > MAXIMUM)
                    fix_excess(nSubSetIdx);
            }
        }

        return false;
    }

    // Precondition: (i < child_count) and the entire B-tree is valid EXCEPT that subset[i] has MAXIMUM + 1 entries.
    // Postcondition: The tree has been rearranged so that the entire B-tree is valid EXCEPT that the number of entries
    // in the root of this set might be one more than the allowed maximum.
    template<typename Item>
    void set<Item>::fix_excess(std::size_t i)
    {
        int midIdx = subset[i]->data_count / 2;

        // 가운데 entity를 parent로 올리고

        // subset 2개로 분할하기
    }
}