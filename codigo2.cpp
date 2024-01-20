
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char nombre[100];
    int cantidad;
    float precio;
} Producto;

typedef struct {
    char cedula[11];
    char nombre[100];
} Cliente;

typedef struct {
    char fecha[20];
    char cedula[11];
    char nombre[100];
    float valorPagado;
    int cantidadProductos;
} Factura;

Producto inventario[100];
int numProductos = 0;

Cliente clientes[100];
int numClientes = 0;

Factura facturas[100];
int numFacturas = 0;

int esCedulaValida(char* cedula) {
    int longitud = strlen(cedula);
    for (int i = 0; i < longitud; i++) {
        if (!isdigit(cedula[i])) {
            return 0; 
        }
    }
    return longitud == 10;
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
int cedulaYaRegistrada(char* cedula) {
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cedula, cedula) == 0) {
            return 1; 
        }
    }
    return 0; 
}
void ingresarProducto() { Producto producto;
    

    limpiarBuffer();
    
    printf("Ingrese el nombre del producto: ");
    fgets(producto.nombre, 100, stdin);
    producto.nombre[strcspn(producto.nombre, "\n")] = 0; 
    
    printf("Ingrese la cantidad: ");
    scanf("%d", &producto.cantidad);
    
    printf("Ingrese el precio: ");
    scanf("%f", &producto.precio);
    
    
    limpiarBuffer();
    
    inventario[numProductos] = producto;
    numProductos++;
    
    printf("Producto ingresado correctamente.\n");
}

void modificarProducto() {
    int i;
    char nombre[100];
    printf("Ingrese el nombre del producto a modificar: ");
    limpiarBuffer();
    fgets(nombre, 100, stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    for (i = 0; i < numProductos; i++) {
        if (strcmp(inventario[i].nombre, nombre) == 0) {
            Producto producto;
            printf("Ingrese el nuevo nombre del producto: ");
            fgets(producto.nombre, 100, stdin);
            producto.nombre[strcspn(producto.nombre, "\n")] = 0;
            printf("Ingrese la nueva cantidad: ");
            scanf("%d", &producto.cantidad);
            printf("Ingrese el nuevo precio: ");
            scanf("%f", &producto.precio);
            limpiarBuffer();

            inventario[i] = producto;

            printf("Producto modificado correctamente.\n");
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

void eliminarProducto() {
    int i;
    char nombre[100];
    printf("Ingrese el nombre del producto a eliminar: ");
    limpiarBuffer();
    fgets(nombre, 100, stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    for (i = 0; i < numProductos; i++) {
        if (strcmp(inventario[i].nombre, nombre) == 0) {
            for (int j = i; j < numProductos - 1; j++) {
                inventario[j] = inventario[j + 1];
            }

            numProductos--;
            printf("Producto eliminado correctamente.\n");
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

void listarProductos() {
    printf("Lista de productos:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("Nombre: %s\n", inventario[i].nombre);
        printf("Cantidad: %d\n", inventario[i].cantidad);
        printf("Precio: %.2f\n", inventario[i].precio);
        printf("\n");
    }
}

void ingresarCliente() {
    Cliente cliente;
    do {
        printf("Ingrese la cedula del cliente (10 dígitos): ");
        scanf("%s", cliente.cedula);
        if (!esCedulaValida(cliente.cedula)) {
            printf("Cedula no valida. Ingrese nuevamente: ");
        } else if (cedulaYaRegistrada(cliente.cedula)) {
            printf("La cedula ya está registrada. Ingrese una diferente: ");
        }
    } while (!esCedulaValida(cliente.cedula) || cedulaYaRegistrada(cliente.cedula));
    limpiarBuffer();
    printf("Ingrese el nombre del cliente: ");
    fgets(cliente.nombre, 100, stdin);
    cliente.nombre[strcspn(cliente.nombre, "\n")] = 0;

    clientes[numClientes] = cliente;
    numClientes++;

    printf("Cliente ingresado correctamente.\n");
}


void modificarCliente() {
    int i;
    char cedula[11];
    printf("Ingrese la cedula del cliente a modificar: ");
    scanf("%s", cedula);
    limpiarBuffer();

    
    for (i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cedula, cedula) == 0) {
            Cliente cliente;
            printf("Ingrese el nuevo nombre del cliente: ");
            fgets(cliente.nombre, 100, stdin);
            cliente.nombre[strcspn(cliente.nombre, "\n")] = 0;

            printf("Ingrese la nueva cedula del cliente (10 dígitos): ");
            char nuevaCedula[11];
            scanf("%s", nuevaCedula);
            limpiarBuffer();

            
            if (esCedulaValida(nuevaCedula) && (!cedulaYaRegistrada(nuevaCedula) || strcmp(cedula, nuevaCedula) == 0)) {
                strcpy(clientes[i].cedula, nuevaCedula);
                printf("Cliente modificado correctamente.\n");
            } else {
                printf("La cedula ya está registrada o no es válida. No se realizaron cambios en la cédula.\n");
            }
            return;
        }
    }
    printf("Cliente no encontrado.\n");
}
void listarClientes() {
    printf("Lista de clientes:\n");
    for (int i = 0; i < numClientes; i++) {
        printf("Cedula: %s\n", clientes[i].cedula);
        printf("Nombre: %s\n", clientes[i].nombre);
        printf("\n");
    }
}

void facturar() {
    Factura factura;
    printf("Ingrese la fecha de la factura: ");
    scanf("%s", factura.fecha);
    do {
        printf("Ingrese la cedula del cliente (10 dígitos): ");
        scanf("%s", factura.cedula);
        if (!esCedulaValida(factura.cedula)) {
            printf("Cedula no válida. Intente de nuevo.\n");
        }
    } while (!esCedulaValida(factura.cedula));
    printf("Ingrese el nombre del cliente: ");
    scanf("%s", factura.nombre);
    printf("Ingrese el valor pagado: ");
    scanf("%f", &factura.valorPagado);
    printf("Ingrese la cantidad de productos comprados: ");
    scanf("%d", &factura.cantidadProductos);

    facturas[numFacturas] = factura;
    numFacturas++;

    printf("Factura generada correctamente.\n");
}
void buscarFactura() {
    char cedula[11];
    printf("Ingrese la cedula del cliente para buscar la factura: ");
    scanf("%s", cedula);

    for (int i = 0; i < numFacturas; i++) {
        if (strcmp(facturas[i].cedula, cedula) == 0) {
            printf("Fecha: %s\n", facturas[i].fecha);
            printf("Cedula: %s\n", facturas[i].cedula);
            printf("Nombre: %s\n", facturas[i].nombre);
            printf("Valor pagado: %.2f\n", facturas[i].valorPagado);
            printf("Cantidad de productos comprados: %d\n", facturas[i].cantidadProductos);
            printf("\n");
            return;
        }
    }

    printf("Factura no encontrada.\n");
}

void listarFacturas() {
    printf("Lista de facturas:\n");
    for (int i = 0; i < numFacturas; i++) {
        printf("Fecha: %s\n", facturas[i].fecha);
        printf("Cedula: %s\n", facturas[i].cedula);
        printf("Nombre: %s\n", facturas[i].nombre);
        printf("Valor pagado: %.2f\n", facturas[i].valorPagado);
        printf("Cantidad de productos comprados: %d\n", facturas[i].cantidadProductos);
        printf("\n");
    }
}

void consultarProducto() {
    char nombre[100];
    printf("Ingrese el nombre del producto a consultar: ");
    scanf("%s", nombre);

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(inventario[i].nombre, nombre) == 0) {
            printf("Nombre: %s\n", inventario[i].nombre);
            printf("Cantidad: %d\n", inventario[i].cantidad);
            printf("Precio: %.2f\n", inventario[i].precio);
            printf("\n");
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

void consultarCliente() {
    char cedula[11];
    printf("Ingrese la cedula del cliente a consultar: ");
    scanf("%s", cedula);

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cedula, cedula) == 0) {
            printf("Cedula: %s\n", clientes[i].cedula);
            printf("Nombre: %s\n", clientes[i].nombre);
            printf("\n");
            return;
        }
    }

    printf("Cliente no encontrado.\n");
}

int main() {
    int opcion;

    do {
        printf("=====TIENDA MINORISTA DE VIVERES LA CANASTA DEL BARRIO=====\n");
        printf("1. Ingresar Producto\n");
        printf("2. Modificar Producto\n");
        printf("3. Eliminar Producto\n");
        printf("4. Consultar Producto\n");
        printf("5. Ver Productos\n");
        printf("6. Ingresar Cliente\n");
        printf("7. Modificar Cliente\n");
        printf("8. Consultar Cliente\n");
        printf("9. Ver listado de clientes\n");
        printf("10. Facturar\n");
        printf("11. Buscar Factura\n");
        printf("12. Ver listado de facturas\n");
        printf("0. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: ingresarProducto(); break;
            case 2: modificarProducto(); break;
            case 3: eliminarProducto(); break;
            case 4: consultarProducto(); break;
            case 5: listarProductos(); break;
            case 6: ingresarCliente(); break;
            case 7: modificarCliente(); break;
            case 8: consultarCliente(); break;
            case 9: listarClientes(); break;
            case 10: facturar(); break;
            case 11: buscarFactura(); break;
            case 12: listarFacturas(); break;
            case 0: printf("Saliendo del programa...\n"); break;
            default: printf("Opción inválida.\n"); break;
        }
    } while (opcion != 0);

    return 0;
}
            