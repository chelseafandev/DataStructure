// FILE: table1.h (part of the namespace main_savitch_12A)
// TEMPLATE CLASS PROVIDED: table<RecordType> (a table of records with keys)
// This class is a container template class for a table of records.
// The template parameter, RecordType, is the data type of the records in the table.
// It may be any of the bulit-in C++ types (int, char, etc.), or a class with a default
// constructor, an assignment operator, and an integer member variable called key.
//
// TYPEDEFS and MEMBER CONSTANT for the table<RecordType> class:
//  static const size_t CAPACITY = _____
//      table<RecordType>::CAPACITY is the maximum number of records held by a table.
//
// CONSTRUCTOR for the table<RecordType> template class:
//  table( )
//      Postcondition: The table has been initialized as an empty table.
//
// MODIFICATION MEMBER FUNCTIONS for the table<RecordType> class:
//  void insert(const RecordType& entry)
//      Precondition: entry.key >= 0. Also if entry.key is not already a key in the table, then
//      the table has space for another record (that is, size( ) < CAPACITY).
//      Postcondition: If the table already had a record with a key equal to entry.key, then that
//      record is replaced by entry. Otherwise, entry has been added as a new record of the
//      table.
//
//  void remove(int key) 
//      Postcondition: If a record was in the table with the specified key, then that record has
//      been removed. Otherwise the table is unchanged.
//
// CONSTANT MEMBER FUNCTIONS for the table<RecordType> class:
//  bool is_present(int key) const
//      Postcondition: The return value is true if there is a record in the table with the
//      specified key. Otherwise, the return value is false.
//
//  void find(int key, bool& found, RecordType& result) const
//      Postcondition: If a record is in the table with the specified key, then found is true, and
//      result is set to a copy of the record with that key. Otherwise found is false,
//      and the result contains garbage.
//
//  size_t size( ) const
//      Postcondition: Return value is the total number of records in the table.
//
// VALUE SEMANTICS for the table<RecordType> template class:
//  Assignments and the copy constructor may be used with table<RecordType> objects
#ifndef TABLE_H
#define TABLE_H
#include <cstdlib> // Provides size_t
namespace main_savitch_12A
{
    template <class RecordType>
    class table
    {
    public:
        // 멤버 상수(public)
        static const std::size_t CAPACITY = 811;
        
        // 생성자
        table()
        {
            used = 0;
            for (int i = 0; i < CAPACITY; ++i)
                data[i].key = NEVER_USED;
        }
        
        // 수정(MODIFICATION)을 위한 멤버 함수
        void insert(const RecordType &entry)
        {
            bool already_present = false; // 동일한 키를 같는 entry가 있는지 여부를 체크

            std::size_t index = 0; // 새롭게 추가된 entry의 index값

            if(entry.key < 0)
                return;
            
            // 새롭게 추가할 entry의 index값을 찾는다
            find_index(entry.key, already_present, index);

            // 위 find_index 함수를 통해 index를 찾았다면 already_present는 true이므로 아래 if문은 타지 않는다
            if (!already_present)
            {
                if( size() >= CAPACITY)
                    return;
                
                index = hash(entry.key);
                while (!is_vacant(index))
                    index = next_index(index);

                ++used;
            }

            data[index] = entry;
        }

        void remove(int key)
        {
        
        }

        // 상수(CONST) 멤버 함수
        bool is_present(int key) const
        {

        }
        
        void find(int key, bool &found, RecordType &result) const
        {

        }
        
        std::size_t size() const 
        {
            return used;
        }

    private:
        // 멤버 상수(private)
        static const int NEVER_USED = -1;
        static const int PREVIOUSLY_USED = -2;
        
        // 멤버 변수
        RecordType data[CAPACITY];
        std::size_t used;

        // 헬퍼 함수
        std::size_t hash(int key) const
        {
            return key % CAPACITY;
        }

        std::size_t next_index(std::size_t index) const
        {
            // 기본적으로 index는 CAPACITY보다 항상 작다(왜냐? index를 결정하는 hash 함수에서 임의의 key값을 CAPACITY로 mod연산하기 때문에)
            // index + 1이 CAPACITY보다 작은 경우는 index + 1을 반환
            // index + 1이 CAPACITY와 같은 경우는 0을 반환
            return (index + 1) % CAPACITY;
        }

        void find_index(int key, bool &found, std::size_t &index) const
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

        bool never_used(std::size_t index) const
        {
            return data[index].key == NEVER_USED;
        }

        bool is_vacant(std::size_t index) const
        {
            return (data[index].key == NEVER_USED) || (data[index].key == PREVIOUSLY_USED);
        }
    };
}
#endif