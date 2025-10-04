#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Clothing::Clothing(const std::string& name, double price, int qty,
                   const std::string& size, const std::string& brand)
: Product("clothing", name, price, qty),
  size_(size), brand_(brand)
{}

std::set<std::string> Clothing::keywords() const
{
    // name words + brand words (size is NOT a keyword)
    std::set<std::string> keys = parseStringToWords(name_);
    std::set<std::string> br = parseStringToWords(brand_);

    std::set<std::string>::const_iterator it = br.begin();
    while (it != br.end()) { keys.insert(*it); ++it; }

    keys.insert("clothing");
    return keys;
}

std::string Clothing::displayString() const
{
    std::ostringstream oss;
    oss << name_ << "\n";
    oss << "Size: " << size_ << " Brand: " << brand_ << "\n";
    oss.setf(std::ios::fixed);
    oss << std::setprecision(2) << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Clothing::dump(std::ostream& os) const
{
    os << "clothing\n";
    os << name_ << "\n";
    os.setf(std::ios::fixed);
    os << std::setprecision(2) << price_ << "\n";
    os << qty_ << "\n";
    os << size_ << "\n";
    os << brand_ << "\n";
}