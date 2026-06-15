#include <iostream>
#include "TP.hpp"

//CPP TEMPORAL

// --- FUNCIONES PARA AGREGAR NODOS A LAS LISTAS ---

// Agrega un Vuelo al final de su lista
void agregarNodo(NodoVuelo*& lista, Vuelo v) {
    NodoVuelo* nuevo = new NodoVuelo();
    nuevo->info = v;
    nuevo->sig = NULL;

    if (lista == NULL) {
        lista = nuevo;
    } else {
        NodoVuelo* aux = lista;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}

// Agrega un Hotel al final de su lista
void agregarNodo(NodoHotel*& lista, Hotel h) {
    NodoHotel* nuevo = new NodoHotel();
    nuevo->info = h;
    nuevo->sig = NULL;

    if (lista == NULL) {
        lista = nuevo;
    } else {
        NodoHotel* aux = lista;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}

// Agrega una Excursion al final de su lista
void agregarNodo(NodoExcursion*& lista, Excursion e) {
    NodoExcursion* nuevo = new NodoExcursion();
    nuevo->info = e;
    nuevo->sig = NULL;

    if (lista == NULL) {
        lista = nuevo;
    } else {
        NodoExcursion* aux = lista;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}


// --- FUNCIONES PARA CARGAR DATOS DESDE CSV ---

// Lee vuelos.csv y llena la lista de vuelos
void cargarVuelos(NodoVuelo*& lista) {
    ifstream archivo("vuelos.csv");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo vuelos.csv" << endl;
        return;
    }

    string linea;
    getline(archivo, linea); // Ignoramos la cabecera

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Vuelo reg;
        getline(ss, reg.codigo, ',');
        getline(ss, reg.origen, ',');
        getline(ss, reg.destino, ',');
        getline(ss, reg.fecha, ',');
        getline(ss, reg.hora, ',');
        getline(ss, reg.precio, ',');
        getline(ss, reg.asientos); // El último campo no tiene coma
        agregarNodo(lista, reg);
    }
    archivo.close();
}

// Lee hoteles.csv y llena la lista de hoteles
void cargarHoteles(NodoHotel*& lista) {
    ifstream archivo("hoteles.csv");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo hoteles.csv" << endl;
        return;
    }
    string linea;
    getline(archivo, linea); // Ignoramos la cabecera

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Hotel reg;
        getline(ss, reg.id, ',');
        getline(ss, reg.nombre, ',');
        getline(ss, reg.ciudad, ',');
        getline(ss, reg.precio_noche, ',');
        getline(ss, reg.cupo);
        agregarNodo(lista, reg);
    }
    archivo.close();
}

// Lee excursiones.csv y llena la lista de excursiones
void cargarExcursiones(NodoExcursion*& lista) {
    ifstream archivo("excursiones.csv");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo excursiones.csv" << endl;
        return;
    }
    string linea;
    getline(archivo, linea); // Ignoramos la cabecera

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Excursion reg;
        getline(ss, reg.id, ',');
        getline(ss, reg.ciudad, ',');
        getline(ss, reg.descripcion, ',');
        getline(ss, reg.fecha, ',');
        getline(ss, reg.precio, ',');
        getline(ss, reg.cupo);
        agregarNodo(lista, reg);
    }
    archivo.close();
}


// --- FUNCIONES PARA MOSTRAR LOS DATOS CARGADOS ---

void mostrarVuelos(NodoVuelo* lista) {
    cout << "--- VUELOS ---" << endl;
    for (NodoVuelo* aux = lista; aux != NULL; aux = aux->sig) {
        cout << "Codigo: " << aux->info.codigo << ", Origen: " << aux->info.origen
             << ", Destino: " << aux->info.destino << ", Fecha: " << aux->info.fecha
             << ", Hora: " << aux->info.hora << ", Precio: " << aux->info.precio
             << ", Asientos: " << aux->info.asientos << endl;
    }
}

void mostrarHoteles(NodoHotel* lista) {
    cout << "--- HOTELES ---" << endl;
    for (NodoHotel* aux = lista; aux != NULL; aux = aux->sig) {
        cout << "ID: " << aux->info.id << ", Nombre: " << aux->info.nombre
             << ", Ciudad: " << aux->info.ciudad << ", Precio noche: " << aux->info.precio_noche
             << ", Cupo: " << aux->info.cupo << endl;
    }
}

void mostrarExcursiones(NodoExcursion* lista) {
    cout << "--- EXCURSIONES ---" << endl;
    for (NodoExcursion* aux = lista; aux != NULL; aux = aux->sig) {
        cout << "ID: " << aux->info.id << ", Ciudad: " << aux->info.ciudad
             << ", Desc: " << aux->info.descripcion << ", Fecha: " << aux->info.fecha
             << ", Precio: " << aux->info.precio << ", Cupo: " << aux->info.cupo << endl;
    }
}

// --- FUNCIÓN PARA MOSTRAR EL MENÚ PRINCIPAL ---

void mostrarMenu() {
    cout << "--- PLANIFICADOR DE VACACIONES ---" << endl;
    cout << "1. Cargar catalogos" << endl;
    cout << "2. Listar vuelos por destino" << endl;
    cout << "3. Listar hoteles por ciudad" << endl;
    cout << "4. Listar excursiones por ciudad" << endl;
    cout << "5. Agregar una reserva al itinerario" << endl;
    cout << "6. Cancelar una reserva" << endl;
    cout << "7. Deshacer ultima accion" << endl;
    cout << "8. Encolar cliente para atencion" << endl;
    cout << "9. Atender proximo cliente" << endl;
    cout << "10. Guardar itinerario" << endl;
    cout << "11. Ver reporte de itinerario" << endl;
    cout << "0. Salir" << endl;
    cout << "------------------------------------" << endl;
}

// --- FUNCIONES DE LISTADO/BÚSQUEDA ---

void listarVuelosPorDestino(NodoVuelo* lista) {
    // Verificamos si hay algo que mostrar.
    if (lista == NULL) {
        cout << "No hay vuelos cargados en el sistema." << endl;
        return; // Salimos de la función.
    }

    string destinoBuscado;
    cout << "Ingrese el codigo de destino que desea buscar (ej: MAD, MIA, EZE): ";
    cin >> destinoBuscado;

    cout << "--- VUELOS ENCONTRADOS PARA '" << destinoBuscado << "' ---" << endl;
    bool encontrados = false;
    
    // 1. Inicializamos tu puntero auxiliar para que apunte al inicio de la lista.
    NodoVuelo* listaAux = lista;

    // 2. Recorremos la lista MIENTRAS el puntero auxiliar no sea NULL.
    while (listaAux != NULL) {
        // 3. Comparamos (==) el destino del nodo ACTUAL con el buscado.
        if (listaAux->info.destino == destinoBuscado) {
            cout << "Codigo: " << listaAux->info.codigo << ", Origen: " << listaAux->info.origen
                 << ", Fecha: " << listaAux->info.fecha << ", Hora: " << listaAux->info.hora
                 << ", Precio: " << listaAux->info.precio << ", Asientos: " << listaAux->info.asientos << endl;
            encontrados = true;
        }
        
        // 4. MUY IMPORTANTE: avanzamos al siguiente nodo para no quedar en un bucle infinito.
        listaAux = listaAux->sig; 
    }

    // Un pequeño extra para avisar si no se encontró nada.
    if (!encontrados) {
        cout << "No se encontraron vuelos con ese destino." << endl;
    }
}

void listarHotelesPorCiudad(NodoHotel* lista) {
    if (lista == NULL) {
        cout << "No hay hoteles cargados en el sistema." << endl;
        return;
    }

    string ciudadBuscada;
    cout << "Ingrese la ciudad que desea buscar (ej: Madrid, Miami): ";
    cin >> ciudadBuscada;

    cout << "--- HOTELES ENCONTRADOS EN '" << ciudadBuscada << "' ---" << endl;
    bool encontrados = false;
    
    NodoHotel* listaAux = lista;

    while (listaAux != NULL) {
        if (listaAux->info.ciudad == ciudadBuscada) {
            cout << "ID: " << listaAux->info.id << ", Nombre: " << listaAux->info.nombre
                 << ", Precio noche: " << listaAux->info.precio_noche
                 << ", Cupo: " << listaAux->info.cupo << endl;
            encontrados = true;
        }
        listaAux = listaAux->sig;
    }

    if (!encontrados) {
        cout << "No se encontraron hoteles en esa ciudad." << endl;
    }
}

void listarExcursionesPorCiudad(NodoExcursion* lista) {
    if (lista == NULL) {
        cout << "No hay excursiones cargadas en el sistema." << endl;
        return;
    }

    string ciudadBuscada;
    cout << "Ingrese la ciudad que desea buscar (ej: Madrid, Miami): ";
    cin >> ciudadBuscada;

    cout << "--- EXCURSIONES ENCONTRADAS EN '" << ciudadBuscada << "' ---" << endl;
    bool encontrados = false;
    
    NodoExcursion* listaAux = lista;

    while (listaAux != NULL) {
        if (listaAux->info.ciudad == ciudadBuscada) {
            cout << "ID: " << listaAux->info.id << ", Desc: " << listaAux->info.descripcion
                 << ", Fecha: " << listaAux->info.fecha << ", Precio: " << listaAux->info.precio
                 << ", Cupo: " << listaAux->info.cupo << endl;
            encontrados = true;
        }
        listaAux = listaAux->sig;
    }

    if (!encontrados) {
        cout << "No se encontraron excursiones en esa ciudad." << endl;
    }
}

// --- FUNCIONES PARA EL ITINERARIO --- (punto 5 y 6)

// ESTA FUNCIÓN NO CAMBIA, ES EXACTAMENTE IGUAL
void insertarOrdenado(NodoItinerario*& itinerario, Reserva nuevaReserva) {
    NodoItinerario* nuevo = new NodoItinerario();
    nuevo->info = nuevaReserva;
    nuevo->sig = NULL;

    if (itinerario == NULL || nuevaReserva.fecha < itinerario->info.fecha) {
        nuevo->sig = itinerario;
        itinerario = nuevo;
    } else {
        NodoItinerario* listaAux = itinerario;
        while (listaAux->sig != NULL && listaAux->sig->info.fecha < nuevaReserva.fecha) {
            listaAux = listaAux->sig;
        }
        nuevo->sig = listaAux->sig;
        listaAux->sig = nuevo;
    }
}

// ESTA FUNCIÓN TAMPOCO CAMBIA
NodoVuelo* buscarVueloPorCodigo(NodoVuelo* lista, string codigo) {
    NodoVuelo* listaAux = lista;
    while (listaAux != NULL) {
        if (listaAux->info.codigo == codigo) {
            return listaAux;
        }
        listaAux = listaAux->sig;
    }
    return NULL;
}

// (Aquí va la función buscarVueloPorCodigo que ya tenés)

NodoHotel* buscarHotelPorId(NodoHotel* lista, string id) {
    NodoHotel* listaAux = lista;
    while (listaAux != NULL) {
        if (listaAux->info.id == id) {
            return listaAux; // ¡Lo encontramos!
        }
        listaAux = listaAux->sig;
    }
    return NULL; // No se encontró.
}

NodoExcursion* buscarExcursionPorId(NodoExcursion* lista, string id) {
    NodoExcursion* listaAux = lista;
    while (listaAux != NULL) {
        if (listaAux->info.id == id) {
            return listaAux; // ¡Lo encontramos!
        }
        listaAux = listaAux->sig;
    }
    return NULL; // No se encontró.
}

//ahora si, punto 5 y 6 (las anteriores 3 funciones las usaremos en este void)

//punto 5, dentro de este esta el punto 7
/**
 * Orquesta el proceso de agregar una nueva reserva al itinerario
 * y registra la acción en la pila del historial.
 */
void agregarReserva(NodoVuelo* listaVuelos, NodoHotel* listaHoteles, NodoExcursion* listaExcursiones, NodoItinerario*& itinerario, NodoPila*& historial) {
    int tipoOpcion;
    cout << "\n¿Que desea reservar?" << endl;
    cout << "1. Vuelo" << endl;
    cout << "2. Hotel" << endl;
    cout << "3. Excursion" << endl;
    cout << "Seleccione una opcion: ";
    cin >> tipoOpcion;

    Reserva nuevaReserva; // La creamos aquí para usarla en todos los casos

    // --- LÓGICA PARA VUELOS ---
    if (tipoOpcion == 1) {
        string codigoVuelo;
        mostrarVuelos(listaVuelos);
        cout << "Ingrese el codigo del vuelo a reservar: ";
        cin >> codigoVuelo;
        NodoVuelo* vueloEncontrado = buscarVueloPorCodigo(listaVuelos, codigoVuelo);

        if (vueloEncontrado != NULL) {
            int asientos = stoi(vueloEncontrado->info.asientos);
            if (asientos > 0) {
                nuevaReserva.tipo = 1; // 1 = VUELO
                nuevaReserva.codigoItem = vueloEncontrado->info.codigo;
                nuevaReserva.descripcion = "Vuelo " + vueloEncontrado->info.origen + " -> " + vueloEncontrado->info.destino;
                nuevaReserva.fecha = vueloEncontrado->info.fecha;
                nuevaReserva.costo = vueloEncontrado->info.precio;
                
                insertarOrdenado(itinerario, nuevaReserva);
                asientos--;
                vueloEncontrado->info.asientos = to_string(asientos);
                cout << "¡Vuelo reservado con exito!" << endl;
			 	//PARA EL LOG
                escribirLog("Reserva AGREGADA: " + nuevaReserva.descripcion);

                // --- REGISTRAMOS EN EL HISTORIAL --- (punto 7)
                Accion nuevaAccion;
                nuevaAccion.tipo = 1; // 1 = AGREGAR
                nuevaAccion.reservaInvolucrada = nuevaReserva;
                apilar(historial, nuevaAccion);
            } else {
                cout << "Error: No hay asientos disponibles para este vuelo." << endl;
            }
        } else {
            cout << "Error: No se encontro ningun vuelo con ese codigo." << endl;
        }
    }
    // --- LÓGICA PARA HOTELES ---
    else if (tipoOpcion == 2) {
        string idHotel;
        mostrarHoteles(listaHoteles);
        cout << "Ingrese el ID del hotel a reservar: ";
        cin >> idHotel;
        NodoHotel* hotelEncontrado = buscarHotelPorId(listaHoteles, idHotel);

        if (hotelEncontrado != NULL) {
            int cupo = stoi(hotelEncontrado->info.cupo);
            if (cupo > 0) {
                nuevaReserva.tipo = 2; // 2 = HOTEL
                nuevaReserva.codigoItem = hotelEncontrado->info.id;
                nuevaReserva.descripcion = "Hotel '" + hotelEncontrado->info.nombre + "' en " + hotelEncontrado->info.ciudad;
                cout << "Ingrese la fecha de check-in (YYYY-MM-DD) para el hotel: ";
                cin >> nuevaReserva.fecha;
                nuevaReserva.costo = hotelEncontrado->info.precio_noche;
                
                insertarOrdenado(itinerario, nuevaReserva);
                cupo--;
                hotelEncontrado->info.cupo = to_string(cupo);
                cout << "¡Hotel reservado con exito!" << endl;
                
                //PARA EL LOG
                escribirLog("Reserva AGREGADA: " + nuevaReserva.descripcion);

                // --- REGISTRAMOS EN EL HISTORIAL ---
                Accion nuevaAccion;
                nuevaAccion.tipo = 1; // 1 = AGREGAR
                nuevaAccion.reservaInvolucrada = nuevaReserva;
                apilar(historial, nuevaAccion);
            } else {
                cout << "Error: No hay cupo disponible para este hotel." << endl;
            }
        } else {
            cout << "Error: No se encontro ningun hotel con ese ID." << endl;
        }
    }
    // --- LÓGICA PARA EXCURSIONES ---
    else if (tipoOpcion == 3) {
        string idExcursion;
        mostrarExcursiones(listaExcursiones);
        cout << "Ingrese el ID de la excursión a reservar: ";
        cin >> idExcursion;
        NodoExcursion* excursionEncontrada = buscarExcursionPorId(listaExcursiones, idExcursion);

        if (excursionEncontrada != NULL) {
            int cupo = stoi(excursionEncontrada->info.cupo);
            if (cupo > 0) {
                nuevaReserva.tipo = 3; // 3 = EXCURSION
                nuevaReserva.codigoItem = excursionEncontrada->info.id;
                nuevaReserva.descripcion = "Excursion '" + excursionEncontrada->info.descripcion + "' en " + excursionEncontrada->info.ciudad;
                nuevaReserva.fecha = excursionEncontrada->info.fecha;
                nuevaReserva.costo = excursionEncontrada->info.precio;
                
                insertarOrdenado(itinerario, nuevaReserva);
                cupo--;
                excursionEncontrada->info.cupo = to_string(cupo);
                cout << "¡Excursión reservada con exito!" << endl;
 				//PARA EL LOG
                escribirLog("Reserva AGREGADA: " + nuevaReserva.descripcion);

                // --- REGISTRAMOS EN EL HISTORIAL ---
                Accion nuevaAccion;
                nuevaAccion.tipo = 1; // 1 = AGREGAR
                nuevaAccion.reservaInvolucrada = nuevaReserva;
                apilar(historial, nuevaAccion);
            } else {
                cout << "Error: No hay cupo disponible para esta excursión." << endl;
            }
        } else {
            cout << "Error: No se encontro ninguna excursion con ese ID." << endl;
        }
    }
    else {
        cout << "Opcion no valida." << endl;
    }
}

// ESTA FUNCIÓN SE MODIFICA para "traducir" el número
void mostrarItinerario(NodoItinerario* itinerario) {
    cout << "\n--- ITINERARIO DE VIAJE (Ordenado por Fecha) ---" << endl;
    if (itinerario == NULL) {
        cout << "El itinerario esta vacio." << endl;
        return;
    }
    NodoItinerario* listaAux = itinerario;
    while (listaAux != NULL) {
        string tipoStr;
        // Traducimos el número a un texto legible
        switch (listaAux->info.tipo) {
            case 1: tipoStr = "Vuelo"; break;
            case 2: tipoStr = "Hotel"; break;
            case 3: tipoStr = "Excursion"; break;
            default: tipoStr = "Desconocido"; break;
        }

        cout << "[" << listaAux->info.fecha << "] - " << tipoStr << ": " << listaAux->info.descripcion 
             << " (Cod: " << listaAux->info.codigoItem << ") - Costo: $" << listaAux->info.costo << endl;
        listaAux = listaAux->sig;
    }
}

//AGREGO UN AYUDANTE PARA EL punto 6 y por ende 7 tmb

bool eliminarReservaPorCodigo(string codigo, NodoItinerario*& itinerario, NodoVuelo* listaVuelos, NodoHotel* listaHoteles, NodoExcursion* listaExcursiones) {
    NodoItinerario* actual = itinerario;
    NodoItinerario* anterior = NULL;
    bool encontrado = false;

    while (actual != NULL && !encontrado) {
        if (actual->info.codigoItem == codigo) {
            encontrado = true;
        } else {
            anterior = actual;
            actual = actual->sig;
        }
    }

    if (encontrado) {
        // Reponemos el cupo
        if (actual->info.tipo == 1) { // Vuelo
            NodoVuelo* vuelo = buscarVueloPorCodigo(listaVuelos, actual->info.codigoItem);
            if (vuelo != NULL) {
                int asientos = stoi(vuelo->info.asientos);
                asientos++;
                vuelo->info.asientos = to_string(asientos);
            }
        } else if (actual->info.tipo == 2) { // Hotel
            NodoHotel* hotel = buscarHotelPorId(listaHoteles, actual->info.codigoItem);
            if (hotel != NULL) {
                int cupo = stoi(hotel->info.cupo);
                cupo++;
                hotel->info.cupo = to_string(cupo);
            }
        } else if (actual->info.tipo == 3) { // Excursión
            NodoExcursion* excursion = buscarExcursionPorId(listaExcursiones, actual->info.codigoItem);
            if (excursion != NULL) {
                int cupo = stoi(excursion->info.cupo);
                cupo++;
                excursion->info.cupo = to_string(cupo);
            }
        }
        
        // Eliminamos el nodo de la lista
        if (anterior == NULL) {
            itinerario = actual->sig;
        } else {
            anterior->sig = actual->sig;
        }
        delete actual;
        return true; // Devolvemos 'true' si se pudo eliminar
    }
    
    return false; // Devolvemos 'false' si no se encontró
}

// //punto 6, dentro de este esta el punto 7


/**
 * Busca y elimina una reserva del itinerario, reponiendo el cupo
 * y registrando la acción en la pila del historial ANTES de borrar.
 */
 
void cancelarReserva(NodoItinerario*& itinerario, NodoVuelo* listaVuelos, NodoHotel* listaHoteles, NodoExcursion* listaExcursiones, NodoPila*& historial) {
    if (itinerario == NULL) {
        cout << "El itinerario esta vacio. No hay nada que cancelar." << endl;
        return;
    }

    mostrarItinerario(itinerario);
    string codigoCancelar;
    cout << "Ingrese el codigo del item que desea cancelar: ";
    cin >> codigoCancelar;
    
    // Buscamos la reserva para poder guardarla en el historial
    NodoItinerario* aux = itinerario;
    bool encontrado = false;

    // Primero, verificamos si existe antes de hacer nada mas.
    while(aux != NULL && !encontrado){
        if(aux->info.codigoItem == codigoCancelar){
            encontrado = true;
        } else {
            aux = aux->sig;
        }
    }
    
    // Si la encontramos, ahora sí procedemos.
    if(encontrado){
        // 1. Registramos en el historial lo que vamos a borrar.
        // La información está en 'aux->info' porque el puntero quedó en la posición correcta.
        Accion nuevaAccion;
        nuevaAccion.tipo = 2; // 2 = CANCELAR
        nuevaAccion.reservaInvolucrada = aux->info; 
        apilar(historial, nuevaAccion);

        // 2. Llamamos al ayudante para que haga el trabajo
        eliminarReservaPorCodigo(codigoCancelar, itinerario, listaVuelos, listaHoteles, listaExcursiones);
        cout << "¡Reserva cancelada con exito!" << endl;
        
        // 3. PARA USAR EL LOG
        // Usamos la información que acabamos de guardar en la Pila
        escribirLog("Reserva CANCELADA: " + nuevaAccion.reservaInvolucrada.descripcion);
        
    } else {
        cout << "No se encontro ninguna reserva con ese codigo." << endl;
    }
}

// --- FUNCIONES PARA EL HISTORIAL (PILA) --- Punto 7

// Apilar (push): Agrega una acción al tope de la pila
void apilar(NodoPila*& pila, Accion accion) {
    NodoPila* nuevo = new NodoPila();
    nuevo->info = accion;
    nuevo->sig = pila;
    pila = nuevo;
}

// Desapilar (pop): Saca una acción del tope de la pila
Accion desapilar(NodoPila*& pila) {
    Accion accion = pila->info;
    NodoPila* aBorrar = pila;
    pila = pila->sig;
    delete aBorrar;
    return accion;
}

void deshacerUltimaAccion(NodoPila*& historial, NodoItinerario*& itinerario, NodoVuelo* listaVuelos, NodoHotel* listaHoteles, NodoExcursion* listaExcursiones) {
    if (historial == NULL) {
        cout << "No hay acciones para deshacer." << endl;
        return;
    }

    Accion ultimaAccion = desapilar(historial);

    if (ultimaAccion.tipo == 1) { // La última acción fue AGREGAR
        cout << "Deshaciendo una accion de 'Agregar Reserva'..." << endl;
        string codigoAEliminar = ultimaAccion.reservaInvolucrada.codigoItem;
        
        // Llamamos al ayudante para que borre la reserva silenciosamente
        eliminarReservaPorCodigo(codigoAEliminar, itinerario, listaVuelos, listaHoteles, listaExcursiones);
        
        cout << "¡Accion deshecha! La reserva fue cancelada." << endl;

	escribirLog("Accion DESHECHA: Se cancelo la reserva '" + codigoAEliminar + "'");
    } else if (ultimaAccion.tipo == 2) { // La última acción fue CANCELAR
        cout << "Deshaciendo una accion de 'Cancelar Reserva'..." << endl;
        Reserva reservaRestaurada = ultimaAccion.reservaInvolucrada;

        // Quitamos un cupo
        if (reservaRestaurada.tipo == 1) { // Vuelo
            NodoVuelo* vuelo = buscarVueloPorCodigo(listaVuelos, reservaRestaurada.codigoItem);
            if(vuelo != NULL){
                int asientos = stoi(vuelo->info.asientos);
                asientos--;
                vuelo->info.asientos = to_string(asientos);
            }
        } else if (reservaRestaurada.tipo == 2) { // Hotel
            NodoHotel* hotel = buscarHotelPorId(listaHoteles, reservaRestaurada.codigoItem);
            if(hotel != NULL){
                int cupo = stoi(hotel->info.cupo);
                cupo--;
                hotel->info.cupo = to_string(cupo);
            }
        } else if (reservaRestaurada.tipo == 3) { // Excursión
            NodoExcursion* excursion = buscarExcursionPorId(listaExcursiones, reservaRestaurada.codigoItem);
            if(excursion != NULL){
                int cupo = stoi(excursion->info.cupo);
                cupo--;
                excursion->info.cupo = to_string(cupo);
            }
        }

        // Y la reinsertamos en el itinerario
        insertarOrdenado(itinerario, reservaRestaurada);
        cout << "¡Accion deshecha! La reserva fue restaurada." << endl;
    	escribirLog("Accion DESHECHA: Se restauro la reserva '" + reservaRestaurada.descripcion + "'");
	}
}

// 

void encolarCliente(NodoCola*& frente, NodoCola*& fin) {
    Cliente nuevoCliente;
    cout << "\n--- Nuevo Cliente en la Fila ---" << endl;
    cout << "Ingrese DNI del cliente: ";
    cin >> nuevoCliente.dni;
    cout << "Ingrese Nombre y Apellido: ";
    cin.ignore(); // Limpia el buffer antes de leer una línea completa
    getline(cin, nuevoCliente.nombreApellido);
    cout << "Ingrese Fecha de Nacimiento (YYYY-MM-DD): ";
    cin >> nuevoCliente.fechaNacimiento;

    // MUY IMPORTANTE: El itinerario del nuevo cliente empieza vacío.
    nuevoCliente.itinerario = NULL;

    // Creamos el nuevo nodo para la cola
    NodoCola* nuevo = new NodoCola();
    nuevo->info = nuevoCliente;
    nuevo->sig = NULL;

    if (frente == NULL) { // Si la cola está vacía
        frente = nuevo;
        fin = nuevo;
    } else { // Si ya hay gente en la cola
        fin->sig = nuevo;
        fin = nuevo;
    }
    cout << "¡Cliente '" << nuevoCliente.nombreApellido << "' agregado a la fila de atención!" << endl;
}

/**
 * Saca al primer cliente de la cola y lo pone en atención.
 */
void atenderCliente(NodoCola*& frente, NodoCola*& fin, Cliente*& clienteEnAtencion) {
    if (frente == NULL) {
        cout << "La fila de atencion esta vacia. No hay clientes para atender." << endl;
        return;
    }

    // Si ya estamos atendiendo a alguien, no hacemos nada.
    if (clienteEnAtencion != NULL) {
        cout << "Ya esta atendiendo a '" << clienteEnAtencion->nombreApellido 
             << "'. Termine con este cliente antes de atender al siguiente." << endl;
        return;
    }
    
    // Creamos una copia del cliente que vamos a atender.
    // Usamos 'new' para que viva fuera de esta función.
    clienteEnAtencion = new Cliente();
    *clienteEnAtencion = frente->info;

    // Sacamos el nodo de la cola
    NodoCola* aBorrar = frente;
    frente = frente->sig;

    if (frente == NULL) { // Si la cola quedó vacía
        fin = NULL;
    }
    delete aBorrar; // Liberamos la memoria del nodo

    cout << "\--- Ahora en atencion ---" << endl;
    cout << "Cliente: " << clienteEnAtencion->nombreApellido << " (DNI: " << clienteEnAtencion->dni << ")" << endl;
}

// --- FUNCIONES PARA ARCHIVOS ---

/**
 * Agrega una línea de texto al final del archivo log.dat.
 */
void escribirLog(string mensaje) {
    // ofstream (output file stream) en modo ios::app (append/añadir)
    ofstream archivoLog("log.dat", ios::app); 
    
    if (archivoLog.is_open()) {
        // Podríamos agregar una marca de tiempo, pero por simplicidad solo guardamos el mensaje.
        archivoLog << mensaje << endl;
        archivoLog.close();
    } else {
        cerr << "Error: No se pudo abrir el archivo log.dat para escribir." << endl;
    }
}

/**
 * Guarda el itinerario de un cliente en un archivo binario.
 */
void guardarItinerario(Cliente* cliente) {
    if (cliente == NULL || cliente->itinerario == NULL) {
        cout << "\nNo hay un itinerario activo para guardar." << endl;
        return;
    }

    // ofstream en modo ios::binary (binario)
    ofstream archivoItinerario("itinerario.dat", ios::binary);

    if (!archivoItinerario.is_open()) {
        cerr << "Error: No se pudo abrir el archivo itinerario.dat para guardar." << endl;
        return;
    }

    // Recorremos la lista enlazada del itinerario del cliente
    NodoItinerario* aux = cliente->itinerario;
    while (aux != NULL) {
        // Escribimos el struct 'Reserva' completo directamente en el archivo
        archivoItinerario.write((char*)&aux->info, sizeof(Reserva));
        aux = aux->sig;
    }

    archivoItinerario.close();
    escribirLog("Itinerario guardado para cliente DNI: " + cliente->dni);
    cout << "\nItinerario para '" << cliente->nombreApellido << "' guardado con exito en itinerario.dat" << endl;
}