#include <algorithm>
#include "string_set.h"
#include <iostream>

string_set::string_set() {
    raiz = new Nodo();
    _cantidadDeElementos = 0;
}


string_set::~string_set() {
    /* @corregir(ivan): Sin terminar */
}


string_set::string_set(const string_set & other) {
    raiz = new Nodo();
    _cantidadDeElementos = 0;
    auto it = other.cbegin();
    while (!it.isEnd()){
        insert(*it);
        ++it;
    }
}


string_set& string_set::operator=(const string_set& otro)  {
    this->clear();
    auto it = otro.cbegin();
    while (!it.isEnd()){
        auto aInsertar = *it;
        this->insert(aInsertar);
        ++it;
    }
    return *this;
}


bool string_set::operator==(const string_set& otro) const {
    if (this->size() != otro.size()) {
        return false;
    } else {
        auto itOtro = otro.cbegin();
        while(!itOtro.isEnd()) { /* @comentario(ivan): O(sn) */
            auto elemOtro = *itOtro;
            if (this->count(elemOtro) == 0) { /* @comentario(ivan): O(S) */
                return false;
            }
            ++itOtro;
        }
    }
    return true;
}

size_t string_set::size() const {
    return this->_cantidadDeElementos;
}


bool string_set::empty() const {
    return this->raiz->hijos.empty();
}

void string_set::clear() {
    auto it = this->begin();
    while (it != end()){
        it = erase(it);
    }
}

string_set::iterator string_set::begin() {
    auto it = new string_set::iterator(this);
    return *it;
}


string_set::const_iterator string_set::end() const {
    auto it = string_set::const_iterator(this);
    it.elementoActual = "";
    return it;
}


string_set::const_iterator string_set::cbegin() const {
    auto it = new string_set::const_iterator(this);
    return *it;
}


string_set::const_iterator string_set::cend() const {
    auto it = new string_set::const_iterator(this);
    it->elementoActual = "";
    return *it;
}

string_set::iterator string_set::find(const string_set::value_type& elem){
    Nodo* nodoEncontrado = findNodo(elem);
    if (nodoEncontrado == nullptr) {
        return end();
    }
    else {
        auto it = string_set::iterator(this);
        it.elementoActual = elem;
        return it;
    }
}

string_set::const_iterator string_set::find(const string_set::value_type& elem) const {
    Nodo* nodoEncontrado = findNodo(elem);
    if (nodoEncontrado == nullptr) {
        return end();
    }
    else {
        auto it = string_set::const_iterator(this);
        it.elementoActual = elem;
        return it;
    }
}

pair<string_set::iterator, bool> string_set::insert(const string_set::value_type& elem) {
    bool inserta = false;
    string elemAInsertar = elem;
    iterator it = find(elem);/* @comentario(ivan): O(S) */
    if (!it.isEnd()) {
        pair<string_set::iterator, bool> res = make_pair(this->end(), inserta);
        return res;
    } else {
        int index = 0;
        Nodo *actual = raiz;
        while (index < elem.size()) { /* @comentario(ivan): O(S) */
            if (actual->hijos.count(elem[index]) == 0) {
                Nodo *nodoSiguiente = new Nodo();
                actual->hijos.insert(pair<char, Nodo *>(elem[index], nodoSiguiente));
            }
            actual = actual->hijos[elem[index]];
            index++;
        }
        actual->esClave = true; /* @comentario(ivan): O(copy(T)) */
        inserta = true;
        this->_cantidadDeElementos++;
        pair<string_set::iterator, bool> res;
        auto it = iterator(this);
        it.elementoActual = elem;
        res = make_pair(it, inserta);
        return res;
    }
}


string_set::size_type string_set::erase(const string_set::value_type& elem) {
    string elemABorrar = elem;
    Nodo* actual = findNodo(elem);
    auto rama = getBranch(elem);
    if(count(elem) == 0){
        return 0;
    }
    actual->esClave = false;
    this->_cantidadDeElementos--;
    if (!actual->hijos.empty()) {//Si es prefijo de otra clave...
        return 1;
    }
    actual = rama.back(); // Ahora actual es el padre
    rama.pop_back();
    while (!rama.empty() && actual->hijos.size() <= 1 && actual->esClave == false) {
        actual->hijos.erase(elemABorrar.back());
        if (actual->hijos.empty()){
            delete actual;
        }
        actual = rama.back();
        rama.pop_back();
        elemABorrar.pop_back();
    }
    actual->hijos.erase(elemABorrar.back());
    return 1;
}


string_set::iterator string_set::erase(string_set::iterator pos) {
    auto elem = pos.elementoActual;
    auto it = ++pos;
    erase(elem);
    return it;
}

string_set::size_type string_set::count(const string_set::value_type& elem) const {
    if (find(elem).isEnd()) {
        return 0;
    } else {
        return 1;
    }
}

string string_set::primerElemento() const {
    Nodo *nodoActual = raiz;
    string elem = "";
    while (nodoActual->hijos.size() != 0 && nodoActual->esClave == false) {
        auto tuplaPrimera = nodoActual->hijos.begin();
        char primerChar = (*tuplaPrimera).first;
        elem += primerChar;
        nodoActual = nodoActual->hijos[primerChar];
    }
    return elem;
}

string string_set::siguienteElemento(string elemActual) const {
    Nodo *nodoActual = findNodo(elemActual);
    if(nodoActual == nullptr){return "";}
    string elem = elemActual;
    if (nodoActual->hijos.size() > 0) { //la clave actual es substring de la siguiente.
        bool primeraVez = true;
        while (nodoActual->hijos.size() != 0 && nodoActual->esClave == false || primeraVez) {
            primeraVez = false;
            auto tuplaPrimera = nodoActual->hijos.begin();
            char primerChar = (*tuplaPrimera).first;
            elem += primerChar;
            nodoActual = nodoActual->hijos[primerChar];
        }
        return elem;
    } else { //la clave siguiente contiene substring de la actual (o es totalmente disjunta)

        vector<Nodo *> branch = getBranch(elemActual);
        unsigned long index = branch.size() - 1;
        nodoActual = branch[index];
        bool flag = true; /* @comentario(ivan): flag es un nombre muy poco declarativo */
        /* @comentario(ivan): Todo este algoritmo es muy dificil de leer, traten de simplificarlo.
         * Si no se puede simplificar al menos pongan comentarios guiando la lectura del algoritmo. */
        while (index > 0 && flag) {
            auto it = nodoActual->hijos.begin();
            while (it->first < elem.back() && it != nodoActual->hijos.end()) {
                it++;
            }
            if (it != nodoActual->hijos.end()) {
                it++;
            }
            elem.pop_back();

            if (it == nodoActual->hijos.end()) {
                nodoActual = branch[index - 1];
                index--;
            } else {
                char c = it->first;
                elem.push_back(c);
                flag = false;
                nodoActual = nodoActual->hijos[it++->first];
            }
        }
        if (nodoActual == false) {
            return "";
        } else {
            if (index != 0) { //longest common substring not empty

                while (nodoActual->esClave == false) {
                    elem += (*nodoActual->hijos.begin()).first;
                    nodoActual = (*nodoActual->hijos.begin()).second;
                }
            } else { //longest common substring is ""
                auto it = raiz->hijos.begin();

                while (it->first <= elem[0] && it != raiz->hijos.end()) {
                    it++;
                }
                if(it==raiz->hijos.end()){return "";}
                elem = "";
                elem += it->first;
                nodoActual = raiz->hijos[it->first];
                while (nodoActual->esClave == false) {
                    elem += (*nodoActual->hijos.begin()).first;
                    nodoActual = (*nodoActual->hijos.begin()).second;
                }
            }
        }
        return elem;
        // ¯\_(ツ)_/¯
    }
}

string_set::Nodo* string_set::findNodo(string elem) const {
    int index = 0;
    string_set::Nodo* actual = raiz;
    while (index < elem.size() && actual->hijos.count(elem[index]) != 0) {
        actual = actual->hijos[elem[index]];
        index++;
    }
    if (index == elem.size() && actual->esClave != false) {
        return actual;
    } else {
        return nullptr;
    }
}


vector<string_set::Nodo*> string_set::getBranch(string elem) const {
    vector<string_set::Nodo*> branch = vector<string_set::Nodo*>();
    int index = 0;
    string_set::Nodo *actual = raiz;
    while (index != elem.size() && actual->hijos.count(elem[index]) != 0) {
        branch.push_back(actual);
        actual = actual->hijos[elem[index]];
        index++;
    }
    return branch;
}


bool string_set::operator!=(const string_set &otro) const {
    return !(*this == otro); /* @corregir(ivan): Si van a hacer esto al final, hubieran dejado sólo esta linea. */
}


string_set::iterator string_set::end() {
    auto it = string_set::iterator(this);
    it.elementoActual = "";
    return it;
}

string_set::const_iterator string_set::begin() const {
    auto it = new string_set::const_iterator(this);
    return *it;
}


/////////////////////  empieza iterator /////////////////////
/* @comentario(ivan): Queda mejor si lo definen en otro archivo. Este ya es largo :( */

string_set::iterator::iterator(const string_set* set) {
    this->elementoActual = set->primerElemento(); /* @comentario(ivan): O(S) */
    this->set = set;
}

string string_set::iterator::operator*() {
    value_type elem = this->elementoActual;
    return elem;
}

string* string_set::iterator::operator->() {
    value_type* elem = new value_type(this->elementoActual);
    return elem;
}

string_set::iterator::iterator() {
    set = nullptr;
    elementoActual = "";
}

bool string_set::iterator::isEnd() {
    return this->elementoActual == "";
}

string_set::iterator& string_set::iterator::operator++() {
    this->elementoActual = this->set->siguienteElemento(elementoActual);
    return *this;
}

string_set::value_type string_set::iterator::getElemento() {
    return elementoActual;
}

bool string_set::iterator::operator==(const string_set::iterator& o_it) const{
    return (o_it.set == this->set) && (o_it.elementoActual == this->elementoActual);
}

bool string_set::iterator::operator!=(const string_set::iterator& o_it) const{
    return not( *this==o_it  );
}

/////////////////////  empieza const_iterator /////////////////////

string string_set::const_iterator::operator*() {
    value_type elem = value_type(this->elementoActual);
    return elem;
}

string* string_set::const_iterator::operator->() {
    value_type* elem = new value_type(this->elementoActual);
    return elem;
}

string_set::const_iterator::const_iterator() {
    set = nullptr;
    elementoActual = "";
}

bool string_set::const_iterator::isEnd() {
    return elementoActual == "";
}

string_set::value_type string_set::const_iterator::getElemento () {
    return elementoActual;
}

string_set::const_iterator::const_iterator(const string_set* set) {
    this->elementoActual = set->primerElemento(); /* @comentario(ivan): O(S) */
    this->set = set;
}

string_set::const_iterator& string_set::const_iterator::operator++() {
    this->elementoActual = this->set->siguienteElemento(elementoActual);
    return *this;
}

bool string_set::const_iterator::operator==(const string_set::const_iterator& o_it)const {
    return (o_it.set == this->set) && (o_it.elementoActual == this->elementoActual);
}

bool string_set::const_iterator::operator!=(const string_set::const_iterator& o_it) const{
    return not( *this==o_it );
}

