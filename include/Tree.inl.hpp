#include "Tree.hpp"
#include <algorithm>
#include <functional>
#include <queue>



 template <typename T>
Tree<T>::Tree(std::nullptr_t) noexcept
    : m_parent {nullptr}
{
}



 template <typename T>
Tree<T>::Tree(T&& val, std::nullptr_t) noexcept
    : m_value  {std::forward<T>(val)}
    , m_parent {nullptr}
{
}



 template <typename T>
Tree<T>::Tree(Tree* parent) noexcept
    : m_parent {parent}
{
    m_parent->m_children.push_back(this);
}



 template <typename T>
Tree<T>::Tree(T&& val, Tree* parent) noexcept
    : m_value  {std::forward<T>(val)}
    , m_parent {parent}
{
    m_parent->m_children.push_back(this);
}



////////////////////////////////////////////////////////////////////////////////
 template <typename T>
void Tree<T>::set_parent(Tree* parent)
{
    if (m_parent) {
        auto& pch = m_parent->m_children;
        pch.erase(std::find(pch.begin(), pch.end(), this));
    }
    m_parent = parent;
    m_parent->m_children.push_back(this);
}



 template <typename T>
void Tree<T>::set_parent(std::nullptr_t)
{
    if (m_parent) {
        auto& pch = m_parent->m_children;
        pch.erase(std::find(pch.begin(), pch.end(), this));
    }
    m_parent = nullptr;
}



////////////////////////////////////////////////////////////////////////////////
 template <typename T>
auto Tree<T>::value() -> T&
{
    return m_value;
}



 template <typename T>
auto Tree<T>::value() const -> T const&
{
    return m_value;
}



 template <typename T>
auto Tree<T>::parent() const -> Tree const*
{
    return m_parent;
}



 template <typename T>
auto Tree<T>::children() const -> std::vector<Tree*> const&
{
    return m_children;
}



////////////////////////////////////////////////////////////////////////////////
 template <typename T>
std::vector<Tree<T>*> flatten_breadth_first(Tree<T>& root)
{
    std::vector<Tree<T>*> flattened;

    std::queue<Tree<T>*> queue;
    queue.push(&root);

    while (!queue.empty())
    {
        auto* node = queue.front();
        flattened.push_back(node);
        queue.pop();

        for (auto *child : node->children()) {
            queue.push(child);
        }
    }

    return flattened;
}



 template <typename T, typename Fn>
void apply_breadth_first(Tree<T>& root, Fn&& callable)
{
    std::queue<Tree<T>*> queue;
    queue.push(&root);

    while (!queue.empty())
    {
        auto* node = queue.front();
        queue.pop();

        for (auto *child : node->children()) {
            queue.push(child);
        }

        std::invoke(callable, *node);
    }
}
