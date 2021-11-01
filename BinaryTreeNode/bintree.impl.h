#pragma once

namespace main_savitch_10
{
    template <typename Item>
    binary_tree_node<Item>::binary_tree_node(const Item &init_data, binary_tree_node<Item> *init_left, binary_tree_node<Item> *init_right)
        : data_field(init_data), left_field(init_left), right_field(init_right)
    {
    }

    template <typename Item>
    Item &binary_tree_node<Item>::data()
    {
        return data_field;
    }

    template <typename Item>
    binary_tree_node<Item> *&binary_tree_node<Item>::left()
    {
        return left_field;
    }

    template <typename Item>
    binary_tree_node<Item> *&binary_tree_node<Item>::right()
    {
        return right_field;
    }

    template <typename Item>
    void binary_tree_node<Item>::set_data(const Item &new_data)
    {
        data_field = new_data;
    }

    template <typename Item>
    void binary_tree_node<Item>::set_left(binary_tree_node<Item> *new_left)
    {
        left_field = new_left;
    }

    template <typename Item>
    void binary_tree_node<Item>::set_right(binary_tree_node<Item> *new_right)
    {
        right_field = new_right;
    }

    template <typename Item>
    const Item &binary_tree_node<Item>::data() const
    {
        return data_field;
    }

    template <typename Item>
    const binary_tree_node<Item> *binary_tree_node<Item>::left() const
    {
        return left_field;
    }

    template <typename Item>
    const binary_tree_node<Item> *binary_tree_node<Item>::right() const
    {
        return right_field;
    }

    template <typename Item>
    bool binary_tree_node<Item>::is_leaf() const
    {
        return (left_field == nullptr) && (right_field == nullptr);
    }
}