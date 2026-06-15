#include "funciones.hpp"

// --- FUNCIÓN PRINCIPAL (VERSIÓN INTERACTIVA) ---

int main() {
    // Punteros a las listas de catálogos
    NodoVuelo* listaVuelos = NULL;
    NodoHotel* listaHoteles = NULL;
    NodoExcursion* listaExcursiones = NULL;

    // Puntero a la pila del historial (para el cliente activo)
    NodoPila* historial = NULL;

    // Manejo de la Cola y Cliente Activo ---
    NodoCola* colaFrente = NULL;
    NodoCola* colaFin = NULL;
    Cliente* clienteActivo = NULL;

    int opcion;

    do {
        mostrarMenu();
        if (clienteActivo != NULL) {
            cout << "* Atendiendo a: " << clienteActivo->nombreApellido << " *" << endl;
        } else {
            cout << "* Ningun cliente en atencion. Use opciones 8 y 9. *" << endl;
        }

        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Cargando catalogos..." << endl;
                cargarVuelos(listaVuelos);
                cargarHoteles(listaHoteles);
                cargarExcursiones(listaExcursiones);
                cout << "¡Catalogos cargados con exito!" << endl;

                mostrarVuelos(listaVuelos);
                mostrarHoteles(listaHoteles);
                mostrarExcursiones(listaExcursiones);
                break;

            case 2:
                listarVuelosPorDestino(listaVuelos);
                break;

            case 3:
                listarHotelesPorCiudad(listaHoteles);
                break;

            case 4:
                listarExcursionesPorCiudad(listaExcursiones);
                break;

            case 5: // Agregar Reserva
                if (clienteActivo != NULL) {
                    agregarReserva(listaVuelos, listaHoteles, listaExcursiones, clienteActivo->itinerario, historial);
                } else {
                    cout << "Error: Debe atender a un cliente primero (opcion 9)." << endl;
                }
                break;

            case 6: // Cancelar Reserva
                if (clienteActivo != NULL) {
                    cancelarReserva(clienteActivo->itinerario, listaVuelos, listaHoteles, listaExcursiones, historial);
                } else {
                    cout << "Error: Debe atender a un cliente primero (opcion 9)." << endl;
                }
                break;

            case 7: // Deshacer
                if (clienteActivo != NULL) {
                    deshacerUltimaAccion(historial, clienteActivo->itinerario, listaVuelos, listaHoteles, listaExcursiones);
                } else {
                    cout << "Error: Debe atender a un cliente primero (opcion 9)." << endl;
                }
                break;

            case 8: // Encolar nuevo cliente
                encolarCliente(colaFrente, colaFin);
                break;

            case 9: // Atender próximo cliente
                atenderCliente(colaFrente, colaFin, clienteActivo);
                break;

            case 10: // Guardar Itinerario y Finalizar Atención
                if (clienteActivo != NULL) {
                    guardarItinerario(clienteActivo);
                    
                    // Liberamos la memoria del cliente que terminamos de atender
                    delete clienteActivo; 
                    // Dejamos el "mostrador" libre para el siguiente
                    clienteActivo = NULL; 
                    
                    cout << "Atencion finalizada. Ya puede atender al siguiente cliente de la fila (opcion 9)." << endl;
                } else {
                    cout << "Error: No hay ningun cliente en atencion." << endl;
                }
                break;

            case 11: // Ver Reporte del cliente activo
                if (clienteActivo != NULL) {
                    mostrarItinerario(clienteActivo->itinerario);
                } else {
                    cout << "Error: Debe atender a un cliente primero (opcion 9)." << endl;
                }
                break;

            case 0:
                cout << "¡Hasta luego!" << endl;
                break;

            default:
                cout << "Opcion no valida. Por favor, intente de nuevo." << endl;
                break;
        }

        // Evita que el programa se cierre en la opción de salida
        if (opcion != 0) {
            // Pequeña pausa para que el usuario pueda leer el mensaje
            cout << "\nPresione Enter para continuar...";
            cin.ignore(); // Limpia el buffer de entrada
            cin.get();    // Espera a que el usuario presione Enter
        }

    } while (opcion != 0);

    // Liberar memoria (pendiente, incluyendo la del clienteActivo y la cola)
    return 0;
}