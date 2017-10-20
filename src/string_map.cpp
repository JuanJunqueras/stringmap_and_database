#include <algorithm>
#include "string_map.h"
#include <iostream>
template <typename T>
string_map<T>::string_map(){
    raiz = new Nodo(nullptr);
    _cantidadDeClaves = 0;
}

template <typename T>
string_map<T>::~string_map() {

}

template <typename T>
string_map<T>::string_map(const string_map &) {

}

template <typename T>
string_map<T> &string_map<T>::operator=(const string_map &otro) {
    raiz = otro.raiz;
    _cantidadDeClaves=otro._cantidadDeClaves;
}

template <typename T>
bool string_map<T>::operator==(const string_map &otro) const {
    return false;
}

template <typename T>
size_t string_map<T>::size() const {
    return this->_cantidadDeClaves;
}

template <typename T>
bool string_map<T>::empty() const {
    return this->raiz->hijos.empty();
}

template <typename mapped_type>
mapped_type &string_map<mapped_type>::operator[](const string_map<mapped_type>::key_type &key) {
    if(find(key).isEnd()){
        insert(make_pair(key,mapped_type()));
    }
    return at(key);
}

template<typename mapped_type>
mapped_type &string_map<mapped_type>::at(const string_map<mapped_type>::key_type &key) {

    int index = 0;
    Nodo* actual = raiz;
    while (index != key.size() && actual->hijos.count(key[index]) != 0) {
        actual = actual->hijos[key[index]];
        index++;
    }
    return *(actual->valor);

}

template <typename T>
const T &string_map<T>::at(const string_map<T>::key_type &key) const {
    return at(key);
}

template <typename T>
void string_map<T>::clear() {
}

template <typename T>
typename string_map<T>::iterator string_map<T>::begin() {
    auto it = new string_map<T>::iterator(this);
    it->claveActual = primeraClave();
    it->valorActual = &at(it->claveActual);
    return *it;
}

template <typename T>
typename string_map<T>::iterator string_map<T>::end() {
    auto it = new string_map<T>::iterator(this);
    it->claveActual="";
    it->valorActual = nullptr;
    return *it;
}

template <typename T>
typename string_map<T>::const_iterator string_map<T>::begin() const {
    return string_map<T>::const_iterator();
}

template <typename T>
typename string_map<T>::const_iterator string_map<T>::end() const {
    return string_map<T>::const_iterator();
}

template <typename T>
typename string_map<T>::const_iterator string_map<T>::cbegin() const {
    return string_map<T>::const_iterator();
}

template <typename T>
typename string_map<T>::const_iterator string_map<T>::cend() const {
    return string_map<T>::const_iterator();
}

template <typename T>
typename string_map<T>::iterator string_map<T>::find(const string_map<T>::key_type &key) {

    Nodo* nodoEncontrado = findNodo(key);
    if(nodoEncontrado==nullptr){return end();}
    else{
        auto it = string_map<T>::iterator(this);
        it.claveActual = key;
        return it;
    }
}

template <typename T>
typename string_map<T>::const_iterator string_map<T>::find(const string_map<T>::key_type &key) const {

    int index = 0;
    Nodo* actual = raiz;
    while (index != key.size() && actual->hijos.count(key[index]) != 0) {
        actual = actual->hijos[key[index]];
        index++;
    }

    if (index == key.size() && actual->valor != nullptr) {
        auto it = string_map<T>::const_iterator(this);
        it.claveActual = key;
        return it;
    } else {
        return this->end();
    }
}

template<typename T>
pair<typename string_map<T>::iterator, bool> string_map<T>::insert(const string_map<T>::value_type &value) {

    bool inserta = false;
    string clave = value.first;
    T valor = value.second;

    auto it = find(clave);

    if (!it.isEnd()) {

        pair<string_map<T>::iterator, bool> res = make_pair(this->end(), inserta);
        return res;
    }
    else {

        int index = 0;
        Nodo* actual = raiz;
        while (index < clave.size()) {

            if (actual->hijos.count(clave[index]) == 0) {

                Nodo* nodoSiguiente = new Nodo(nullptr);
                actual->hijos.insert(pair<char,Nodo*>(clave[index], nodoSiguiente));
            }
            actual = actual->hijos[clave[index]];
            index++;
        }
        actual->valor = new T(value.second);
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
    Nodo* actual = raiz;
    stack<Nodo*> nodosRecorridos;
    while (index != key.size()) {//Lo busca
         actual = actual->hijos[key[index]];
         nodosRecorridos.push(actual);
         index++;
    }
    nodosRecorridos.pop();
    index--;
    actual->valor = nullptr;
    if (actual->hijos.empty()){//Si no era prefijo de otra clave...
        delete actual;
        this->_cantidadDeClaves--;
        while (!nodosRecorridos.empty()){
            actual = nodosRecorridos.top();//Recorre hacia atrás
            nodosRecorridos.pop();
            if (actual->hijos.size() == 1){//Si ese nodo solo existía para formar la clave que borré...
                delete actual;//...lo borra también...
            } else {
                actual->hijos.erase(key[index]);//... y sino le saca el hijo correspondiente...
            }
            index--;//... iterando en reversa por la clave.
        }
    }
    return this->size();
}

template <typename T>
typename string_map<T>::size_type string_map<T>::count(const string_map<T>::key_type &key) const {
    return 0;
}

template <typename T>
string string_map<T>::primeraClave() const {
    Nodo* nodoActual = raiz;
    string clave = "";

    while(nodoActual->hijos.size()!=0&&nodoActual->valor== nullptr){
        auto tuplaPrimera = nodoActual->hijos.begin();
        char primerChar = (*tuplaPrimera).first;
        clave+=primerChar;
        nodoActual= nodoActual->hijos[primerChar];
    }
    return clave;
}
template <typename T>
string string_map<T>::siguienteClave(string claveActual) const {
    Nodo* nodoActual = findNodo(claveActual);
    std::string clave = claveActual;
    if(nodoActual->hijos.size()>0){
        bool primeraVez= true;
        while(nodoActual->hijos.size()!=0 && nodoActual->valor== nullptr||primeraVez){
            primeraVez=false;
            auto tuplaPrimera = nodoActual->hijos.begin();
            char primerChar = (*tuplaPrimera).first;
            clave+=primerChar;
            nodoActual= nodoActual->hijos[primerChar];
        }
        return clave;
    }
    else{
        cout << "entra aca" << endl ;
        vector<Nodo*> branch = getBranch(claveActual);
        unsigned long index = branch.size()-1;
        nodoActual = branch[index-1];
        bool flag = true;
        while(index!=1 && flag){
            auto it =nodoActual->hijos.begin();

            cout << index << endl;
            cout << clave<<endl;
            cout << it->first << " la puta madre" << endl;

            while(it->first<clave.back()&&it!=nodoActual->hijos.end()){
                it++;
            }
            if(it!=nodoActual->hijos.end()){it++;}
            clave.pop_back();
            cout << index << endl;
            if(it==nodoActual->hijos.end()){
                nodoActual = branch[index-1];
                index--;
            }
            else{

                char c = it->first;
                clave.push_back(c);
                flag = false;
                nodoActual=nodoActual->hijos[it++->first];

            }
        }


        cout << clave <<" es la clave" << endl;
        if (nodoActual == nullptr){
            return "";
        }
        else {
            cout << "entramos aca a veces!"<<endl;
            while(nodoActual->valor == nullptr){
                clave+=(*nodoActual->hijos.begin()).first;
                nodoActual = (*nodoActual->hijos.begin()).second;
            }
        }
        return clave;
    }

}
template <typename T>
typename  string_map<T>::Nodo * string_map<T>::findNodo(string key)const {
    int index = 0;
    string_map<T>::Nodo* actual = raiz;
    while (index != key.size() && actual->hijos.count(key[index]) != 0) {
        actual = actual->hijos[key[index]];
        index++;
    }

    if (index == key.size() && actual->valor != nullptr) {
        return actual;
    } else {
        return nullptr;
    }
}
template <typename T>
vector<typename string_map<T>::Nodo *> string_map<T>::getBranch(string key) const {
    vector<string_map<T>::Nodo *> branch = vector<string_map<T>::Nodo *>();
    int index = 0;
    string_map<T>::Nodo* actual = raiz;
    while (index != key.size() && actual->hijos.count(key[index]) != 0) {
        branch.push_back(actual);
        actual = actual->hijos[key[index]];
        cout <<key[index] << endl ;
        index++;
    }
    return branch;
}

////////  empieza iterador /////////////////////

template <typename T>
string_map<T>::iterator::iterator(string_map* mapa) {

    this->claveActual = mapa->primeraClave();
    this->valorActual = &mapa->at(claveActual);
    this->mapa = mapa;
}


/*
template <typename T>
typename value_type& string_map<T>::iterator::operator*() {
    cout << claveActual<<endl;
    value_type& pair = make_pair(claveActual, mapa->at(claveActual));
    cout << pair.first <<endl;
    return pair;
}*/

template <typename T>
typename string_map<T>::iterator::value_type string_map<T>::iterator::operator->() {
    value_type pair = make_pair(claveActual,mapa->at(claveActual));
    return pair;
}
template <typename T>
string_map<T>::iterator::iterator() {
    mapa = nullptr;
    claveActual="";
}
template <typename T>
bool string_map<T>::iterator::isEnd() {
    return this->claveActual=="";
}

template <typename T>
bool string_map<T>::iterator::operator==(string_map<T>::iterator &o_it) {
    return (o_it.mapa == this->mapa) && (o_it.claveActual == this->claveActual);
}
template <typename T>
bool string_map<T>::iterator::operator!=(string_map<T>::iterator &o_it) {
    return not((o_it.mapa == this->mapa) && (o_it.claveActual == this->claveActual));
}


template <typename T>
typename string_map<T>::key_type string_map<T>::iterator::getClave() {
    return claveActual;
}

template <typename T>
void string_map<T>::iterator::setClave(string_map::key_type key) {
 claveActual=key;
}

////////  empieza const-iterator /////////////////////
template <typename T>
string_map<T>::const_iterator::const_iterator(const string_map* mapa) {

    this->claveActual = mapa->primeraClave();

    this->mapa = mapa;
}


template <typename T>
T& string_map<T>::const_iterator::operator*() {
    return mapa->at(claveActual);
}
template <typename T>
T string_map<T>::const_iterator::operator->() {
    return mapa->at(claveActual);
}
template <typename T>
string_map<T>::const_iterator::const_iterator() {
    mapa = nullptr;
    claveActual="";
}
template <typename T>
bool string_map<T>::const_iterator::isEnd() {
    return claveActual=="";
}

template <typename T>
bool operator==(typename string_map<T>::const_iterator& o_it, typename string_map<T>::const_iterator& o_it2){
    return (o_it.mapa == o_it2.mapa) && (o_it.claveActual == o_it2.claveActual);
}
