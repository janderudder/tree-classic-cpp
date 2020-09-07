#include "Tree.hpp"
#include <cassert>
#include <iostream>
#include <type_traits>


int main()
{
    std::boolalpha(std::cout);

    Tree<int> r {nullptr}, n1 {&r}, n2 {2}, n3 {3, &n1}, n4 {4, &n3}, n5;

    n2.set_parent(&r);
    n4.set_parent(&n2);
    n5.set_parent(&n4);

    assert(&r == n1.parent()
        && &r == n2.parent()
        && &n1 == n3.parent()
        && &n2 == n4.parent()
        && &n4 == n5.parent());

    r.value() = 0;
    n1.value() = 1;
    n5.value() = 5;

    auto const flattened_tree = flatten_breadth_first(r);
    static_assert(
        std::is_same_v<decltype(flattened_tree)::value_type,
        Tree<int>*>
    );

    for (auto const* node : flattened_tree)
    {
        std::cout << node->value() << "\n";
    }

    auto const const_flattened_tree = flatten_breadth_first(std::as_const(r));
    static_assert(
        std::is_same_v<decltype(const_flattened_tree)::value_type,
        Tree<int> const*>
    );

    std::vector<Tree<int>*> nodes;
    apply_breadth_first(r, [&nodes](auto& node) { nodes.push_back(&node); });

    std::vector<Tree<int> const*> const_nodes;
    apply_breadth_first(std::as_const(r), [&const_nodes](auto const& node) {
        const_nodes.push_back(&node);
    });

    assert(nodes == flattened_tree);
    assert(const_nodes == const_flattened_tree);
}
