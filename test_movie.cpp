#include "movie.h"
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
    Movie m("Hidden Figures DVD", 17.99, 1, "Drama", "PG");

    std::cout << m.displayString() << "\n\n";

    std::set<std::string> ks = m.keywords();
    std::cout << "keywords = ";
    printSet(ks);
    std::cout << "\n";
    return 0;
}