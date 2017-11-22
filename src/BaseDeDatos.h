#ifndef _BASEDEDATOS_H
#define _BASEDEDATOS_H

#include "Registro.h"
#include "Restriccion.h"
#include "Tabla.h"
#include <utility>
#include <list>
#include <string>
#include <set>
#include "linear_map.h"
#include "linear_set.h"
#include "utils.h"
#include "string_set.h"

using namespace std;

/**
 * @brief Una base de datos es un administrador de tablas con funciones de
 * búsqueda.
 *
 * Una base de datos permite administrar tablas identificadas por registro.
 * Permite saber si se puede agregar un registro a una tabla y luego agregarlo.
 * Permite realizar filtros del contenido de tablas mediante criterios de
 * búsqueda. Además mantiene estadísticas del uso de los criterios,
 * permite crear un indice para un determinado campo y hacer join entre tablas.
 *
 * **se explica con** TAD BaseDeDatos
 */
class BaseDeDatos {

public:

  class Indice;
  class join_iterator;

  /** @brief Criterio de búsqueda para una base de datos */
  typedef linear_set<Restriccion> Criterio;

  /**
   * @brief Inicializa una base de datos sin tablas.
   *
   * \pre true
   * \post \P{this} = nuevaDB
   *
   * \complexity{\O(1)}
   */
  BaseDeDatos();

  /**
   * @brief Crea una nueva tabla en la base de datos.
   *
   * @param nombre Nombre identificador de la tabla
   * @param claves Claves de la tabla a crear
   * @param campos Campos de la tabla a crear
   * @param tipos  Tipos para los campos de la tabla a crear
   *
   * \pre db = \P{this} \LAND
   *      \LNOT (nombre \IN tablas(\P{this})) \LAND
   *      \LAND \LNOT \EMPTYSET?(claves) \LAND
   *      \FORALL (c: campo) c \IN claves \IMPLICA c \IN campos \LAND
   *      long(campos) = long(tipos) \LAND sinRepetidos(campos)
   * \post \P{this} = agregarTabla(nuevaTabla(claves, nuevoRegistro(campos, tipos)), db)
   *
   * \complexity{\O(C)}
   */
  void crearTabla(const string &nombre, const linear_set<string> &claves,
                  const vector<string> &campos, const vector<Dato> &tipos);

  /**
   * @brief Agrega un registro a la tabla parámetro y actualiza el índice si es necesario.
   *
   * @param r Registro a agregar
   * @param nombre Nombre de la tabla donde se agrega el registro
   *
   * \pre db = \P{this} \LAND nombre \IN tablas(\P{this}) \LAND
   *      puedoInsertar?(r, dameTabla(\P{this}))
   * \post \P{this} = insertarEntrada(r, nombre, db)
   *
   * \complexity{\O([L + log(m)] ∗ C + copy(registro)))}
   */
  void agregarRegistro(const Registro &r, const string &nombre);

  /**
   * @brief Devuelve el conjunto de tablas existentes en la base.
   *
   * El conjunto de nombres se devuelve por referencia no-modificable.
   *
   * \pre true
   * \post \P{res} = tablas(\P{this})
   *
   * \complexity{\O(1)}
   */
  const linear_set<string> &tablas() const;

  /**
   * @brief Devuelve la tabla asociada al nombre.
   *
   * La tabla se devuelve por referencia no modificable.
   *
   * @param nombre Nombre de la tabla buscada.
   *
   * \pre nombre \IN tablas(\P{this})
   * \post \P{res} = dameTabla(nombre, \P{this})
   *
   * \complexity{O(T)}
   */
  const Tabla &dameTabla(const string &nombre) const;

  /**
   * @brief Devuelve la cantidad de usos que tiene un criterio
   *
   * @param criterio Criterio por el cual se consulta.
   *
   * \pre nombre \IN tablas(\P{this})
   * \post \P{res} = usoCriterio(criterio, \P{this})
   *
   * \complexity{\O(#cs * cmp(Criterio))}
   */
  int uso_criterio(const Criterio &criterio) const;

  /**
   * @brief Evalúa si un registro puede ingresarse en la tabla parámetro.
   *
   * @param r Registro a ingresar en la tabla.
   * @param nombre Nombre de la tabla.
   *
   * \pre nombre \IN tablas(\P{this})
   * \post \P{res} = puedoInsertar?(r, dameTabla(nombre, \P{this}))
   *
   * \complexity{\O(C + (c ∗ n ∗ L))}
   */
  bool registroValido(const Registro &r, const string &nombre) const;

  /**
   * @brief Evalúa si un criterio puede aplicarse en la tabla parámetro.
   *
   * @param c Criterio a utilizar.
   * @param nombre Nombre de la tabla.
   *
   * \pre tabla \IN tablas(\P{this})
   * \post \P{res} = criterioValido(c, nombre, \P{this})
   *
   * \complexity{\O(T + cr * C)}
   */
  bool criterioValido(const Criterio &c, const string &nombre) const;

  /**
   * @brief Devuelve el resultado de buscar en una tabla con un criterio.
   *
   * @param c Criterio de búsqueda utilizado.
   * @param nombre Nombre de la tabla.
   *
   * \pre nombre \IN tablas(\P{this}) \LAND criterioValido(c, nombre, \P{this})
   * \post \P{res} = buscar(c, nombre, \P{this})
   *
   * \complexity{\O(T + cs * cmp(Criterio) + cr * n * (C + L + copy(reg)))}
   */
  Tabla busqueda(const Criterio &c, const string &nombre);

  /**
   * @brief Devuelve los criterios de máximo uso.
   *
   * \pre true
   * \post \FORALL (c : Criterio) [c \IN \P{res} \IFF
   *       \FORALL (c' : Criterio) usoCriterio(c, db) >= usoCriterio(c', db)]
   *
   * \complexity{\O(cs * copy(Criterio))}
   */
  linear_set<Criterio> top_criterios() const;

  /**
   * @brief Crea un índice para el campo de la tabla parámetro
   *
   * @param nombre Nombre de la tabla donde se crea el índice
   * @param campo Nombre del campo donde se crea el índice
   *
   * \pre db = \P{this} \LAND nombre \IN tablas(\P{this}) \LAND
   *      campo \IN campos(dameTabla(nombre, \P{this}))
   * \post \P{this} = crearIndice(tabla, campo, db)
   *
   * \complexity{\O(m ∗ [L + log(m)])}
   */
    void crearIndice(const string &nombre, const string &campo);

    /**
     * @brief Efectua un join entre las dos tablas y devuelve un iterador apuntando al primer registro del conjunto resultante
     *
     * @param tabla1 Nombre de una tabla
     * @param tabla2 Nombre de la otra tabla
     * @param campo Nombre del campo presente en ambas tablas sobre el que se crea el indice.
     *
     * \pre db = campo \pertenece campos(Tabla1) \LAND campo \pertenece campos(Tabla2) \LAND \existe ind en (indices(Tabla1)\CUP indices(Tabla2)) \talque campo = clave(ind)
     * \post \P{this} = this = iterador(t) donde t es una tabla tal que campos(t) = campos(tabla1) \union campos(tabla2)
     * y r esta en t si \existe r1 en tabla 1 y r2 en tabla 2 tal que r1[campo]=r2[campo]=r[campo]
     * y #paratodo campo i en campos(r) r[i] = r1[i] o r[i] = r2[i]
     *
     * \complexity{\O(T + copy(reg))}
     */
    join_iterator join(const string &tabla1, const string &tabla2, const string &campo) const;

    join_iterator join_end() const;

    /** @brief Operadores de comparacion
    *
    * \pre true
    * \post res  = (_nombres_tablas(this) = _nombres_tablas(otro) \LAND
    * (_tablas(this) = _tablas(otro) \LAND
    * (_uso_criterios(this) = _uso_criterios(otro) \LAND
    * siendo n la cantidad de claves en _nombres_tablas,
    * m la cantidad de claves en _tablas, p la cantidad de claves en _uso_criterios,
    * q la cantidad de claves en indices
    *
    * \complexity{O(n+m+p+q)}
    *
    **/
    bool operator==(const BaseDeDatos &db) const {
      return this->_nombres_tablas == db._nombres_tablas &&
             this->_tablas == db._tablas &&
             this->_uso_criterios == db._uso_criterios &&
             this->indices == db.indices;
    }
    /** @brief Operadores de comparacion
        *
        * \pre true
        * \post true sii el operator== es falso.
        * siendo n la cantidad de claves en _nombres_tablas,
        * m la cantidad de claves en _tablas, p la cantidad de claves en _uso_criterios,
        * q la cantidad de claves en indices
        *
        * \complexity{O(n+m+p+q)}
        **/
    bool operator!=(const BaseDeDatos &db) const {
      return !(*this == db);
    }

private:
	  ///////////////////////////////////////////////////////////////////////////////////////////////////
    /** \name Representación
     * rep: basededatos \TO bool\n
     * rep(bd) \EQUIV 
     *  * _nombres_tablas = claves(_tablas) \LAND
     *  * \FORALL (c : Criterio) c \IN claves(_uso_criterios) \IMPLIES 
     *     * (
     *       * \EXISTS (n : string) n \IN _nombres_tablas 
     *       * \LAND criterioValido(c, n, db)
     *     * ) \LAND
     *     * obtener(c, _uso_criterios) > 0
     *
     * abs: basededatos \TO BaseDeDatos\n
     * abs(bd) \EQUIV bd' \|
     *  * _nombres_tablas = tablas(bd') \LAND
     *  * (\FORALL nt : string) nt \IN _nombres_tablas \IMPLIES
     *    * obtener(nt, _tablas) = dameTabla(nt, bd') \LAND
     *  * (\FORALL c : criterio) 
     *    * (usoCriterio(c, bd') == 0 \LAND \LNOT def?(c, _uso_criterios)) \LOR
     *    * (usoCriterio(c, db') == obtener(c, _uso_criterios))
     */
    //////////////////////////////////////////////////////////////////////////////////////////////////////


    /** @{ */
    linear_set<string> _nombres_tablas;
    string_map<Tabla> _tablas;
    linear_map<Criterio, int> _uso_criterios;
    string_map<string_map<Indice>> indices;


  /** @} */

    /** @{ */
    /**
     * @brief Revisa si los campos del registro y la tabla tienen el mismo tipo.
     *
     * \pre campos(r) == campos(t)
     * \post \P{res} == \FORALL (c : campo) c \IN campos(r) \IMPLIES
     * Nat?(valor(c, r)) == tipoCampo(c, t)
     *
     * \complexity{O(C^2)}
     */
    bool _mismos_tipos(const Registro &r, const Tabla &t) const;

    /**
     * @brief Revisa si el registro no repite claves en la tabla.
     *
     * \pre compatible(r, t)
     * \post \P{res} = \FORALL (r' : Registro) r \IN registros(t) \IMPLIES
     *  \EXISTS (c : campo) c \IN claves(t) \LAND valor(c, r') != valor(c, r)
     *
     * \complexity{O(c * C + c * n * (C + L))}
     */
    bool _no_repite(const Registro &r, const Tabla &t) const;

    /**
     * @brief Filtra la lista de registros parametro según el criterio.
     *
     * El resultado tiene aliasing con el parámetro registros.
     *
     * \pre \FORALL (r : Registro) r \IN registros \IMPLIES campo \IN
     *      campos(r) \LAND tipo?(valor(campo, r)) = tipo?(valor)
     * \post \P{res} = filtrarRegistrosSegunRestriccion(
     *       nueva(campo, valor, igualdad), registros)
     */
    list<Registro> &_filtrar_registros(const string &campo, const Dato &valor,
                                      list<Registro> &registros,
                                      bool igualdad) const;

    /**
     * @brief Filtra la lista de registros parametro según el criterio.
     *
     * El resultado tiene aliasing con el parámetro registros.
     *
     * \pre \FORALL (r : Registro) r \IN registros \IMPLIES campo \IN
     *      campos(r) \LAND tipo?(valor(campo, r)) = tipo?(valor)
     * \post \P{res} = filtrarRegistrosSegunRestriccion(
     *       nueva(campo, valor, true), registros)
     */
    list<Registro> &_filtrar_registros(const string &campo, const Dato &valor,
                                       list<Registro> &registros) const;

    /**
     * @brief Obtiene los campos y tipos de una tabla.
     *
     * \pre true
     * \post (\FORALL (c : Campo) está?(c, \P1(\P{res})) \IFF c \IN campos(t))
     *       \LAND #(campos(t)) = long(\P1(\P{res}))
     *       \LAND \FORALL (i : Nat) 0 \LEQ i < #(campos(t)) \IMPLIES
     *       tipo?(\P2(\P{res})[i]) = tipoCampo(\P1(\P{res})[i], t)
     */
    pair<vector<string>, vector<Dato> > _tipos_tabla(const Tabla &t);
    /** @} */
};

#endif
