#include "set.h"

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
}