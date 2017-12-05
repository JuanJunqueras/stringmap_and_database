#include <algorithm>
#include "string_set.h"
#include <iostream>

string_set::string_set() {
    diccionario = string_map<bool>();
}


string_set::~string_set() {
    diccionario.clear();
}


string_set::string_set(const string_set& other) {
    diccionario = string_map<bool>(other.diccionario);
}

string_set::string_set(const linear_set<string>& other){
    diccionario.clear();
    for (auto s : other){
        insert(s);
    }
}


string_set& string_set::operator=(const string_set& otro)  {
    this->diccionario = otro.diccionario;
}


bool string_set::operator==(const string_set& otro) const {
    return this->diccionario==otro.diccionario;
}

size_t string_set::size() const {
    return this->diccionario.size();
}


bool string_set::empty() const {
    return this->diccionario.empty();
}

void string_set::clear() {
    this->diccionario.clear();
}

string_set::iterator string_set::begin() {
    return string_set::iterator(this);
}

string_set::const_iterator string_set::begin() const {
    return string_set::const_iterator(this);
}


string_set::iterator string_set::end() {
    auto it = string_set::iterator(this);
    it.vastago = this->diccionario.end();
    return it;
}

string_set::const_iterator string_set::end() const {
    auto it = string_set::const_iterator(this);
    it.vastago = this->diccionario.cend();
    return it;
}


string_set::const_iterator string_set::cbegin() const {
    auto it = string_set::const_iterator(this);
    return it;
}


string_set::const_iterator string_set::cend() const {
    auto it = string_set::const_iterator(this);
    it.vastago = this->diccionario.cend();
    return it;
}

string_set::iterator string_set::find(const string_set::value_type& elem){
    string_set::iterator it = this->begin();
    it.vastago = this->diccionario.find(elem);
    return it;
}

//string_set::const_iterator string_set::find(const string_set::value_type& elem) const {
//    string_set::const_iterator it = this->cbegin();
//    it.vastago = this->diccionario.find(elem);
//    return it;
//}

pair<string_set::iterator, bool> string_set::insert(const string_set::value_type& elem) {
    pair<string_map<bool>::iterator, bool> result = this->diccionario.insert(make_pair(elem,true));
    auto it = this->begin();
    it.vastago = result.first;
    return make_pair(it, result.second);
    }


string_set::size_type string_set::erase(const string_set::value_type& elem) {
    return this->diccionario.erase(elem);
}


string_set::iterator string_set::erase(string_set::iterator pos) {
    auto it = string_set::iterator(this);
    it.vastago = this->diccionario.erase(pos.vastago);
    return it;
}

string_set::size_type string_set::count(const string_set::value_type& elem) const {
    return this->diccionario.count(elem);
}


bool string_set::operator!=(const string_set &otro) const {
    return !(*this == otro);
}


/////////////////////  empieza iterator /////////////////////

string_set::iterator::iterator(const string_set* set) {
    this->vastago = string_map<bool>::iterator(&set->diccionario);
}

string_set::iterator::value_type string_set::iterator::operator*() {
    return (*vastago).first;
}

string_set::iterator::pointer string_set::iterator::operator->() {
   this->stringActual = &this->vastago.operator->()->first;
    return stringActual;
}

string_set::iterator::iterator() {
    set = nullptr;
}

bool string_set::iterator::isEnd() {
    return vastago.isEnd();
}

string_set::iterator& string_set::iterator::operator++() {
    this->stringActual = nullptr;
    this->vastago.operator++();
    return *this;
}


bool string_set::iterator::operator==(const string_set::iterator& o_it) const{
    return (o_it.set == this->set) && (this->elementoActual() == o_it.elementoActual());
}

bool string_set::iterator::operator!=(const string_set::iterator& o_it) const{
    return not( *this==o_it  );
}

string_set::iterator::value_type string_set::iterator::elementoActual() const {
    return this->vastago.getClave();
}

/////////////////////  empieza const_iterator /////////////////////
string_set::const_iterator::value_type string_set::const_iterator::elementoActual() const {
    return this->vastago.getClave();
}

string_set::const_iterator::value_type string_set::const_iterator::operator*() {
    return (*vastago).first;
}

string_set::const_iterator::pointer string_set::const_iterator::operator->() {
    this->stringActual = &this->vastago.operator->()->first;
    return stringActual;
}


bool string_set::const_iterator::isEnd() {
    return this->vastago.isEnd();
}


string_set::const_iterator::const_iterator(const string_set* set) {
    this->vastago = set->diccionario.cbegin(); /* @comentario(ivan): O(S) */
    this->set = set;
}

string_set::const_iterator& string_set::const_iterator::operator++() {
    this->stringActual = nullptr;
    this->vastago.operator++();
    return *this;
}

bool string_set::const_iterator::operator==(const string_set::const_iterator& o_it)const {
    return (o_it.set == this->set) &&
            (this->vastago.getClave()==o_it.vastago.getClave());
}

bool string_set::const_iterator::operator!=(const string_set::const_iterator& o_it) const{
    return not( *this==o_it );
}

