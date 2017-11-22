
#ifndef TP2_GRUPO2_JOIN_ITERATOR_H
#define TP2_GRUPO2_JOIN_ITERATOR_H

#include <set>
#include <utility>
#include "Tabla.h"
#include "BaseDeDatos.h"
#include "Indice.h"

/**
 * @brief Un join_iterator es un iterador que nos permite movernos entre dos tablas
 * a las cuales se les aplicó la función join.
 *
 * Una join_iterator permite generar un iterador entre dos tablas,
 * Permite avanzar el iterador y
 * Permite desreferenciar devolviendo un registro compuesto por el contenido de ambos punteros.
 *
 */
class BaseDeDatos::join_iterator {

private:

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /** \name Representación
     * rep: join_iterator \TO bool\n
	rep(ji) \EQUIV

     * db es un puntero a la base de datos a la que pertenecen las tablas a las que se les hace el join.
     *it_registros_tabla_principal es un iterador que apunta a un registro de la tabla no necesariamente
     indexada.
     *it_registros_tabla_con_indice es un iterador que apunta a un registro de la tabla indexada.
     *it_registros_tabla_principal e it_registros_tabla_principal_end apuntan a registros de la misma tabla.
     *it_registros_tabla_con_indice e it_registros_tabla_con_indice_end apuntan a registros de la misma tabla.
     *it_registros_tabla_principal_end es el iterador past-the-end de los registros de la tabla principal.
     *it_registros_tabla_principal solo puede ser igual a it_registros_tabla_principal_end si la tabla principal
     no tiene registros o si it_registros_tabla_con_indice es igual a it_registros_tabla_con_indice_end.
     *

	abs: No equivale a ningun TAD, pues no vimos una representacion abstracta para los iteradores.
     Sin embargo la tabla que 'itera'
     es el resultado de hacer join de las dos tablas pasadas por parametro.
     */
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    BaseDeDatos const *db;
    Tabla::const_iterador_registros it_registros_tabla_principal;
    Tabla::const_iterador_registros it_registros_tabla_principal_end;
    set<Tabla::const_iterador_registros> const* registros_en_indice;
    set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice;
    set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice_end;
    string nombre_tabla;
    string nombre_campo;
    bool isEnd;
    bool prioridad_campos_r1;

public:
    /**
     * @brief Constructor por parámetros de la clase join_iterator.
     *
     * \pre true
     * \post  Genera un iterador entre dos tablas
     * \complexity O(1)
     **/

    join_iterator(
            BaseDeDatos const *db,
            string nombre_tabla,
            string nombre_campo,
            const Tabla::const_iterador_registros &it_registros_tabla_principal,
            const Tabla::const_iterador_registros &it_registros_tabla_principal_end,
            const set<Tabla::const_iterador_registros>* registros_en_indice,
            const set<Tabla::const_iterador_registros>::iterator &it_registros_tabla_con_indice,
            const set<Tabla::const_iterador_registros>::iterator &it_registros_tabla_con_indice_end,
            bool prioridad_campos_tabla_principal
    ) :
            db(db),
            nombre_tabla(std::move(nombre_tabla)),
            nombre_campo(std::move(nombre_campo)),
            it_registros_tabla_principal(it_registros_tabla_principal),
            it_registros_tabla_principal_end(it_registros_tabla_principal_end),
            registros_en_indice(registros_en_indice),
            it_registros_tabla_con_indice(it_registros_tabla_con_indice),
            it_registros_tabla_con_indice_end(it_registros_tabla_con_indice_end),
            prioridad_campos_r1(prioridad_campos_tabla_principal)
    {
        isEnd = it_registros_tabla_principal == it_registros_tabla_principal_end;
    }
    /**
     * @brief Constructor por copia de la clase join_iterator.
     *
     * \pre true
     * \post  Genera un iterador entre dos tablas
     * \complexity O(m)
     **/
    join_iterator(const join_iterator &join_it) :
            db(join_it.db), //O(1)
            nombre_tabla(join_it.nombre_tabla), //O(1)
            nombre_campo(join_it.nombre_campo), //O(1)
            it_registros_tabla_principal(join_it.it_registros_tabla_principal), //O(1)
            it_registros_tabla_principal_end(join_it.it_registros_tabla_principal_end), //O(1)
            registros_en_indice(join_it.registros_en_indice), //O(1)
            it_registros_tabla_con_indice(join_it.registros_en_indice->begin()), //O(m)
            it_registros_tabla_con_indice_end(join_it.registros_en_indice->end()), //O(1)
            isEnd(join_it.isEnd), //O(1)
            prioridad_campos_r1(join_it.prioridad_campos_r1) {} //O(1)
    /**
        * @brief Comparación entre join_iterators
        *
        * \pre ambos join_iterators refieren al mismo par de tablas.
        * \post true sii los iteradores generados son iguales
        *
        * \complexity //FIXME: chequear con Agus
    */
    join_iterator &operator=(const join_iterator &join_it) = default;
    /**
     * @brief Si la tabla con índice no llegó a su final, avanza el iterador de ésta tabla una posición.
     * En caso contrario (la tabla con índice llegó a su fin), avanza el iterador de la tabla principal
     * una posición. Si el iterador de la tabla principal es igual a end, activa el flag correspondiente.
     *
     * \pre Los iteradores no deben estar en la posición pasando-el-último de ambas tablas.
     * \post \P{res} es una referencia a \P{this}. \P{this} apunta a la posición
     * siguiente. En caso de que la tabla con índice llegue a su fin, se apunta a la posición siguiente
     * de la tabla que no tiene índice y a la primera de la que sí lo tiene //FIXME: chequear con Agus
     *
     * \complexity{\O(n * (L + log(m)))} //FIXME: chequear con Agus
    **/

    void operator++() {

        if (it_registros_tabla_con_indice != it_registros_tabla_con_indice_end) { //O(1)
            ++it_registros_tabla_con_indice; //O(1)
        }

        if (it_registros_tabla_con_indice == it_registros_tabla_con_indice_end) { //O(1)

            ++it_registros_tabla_principal; //O(1)
            const BaseDeDatos::Indice &indice = db->indices.at(nombre_tabla).at(nombre_campo); //O(1)

            // Iteramos sobre tabla principal, buscando el primer siguiente match con registro del indice
            bool match = false; //O(1)
            while (!match && it_registros_tabla_principal != it_registros_tabla_principal_end) { //O(n)
                auto dato = (*it_registros_tabla_principal).dato(nombre_campo); //O(L + log (m))
                if (indice.existe(dato)) { //O(L + log(m))
                    registros_en_indice = &indice.registros(dato); //O(1)
                    it_registros_tabla_con_indice = indice.registros(dato).begin(); //O(1)
                    it_registros_tabla_con_indice_end = indice.registros(dato).end(); //O(1)
                    match = true; //O(1)
                } else {
                    ++it_registros_tabla_principal; //O(1)
                }
            }
        }

        if (it_registros_tabla_principal == it_registros_tabla_principal_end) { //O(1)
            this->isEnd = true; //O(1)
        }
    }

    void operator++(int) {
        ++(*this);
    }

    /**
   * @brief Desreferencia los registros a los que apuntan los punteros
   * y devuelve un registro por referencia.
   *
   *
   * \pre true
   * \post todo dato en el resultado de desreferenciar, está en alguno
   * de los registros a los que apuntan los iteradores it_ o en ambos.
   * \complexity{\O(copy(Registro))}
   **/
    Registro operator*() {

        // O(1)
        const Registro &r1 = *it_registros_tabla_principal;
        const Registro &r2 = *(*it_registros_tabla_con_indice);
        vector<string> campos_registro_join;
        vector<Dato> datos_registro_join;

        // Agregamos campos y datos del primer registro
        const string_set &campos_r1 = r1.campos(); // O(1)
        for (const string &campo_r1 : campos_r1) { // O(C)
            if (!r2.pertenece(campo_r1) || prioridad_campos_r1) { // O(1)
                campos_registro_join.push_back(campo_r1); // O(1)
                datos_registro_join.push_back(r1.dato(campo_r1)); // O(1)
            }
        }

        // Agregamos campos y datos del segundo registro, si estos no están ya en el primero
        const string_set &campos_r2 = r2.campos();
        for (const string &campo_r2 : campos_r2) { // O(C)
            if (!r1.pertenece(campo_r2) || !prioridad_campos_r1) { // O(1)
                campos_registro_join.push_back(campo_r2); // O(1)
                datos_registro_join.push_back(r2.dato(campo_r2)); // O(1)
            }
        }

        Registro registro_join = Registro(campos_registro_join,
                                          datos_registro_join); // O(C * copy(Dato)) = O(C) = O(copy(Registro))
        return registro_join;
    }

    /** @brief Operadores de comparacion
     *
     * \pre true
     * \post true sii las tablas por las que se hace el join_iterator son iguales, esto quiere decir
     * que avanzar desde una misma posición del mismo iterador, y desreferenciar desde la misma posición devuelve
     * los mismos registros.
     *
     * \complexity O(1)
    */
    bool operator==(const join_iterator &it_1) const {
        if (this->db != it_1.db){
            return false;
        }
        if (this->isEnd && it_1.isEnd) {
            return true;
        } else {
            bool a = this->db == it_1.db;
            bool b = this->nombre_tabla == it_1.nombre_tabla;
            bool c = this->nombre_campo == it_1.nombre_campo;
            bool d = this->it_registros_tabla_principal == it_1.it_registros_tabla_principal;
            bool e = this->it_registros_tabla_principal_end == it_1.it_registros_tabla_principal_end;
            bool f = this->it_registros_tabla_con_indice == it_1.it_registros_tabla_con_indice;
            bool g = this->it_registros_tabla_con_indice_end == it_1.it_registros_tabla_con_indice_end;
            return a && b && c && d && e && f && g;
        }
    }
    /** @brief Operadores de comparación
    *
    * \pre true
    * \post true sii el operator== es falso.
    *
    * \complexity //O(1)
   */
    bool operator!=(const join_iterator &it_1) const {
        return !(*this == it_1);
    }
};

#endif //TP2_GRUPO2_JOIN_ITERATOR_H
