#include <algorithm>
#include "string_map.h"
#include <iostream>



template<typename T>
string_map<T>::string_map() {
    raiz = new Nodo(nullptr);
    _cantidadDeClaves = 0;
}

template<typename T>
string_map<T>::~string_map() {
    /* @corregir(ivan): Sin terminar */
}

template<typename T>
string_map<T>::string_map(const string_map &) {
    /* @corregir(ivan): Sin terminar */
}

template<typename T>
string_map<T>& string_map<T>::operator=(const string_map &otro)  {
    this->clear();
    auto it = iterator(&otro);
    while (!it.isEnd()){ /* @comentario(ivan): O(sn) */
        auto aInsertar = *it;
        this->insert(aInsertar); /* @comentario(ivan): O(S + copy(value_type)) */
        ++it;
    }
    return *this;
}

template<typename T>
bool string_map<T>::operator==(const string_map<T> &otro) const {
    if (this->size() != otro.size()) {
        return false;
    } else {
        auto itOtro = otro.cbegin();
        while(!itOtro.isEnd()) { /* @comentario(ivan): O(sn) */
            auto parOtro = *itOtro;
            if (this->count(parOtro.first) == 0) { /* @comentario(ivan): O(S) */
                return false;
            }
            if (otro.at(parOtro.first) != this->at(parOtro.first)){ /* @comentario(ivan): O(S + cmp(T)) */
                return false;
            }
        }
    }
    return true;
}

template<typename T>
size_t string_map<T>::size() const {
    return this->_cantidadDeClaves;
}

template<typename T>
bool string_map<T>::empty() const {
    return this->raiz->hijos.empty();
}

template<typename mapped_type>
mapped_type &string_map<mapped_type>::operator[](const string_map<mapped_type>::key_type &key) {
    if (find(key).isEnd()) {
        insert(make_pair(key, mapped_type()));
    }
    return at(key);
}

template<typename mapped_type>
mapped_type &string_map<mapped_type>::at(const string_map<mapped_type>::key_type &key) {

    int index = 0;
    Nodo *actual = raiz;
    while (index != key.size() && actual->hijos.count(key[index]) != 0) {
        actual = actual->hijos[key[index]];
        index++;
    }
    return *(actual->valor);

}

template<typename T>
const T &string_map<T>::at(const string_map<T>::key_type &key) const {
    int index = 0;
    Nodo *actual = raiz;
    while (index != key.size() && actual->hijos.count(key[index]) != 0) {
        actual = actual->hijos[key[index]];
        index++;
    }
    return *(actual->valor);
}

template<typename T>
void string_map<T>::clear() {
    auto it = this->begin();
    while (!it.isEnd()){
        erase(it);
        ++it;
    }
}

template<typename T>
typename string_map<T>::iterator string_map<T>::begin() {
    auto it = new string_map<T>::iterator(this);
    /* @comentario(ivan): No hace falta cambiar la clave y valor actual del iterador recién creado.
     * Según el constructor que hicieron, ya se crea apuntando a la primera clave. */
    it->claveActual = primeraClave();
    it->valorActual = &at(it->claveActual);
    return *it;
}

template<typename T>
typename string_map<T>::iterator string_map<T>::end() const {
    /* @comentario(ivan): acá podrían usar un constructor vacío como hacen con el cons_iterator (linea 131 de este archivo) */
    auto it = string_map<T>::iterator(this);

    it.claveActual = "";
    it.valorActual = nullptr;
    return it;
}

template<typename T>
typename string_map<T>::const_iterator string_map<T>::cbegin() const {
    auto it = new string_map<T>::const_iterator(this);
    it->claveActual = "";
    it->valorActual = nullptr;
    return *it;
}

template<typename T>
typename string_map<T>::const_iterator string_map<T>::cend() const {
    return string_map<T>::const_iterator();
}

template<typename T>
typename string_map<T>::iterator string_map<T>::find(const string_map<T>::key_type &key) {
    Nodo *nodoEncontrado = findNodo(key);
    if (nodoEncontrado == nullptr) {
        return end();
    }
    else {
        auto it = string_map<T>::iterator(this);
        it.claveActual = key;
        /* @corregir(ivan): No actualizan el valor al cual apunta el iterador ? */
        return it;
    }
}

template<typename T>
/* @corregir(ivan): Por qué el algoritmo del find para el string_map const difiere del algoritmo del find para el string_map ? */
typename string_map<T>::const_iterator string_map<T>::find(const string_map<T>::key_type &key) const {
    int index = 0;
    Nodo *actual = raiz;
    while (index != key.size() && actual->hijos.count(key[index]) != 0) {
        actual = actual->hijos[key[index]];
        index++;
    }
    if (index == key.size() && actual->valor != nullptr) {
        auto it = string_map<T>::const_iterator(this);
        it.claveActual = key;
        /* @corregir(ivan): No actualizan el valor al cual apunta el iterador ? */
        return it;
    } else {
        return this->cend();
    }
}

template<typename T>
pair<typename string_map<T>::iterator, bool> string_map<T>::insert(const string_map<T>::value_type &value) {

    bool inserta = false;
    string clave = value.first;
    T valor = value.second;
    iterator it = find(clave);/* @comentario(ivan): O(S) */
    if (!it.isEnd()) {
        pair<string_map<T>::iterator, bool> res = make_pair(this->end(), inserta);
        return res;
    } else {
        int index = 0;
        Nodo *actual = raiz;
        while (index < clave.size()) { /* @comentario(ivan): O(S) */
            if (actual->hijos.count(clave[index]) == 0) {
                Nodo *nodoSiguiente = new Nodo(nullptr);
                actual->hijos.insert(pair<char, Nodo *>(clave[index], nodoSiguiente));
            }
            actual = actual->hijos[clave[index]];
            index++;
        }
        actual->valor = new T(value.second); /* @comentario(ivan): O(copy(T)) */
        inserta = true;
        this->_cantidadDeClaves++;
        pair<string_map<T>::iterator, bool> res;
        auto it = iterator(this);
        it.setClave(value.first);
        res = make_pair(it, inserta);
        return res;
    }
}

template<typename T>
typename string_map<T>::size_type string_map<T>::erase(const string_map<T>::key_type &key) {
    int index = 0;
    size_type elementosEliminados = 0;
    Nodo *actual = raiz;
    stack<Nodo *> nodosRecorridos;
    while (index != key.size()) {//Lo busca
        actual = actual->hijos[key[index]];
        nodosRecorridos.push(actual);
        index++;
    }
    nodosRecorridos.pop(); /* @comentario(ivan): Quito del stack el nodo que contiene el significado de la clave
    * Queda como primer nodo en el stack el padre del nodo actual.*/
    index--;
    actual->valor = nullptr;
    if (actual->hijos.empty()) {//Si no era prefijo de otra clave...
        delete actual;
        this->_cantidadDeClaves--;
        elementosEliminados++;
        while (!nodosRecorridos.empty()) {
            actual = nodosRecorridos.top();//Recorre hacia atrás
            nodosRecorridos.pop();
            if (actual->hijos.size() == 1) {//Si ese nodo solo existía para formar la clave que borré...
                delete actual;//...lo borra también...
                elementosEliminados++;
            } else {
                actual->hijos.erase(key[index]);//... y sino le saca el hijo correspondiente...
            }
            index--;//... iterando en reversa por la clave.
        }
    }
    return elementosEliminados;
}

template<typename T>
typename string_map<T>::size_type string_map<T>::count(const string_map<T>::key_type &key) const {
    auto it = string_map<T>::const_iterator(this); /* @comentario(ivan): Para qué se crea este const_iterator ? */
    if (find(key).isEnd()) {
        return 0;
    } else {
        return 1;
    }
}

template<typename T>
string string_map<T>::primeraClave() const {
    Nodo *nodoActual = raiz;
    string clave = "";

    while (nodoActual->hijos.size() != 0 && nodoActual->valor == nullptr) {
        auto tuplaPrimera = nodoActual->hijos.begin();
        char primerChar = (*tuplaPrimera).first;
        clave += primerChar;
        nodoActual = nodoActual->hijos[primerChar];
    }
    return clave;
}

template<typename T>
string string_map<T>::siguienteClave(string claveActual) const {
    Nodo *nodoActual = findNodo(claveActual);
    std::string clave = claveActual;
    if (nodoActual->hijos.size() > 0) { //la clave actual es substring de la siguiente.
        bool primeraVez = true;
        while (nodoActual->hijos.size() != 0 && nodoActual->valor == nullptr || primeraVez) {
            primeraVez = false;
            auto tuplaPrimera = nodoActual->hijos.begin();
            char primerChar = (*tuplaPrimera).first;
            clave += primerChar;
            nodoActual = nodoActual->hijos[primerChar];
        }
        return clave;
    } else { //la clave siguiente contiene substring de la actual (o es totalmente disjunta)

        vector<Nodo *> branch = getBranch(claveActual);
        unsigned long index = branch.size() - 1;
        nodoActual = branch[index];
        bool flag = true; /* @comentario(ivan): flag es un nombre muy poco declarativo */
        /* @comentario(ivan): Todo este algoritmo es muy dificil de leer, traten de simplificarlo.
         * Si no se puede simplificar al menos pongan comentarios guiando la lectura del algoritmo. */
        while (index > 0 && flag) {
            auto it = nodoActual->hijos.begin();
            while (it->first < clave.back() && it != nodoActual->hijos.end()) {
                it++;
            }
            if (it != nodoActual->hijos.end()) {

                it++;
            }
            clave.pop_back();

            if (it == nodoActual->hijos.end()) {

                nodoActual = branch[index - 1];
                index--;
            } else {

                char c = it->first;
                clave.push_back(c);
                flag = false;
                nodoActual = nodoActual->hijos[it++->first];
            }
        }
        if (nodoActual == nullptr) {
            return "";
        } else {
            if (index != 0) { //longest common substring not empty

                while (nodoActual->valor == nullptr) {
                    clave += (*nodoActual->hijos.begin()).first;
                    nodoActual = (*nodoActual->hijos.begin()).second;
                }
            } else { //longest common substring is ""
                auto it = raiz->hijos.begin();

                while (it->first <= clave[0] && it != raiz->hijos.end()) {

                    it++;
                }
                clave = "";
                clave += it->first;
                nodoActual = raiz->hijos[it->first];
                while (nodoActual->valor == nullptr) {
                    clave += (*nodoActual->hijos.begin()).first;
                    nodoActual = (*nodoActual->hijos.begin()).second;
                }
            }
        }
        return clave;
    }
}

template<typename T>
typename string_map<T>::Nodo *string_map<T>::findNodo(string key) const {
    int index = 0;
    string_map<T>::Nodo *actual = raiz;
    while (index < key.size() && actual->hijos.count(key[index]) != 0) {

        actual = actual->hijos[key[index]];
        index++;
    }
    if (index == key.size() && actual->valor != nullptr) {
        return actual;
    } else {
        return nullptr;
    }
}

template<typename T>
vector<typename string_map<T>::Nodo *> string_map<T>::getBranch(string key) const {
    vector<string_map<T>::Nodo *> branch = vector<string_map<T>::Nodo *>();
    int index = 0;
    string_map<T>::Nodo *actual = raiz;
    while (index != key.size() && actual->hijos.count(key[index]) != 0) {
        branch.push_back(actual);
        actual = actual->hijos[key[index]];
        index++;
    }
    return branch;
}
template <typename T>
bool string_map<T>::operator!=(const string_map<T> &otro) const {
    if (this->size() != otro.size()) {
        return true;
    } else {
        for (auto s : otro) {
            if (this->count(s.first) == 0) {
                return true;
            }
        }
    }
    return !(*this == otro); /* @corregir(ivan): Si van a hacer esto al final, hubieran dejado sólo esta linea. */
}

template <typename T>
typename string_map<T>::iterator string_map<T>::erase(string_map::iterator pos) {
    auto clave = pos.claveActual;
    ++pos;
    erase(clave);
    return pos;
}

/////////////////////  empieza iterator /////////////////////
/* @comentario(ivan): Queda mejor si lo definen en otro archivo. Este ya es largo :) */

template<typename T>
string_map<T>::iterator::iterator(const string_map *mapa) {
    this->claveActual = mapa->primeraClave(); /* @comentario(ivan): O(S) */
    if(this->claveActual!=""){
        this->valorActual = &(mapa->at(claveActual));
    }
    this->mapa = mapa;
}

template<typename T>
typename string_map<T>::iterator::value_type string_map<T>::iterator::operator*() {
    value_type pair = value_type(getClave(), *valorActual);
    return pair;
}

template<typename T>
typename string_map<T>::iterator::value_type* string_map<T>::iterator::operator->() {
    value_type* pair = new value_type(getClave(), *valorActual);
    return pair;
}

template<typename T>
string_map<T>::iterator::iterator() {
    mapa = nullptr;
    claveActual = "";
}

template<typename T>
bool string_map<T>::iterator::isEnd() {
    return this->claveActual == "";
}


template<typename T>
typename string_map<T>::iterator &string_map<T>::iterator::operator++() {
    this->claveActual = this->mapa->siguienteClave(claveActual);
    this->valorActual = &mapa->at(claveActual);
}

template<typename T>
typename string_map<T>::key_type string_map<T>::iterator::getClave() {
    return claveActual;
}

template<typename T>
void string_map<T>::iterator::setClave(string_map::key_type key) {
    claveActual = key;
}


template<typename T>
bool string_map<T>::iterator::operator==(const string_map<T>::iterator &o_it){
    return (o_it.mapa == this->mapa) && (o_it.claveActual == this->claveActual);
}

template<typename T>
bool string_map<T>::iterator::operator!=(const string_map<T>::iterator &o_it){
    return not((o_it.mapa == this->mapa) && (o_it.claveActual == this->claveActual));
}

/////////////////////  empieza const_iterator /////////////////////

template<typename T>
typename string_map<T>::const_iterator::value_type string_map<T>::const_iterator::operator*() {
    value_type pair = make_pair(claveActual, *valorActual);
    return pair;
}

template<typename T>
typename string_map<T>::const_iterator::value_type* string_map<T>::const_iterator::operator->() {
    return &(mapa->at(claveActual));
}

template<typename T>
string_map<T>::const_iterator::const_iterator() {
    mapa = nullptr;
    claveActual = "";
}

template<typename T>
bool string_map<T>::const_iterator::isEnd() {
    return claveActual == "";
}

template<typename T>
void string_map<T>::const_iterator::setClave(string_map<T>::key_type key) {
    claveActual = key;
}

template<typename T>
typename string_map<T>::key_type string_map<T>::const_iterator::getClave() {
    return claveActual;
}

template<typename T>
string_map<T>::const_iterator::const_iterator(const string_map<T> *mapa) {
    this->claveActual = mapa->primeraClave(); /* @comentario(ivan): O(S) */
    this->valorActual = &mapa->at(claveActual);
    this->mapa = mapa;
}

template<typename T>
typename string_map<T>::const_iterator &string_map<T>::const_iterator::operator++() {
    this->claveActual = this->mapa->siguienteClave(claveActual);
    this->valorActual = &mapa->at(claveActual);
    return *this;
}

template<typename T>
bool string_map<T>::const_iterator::operator==(typename string_map<T>::const_iterator &o_it) {
    return (o_it.mapa == this->mapa) && (o_it.claveActual == this->claveActual);
}

template<typename T>
bool string_map<T>::const_iterator::operator!=(typename string_map<T>::const_iterator &o_it) {
    return not((o_it.mapa == this->mapa) && (o_it.claveActual == this->claveActual));;
}
