#include "BaseDeDatos.h"
#include "Indice.h"
#include "join_iterator.h"

BaseDeDatos::BaseDeDatos(){};

void BaseDeDatos::crearTabla(const string &nombre, 
                             const linear_set<string> &claves,
                             const vector<string> &campos,
                             const vector<Dato> &tipos) {
  _nombres_tablas.fast_insert(nombre);
    const string elNombre = nombre;
  _tablas.insert(make_pair(elNombre, Tabla(claves, campos, tipos)));
}

void BaseDeDatos::agregarRegistro(const Registro &r, const string &nombre) {

  Tabla &t = _tablas.at(nombre); // O(1)
  Tabla::const_iterador_registros reg = t.agregarRegistro(r); // O(copy(registro))

  auto t_campos_indices = indices.find(nombre); // O(1) (pues largo de claves acotado)
  if (!t_campos_indices.isEnd()) {

    // Iteramos sobre los índices de la tabla (en el peor caso todos los campos tienen índice y hacemos C iteraciones)
    for (auto it_campos = (*t_campos_indices).second.cbegin(); !it_campos.isEnd(); ++it_campos) { // O(C)
      auto dato = r.dato(it_campos.getClave());
      Indice indice = (*it_campos).second;
      auto registros = indice.registros(dato); // O(max{L,log(m)})
      registros.insert(reg); // O(log(m))
    }
  }
}

const linear_set<string> &BaseDeDatos::tablas() const { return _nombres_tablas; }

const Tabla &BaseDeDatos::dameTabla(const string &nombre) const {
  return _tablas.at(nombre);
}

int BaseDeDatos::uso_criterio(const BaseDeDatos::Criterio &criterio) const {
  if (_uso_criterios.count(criterio)) {
    return _uso_criterios.at(criterio);
  } else {
    return 0;
  }
}

/* @corregir(ivan): No cumple la complejidad pedida. */
bool BaseDeDatos::registroValido(const Registro &r,
                                 const string &nombre) const {
  const Tabla &t = _tablas.at(nombre);

  return (t.campos() == r.campos() and _mismos_tipos(r, t) and
          _no_repite(r, t)); // O(C^2 + C + n + c*n*cmp(T))
}

bool BaseDeDatos::_mismos_tipos(const Registro &r, const Tabla &t) const {
  for (auto c : t.campos()) {
    if (r.dato(c).esNat() != t.tipoCampo(c).esNat()) {
      return false;
    }
  }
  return true;
}

bool BaseDeDatos::_no_repite(const Registro &r, const Tabla &t) const {
  list<Registro> filtrados(t.registros().begin(), t.registros().end()); /* @comentario(ivan): O(n) */
  for (auto clave : t.claves()) { /* @comentario(ivan): O(c) */
    _filtrar_registros(clave, r.dato(clave), filtrados); /* @comentario(ivan): O(n * cmp(T)) */
  }
  return filtrados.empty();
}

list<Registro> &
BaseDeDatos::_filtrar_registros(const string &campo, const Dato &valor,
                                list<Registro> &registros) const {
  return _filtrar_registros(campo, valor, registros, true);
}

list<Registro> &BaseDeDatos::_filtrar_registros(const string &campo,
                                                const Dato &valor,
                                                list<Registro> &registros,
                                                bool igualdad) const {
  auto iter = registros.begin();
  while ( iter != registros.end()) { // O(n)
    auto now = iter;
    iter++;
    if ((not igualdad) xor now->dato(campo) != valor) { // O(cmp(T))
      registros.erase(now);
    }
  }

  return registros;
}

pair<vector<string>, vector<Dato> > BaseDeDatos::_tipos_tabla(const Tabla &t) {
  vector<string> res_campos;
  vector<Dato> res_tipos;
  for (auto c : t.campos()) {
    res_campos.push_back(c);
    res_tipos.push_back(t.tipoCampo(c));
  }
  return make_pair(res_campos, res_tipos);
}

/* @corregir(ivan): No cumple con la complejidad pedida. */
bool BaseDeDatos::criterioValido(const Criterio &c,
                                 const string &nombre) const {
  const Tabla &t = _tablas.at(nombre);
  for (auto restriccion : c) { // O(cr)
    if (not t.campos().count(restriccion.campo())) { // O(C)
      return false;
    }
    if (t.tipoCampo(restriccion.campo()).esNat() != 
        restriccion.dato().esNat()) { // O(C)
      return false;
    }
  }
  return true;
}

Tabla BaseDeDatos::busqueda(const BaseDeDatos::Criterio &c,
                            const string &nombre) {
  if (_uso_criterios.count(c)) {
    _uso_criterios.at(c)++;
  } else {
    _uso_criterios.fast_insert(make_pair(c, 1));
  }

  const Tabla &ref = dameTabla(nombre);
  auto campos_datos = _tipos_tabla(ref);
  Tabla res(ref.claves(), campos_datos.first, campos_datos.second);
  list<Registro> regs(ref.registros().begin(), ref.registros().end());
  for (auto restriccion : c) {
    _filtrar_registros(restriccion.campo(), restriccion.dato(),
                       regs, restriccion.igual());
  }
  for (auto r : regs) {
    res.agregarRegistro(r);
  }
  return res;
}

linear_set<BaseDeDatos::Criterio> BaseDeDatos::top_criterios() const {
  linear_set<Criterio> ret;
  int max = 0;
  for (auto crit_count : _uso_criterios) {
    if (crit_count.second >= max) {
      if (crit_count.second > max) {
        ret = linear_set<Criterio>();
        max = crit_count.second;
      }
      ret.fast_insert(crit_count.first);
    }
  }
  return ret;
}

/* @corregir(ivan): No cumple con la complejidad pedida. */
void BaseDeDatos::crearIndice(const string &nombre, const string &campo) {

  /* @comentario(ivan): La operación dameTabla ya es O(1) como la tienen implementada ahora. Se ve por qué ? */
  Tabla t = this->dameTabla(nombre); // O(T) (TODO: convertir a esta operación en O(1))
  Indice indice; // O(1)

  for (auto it_reg = t.registros_begin(); it_reg != t.registros_end(); ++it_reg){ // O(m)
    auto dato = (*it_reg).dato(campo);
    auto registros = indice.registros(dato); // O(L) /* @comentario(ivan): Esta complejidad no es lo que dice la documentación de la función registros (Inidice.h:17) */
    registros.insert(it_reg); // O(log(m))
  }

  indices[nombre][campo] = indice; // O(copy(Indice)) /* @corregir(ivan): Este copy(Indice) hace que no cierre la complejidad. */
}

join_iterator BaseDeDatos::join(const string &tabla1, const string &tabla2, const string &campo) const {

  string tabla_principal = tabla1;
  string tabla_con_indice = tabla2;
  set<Tabla::const_iterador_registros> registros_tabla_2;

  // Chequeamos si efectivamente la tabla2 tiene indice
  // Si no lo tiene, por precondicion sabemos que tabla1 tiene indice
  if (indices.find(tabla_con_indice).isEnd()) {
    tabla_principal = tabla2;
    tabla_con_indice = tabla1;
  }

  const Tabla &tabla = this->dameTabla(tabla_principal);
  Indice indice = indices.at(tabla_con_indice).at(campo);

  // Declaramos iterador de tabla principal y variable para almacenar los conjuntos de registros del indice
  set<Tabla::const_iterador_registros> registros_en_indice;
  auto it_registros_tabla_principal = tabla.registros_begin();
  auto it_registros_tabla_principal_end = tabla.registros_end();

  // Iteramos sobre tabla principal, buscando el primer match con registro del indice
  bool match = false;
  while (it_registros_tabla_principal != it_registros_tabla_principal_end) {
    auto dato = (*it_registros_tabla_principal).dato(campo);
    if (indice.existe(dato)) {
      registros_en_indice = indice.registros(dato);
      match = true;
    }
  }

  join_iterator join_it(it_registros_tabla_principal, it_registros_tabla_principal_end, registros_en_indice.begin(), registros_en_indice.end());

  return join_it;
}
