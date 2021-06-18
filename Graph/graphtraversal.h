#pragma once

#include "graph.h"
#include <vector>
#include <stack>

template <typename Item>
void depth_first(main_savitch_15::graph<Item>& g, std::size_t start)
{
    bool *dfs_vertex_mark = new bool[g.size()];
    for(int i = 0; i < g.size(); i++)
    {
        dfs_vertex_mark[i] = false;
    }

    std::stack<Item> dfs_stack;
    
    if (g.size() == 0)
    {
        std::cout << "graph is empty" << std::endl;
        return;
    }

    // start vertex
    Item start_vertex = g[start];
    std::cout << start_vertex << std::endl;

    std::cout << "[";
    dfs_stack.push(start);
    while (!dfs_stack.empty())
    {
        Item top = dfs_stack.top();
        dfs_stack.pop();
        dfs_vertex_mark[top] = true;
        std::cout << g[top] << ", ";

        std::set<std::size_t> neighbors_set = g.neighbors(top);
        typename std::set<std::size_t>::iterator itr;
        for (itr = neighbors_set.begin(); itr != neighbors_set.end(); itr++)
        {
            if (dfs_vertex_mark[*itr] == false)
            {
                dfs_stack.push(*itr);
            }
        }
    }
    std::cout << "]" << std::endl;
    
    delete[] dfs_vertex_mark;

    return;
}

template <typename Item>
void breadth_first(main_savitch_15::graph<Item>& g, std::size_t start)
{

}