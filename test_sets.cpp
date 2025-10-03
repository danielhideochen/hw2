#include "util.h"
#include <iostream>

int main() {
    std::set<int> a; a.insert(1); a.insert(3); a.insert(5);
    std::set<int> b; b.insert(3); b.insert(4); b.insert(6);

    std::set<int> u = setUnion(a,b);         // {1,3,4,5,6}
    std::set<int> i = setIntersection(a,b);  // {3}

    for (std::set<int>::const_iterator it=u.begin(); it!=u.end(); ++it) std::cout<<*it<<" ";
    std::cout << "\n";
    for (std::set<int>::const_iterator it=i.begin(); it!=i.end(); ++it) std::cout<<*it<<" ";
    std::cout << "\n";
}