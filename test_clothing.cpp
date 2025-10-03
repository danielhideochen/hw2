#include "clothing.h"
#include "util.h"
#include <iostream>
#include <set>
#include <string>

static void printSet(const std::set<std::string>& s)
{
    std::cout << "{";
    bool first = true;
    for (std::set<std::string>::const_iterator it = s.begin(); it != s.end(); ++it) {
        if (!first) std::cout << ", ";
        std::cout << *it;
        first = false;
    }
    std::cout << "}";
}

int main() {
    Clothing c("Men's Fitted Shirt", 39.99, 25, "Medium", "J. Crew");

    std::cout << c.displayString() << "\n\n";

    std::set<std::string> ks = c.keywords();
    std::cout << "keywords = ";
    printSet(ks);
    std::cout << "\n";
    return 0;
}