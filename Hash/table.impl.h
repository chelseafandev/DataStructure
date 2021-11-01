#pragma once

namespace main_savitch_12A
{
    template <typename RecordType>
    table<RecordType>::table()
    {
        used = 0;
        for (int i = 0; i < CAPACITY; ++i)
            data[i].key = NEVER_USED;
    }

    template <typename RecordType>
    void table<RecordType>::insert(const RecordType &entry)
    {
        bool already_present = false; // 동일한 키를 같는 entry가 있는지 여부를 체크

        std::size_t index = 0; // 새롭게 추가된 entry의 index값

        if (entry.key < 0)
            return;

        // 새롭게 추가할 entry의 index값을 찾는다
        find_index(entry.key, already_present, index);

        // 위 find_index 함수를 통해 index를 찾았다면 already_present는 true이므로 아래 if문은 타지 않는다
        if (!already_present)
        {
            if (size() >= CAPACITY)
                return;

            index = hash(entry.key);
            while (!is_vacant(index))
                index = next_index(index);

            ++used;
        }

        data[index] = entry;
    }

    template <typename RecordType>
    void table<RecordType>::remove(int key)
    {
    }

    template <typename RecordType>
    bool table<RecordType>::is_present(int key) const
    {
    }

    template <typename RecordType>
    void table<RecordType>::find(int key, bool &found, RecordType &result) const
    {
    }

    template <typename RecordType>
    std::size_t table<RecordType>::size() const
    {
        return used;
    }

    template <typename RecordType>
    std::size_t table<RecordType>::hash(int key) const
    {
        return key % CAPACITY;
    }

    template <typename RecrodType>
    std::size_t table<RecordType>::next_index(std::size_t index) const
    {
        // 기본적으로 index는 CAPACITY보다 항상 작다(왜냐? index를 결정하는 hash 함수에서 임의의 key값을 CAPACITY로 mod연산하기 때문에)
        // index + 1이 CAPACITY보다 작은 경우는 index + 1을 반환
        // index + 1이 CAPACITY와 같은 경우는 0을 반환
        return (index + 1) % CAPACITY;
    }

    template <typename RecrodType>
    void table<RecordType>::find_index(int key, bool &found, std::size_t &index) const
    {
        std::size_t count = 0;

        index = hash(key);
        while ((count < CAPACITY) && (data[index].key != NEVER_USED) && (data[index].key != key))
        {
            ++count;
            index = next_index(index);
        }

        found = (data[index].key == key);
    }

    template <typename RecrodType>
    bool table<RecordType>::never_used(std::size_t index) const
    {
        return data[index].key == NEVER_USED;
    }

    template <typename RecrodType>
    bool table<RecordType>::is_vacant(std::size_t index) const
    {
        return (data[index].key == NEVER_USED) || (data[index].key == PREVIOUSLY_USED);
    }
}
