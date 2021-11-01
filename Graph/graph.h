#pragma once

#include <cstdlib> // Provides size_t
#include <iostream>
#include <set>

namespace main_savitch_15
{
    template <typename Item>
    class graph
    {
    public:
        static const std::size_t MAXIMUM = 20;

        graph();

        // Precondition: size( ) < MAXIMUM.
        // Postcondition: graph의 크기는 새로운 vertex가 추가됨으로 인해 증가한다. 
        // 새롭게 추가된 vertex는 특정한 label 값을 갖으며 edge는 없다.
        void add_vertex(const Item &label);

        // Precondition: (source < size( )) and (target < size( )).
        // Postcondition: graph는 기존에 갖고 있던 모든 edge뿐만 아니라 특정 source에서 target으로 향하는 또 다른 edge를 포함한다.
        // (추가하려는 edge가 이미 존재한다면 graph에 변화는 없다.)
        void add_edge(std::size_t source, std::size_t target);

        // Precondition: (source < size( )) and (target < size( )).
        // Postcondition: graph는 특정 source에서 target으로 향하는 edge를 제외한 기존에 갖고 있던 모든 edge를 포함한다.
        // (만약 삭제하려는 edge가 존재하지 않는다면 graph에 변화는 없다.)
        void remove_edge(std::size_t source, std::size_t target);

        // Precondition: vertex < size( ).
        // Postcondition: 반환 값은 특정 vertex 라벨의 참조 값이다.
        Item &operator[](std::size_t vertex);

        // Precondition: vertex < size( ).
        // Postcondition: 반환 값은 Item의 복사본(참조 값이 아닌) 이다. 이 함수는 단지 Item의 복사본을 반환하므로 const 멤버 함수이다.
        Item operator[](std::size_t vertex) const;

        std::size_t size() const;

        // Precondition: (source < size( )) and (target < size( )).
        // Postcondition: 반환 값은 source에서 target으로 향하는 edge가 존재한다면 true이고 그렇지 않다면 false이다.
        bool is_edge(std::size_t source, std::size_t target) const;
        
        // Precondition: (vertex < size( )).
        // Postcondition: 반환 값은 source를 특정 vertex로 하는 모든 edge의 target vertex값들의 집합(set)이다.
        std::set<std::size_t> neighbors(std::size_t vertex) const;

    private:
        bool edges[MAXIMUM][MAXIMUM];
        Item labels[MAXIMUM];
        std::size_t many_vertices;
    };
}

#include "graph.impl.h"