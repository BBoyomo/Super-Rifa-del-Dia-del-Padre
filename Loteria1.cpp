#include <iostream>
#include <cstring>
#include <cstdlib> 

using namespace std;

struct Cliente {
    int id;
    char nombre[50];
    char telefono[20];
    char instagram[30];
};

struct Rifa {
    int numero; // Guardará visualmente del 1 al 200
    int idCliente; // -1 si está libre
};

Cliente clientes[200];
Rifa rifas[200];
int cantidadClientes = 0;

void cargarDatos() {
    for (int i = 0; i < 200; i++) {
        rifas[i].numero = i + 1; // Guardamos el numero real (1 a 200)
        rifas[i].idCliente = -1;
    }

    FILE *archC = fopen("clientes.dat", "rb");
    if (archC != NULL) {
        fread(&cantidadClientes, sizeof(int), 1, archC);
        fread(clientes, sizeof(Cliente), cantidadClientes, archC);
        fclose(archC);
    }

    FILE *archR = fopen("rifas.dat", "rb");
    if (archR != NULL) {
        fread(rifas, sizeof(Rifa), 200, archR);
        fclose(archR);
        
        // PARCHE: Estandarizamos los números cargados para limpiar la base de datos
        for(int i = 0; i < 200; i++) {
            rifas[i].numero = i + 1;
        }
    }
}

void guardarDatos() {
    FILE *archC = fopen("clientes.dat", "wb");
    if (archC != NULL) {
        fwrite(&cantidadClientes, sizeof(int), 1, archC);
        fwrite(clientes, sizeof(Cliente), cantidadClientes, archC);
        fclose(archC);
    }

    FILE *archR = fopen("rifas.dat", "wb");
    if (archR != NULL) {
        fwrite(rifas, sizeof(Rifa), 200, archR);
        fclose(archR);
    }
}

unsigned int gestionarSemilla() {
    unsigned int semillaActual = 0;
    
    FILE *archS = fopen("semilla.dat", "rb");
    if (archS != NULL) {
        fread(&semillaActual, sizeof(unsigned int), 1, archS);
        fclose(archS);
        semillaActual++; 
    }

    archS = fopen("semilla.dat", "wb");
    if (archS != NULL) {
        fwrite(&semillaActual, sizeof(unsigned int), 1, archS);
        fclose(archS);
    }

    return semillaActual;
}

int contarFaltantes() {
    int cont = 0;
    for (int i = 0; i < 200; i++) {
        if (rifas[i].idCliente == -1) {
            cont++;
        }
    }
    return cont;
}

void mostrarClientesYNums() {
    if (cantidadClientes == 0) {
        cout << "\nNo hay clientes registrados todavia.\n";
        return;
    }

    cout << "\n--- LISTADO DE CLIENTES Y SUS NUMEROS ---\n";
    for (int i = 0; i < cantidadClientes; i++) {
        cout << "[" << clientes[i].id << "] " << clientes[i].nombre << " | IG: " << clientes[i].instagram << "\n";
        cout << "    Numeros: ";
        bool tieneNumeros = false;
        for (int j = 0; j < 200; j++) {
            if (rifas[j].idCliente == clientes[i].id) {
                // CORRECCIÓN VITAL: Sin el + 1
                cout << rifas[j].numero << " ";
                tieneNumeros = true;
            }
        }
        if (!tieneNumeros) cout << "Ninguno";
        cout << "\n------------------------------------------\n";
    }
}

void mostrarDisponibles() {
    cout << "\n--- NUMEROS DISPONIBLES ---\n";
    int cont = 0;
    for (int i = 0; i < 200; i++) {
        if (rifas[i].idCliente == -1) {
            cout << rifas[i].numero << "\t";
            cont++;
            if (cont % 10 == 0) cout << "\n";
        }
    }
    if (cont == 0) cout << "¡No quedan numeros disponibles!";
    cout << "\nTotal disponibles: " << cont << "\n";
}

void eliminarCliente() {
    if (cantidadClientes == 0) {
        cout << "\nNo hay clientes registrados para eliminar.\n";
        return;
    }

    int idEliminar;
    cout << "\nIngrese el indice del cliente a eliminar (0 a " << cantidadClientes - 1 << "): ";
    cin >> idEliminar;

    if (idEliminar < 0 || idEliminar >= cantidadClientes) {
        cout << "Indice invalido.\n";
        return;
    }

    int numerosLiberados = 0;
    for (int i = 0; i < 200; i++) {
        if (rifas[i].idCliente == idEliminar) {
            rifas[i].idCliente = -1; 
            numerosLiberados++;
        } else if (rifas[i].idCliente > idEliminar) {
            rifas[i].idCliente--; 
        }
    }

    for (int i = idEliminar; i < cantidadClientes - 1; i++) {
        clientes[i] = clientes[i + 1];
        clientes[i].id = i; 
    }

    cantidadClientes--;
    guardarDatos();

    cout << "\nCliente eliminado con exito. Se liberaron " << numerosLiberados << " numero(s).\n";
    cout << "Faltan por vender: " << contarFaltantes() << " numeros.\n";
}

int main() {
    cargarDatos();
    int opcion = 0;
    
    unsigned int semilla = gestionarSemilla();
    srand(semilla);

    while (opcion != 6) {
        cout << "\n--- MENU SORTEO ---\n";
        cout << "1. Registrar numero comprado\n";
        cout << "2. Ver clientes y sus numeros\n";
        cout << "3. Ver numeros disponibles\n";
        cout << "4. Eliminar un cliente\n";
        cout << "5. SORTEAR\n";
        cout << "6. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            int nro;
            cout << "Ingrese el numero de rifa (1-200): ";
            cin >> nro;

            if (nro < 1 || nro > 200 || rifas[nro - 1].idCliente != -1) {
                cout << "Numero no disponible o invalido.\n";
            } else {
                int tipo;
                cout << "1. Nuevo cliente\n2. Cliente existente\nSeleccion: ";
                cin >> tipo;

                if (tipo == 1) {
                    clientes[cantidadClientes].id = cantidadClientes;
                    cout << "Nombre y Apellido: ";
                    cin.ignore();
                    cin.getline(clientes[cantidadClientes].nombre, 50);
                    cout << "Telefono: ";
                    cin.getline(clientes[cantidadClientes].telefono, 20);
                    cout << "Instagram: ";
                    cin.getline(clientes[cantidadClientes].instagram, 30);

                    rifas[nro - 1].idCliente = cantidadClientes;
                    cout << "Registrado con exito. Indice de cliente: " << cantidadClientes << "\n";
                    cantidadClientes++;
                } else {
                    int idBuscado;
                    cout << "Ingrese el indice del cliente (0 a " << cantidadClientes - 1 << "): ";
                    cin >> idBuscado;

                    if (idBuscado >= 0 && idBuscado < cantidadClientes) {
                        rifas[nro - 1].idCliente = idBuscado;
                        cout << "Numero " << nro << " asignado a " << clientes[idBuscado].nombre << "\n";
                    } else {
                        cout << "Indice inexistente.\n";
                    }
                }
                guardarDatos();
                cout << "Faltan por vender: " << contarFaltantes() << " numeros.\n";
            }
        } 
        else if (opcion == 2) mostrarClientesYNums();
        else if (opcion == 3) mostrarDisponibles();
        else if (opcion == 4) eliminarCliente();
        else if (opcion == 5) {
            int ocupados[200], count = 0;
            for (int i = 0; i < 200; i++) {
                if (rifas[i].idCliente != -1) ocupados[count++] = i;
            }

            if (count == 0) cout << "No hay numeros vendidos.\n";
            else {
                int indiceGanador = ocupados[rand() % count];
                Cliente c = clientes[rifas[indiceGanador].idCliente];
                
                cout << "\n================================\n";
                cout << "EL GANADOR ES EL NUMERO " << rifas[indiceGanador].numero << "\n";
                cout << "Ganador: " << c.nombre << "\n";
                cout << "================================\n";
            }
        }
    }
    return 0;
}