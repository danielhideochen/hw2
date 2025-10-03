#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> keyWords;

    std::string prePunc;
    std::string postPunc;
    bool foundPunc = false;

    for (unsigned char uch : rawWords) {
        if (std::isalnum(uch)) {
            char lc = static_cast<char>(std::tolower(uch));
            if (!foundPunc) {
                prePunc.push_back(lc);
            } else {
                postPunc.push_back(lc);
            }
        } else if (std::ispunct(uch)) {
            if (!foundPunc) {
                if (prePunc.size() >= 2) {
                    keyWords.insert(prePunc);
                }
                prePunc.clear();
                foundPunc = true;
            } else {
                if (postPunc.size() >= 2) {
                    keyWords.insert(postPunc);
                }
                postPunc.clear();
            }
        } else {
            if (!foundPunc) {
                if (prePunc.size() >= 2) {
                    keyWords.insert(prePunc);
                }
                prePunc.clear();
            } else {
                if (postPunc.size() >= 2) {
                    keyWords.insert(postPunc);
                }
                postPunc.clear();
            }
        }
    }
    
    // final flush
    if (!foundPunc) {
        if (prePunc.size() >= 2) {
            keyWords.insert(prePunc);
        }
    } else {
        if (postPunc.size() >= 2) {
            keyWords.insert(postPunc);
        }
        if (prePunc.size() >= 2) {
            keyWords.insert(prePunc);
        }
    }

    return keyWords;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
