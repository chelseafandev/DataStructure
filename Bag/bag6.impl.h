#pragma once

namespace main_savitch_10
{
    template <typename Item>
    bag<Item>::bag()
    {
        syslog(LOG_LOCAL0, "%s", "bag constructor called!");
        root_ptr = nullptr;
    }

    template <typename Item>
    bag<Item>::bag(const bag &source)
    {
        syslog(LOG_LOCAL0, "%s", "bag copy constructor called!");
        root_ptr = tree_copy(source.root_ptr);
    }

    template <typename Item>
    bag<Item>::~bag()
    {
        syslog(LOG_LOCAL0, "%s", "bag destructor called!");
        tree_clear(root_ptr);
    }

    template <typename Item>
    typename bag<Item>::size_type bag<Item>::erase(const Item &target)
    {
        int nRet = 0;

        while (1)
        {
            if (!erase_one(target))
                break;

            nRet++;
        }

        return nRet;
    }

    template <typename Item>
    bool bag<Item>::erase_one(const Item &target)
    {
        return bst_remove(root_ptr, target);
    }

    template <typename Item>
    void bag<Item>::insert(const Item &entry)
    {
        binary_tree_node<Item> *cursor = nullptr;

        if (root_ptr == nullptr)
        {
            root_ptr = new binary_tree_node<Item>(entry);
            return;
        }
        else
        {
            cursor = root_ptr;
            while (1)
            {
                if (cursor->data() >= entry)
                {
                    if (cursor->left() == nullptr)
                    {
                        cursor->left() = new binary_tree_node<Item>(entry);
                        break;
                    }
                    else
                    {
                        cursor = cursor->left();
                        continue;
                    }
                }
                else
                {
                    if (cursor->right() == nullptr)
                    {
                        cursor->right() = new binary_tree_node<Item>(entry);
                        break;
                    }
                    else
                    {
                        cursor = cursor->right();
                        continue;
                    }
                }
            }
        }
    }

    template <typename Item>
    void bag<Item>::operator+=(const bag<Item> &addend)
    {
        syslog(LOG_LOCAL0, "%s", "bag operator+= called!");
        binary_tree_node<Item> *addroot_ptr;

        if (root_ptr == addend.root_ptr)
        {
            addroot_ptr = tree_copy(addend.root_ptr);
            insert_all(addroot_ptr);
            tree_clear(addroot_ptr);
        }
        else
        {
            insert_all(addend.root_ptr);
        }
    }

    template <typename Item>
    void bag<Item>::operator=(const bag<Item> &source)
    {
        syslog(LOG_LOCAL0, "%s", "bag operator= called!");
        if (root_ptr == source.root_ptr)
            return;

        tree_clear(root_ptr);
        root_ptr = tree_copy(source.root_ptr);
    }

    template <typename Item>
    typename bag<Item>::size_type bag<Item>::size() const
    {
        return tree_size(root_ptr);
    }

    template <typename Item>
    typename bag<Item>::size_type bag<Item>::count(const Item &target) const
    {
        int nRet = 0;
        binary_tree_node<Item> *cursor = root_ptr;
        while (cursor != nullptr)
        {
            if (cursor->data() == target)
            {
                nRet++;
                cursor = cursor->left();
            }
            else if (cursor->data() > target)
            {
                cursor = cursor->left();
            }
            else
            {
                cursor = cursor->right();
            }
        }

        return nRet;
    }

    template <typename Item>
    void bag<Item>::printBag()
    {
        print(root_ptr, 0);
    }

    template <typename Item>
    bool bag<Item>::bst_remove(binary_tree_node<Item> *&root_ptr, const Item &target)
    {
        if (root_ptr == nullptr)
        {
            return false;
        }
        else
        {
            if (root_ptr->data() > target)
            {
                bst_remove(root_ptr->left(), target);
            }
            else if (root_ptr->data() < target)
            {
                bst_remove(root_ptr->right(), target);
            }
            else
            {
                if (root_ptr->left() == nullptr)
                {
                    // 루트 노드에 왼쪽 자식 노드가 존재하지 않는 경우
                    binary_tree_node<Item> *tmp_ptr = root_ptr;
                    root_ptr = root_ptr->right();
                    delete tmp_ptr;
                    return true;
                }
                else
                {
                    // 루트 노드에 왼쪽 자식 노드가 존재하는 경우(왼쪽 서브 트리에서 가장 큰 값을 찾아서 그 값을 루트 노드로 올림)
                    Item swapData;
                    bst_remove_max(root_ptr->left(), swapData);
                    root_ptr->set_data(swapData);
                    return true;
                }
            }
        }
    }

    template <typename Item>
    void bag<Item>::bst_remove_max(binary_tree_node<Item> *&root_ptr, Item &removed)
    {
        if (root_ptr->right() == nullptr)
        {
            // 오른쪽 자식 노드가 없는 경우에는 루트 노드가 가장 큰 노드이다
            removed = root_ptr->data();
            binary_tree_node<Item> *tmp_ptr = root_ptr;
            root_ptr = root_ptr->left();
            delete tmp_ptr;
        }
        else
        {
            // 오른쪽 자식 노드가 있는 경우에는 오른쪽 서브 트리를 기준으로 다시 가장 큰 값을 찾는다
            bst_remove_max(root_ptr->right(), removed);
        }
    }

    template <typename Item>
    void bag<Item>::insert_all(const binary_tree_node<Item> *addroot_ptr)
    {
        // pre-order나 post-order를 사용하라(in-order는 Unbalanced Tree를 발생시킴)
        if (addroot_ptr != nullptr)
        {
            insert(addroot_ptr->data());
            insert_all(addroot_ptr->left());
            insert_all(addroot_ptr->right());
        }
    }
}
