#include "string_map.h"

string_map::string_map(){
    raiz = new Nodo(NULL);
}

string_map::~string_map() {

}

string_map::string_map(const string_map &) {

}

string_map &string_map::operator=(const string_map &) {
    return <#initializer#>;
}

bool string_map::operator==(const string_map &otro) const {
    return false;
}

size_t string_map::size() const {
    return 0;
}

bool string_map::empty() const {
    bool empty = true;
    for (int i = 0; i < 27 && empty; ++i) {
        if (raiz->hijos[i] != nullptr) {
            empty = false;
        }
    }
    return empty;
}

mapped_type &string_map::operator[](const string_map::key_type &key) {
    return <#initializer#>;
}

mapped_type &string_map::at(const string_map::key_type &key) {
    return <#initializer#>;
}

const mapped_type &string_map::at(const string_map::key_type &key) const {
    return <#initializer#>;
}

void string_map::clear() {

}

string_map::iterator string_map::begin() {
    return string_map::iterator();
}

string_map::iterator string_map::end() {
    return string_map::iterator();
}

string_map::const_iterator string_map::begin() const {
    return string_map::const_iterator();
}

string_map::const_iterator string_map::end() const {
    return string_map::const_iterator();
}

string_map::const_iterator string_map::cbegin() const {
    return string_map::const_iterator();
}

string_map::const_iterator string_map::cend() const {
    return string_map::const_iterator();
}

string_map::iterator string_map::find(const string_map::key_type &key) {
    return string_map::iterator();
}

string_map::const_iterator string_map::find(const string_map::key_type &key) const {
    return string_map::const_iterator();
}

pair<string_map::iterator, bool> string_map::insert(const string_map::value_type &value) {
    return pair<string_map::iterator, bool>();
}

string_map::size_type string_map::erase(const string_map::key_type &key) {
    return 0;
}

string_map::size_type string_map::count(const string_map::key_type &key) const {
    return 0;
}
