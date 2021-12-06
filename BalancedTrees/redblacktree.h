#include <iostream>

// data structure that represents a node in the tree

struct Node
{
    int data;     // holds the key
    Node *parent; // pointer to the parent
    Node *left;   // pointer to left child
    Node *right;  // pointer to right child
    int color;    // 1 -> Red, 0 -> Black
};

namespace algorithmtutor
{
    class Node
    {
    public:
        Node() {}
        ~Node() {}

        const int &data() const { return data_; }
        const Node *parent() const { return parent_; }
        const Node *left() const { return left_; }
        const Node *right() const { return right_; }
        const int &color() const { return color_; }

        void set_data(int data) { data_ = data; }
        void set_parent(Node *parent) { parent_ = parent; }
        void set_left(Node *left) { left_ = left; }
        void set_right(Node *right) { right_ = right; }
        void set_color(int data) { color_ = data; }

    private:
        int data_;     // holds the key
        Node *parent_; // pointer to the parent
        Node *left_;   // pointer to left child
        Node *right_;  // pointer to right child
        int color_;    // 1 -> Red, 0 -> Black
    };

    class RBTree
    {
    public:
    
    private:
    
    };
}