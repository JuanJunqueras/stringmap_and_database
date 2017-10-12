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

size_t string_map::sizeBelow(Nodo* pseudoRaiz)const {
    int total = 0;
    for(int i = 0 ; i<27 ; i++){
        if(pseudoRaiz->hijos[i]){
            size_t debajo = sizeBelow(pseudoRaiz->hijos[i]);
            total+= (1 + debajo);
        }

    }
    return (size_t) total;
}
size_t string_map::size() const {
    return sizeBelow(raiz);
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

//    (int) key[index] - 97

    Nodo *actual = raiz;
    while (actual != nullptr) {

        if (actual->hijos[26] != nullptr) {
            auto it = new string_map::iterator();
//            return new string_map::iterator();// actual->hijos[26]->valor;
        }

        for (int i = 0; i < 26; ++i) {
            if (actual->hijos[i] != nullptr) {
//                actual =
            }
        }

    }

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


    int index = 0;
    int siguiente = (int) key[index] - 97;
    Nodo* actual = raiz;
    while (index != key.size() && actual->hijos[siguiente] != nullptr) {
        siguiente = (int) key[index] - 97;
        actual = actual->hijos[siguiente];
        index++;
    }

    if (index == key.size() && actual->hijos[26]->valor != NULL) {
        //FIXME> devolver el iterador
    } else {
        // FIXME> devolver iterador al final del map.
    }

    return string_map::const_iterator();
}

template<typename T>
pair<string_map::iterator, bool> string_map::insert(const string_map::value_type &value) {

    bool inserta = false;
    string clave = value.first;
    T valor = value.second;

    int index = 0;
    Nodo* actual = raiz;
    while (index != clave.size()) {
        int siguiente = (int) clave[index] - 97;
        if (actual->hijos[siguiente] == nullptr) {
            actual->hijos[siguiente] = new Nodo(NULL);
        }
        actual = actual->hijos[siguiente];
        index++;
    }

    Nodo* ultimo = actual->hijos[26];
    if (ultimo->valor == nullptr) {
        ultimo->valor = valor;
        inserta = true;
    }

    // TODO: agregar iterador
    return pair<string_map::iterator, bool>(, inserta);
}

string_map::size_type string_map::erase(const string_map::key_type &key) {
    return 0;
}

string_map::size_type string_map::count(const string_map::key_type &key) const {
    return 0;
}
////////  empieza iterador /////////////////////

string_map::iterador::iterador() {
    raiz = this->raiz;
    posicion = this->posicion;
}


template <typename T>
T& string_map::iterador::operator*() {
    return posicion->valor;
}
template <typename T>
T string_map::iterador::operator->() {
    return posicion->valor;
}

bool operator==(string_map::iterador& o_it){
    return (o_it.raiz==raiz) &&(o_it.posicion==posicion);

}