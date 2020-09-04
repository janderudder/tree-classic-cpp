#include "Tree.hpp"
#include <iostream>



int main()
{
    std::boolalpha(std::cout);

    Tree<int> r {nullptr}, n1 {&r}, n2 {2}, n3 {3, &n1}, n4 {4, &n2}, n5;

    n2.set_parent(&r);
    n4.set_parent(&n3);
    n5.set_parent(&n3);

    std::cout << (&r == n1.parent()) << "\n";
    std::cout << (&r == n2.parent()) << "\n";
    std::cout << (&n1 == n3.parent()) << "\n";
    std::cout << (&n3 == n4.parent()) << "\n";
    std::cout << (&n3 == n5.parent()) << "\n";

    r.value() = 0;
    n1.value() = 1;
    n5.value() = 5;

    n3.value() = 3;
    n4.value() = 4;

    auto const flattened_tree = flatten_breadth_first(r);
    for (auto const* node : flattened_tree)
    {
        std::cout << node->value() << "\n";
    }

}
