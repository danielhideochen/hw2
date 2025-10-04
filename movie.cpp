#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Movie::Movie(const std::string& name, double price, int qty,
             const std::string& genre, const std::string& rating)
: Product("movie", name, price, qty),
  genre_(genre), rating_(rating)
{}

std::set<std::string> Movie::keywords() const
{
    // name words + genre verbatim (no punctuation splitting)
    std::set<std::string> keys = parseStringToWords(name_);
    std::string g = convToLower(genre_);

    if (!g.empty()) keys.insert(g);

    keys.insert("movie");
    return keys;
}

std::string Movie::displayString() const
{
    std::ostringstream oss;
    oss << name_ << "\n";
    oss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    oss.setf(std::ios::fixed);
    oss << std::setprecision(2) << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Movie::dump(std::ostream& os) const
{
    os << "movie\n";
    os << name_ << "\n";
    os.setf(std::ios::fixed);
    os << std::setprecision(2) << price_ << "\n";
    os << qty_ << "\n";
    os << genre_ << "\n";
    os << rating_ << "\n";
}