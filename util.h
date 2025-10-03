#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> out;
    typename std::set<T>::const_iterator i = s1.begin();
    typename std::set<T>::const_iterator j = s2.begin();

    while (i != s1.end() && j != s2.end()) {
        if (*i < *j) {
            ++i;
        } else if (*j < *i) {
            ++j;
        } else {
            out.insert(*i);
            ++i; ++j;
        }
    }
    return out;


}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> out;
    typename std::set<T>::const_iterator i = s1.begin();
    typename std::set<T>::const_iterator j = s2.begin();

    while (i != s1.end() && j != s2.end()) {
        if (*i < *j) {
            out.insert(*i);
            ++i;
        } else if (*j < *i) {
            out.insert(*j);
            ++j;
        } else {
            out.insert(*i);   // equal
            ++i; ++j;
        }
    }
    while (i != s1.end()) { out.insert(*i); ++i; }
    while (j != s2.end()) { out.insert(*j); ++j; }
    return out;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
