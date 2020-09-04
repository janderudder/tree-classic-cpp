#pragma once
#include <vector>



////////////////////////////////////////////////////////////////////////////////
 template <typename T>
class Tree
{
    T                   m_value;
    Tree*               m_parent;
    std::vector<Tree*>  m_children;

public:
    Tree(std::nullptr_t =nullptr) noexcept;
    Tree(T&&, std::nullptr_t =nullptr) noexcept;
    Tree(Tree* parent) noexcept;
    Tree(T&&, Tree* parent) noexcept;

    void set_parent(Tree*);
    void set_parent(std::nullptr_t);

    auto value()            -> T&;
    auto value() const      -> T const&;
    auto parent() const     -> Tree const*;
    auto children() const   -> std::vector<Tree*> const&;

};



////////////////////////////////////////////////////////////////////////////////
 template <typename T>
std::vector<Tree<T>*> flatten_breadth_first(Tree<T>&);


 template <typename T, typename Fn>
void apply_breadth_first(Tree<T>&, Fn&& callable);



////////////////////////////////////////////////////////////////////////////////
#include "Tree.inl.hpp"
