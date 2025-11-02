# C++ INI Parser

Un parser de ficheros de configuración `.ini` implementado en C++23, enfocado en la gestión de memoria segura (RAII) y el rendimiento de la API.

## Resumen del Proyecto

Este repositorio documenta el desarrollo de un parser `.ini` y presenta dos implementaciones distintas que contrastan dos filosofías de programación en C++:

1.  **Gestión Manual de Memoria (Estilo C):** Un enfoque de bajo nivel que requiere la gestión explícita de la memoria, punteros y redimensionamiento de arrays.
2.  **Gestión Automática de Memoria (C++ Moderno):** Un enfoque idiomático que utiliza los principios de RAII (Resource Acquisition Is Initialization) y los contenedores de la Librería Estándar (STL) para eliminar la gestión manual de memoria y garantizar la seguridad.

---

## Ramas de Implementación

### `main` Branch (Modern C++ Implementation)

Esta rama contiene la implementación final, estable y recomendada. Utiliza las mejores prácticas de C++ moderno para lograr seguridad, legibilidad y rendimiento.

**Características Técnicas:**
* **Gestión de Memoria Segura (RAII):** El código está libre de llamadas a `new` o `delete` en la lógica de la aplicación. `std::string` y `std::map` gestionan sus propios recursos, eliminando el riesgo de fugas de memoria.
* **Contenedores STL:** Utiliza `std::map` para el almacenamiento de datos, proporcionando una complejidad de búsqueda optimizada de O(log n).
* **API de Alto Rendimiento:**
    * Los parámetros de la API pública utilizan `std::string_view` para evitar asignaciones de memoria innecesarias durante la invocación de funciones.
    * Los contenedores `std::map` se definen con el comparador `std::less<>` para habilitar búsquedas "transparentes", permitiendo que `find()` opere directamente con `std::string_view` sin crear objetos `std::string` temporales.
* **Testing:** Incluye una suite de tests unitarios desarrollada con Google Test para validar la robustez, el manejo de casos borde y la correctitud del parser.

### `manual-way` Branch (C-Style Implementation)

Esta rama se preserva como un caso de estudio. Es una implementación funcional del mismo parser, pero escrita con un enfoque de gestión de memoria manual.

**Características Técnicas:**
* **Gestión de Memoria Manual:** Todo el almacenamiento para secciones, claves y valores se gestiona explícitamente a través de `new[]` y `delete[]`.
* **Punteros `char*`:** Se utiliza `char*` para el almacenamiento de todas las cadenas de texto.
* **Estructuras de Datos Manuales:** El código implementa la lógica necesaria para redimensionar dinámicamente los arrays de `structs` cuando se supera su capacidad.
* **Gestión de Recursos Explícita:** El destructor de la clase es crítico y contiene la lógica para liberar recursivamente toda la memoria reservada. Esta implementación es susceptible a errores de copia superficial (shallow copy) y fugas de memoria si no se maneja con precisión.

---

## Compilación y Pruebas (Rama `main`)

El proyecto utiliza CMake como sistema de compilación y Google Test para el framework de pruebas.

### Prerrequisitos
* Un compilador compatible con C++23 (g++, Clang)
* CMake (versión 3.25 o superior)
* Git
* Un sistema de compilación (Make o Ninja)

### Pasos de Compilación
```bash
# 1. Clonar el repositorio
git clone [https://github.com/tu-usuario/ini-parser.git](https://github.com/tu-usuario/ini-parser.git)
cd ini-parser

# 2. Configurar el proyecto con CMake
# (Se recomienda crear un directorio de compilación separado)
cmake -S . -B build

# 3. Compilar el proyecto
cmake --build build
```

### Ejecución de Tests

Los tests se compilan automáticamente como parte del proceso anterior. Para ejecutarlos, utilice CTest desde el directorio de compilación:
```bash
# 1. Entrar en el directorio de compilación
cd build

# 2. Ejecutar CTest
ctest
```
