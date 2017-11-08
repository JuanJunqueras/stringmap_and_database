//
// Created by Agustín Argüello on 11/4/17.
//

#ifndef TP2_GRUPO2_JOIN_ITERATOR_H
#define TP2_GRUPO2_JOIN_ITERATOR_H

#include <set>
#include "Tabla.h"

class join_iterator {

private:
        Tabla::const_iterador_registros it_registros_tabla_principal;
        Tabla::const_iterador_registros it_registros_tabla_principal_end;
        set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice;
        set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice_end;

public:

    join_iterator(
            Tabla::const_iterador_registros it_registros_tabla_principal,
            Tabla::const_iterador_registros it_registros_tabla_principal_end,
            set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice,
            set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice_end
    ) :
            it_registros_tabla_principal(it_registros_tabla_principal),
            it_registros_tabla_principal_end(it_registros_tabla_principal_end),
            it_registros_tabla_con_indice(it_registros_tabla_con_indice),
            it_registros_tabla_con_indice_end(it_registros_tabla_con_indice_end)
    { }
};

#endif //TP2_GRUPO2_JOIN_ITERATOR_H
