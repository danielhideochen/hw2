#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <cctype>

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
    for (size_t i = 0; i < products_.size(); ++i) delete products_[i];
    std::map<std::string, User*>::iterator it = users_.begin();
    while (it != users_.end()) { delete it->second; ++it; }
}

std::string MyDataStore::toLowerCopy(const std::string& s) const {
    std::string t = s; convToLower(t); return t;
}

void MyDataStore::addProduct(Product* p) {
    if (!p) return;
    products_.push_back(p);
    std::set<std::string> keys = p->keywords();
    std::set<std::string>::const_iterator it = keys.begin();
    while (it != keys.end()) { index_[*it].insert(p); ++it; }
}

void MyDataStore::addUser(User* u) {
    if (!u) return;
    users_[toLowerCopy(u->getName())] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::vector<std::string> q = terms;
    for (size_t i = 0; i < q.size(); ++i) convToLower(q[i]);

    std::set<Product*> result;
    if (q.empty()) return std::vector<Product*>();

    std::map<std::string, std::set<Product*> >::iterator f = index_.find(q[0]);
    if (f != index_.end()) result = f->second;

    if (type == 0) { // AND
        for (size_t t = 1; t < q.size(); ++t) {
            std::map<std::string, std::set<Product*> >::iterator g = index_.find(q[t]);
            if (g == index_.end()) { result.clear(); break; }
            result = setIntersection(result, g->second);
            if (result.empty()) break;
        }
    } else { // OR
        for (size_t t = 1; t < q.size(); ++t) {
            std::map<std::string, std::set<Product*> >::iterator g = index_.find(q[t]);
            if (g != index_.end()) result = setUnion(result, g->second);
        }
    }

    std::vector<Product*> hits;
    for (size_t i = 0; i < products_.size(); ++i)
        if (result.find(products_[i]) != result.end()) hits.push_back(products_[i]);
    return hits;
}

bool MyDataStore::addToCart(const std::string& user, Product* p) {
    if (!p || users_.find(user) == users_.end()) return false;
    carts_[user].push_back(p);
    return true;
}

void MyDataStore::viewCart(const std::string& user, std::ostream& os) {
    if (users_.find(user) == users_.end()) { os << "Invalid username\n"; return; }
    std::vector<Product*>& cart = carts_[user];
    size_t idx = 1;
    for (size_t i = 0; i < cart.size(); ++i) {
        os << "Item " << idx++ << "\n" << cart[i]->displayString() << "\n\n";
    }
}

void MyDataStore::buyCart(const std::string& user) {
    std::map<std::string, User*>::iterator it = users_.find(user);
    if (it == users_.end()) { std::cout << "Invalid username\n"; return; }
    User* u = it->second;
    std::vector<Product*>& cart = carts_[user];
    std::vector<Product*> remain;
    for (size_t i = 0; i < cart.size(); ++i) {
        Product* p = cart[i];
        if (p->getQty() > 0 && u->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            u->deductAmount(p->getPrice());
        } else {
            remain.push_back(p);
        }
    }
    cart.swap(remain);
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>\n";
    for (size_t i = 0; i < products_.size(); ++i) products_[i]->dump(ofile);
    ofile << "</products>\n<users>\n";
    std::map<std::string, User*>::iterator it = users_.begin();
    while (it != users_.end()) { it->second->dump(ofile); ++it; }
    ofile << "</users>\n";
}