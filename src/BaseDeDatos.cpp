#include "BaseDeDatos.h"

BaseDeDatos::BaseDeDatos(){};

void BaseDeDatos::crearTabla(const string &nombre, 
                             const linear_set<string> &claves,
                             const vector<string> &campos,
                             const vector<Dato> &tipos) {
  _nombres_tablas.fast_insert(nombre);
  _tablas.insert(make_pair(nombre, Tabla(claves, campos, tipos)));
}

void BaseDeDatos::agregarRegistro(const Registro &r, const string &nombre) {

  Tabla &t = _tablas.at(nombre);
  Tabla::const_iterador_registros reg = t.agregarRegistro(r);

  // Agregar el índice en O(C * (L + log(m)))
  auto t_campos_indices = tablas_indices.find(nombre); // O(1) (pues largo de claves acotado)
  if (!t_campos_indices.isEnd()) {

    // Iteramos sobre los índices de la tabla (en el peor caso todos los campos tienen índice y hacemos C iteraciones)
    for (auto it_campos = (*t_campos_indices).second.begin(); !it_campos.isEnd(); ++it_campos) {
      string valor = obtener_dato_str(r, it_campos.getClave()); // O(1)
      Indice indice = (*it_campos).second; // O(1)
      auto registros = indice[valor]; // O(L)
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

bool BaseDeDatos::registroValido(const Registro &r,
                                 const string &nombre) const {
  const Tabla &t = _tablas.at(nombre);

  return (t.campos() == r.campos() and _mismos_tipos(r, t) and
          _no_repite(r, t));
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
  list<Registro> filtrados(t.registros().begin(), t.registros().end());
  for (auto clave : t.claves()) {
    _filtrar_registros(clave, r.dato(clave), filtrados);
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
  while ( iter != registros.end()) {
    auto now = iter;
    iter++;
    if ((not igualdad) xor now->dato(campo) != valor) {
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

bool BaseDeDatos::criterioValido(const Criterio &c,
                                 const string &nombre) const {
  const Tabla &t = _tablas.at(nombre);
  for (auto restriccion : c) {
    if (not t.campos().count(restriccion.campo())) {
      return false;
    }
    if (t.tipoCampo(restriccion.campo()).esNat() != 
        restriccion.dato().esNat()) {
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

void BaseDeDatos::crearIndice(const string &nombre, const string &campo) {

  Tabla t = this->dameTabla(nombre); // O(T) (TODO: convertir a esta operación en O(1))
  Indice i; // O(1)

  for (auto it_reg = t.registros_begin(); it_reg != t.registros_end(); ++it_reg){ // O(m)
    string valor = obtener_dato_str(*it_reg, campo); // O(1)
    auto registros = i[valor]; // O(L)
    registros.insert(it_reg); // O(log(m))
  }

  tablas_indices[nombre][campo] = i; // O(copy(i))
}


string BaseDeDatos::obtener_dato_str(const Registro &reg, string campo) {
  Dato dato = reg.dato(campo); // TODO: convertir a esta operación en O(1)
  return dato.esString() ? dato.valorStr() : to_string(dato.valorNat());
}