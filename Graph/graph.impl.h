#pragma once

namespace main_savitch_15
{
    template <typename Item>
    graph<Item>::graph()
    {
        many_vertices = 0;
    }

    template <typename Item>
    void graph<Item>::add_vertex(const Item &label)
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

    template <typename Item>
    void graph<Item>::add_edge(std::size_t source, std::size_t target)
    {
        if (source < size() && target < size())
        {
            edges[source][target] = true;
        }
    }

    template <typename Item>
    void graph<Item>::remove_edge(std::size_t source, std::size_t target)
    {
        if (source < size() && target < size())
        {
            edges[source][target] = false;
        }
    }

    template <typename Item>
    Item& graph<Item>::operator[](std::size_t vertex)
    {
        return labels[vertex];
    }

    template <typename Item>
    Item graph<Item>::operator[](std::size_t vertex) const
    {
        return labels[vertex];
    }

    template <typename Item>
    std::size_t graph<Item>::size() const
    {
        return many_vertices;
    }

    template <typename Item>
    bool graph<Item>::is_edge(std::size_t source, std::size_t target) const
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

    template <typename Item>
    std::set<std::size_t> graph<Item>::neighbors(std::size_t vertex) const
    {
        std::set<std::size_t> result;

        if (vertex < size())
        {
            for (std::size_t i = 0; i < size(); i++)
            {
                if (edges[vertex][i])
                {
                    result.insert(i);
                }
            }
        }

        return result;
    }
}