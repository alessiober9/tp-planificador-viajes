#ifndef TP_HPP
#define TP_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Usamos el namespace std para escribir 'cout' en vez de 'std::cout'
using namespace std;

// --- ESTRUCTURAS DE DATOS (TODO COMO STRING) ---

struct Vuelo {
    string codigo;
    string origen;
    string destino;
    string fecha;
    string hora;
    string precio;
    string asientos;
};

struct Hotel {
    string id;
    string nombre;
    string ciudad;
    string precio_noche;
    string cupo;
};

struct Excursion {
    string id;
    string ciudad;
    string descripcion;
    string fecha;
    string precio;
    string cupo;
};

// --- NODOS PARA LAS LISTAS ENLAZADAS ---

struct NodoVuelo {
    Vuelo info;
    NodoVuelo* sig;
};

struct NodoHotel {
    Hotel info;
    NodoHotel* sig;
};

struct NodoExcursion {
    Excursion info;
    NodoExcursion* sig;
};

// --- ESTRUCTURAS PARA EL ITINERARIO ---

struct Reserva {
    int tipo;             // Usaremos un int: 1=VUELO, 2=HOTEL, 3=EXCURSION
    string codigoItem;    // Código del vuelo, id del hotel o excursión
    string descripcion;   // "Vuelo a Madrid", "Hotel Sol", etc.
    string fecha;         // "YYYY-MM-DD", clave para ordenar
    string costo;
};

struct NodoItinerario {
    Reserva info;
    NodoItinerario* sig;
};

// --- ESTRUCTURAS PARA EL HISTORIAL (PILA) --- (punto 7)

struct Accion {
    int tipo; // 1 = AGREGAR, 2 = CANCELAR
    Reserva reservaInvolucrada; // Guardamos una copia de la reserva
};

struct NodoPila {
    Accion info;
    NodoPila* sig;
};

// ESTRUCTURAS PARA COLA

struct Cliente {
    string dni;
    string nombreApellido;
    string fechaNacimiento;
    NodoItinerario* itinerario; // ¡Cada cliente tiene su propio itinerario!
};

struct NodoCola {
    Cliente info;
    NodoCola* sig;
};

//////////////////////////////////////////////////////////////////////////////////////////////

// --- DECLARACIÓN DE FUNCIONES ---

// Funciones para cargar y mostrar catalogos (punto 1)

// Funciones para cargar los catálogos desde los CSV
void cargarVuelos(NodoVuelo*& lista);
void cargarHoteles(NodoHotel*& lista);
void cargarExcursiones(NodoExcursion*& lista);

// Funciones para mostrar los catálogos y verificar que se cargaron bien
void mostrarVuelos(NodoVuelo* lista);
void mostrarHoteles(NodoHotel* lista);
void mostrarExcursiones(NodoExcursion* lista);

//Funcion para el menu principal
void mostrarMenu(); 


// --- FUNCIONES DE LISTADO --- (Puntos 2,3 y 4)
void listarVuelosPorDestino(NodoVuelo* lista);
void listarHotelesPorCiudad(NodoHotel* lista);
void listarExcursionesPorCiudad(NodoExcursion* lista);


// --- FUNCIONES PARA EL ITINERARIO --- (Punto 5)
void agregarReserva(NodoVuelo* listaVuelos, NodoHotel* listaHoteles, NodoExcursion* listaExcursiones, NodoItinerario*& itinerario, NodoPila*& historial);
void mostrarItinerario(NodoItinerario* itinerario);

//IDEM (punto 6)
void cancelarReserva(NodoItinerario*& itinerario, NodoVuelo* listaVuelos, NodoHotel* listaHoteles, NodoExcursion* listaExcursiones, NodoPila*& historial);


// Funciones auxiliares de búsqueda
NodoVuelo* buscarVueloPorCodigo(NodoVuelo* lista, string codigo);
NodoHotel* buscarHotelPorId(NodoHotel* lista, string id);
NodoExcursion* buscarExcursionPorId(NodoExcursion* lista, string id);

//Declaramos la nueva función para el punto 7

void deshacerUltimaAccion(NodoPila*& historial, NodoItinerario*& itinerario, NodoVuelo* listaVuelos, NodoHotel* listaHoteles, NodoExcursion* listaExcursiones);

// --- Función ayudante para eliminación silenciosa del punto (6 y 7)---
bool eliminarReservaPorCodigo(string codigo, NodoItinerario*& itinerario, NodoVuelo* listaVuelos, NodoHotel* listaHoteles, NodoExcursion* listaExcursiones);

// --- FUNCIONES PARA LA PILA ---
void apilar(NodoPila*& pila, Accion accion);
Accion desapilar(NodoPila*& pila);
void deshacerUltimaAccion(NodoPila*& historial, NodoItinerario*& itinerario, NodoVuelo* listaVuelos, NodoHotel* listaHoteles, NodoExcursion* listaExcursiones);

// FUNCIONES PARA COLA
void encolarCliente(NodoCola*& frente, NodoCola*& fin);
void atenderCliente(NodoCola*& frente, NodoCola*& fin, Cliente*& clienteEnAtencion);

// --- FUNCIONES PARA ARCHIVOS ---
void escribirLog(string mensaje);
void guardarItinerario(Cliente* cliente);

// --- FUNCIONES PARA ARCHIVOS ---
void escribirLog(string mensaje);
void guardarItinerario(Cliente* cliente);

#endif // TP_HPP