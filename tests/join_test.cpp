#include "../src/BaseDeDatos.h"
#include "../src/Dato.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

TEST(join_test, generadores) {

    // Iniciar DB
    BaseDeDatos db;

    // Crear tabla: Materias
    vector<string> campos_materias({"id", "nombre_materia"});
    vector<Dato> tipos_materias = {tipoNat, tipoStr};
    linear_set<string> claves_materias = {"id"};
    db.crearTabla("materias", claves_materias, campos_materias, tipos_materias);
//    db.agregarRegistro(Registro(campos_materias, {datoNat(1), datoStr("Analisis I")}), "materias");
//    db.agregarRegistro(Registro(campos_materias, {datoNat(2), datoStr("Algebra I")}), "materias");
//    db.agregarRegistro(Registro(campos_materias, {datoNat(3), datoStr("Probabilidades y Estadistica (C)")}), "materias");
//    db.agregarRegistro(Registro(campos_materias, {datoNat(4), datoStr("Algoritmos y Estructuras de Datos I")}), "materias");
//    db.agregarRegistro(Registro(campos_materias, {datoNat(5), datoStr("Algoritmos y Estructuras de Datos II")}), "materias");
//    db.agregarRegistro(Registro(campos_materias, {datoNat(6), datoStr("Organizacion del Computador I")}), "materias");
//    db.agregarRegistro(Registro(campos_materias, {datoNat(7), datoStr("Metodos Numericos")}), "materias");
//    db.agregarRegistro(Registro(campos_materias, {datoNat(8), datoStr("Organizacion del Computador II")}), "materias");
//    db.agregarRegistro(Registro(campos_materias, {datoNat(9), datoStr("Algoritmos y Estructuras de Datos III")}), "materias");
//    db.agregarRegistro(Registro(campos_materias, {datoNat(10), datoStr("Sistemas Operativos")}), "materias");

//    // Crear tabla: alumnos_materias
//    vector<string> campos_alumnos_materias({"LU", "nombre_materia"});
//    vector<Dato> tipos_alumnos_materias = {tipoNat, tipoNat, tipoStr, tipoStr};
//    linear_set<string> claves_alumnos_materias = {};
//    db.crearTabla("alumnos_materias", claves_materias, campos_alumnos_materias, tipos_materias);
//    db.agregarRegistro(Registro(campos_alumnos_materias, {datoNat(11), datoStr("Analisis I")}), "alumnos_materias");
//    db.agregarRegistro(Registro(campos_alumnos_materias, {datoNat(22), datoStr("Analisis I")}), "alumnos_materias");
//    db.agregarRegistro(Registro(campos_alumnos_materias, {datoNat(33), datoStr("Analisis I")}), "alumnos_materias");
//    db.agregarRegistro(Registro(campos_alumnos_materias, {datoNat(44), datoStr("Analisis I")}), "alumnos_materias");
//    db.agregarRegistro(Registro(campos_alumnos_materias, {datoNat(11), datoStr("Algebra I")}), "alumnos_materias");
//    db.agregarRegistro(Registro(campos_alumnos_materias, {datoNat(22), datoStr("Algebra I")}), "alumnos_materias");
//    db.agregarRegistro(Registro(campos_alumnos_materias, {datoNat(33), datoStr("Algebra I")}), "alumnos_materias");
//    db.agregarRegistro(Registro(campos_alumnos_materias, {datoNat(11), datoStr("Metodos Numericos")}), "alumnos_materias");
//    db.agregarRegistro(Registro(campos_alumnos_materias, {datoNat(44), datoStr("Metodos Numericos")}), "alumnos_materias");
//
//    // Crear indice
//    db.crearIndice("alumnos_materias", "nombre_materia");

    EXPECT_TRUE(false);
}