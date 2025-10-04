#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>
#include <set>
#include <vector>
#include <string>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    // required by datastore.h
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    // helpers used by amazon.cpp
    bool addToCart(const std::string& usernameLower, Product* p);
    void viewCart(const std::string& usernameLower, std::ostream& os);
    void buyCart(const std::string& usernameLower);

private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;                   // key: lower(username)
    std::map<std::string, std::set<Product*> > index_;     // keyword -> products
    std::map<std::string, std::vector<Product*> > carts_;  // FIFO

    std::string toLowerCopy(const std::string& s) const;
};

#endif