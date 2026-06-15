# 🗺️ Planificador de Vacaciones

Trabajo Práctico final de **Algoritmos y Estructuras de Datos** — UTN FRBA.

Sistema de gestión de viajes desarrollado en **C++** que permite a agentes de turismo administrar catálogos, reservas e itinerarios de clientes mediante una interfaz de menú por consola.

---

## ✨ Funcionalidades

| # | Función |
|---|---------|
| 1 | Carga de catálogos desde archivos CSV (vuelos, hoteles, excursiones) |
| 2 | Búsqueda de vuelos por destino |
| 3 | Búsqueda de hoteles por ciudad |
| 4 | Búsqueda de excursiones por ciudad |
| 5 | Reserva de vuelos, hoteles y excursiones (con control de cupo) |
| 6 | Cancelación de reservas (repone cupo automáticamente) |
| 7 | Deshacer última acción (undo) |
| 8 | Encolar nuevos clientes |
| 9 | Atender al próximo cliente de la fila |
| 10 | Guardar itinerario del cliente en archivo |
| 11 | Ver reporte con costo total + IVA (21%) |

---

## 🧱 Estructuras de datos utilizadas

- **Lista enlazada**: catálogos de vuelos, hoteles y excursiones; itinerario del cliente (ordenado por fecha).
- **Pila (stack)**: historial de acciones para implementar el *undo*.
- **Cola (queue)**: fila de atención al cliente por orden de llegada.
- **Archivos**: `itinerario.dat` para persistir reservas; `log.dat` como bitácora de auditoría.

---

## 📁 Estructura del proyecto

```
tp-planificador-vacaciones/
│
├── src/
│   ├── main.cpp          # Función principal y menú interactivo
│   ├── funciones.cpp     # Implementación de todas las funciones
│   └── funciones.hpp     # Estructuras y declaraciones
│
├── data/
│   ├── vuelos.csv        # Catálogo de vuelos de ejemplo
│   ├── hoteles.csv       # Catálogo de hoteles de ejemplo
│   └── excursiones.csv   # Catálogo de excursiones de ejemplo
│
└── README.md
```

---

## ▶️ Compilación y ejecución

**Requisito:** tener instalado `g++` (MinGW en Windows o GCC en Linux/Mac).

```bash
# Desde la raíz del proyecto
g++ src/main.cpp src/funciones.cpp -o planificador

# Ejecutar (los CSV deben estar en la misma carpeta desde donde se corre)
./planificador
```

> **Nota:** al ejecutar, los archivos `vuelos.csv`, `hoteles.csv` y `excursiones.csv` deben estar en el directorio de trabajo actual (la carpeta `data/` o donde se corra el binario).

---

## 🛠️ Tecnologías

- **Lenguaje:** C++
- **Compilador:** g++ / MinGW
- **IDE usado en desarrollo:** Dev-C++
- **Paradigma:** Programación estructurada con manejo dinámico de memoria (punteros)
