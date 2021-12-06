#pragma once

#include "graph.h"
#include <vector>
#include <stack>
#include <queue>

template <typename Item>
void depth_first_search(main_savitch_15::graph<Item>& g, std::size_t start)
{
    bool *dfs_vertex_mark = new bool[g.size()];
    for (int i = 0; i < g.size(); i++)
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

    std::cout << "depth first search : [ ";
    dfs_stack.push(start);
    while (!dfs_stack.empty())
    {
        Item top = dfs_stack.top();
        dfs_stack.pop();
        dfs_vertex_mark[top] = true;
        std::cout << g[top] << " ";

        auto neighbors_set = g.neighbors(top);
        for(const auto& neighbor : neighbors_set)
        {
            if (dfs_vertex_mark[neighbor] == false)
            {
                dfs_stack.push(neighbor);
            }
        }
    }
    std::cout << "]" << std::endl;
    
    delete[] dfs_vertex_mark;

    return;
}

template <typename Item>
void breadth_first_search(main_savitch_15::graph<Item>& g, std::size_t start)
{
    bool *bfs_vertex_mark = new bool[g.size()];
    for (int i = 0; i < g.size(); i++)
    {
        bfs_vertex_mark[i] = false;
    }

    std::queue<Item> bfs_queue;

    if (g.size() == 0)
    {
        std::cout << "graph is empty" << std::endl;
        return;
    }

    // start vertex
    Item start_vertex = g[start];

    std::cout << "breadth first search : [ ";
    bfs_queue.push(start);
    while (!bfs_queue.empty())
    {
        Item front = bfs_queue.front();
        bfs_queue.pop();
        bfs_vertex_mark[front] = true;
        std::cout << g[front] << " ";

        auto neighbors_set = g.neighbors(front);
        for (const auto& neighbor : neighbors_set)
        {
            if (bfs_vertex_mark[neighbor] == false)
            {
                bfs_queue.push(neighbor);
            }
        }
    }
    std::cout << "]" << std::endl;
    
    delete[] bfs_vertex_mark;

    return;
}