#include "Tree.hpp"
#include <algorithm>
#include <functional>
#include <queue>
#include <type_traits>



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
namespace // const-generic functions
{
     template <class TreeRefType>
    auto impl_flatten_breadth_first(TreeRefType &&root)
    {
        using TreeType = std::remove_reference_t<TreeRefType>;

        std::vector<TreeType*> flattened;
        std::queue<TreeType*> queue;
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



     template <typename TreeRefType, typename Fn>
    void impl_apply_breadth_first(TreeRefType &&root, Fn &&callable)
    {
        using TreeType = std::remove_reference_t<TreeRefType>;

        std::queue<TreeType*> queue;
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


} // ::



 template <typename T>
std::vector<Tree<T> const*> flatten_breadth_first(Tree<T> const& root)
{
    return impl_flatten_breadth_first(root);
}



 template <typename T>
auto flatten_breadth_first(Tree<T>& root) -> std::vector<Tree<T>*>
{
    return impl_flatten_breadth_first(root);
}



 template <typename T, typename Fn>
void apply_breadth_first(Tree<T>& root, Fn&& callable)
{
    impl_apply_breadth_first(root, std::forward<Fn>(callable));
}



 template <typename T, typename Fn>
void apply_breadth_first(Tree<T> const& root, Fn&& callable)
{
    impl_apply_breadth_first(root, std::forward<Fn>(callable));
}
