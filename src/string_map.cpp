#include "string_map.h"

string_map::string_map(){
    raiz = new Nodo(nullptr);
    _cantidadDeClaves = 0;
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
    return this->raiz->hijos.empty();
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
    Nodo *actual = raiz;
    while (actual->valor == nullptr && !actual->hijos.empty()) {
        actual = actual->hijos.begin();
    }
    //TODO devolver iterador a actual
    return string_map::iterator();
}

string_map::iterator string_map::end() {
    // FIXME esto sería return nullptr creo.
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
    int index = 0;
    Nodo* actual = raiz;
    while (index != key.size() && actual->hijos.count(key[index]) != 0) {
        actual = actual->hijos[key[index]];
        index++;
    }
    if (index == key.size() && actual->valor != nullptr) {
        //FIXME: devolver el iterador. Creo que acá iría return string_map::iterator() en vez de al final de la función.
    } else {
        return this->end();
    }
    return string_map::iterator();
}

string_map::const_iterator string_map::find(const string_map::key_type &key) const {
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

    return string_map::const_iterator();
}

template<typename T>
pair<string_map::iterator, bool> string_map::insert(const string_map::value_type &value) {
    bool inserta = false;
    string clave = value.first;
    T valor = value.second;
    if (this->find(clave) != this->end()) {
        pair<string_map::iterator, bool> res = make_pair(this->end(), inserta);
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
    return pair<string_map::iterator, bool>(, inserta);
    }
}

string_map::size_type string_map::erase(const string_map::key_type &key) {
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
    return (o_it.raiz==raiz) && (o_it.posicion==posicion);

}