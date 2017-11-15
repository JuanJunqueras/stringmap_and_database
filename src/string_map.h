#ifndef STRING_MAP_STRING_MAP_H
#define STRING_MAP_STRING_MAP_H

#include <cassert>
#include <string>
#include <vector>
#include <stack>
#include <map>

using namespace std;

/**
 * @brief Representa un diccionario cuyas claves son strings.
 *
 * **se explica con** TAD Diccionario(string, T)
 */

/**
 * Implementacion de map<string,T> sobre Trie
 * Asume de T:
 * - tiene constructor por copia 
 * - tiene operador ==
 * - solo permite utilizar el operator[] si T tiene constructor por defecto
 */
/* @corregir(ivan): quitaron las asunciones de complejidades sobre el tipo de dato T. */

template < typename T >
class string_map {
public:
    typedef string key_type;
    typedef T mapped_type;
    typedef std::pair<const key_type, mapped_type> value_type;
    typedef size_t size_type;

    /* @corregir(ivan): Falta la documentación de este iterador */
    class iterator{
        void setClave(key_type key);
        const string_map* mapa;
        friend class string_map;
        key_type claveActual;
        const mapped_type* valorActual;
    public:
        key_type getClave();
        iterator(const string_map* mapa);
        iterator();
        using value_type = const string_map::value_type;
        using iterator_category = std::forward_iterator_tag;
        using reference =value_type&;
        using pointer = value_type*;
        using difference_type = std::ptrdiff_t;
        value_type operator*();
        value_type* operator->();
        iterator& operator++();
        bool operator!=(const iterator& o_it) const;
        bool operator==(const iterator& o_it) const;
        bool isEnd();

    };
    /* @corregir(ivan): Falta la documentación de este iterador */
    class const_iterator{

            void setClave(key_type key);
            const string_map* mapa;
            friend class string_map;
            key_type claveActual;
            const mapped_type* valorActual;
        public:
            key_type getClave();
            const_iterator(const string_map* mapa);
            const_iterator();
            using value_type = const string_map::value_type;
            using iterator_category = std::forward_iterator_tag;
            using reference = value_type&;
            using pointer = value_type*;
            using difference_type = std::ptrdiff_t;
            value_type operator*();
            value_type* operator->();
            const_iterator& operator++();
            bool operator!=(const const_iterator &o_it) const;
            bool operator==(const const_iterator &o_it) const;

        bool isEnd();


    };
    friend class iterator;
    friend class const_iterator;


    /* @corregir(ivan): De dónde sale "raiz" en la post del constructor vacío ?
     * En la pre y la post sólo pueden hablar en terminos de las operaciones del TAD con el cual se explica el módulo.
     * */
    /**
   * @brief Construye mapa con su raiz.
   *
   * \pre true
   * \post vacio?(claves(res))
   *
   * \complexity{\O(1)}
   */

    string_map();

    /** @brief Destruye mapa
     *
     * \complexity{\O(sn * S)}
     */
    ~string_map();

    /** @brief Constructor por copia
     *
     * \pre true
     * \post res = @param
     *
     * \complexity{\O(sn * (S + copy(value_type)))}
     */
    string_map(const string_map &);

    /** @brief Operador de asignacion
     *
     * \pre true
     * \post res = @param
     *
     * \complexity{\O(sn * (S + copy(value_type)) }
     */
    string_map& operator=(const string_map &);

    /** @brief Operadores de comparacion
     *
     * \pre true
     * \post res  = (claves(this) = claves(otro) \LAND (\FORALL k :claves(this))( obtener(k,this) = obtener(k,otro))    )
     *
     * \complexity{\O(sn * (S+cmp(T)))}
     */
    bool operator==(const string_map& otro) const;

    /** @brief Operadores de comparacion
      *
      * \pre true
      * \post res  = (claves(this) != claves(otro) \LOR \LNOT (\FORALL k :claves(this))( obtener(k,this) = obtener(k,otro))    )
      *
      * \complexity{\O(sn * (S+cmp(T)))}
      */
    bool operator!=(const string_map& otro) const;

    /** @brief Cantidad de apariciones de la clave (0 o 1)
     *  @param key clave a buscar
     *
     *  \pre true
     *  \post res = if def?(this, key) then 1 else 0 fi
     *
     *  \complexity{\O(S)}
     */
    size_type count(const key_type &key) const;

    /** @brief Devuelve cantidad de claves definidas
     *
     * \pre true
     * \post res = #claves(this)
     *
     * \complexity{\O(1)}
     * */
    size_t size() const;

    /** @brief devuelve true si size() == 0
     *
     * \pre true
     * \post res = if #claves(this) = 0 then true else false fi
     *
     * \complexity{\O(1)}
     * */
    bool empty() const;

    /** @brief Acceso / definición de pares clave/valor
     *  @param key clave a acceder, si no existe, se crea
     *  @returns una referencia a la definicion.
     *
     * \pre true
     * \post res = significado(key, this)
     *
     *  \complexity{\O(S + copy(T))}
     */
    mapped_type &operator[](const key_type &key);

    /** @brief Acceso a una clave sin modificar mapa
     *  @param key clave a acceder que debe existir previamente
     *  @returns una referencia a la definicion.
     *
     * \pre def?(this, key)
     * \post res = significado(key, this)
     *
     *  \complexity{\O(S + copy(T))}
     */
    mapped_type& at(const key_type& key);

    /** @brief Acceso a una clave sin modificar mapa
     *  @param key clave a acceder que debe existir previamente
     *  @returns una referencia const a la definicion.
     *
     * \pre def?(this, key)
     * \post res = significado(key, this)
     *
     *  \complexity{\O(S + copy(T))}
     */
    const mapped_type& at(const key_type& key) const;

    /** @brief Vacia el mapa
     *
     * \pre true
     * \post vacio?(claves(this))
     *
     * \complexity{\O(n)}
     *
     */
    void clear();

    // Accesos con iteradores FIXME fix this

    /** @brief iterador al primer par <clave,significado> en orden lexicografico
     *  @returns iterador al elemento o end() si el mapa era vacio
     *
     * \pre true
     * \post El iterador resultante apunta al primer elemento o end() si el mapa era vacio
     *
     *  \complexity{\O(S)}
     */
   iterator begin();
   iterator end();
   const_iterator begin() const;
    /** @brief iterador al fin de la coleccion
     *
     * \pre true
     * \post El iterador resultante apunta al final de la coleccion
     *
     *
     *  \complexity{\O(S)}
     */
   const_iterator end() const;

    /// Versiones const de begin/end

   const_iterator cbegin() const;
   const_iterator cend() const;

    /** @brief busca una clave
     *  @param key clave a buscar
     *  @returns un iterador al par <clave, significado>
     *
     *  \pre true
     *  \post El iterador resultante apunta a la tupla <key, this.at(key)>
     *  o al final de la coleccion si key no esta definida en this.
     *
     *  \complexity{\O(S)}
     */
   iterator find(const key_type &key);

    /** @brief busca una clave
     *  @param key clave a buscar
     *  @returns un iterador const al par <clave, significado>
     *
     *  \pre true
     *  \post El iterador resultante apunta a la tupla <key, this.at(key)>
     *  o al final de la coleccion si key no esta definida en this.
     *
     *  \complexity{\O(S)}
     */
   const_iterator find(const key_type &key) const;

    /* @corregir(ivan): Acá falta hablar en la post de que pasa con el diccionario */
    /** @brief insercion
     *
     * @param value par <clave,significado> a insertar
     * @returns un par con un iterador al par clave-significado agregado o
     * modificado y un bool que indica si la clave se insertó como una clave
     * nueva.
     *
     * \pre this=this_0
     * \post El primer elemento del par resultante es un iterador que apunta a tupla <key, this.at(key)>
     * y el segundo elemento es true si la clave no estaba definida en this_0 y false en caso contrario.
     * ademas, obtener(this,value.first) = value.second
     * \complexity{\O(S + copy(value_type))}
     */
    pair<iterator,bool> insert(const value_type &value);

    /* @corregir(ivan): terminar de escribir la post (si tienen dudas, pregunten). */
    /** @brief eliminar una clave
     *  @param key clave a eliminar
     *  @returns cantidad de elementos eliminados
     *
     *  \pre this = dicc0
     *  \post key \NOTIN claves(this) \AND res = if clave \ISIN claves(dicc0) then 1 else 0 fi
     *
     *  \complexity{\O(S)}
     */
    size_type erase(const key_type& key);

    /** @brief eliminar una clave mediante irerador
     *  @param pos iterador apuntando a clave a eliminar
     *  @returns iterador apuntando el proximo de la clave eliminada (o end() si era la ultima)
     *
     *  \pre this = dicc0
     *  \post key \NOTIN claves(this) \AND la claveActual del iterador resultante es la siguiente clave
     *  y valorActual del iterador resultante es un puntero a this.at(claveActual)
     *  o un puntero nulo en caso de ser el fin de la coleccion.
     *  \LAND res = if clave \ISIN claves(dicc0) then 1 else 0 fi
     *  \complexity{\O(S)}
     */
    iterator erase(iterator pos);


    string siguienteClave(string claveActual) const;

private:

    /* @corregir(ivan): Dado que el string_map tiene dentro una estructura recursiva, les conviene armar un predicado auxiliar que les ayude a escribir el Rep. */
    /* @corregir(ivan): Están mezclando el abs del string_map con el de sus iteradores. */
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /** \name Representación
     * rep: string_map \TO bool\n
     * rep(m) \EQUIV
     *  * m.raiz.valor = null
     *  * m._cantidadDeClaves = 0
     *
     * abs: string_map \TO Diccionario(string, T)\n
     * abs(m) \EQUIV m' \|
     *  * #claves(m') = m._cantidadDeClaves \AND
     *  * \FORALL (c : string) def?(c,m') \IMPLIES \EXISTS (i: string_map_iterator(m))(i.claveActual = c) \LAND
     *  (i.valorActual = obtener(c,m')
     */
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    struct Nodo {
        map<char, Nodo*> hijos;
        T* valor;
        Nodo(T* v) : valor(v) {};
    };

    Nodo* raiz;
    size_t _cantidadDeClaves;
    string primeraClave() const;
    Nodo* findNodo(string key)const;
    vector<Nodo*> getBranch(string key)const;
};
/* FIXME ESTO ES EL REP D LOS ITERADORES; VER DONDE METERLO
*   \FORALL (i: string_map_iterator(m)) (i \NEQ m.end) \LIMPLIES def?(i.claveActual, m') \AND
*  obtener(i.claveActual, m') = i.valorActual */
#include "string_map.hpp"

#endif //STRING_MAP_STRING_MAP_H
