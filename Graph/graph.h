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

        graph()
        {
            many_vertices = 0;
        }

        // Precondition: size( ) < MAXIMUM.
        // Postcondition: The size of the graph has been increased by adding
        // one new vertex. This new vertex has the specified label and no edges.
        void add_vertex(const Item &label)
        {
            if (size() < MAXIMUM)
            {
                std::size_t new_vertext_number;
                std::size_t other_number;

                new_vertext_number = many_vertices;
                many_vertices++;

                // 새로 추가되는 vertext에 대하여 adjacency matrix에 포함시키기
                for (other_number = 0; other_number < many_vertices; other_number++)
                {
                    edges[other_number][new_vertext_number] = false;
                    edges[new_vertext_number][other_number] = false;
                }
                labels[new_vertext_number] = label;
            }
        }

        // Precondition: (source < size( )) and (target < size( )).
        // Postcondition: The graph has all the edges that it originally had, and
        // also has another edge from the specified source to the specified target.
        // (If this edge was already present, then the graph is unchanged.)
        void add_edge(std::size_t source, std::size_t target)
        {
            if (source < size() && target < size())
            {
                edges[source][target] = true;
            }
        }

        // Precondition: (source < size( )) and (target < size( )).
        // Postcondition: The graph has all the edges that it originally had except for the edge
        // from the specified source to the specified target. (If this edge was not originally
        // present, then the graph is unchanged.)
        void remove_edge(std::size_t source, std::size_t target)
        {
            if (source < size() && target < size())
            {
                edges[source][target] = false;
            }
        }

        // Precondition: vertex < size( ).
        // Postcondition: The return value is a reference to the label of the specified vertex.
        Item &operator[](std::size_t vertex)
        {
            return labels[vertex];
        }

        // Precondition: vertex < size( ).
        // Postcondition: The return value is a reference to the label of the specified vertex.
        // NOTE: This function differs from the other operator [ ] because its return value is
        // simply a copy of the Item (rather than a reference of type Item&). Since this function
        // returns only a copy of the Item, it is a const member function.
        Item operator[](std::size_t vertex) const
        {
            return labels[vertex];
        }

        std::size_t size() const
        {
            return many_vertices;
        }

        // Precondition: (source < size( )) and (target < size( )).
        // Postcondition: The return value is true if the graph has an edge from source to target.
        // Otherwise the return value is false.
        bool is_edge(std::size_t source, std::size_t target) const
        {
            if (source < size() && target < size())
            {
                return edges[source][target];
            }
            else
            {
                return false;
            }
        }

        // Precondition: (vertex < size( )).
        // Postcondition: The return value is a set that contains all the vertex numbers of
        // vertices that are the target of an edge whose source is at the specified vertex.
        std::set<std::size_t> neighbors(std::size_t vertext) const
        {
            std::set<std::size_t> result;
            
            if (vertext < size())
            {
                for (std::size_t i = 0; i < size(); i++)
                {
                    if (edges[vertext][i])
                    {
                        result.insert(i);
                    }
                }
            }
            
            return result;
        }

    private:
        bool edges[MAXIMUM][MAXIMUM];
        Item labels[MAXIMUM];
        std::size_t many_vertices;
    };
}
