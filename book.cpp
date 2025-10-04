#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Book::Book(const std::string& name, double price, int qty,
           const std::string& isbn, const std::string& author)
: Product("book", name, price, qty),
  isbn_(isbn), author_(author)
{}

std::set<std::string> Book::keywords() const
{
    // name words + author words (split at punctuation, len >= 2)
    std::set<std::string> keys = parseStringToWords(name_);
    std::set<std::string> auth = parseStringToWords(author_);

    // union by inserting (std::set dedupes)
    std::set<std::string>::const_iterator it = auth.begin();
    while (it != auth.end()) { keys.insert(*it); ++it; }

    // ISBN verbatim (no splitting), but lowercased for case-insensitive index
    std::string isbn_lower = convToLower(isbn_);
    if (!isbn_lower.empty()) keys.insert(isbn_lower);

    keys.insert("book");
    return keys;
}

std::string Book::displayString() const
{
    std::ostringstream oss;
    oss << name_ << "\n";
    oss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
    oss.setf(std::ios::fixed); 
    oss << std::setprecision(2) << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Book::dump(std::ostream& os) const
{
    os << "book\n";
    os << name_ << "\n";
    os.setf(std::ios::fixed);
    os << std::setprecision(2) << price_ << "\n";
    os << qty_ << "\n";
    os << isbn_ << "\n";
    os << author_ << "\n";
}
