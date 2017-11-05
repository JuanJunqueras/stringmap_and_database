//
// Created by Agustín Argüello on 11/4/17.
//

#ifndef TP2_GRUPO2_JOIN_ITERATOR_H
#define TP2_GRUPO2_JOIN_ITERATOR_H

#include <set>
#include "Tabla.h"

class join_iterator {

//    void agregarIteradorTablaPrincipal(Tabla::const_iterador_registros *begin, Tabla::const_iterador_registros*end) {
//        it_registros_tabla_principal = begin;
//        it_registros_tabla_principal_end = end;
//    }
//
//    void agregarIteradorTablaIndice(set<Tabla::const_iterador_registros>::iterator begin, set<Tabla::const_iterador_registros>::iterator end) {
//        it_registros_tabla_con_indice = begin;
//        it_registros_tabla_con_indice_end = end;
//    }


private:
        Tabla::const_iterador_registros &it_registros_tabla_principal;
        Tabla::const_iterador_registros it_registros_tabla_principal_end;
        set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice;
        set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice_end;

public:

    join_iterator(Tabla::const_iterador_registros it_registros_tabla_principal,
                  Tabla::const_iterador_registros it_registros_tabla_principal_end,
                  set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice,
                  set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice_end) :
        it_registros_tabla_principal(it_registros_tabla_principal),
        it_registros_tabla_con_indice(it_registros_tabla_con_indice),
        it_registros_tabla_principal_end(it_registros_tabla_principal_end),
        it_registros_tabla_con_indice_end(it_registros_tabla_con_indice_end)
    {};
//    Lista<T>::Lista() :
//            _primero(nullptr), _ultimo(nullptr), _cardinal(0) {
//    }

//    void setValor(Tabla::const_iterador_registros it_registros_tabla_principal){
//        Tabla::const_iterador_registros _it_registros_tabla_principal = it_registros_tabla_principal;
//    }
};

#endif //TP2_GRUPO2_JOIN_ITERATOR_H
