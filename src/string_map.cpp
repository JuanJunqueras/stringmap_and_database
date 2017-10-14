#include <algorithm>
#include "string_map.h"

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
    return find(key);
}

template<typename mapped_type>
mapped_type &string_map<mapped_type>::at(const string_map<mapped_type>::key_type &key) {
    return *find(key).first;
}

template <typename T>
const T &string_map<T>::at(const string_map<T>::key_type &key) const {
    return *find(key).first;
}

template <typename T>
void string_map<T>::clear() {
}

template <typename T>
typename string_map<T>::iterator string_map<T>::begin() {
    Nodo *actual = raiz;
    while (actual->valor == nullptr && !actual->hijos.empty()) {
        actual = actual->hijos.begin();
    }
    //TODO devolver iterador a actual
    return string_map<T>::iterator(this);
}

template <typename T>
typename string_map<T>::iterator string_map<T>::end() {
    // FIXME esto sería return nullptr creo.
    return string_map<T>::iterator(this);
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
    return string_map<T>::iterator(this);
}

template <typename T>
typename string_map<T>::const_iterator string_map<T>::find(const string_map<T>::key_type &key) const {
    int index = 0;;
    Nodo* actual = raiz;
    while (index != key.size() && actual->hijos.count(key[index]) != 0) {
        actual = actual->hijos[key[index]];
        index++;
    }

    if (index == key.size() && actual->valor != nullptr) {
        //FIXME devolver el iterador
    } else {
        return this->end();
    }

    return string_map<T>::const_iterator();
}

template<typename T>
pair<typename string_map<T>::iterator, bool> string_map<T>::insert(const string_map<T>::value_type &value) {
    bool inserta = false;
    string clave = value.first;
    T valor = value.second;
    if (this->find(clave) != this->end()) {
        pair<string_map<T>::iterator, bool> res = make_pair(this->end(), inserta);
        return res;
    }
    else {
        int index = 0;
        Nodo* actual = raiz;
        while (index != clave.size()-1) {
            char siguiente = clave[index + 1];
            if (actual->hijos.count(clave[index]) == nullptr) {
                Nodo* nodoSiguiente = new Nodo(nullptr);
                actual->hijos.insert(pair<char,Nodo*>(siguiente, nodoSiguiente));
            }
            actual = actual->hijos[siguiente];

            index++;
        }
        actual->valor = &value;
        inserta = true;
        this->_cantidadDeClaves++;
        // TODO agregar return al iterador
        return pair<string_map<T>::iterator, bool>(new iterator(this), inserta);
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
    if(raiz->hijos.size() == 0){
        return NULL;
    } else {
        string clave = encontrarClave(nodoActual, "");
        if (true){
            return clave;
        }
    }
}

template <typename T>
string string_map<T>::encontrarClave(Nodo* nodoActual, string claveHastaAhora)const {
    if(find(claveHastaAhora)){return claveHastaAhora;}
    int n = 0;
    while(enesimoCaracter(nodoActual,n)){
        char siguiente = enesimoCaracter(nodoActual,n);
        if(encontrarClave(nodoActual->hijos[siguiente],claveHastaAhora+siguiente)!=NULL){
            return encontrarClave(nodoActual->hijos[siguiente],claveHastaAhora+siguiente);
        }
        n++;
    }
    return NULL;
}

template <typename T>
char string_map<T>::enesimoCaracter(string_map<T>::Nodo *pNodo, int n) const {
    auto hijos = pNodo->hijos;
    vector<char> claves = vector<char>();
    for(auto it = hijos.begin();it!=hijos.end;it++){
        claves.push_back(*it.first);
    }
    std::sort(claves.begin(),claves.end());
    if(claves.size()>n){return claves[n];}
    return NULL;
}


////////  empieza iterador /////////////////////

template <typename T>
string_map<T>::iterator::iterator(string_map* mapa) {
    claveActual = mapa->primeraClave();
    this->mapa = mapa;
}


template <typename T>
T& string_map<T>::iterator::operator*() {
    return mapa->find(claveActual);
}
template <typename T>
T string_map<T>::iterator::operator->() {
    return mapa->find(claveActual);
}

template <typename T>
bool operator==(typename string_map<T>::iterator& o_it, typename string_map<T>::iterator& o_it2){
    return (o_it.mapa == o_it2->mapa) && (o_it.claveActual == o_it2->claveActual);
}