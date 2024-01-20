#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


void limpiarBuffer();
int leerEnteroPositivo(char*);
int leerEntero(char*);
int leerEnteroEntre(char*, int, int);
float leerFlotantePositivo(char*);
float leerFlotante(char*);
float leerFlotanteEntre(char*, float, float);
char leerCaracter(char*);


typedef struct {
    char cedula[11];
    char nombre[100];
} Cliente;

typedef struct {
    char nombre[100];
    int cantidad;
    float precio;
    char categoria[100];
} Producto;

typedef struct {
    char fecha[20];
    char cedula[11];
    char nombre[100];
    float valorPagado;
    int cantidadProductos;
} Factura;

int esCedulaValida(char* cedula) {
    int longitud = strlen(cedula);
    for (int i = 0; i < longitud; i++) {
        if (!isdigit(cedula[i])) {
            return 0; 
        }
    }
    return longitud == 10;
}
int esCedulaRegistrada(Cliente clientes[], int numClientes, char* cedula) {
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cedula, cedula) == 0) {
            return 1; 
        }
    }
    return 0; 
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int leerEnteroPositivo(char* mensaje) {
    int numero;
    do {
        printf("%s", mensaje);
        scanf("%d", &numero);
    } while (numero <= 0);
    return numero;
}

int leerEntero(char* mensaje) {
    int numero;
    printf("%s", mensaje);
    scanf("%d", &numero);
    return numero;
}

int leerEnteroEntre(char* mensaje, int min, int max) {
    int numero;
    do {
        printf("%s", mensaje);
        scanf("%d", &numero);
    } while (numero < min || numero > max);
    return numero;
}

float leerFlotantePositivo(char* mensaje) {
    float numero;
    do {
        printf("%s", mensaje);
        scanf("%f", &numero);
    } while (numero <= 0);
    return numero;
}

float leerFlotante(char* mensaje) {
    float numero;
    printf("%s", mensaje);
    scanf("%f", &numero);
    return numero;
}

float leerFlotanteEntre(char* mensaje, float min, float max) {
    float numero;
    do {
        printf("%s", mensaje);
        scanf("%f", &numero);
    } while (numero < min || numero > max);
    return numero;
}

char leerCaracter(char* mensaje) {
    char caracter;
    printf("%s", mensaje);
    scanf(" %c", &caracter);
    return caracter;
}


int main() {
    int opcion;
    Cliente clientes[100];
    int numClientes = 0;
    Producto productos[100];
    int numProductos = 0;
    Factura facturas[100];
    int numFacturas = 0;
    do {
         printf("\ntienda minorista de viveres LA CANASTA DEL BARRIO \n");
        printf("========== MENU ==========\n");
        printf("1. Ingresar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Listar productos\n");
        printf("5. Ingresar cliente\n");
        printf("6. Modificar cliente\n");
        printf("7. Consultar cliente\n");
        printf("8. Ver listado de clientes\n");
        printf("9. Facturar\n");
        printf("10. Buscar factura\n");
        printf("11. Ver listado de facturas\n");
        printf("12. Salir\n");
        opcion = leerEnteroEntre("Seleccione una opción: ", 1, 12);

        switch (opcion) {
            case 1:   
    printf("========== INGRESAR PRODUCTO ==========\n");
    char nombreProducto[100];

    limpiarBuffer();
    printf("Ingrese el nombre del producto o 'x' para cancelar: ");
    fgets(nombreProducto, 100, stdin);
    if (strcmp(nombreProducto, "x\n") == 0) {
        break;
    }
    nombreProducto[strcspn(nombreProducto, "\n")] = 0;
    strcpy(productos[numProductos].nombre, nombreProducto);

    printf("Ingrese la cantidad o 'x' para cancelar: ");
    char cantidadStr[10];
    scanf("%s", cantidadStr);
    if (strcmp(cantidadStr, "x") == 0) {
        break;
    }
    productos[numProductos].cantidad = atoi(cantidadStr);

    printf("Ingrese el precio o 'x' para cancelar: ");
    char precioStr[10];
    scanf("%s", precioStr);
    if (strcmp(precioStr, "x") == 0) {
        break;
    }
    productos[numProductos].precio = atof(precioStr);

    limpiarBuffer();
    printf("Ingrese la categoría del producto o 'x' para cancelar: ");
    fgets(productos[numProductos].categoria, 100, stdin);
    if (strcmp(productos[numProductos].categoria, "x\n") == 0) {
        break;
    }
    productos[numProductos].categoria[strcspn(productos[numProductos].categoria, "\n")] = 0;

    numProductos++;
    printf("Producto ingresado correctamente.\n");
    break;
               case 2:
               printf("========== EDITAR PRODUCTO ==========\n");
               int indiceProducto;
               if (numProductos == 0) {
                   printf("No hay productos registrados.\n");
                   break;
               }
               for (int i = 0; i < numProductos; i++) {
                   printf("%d. %s\n", i + 1, productos[i].nombre);
               }
               printf("Si desea volver al menú principal, ingrese 'x'\n");
               printf("Seleccione el número del producto a editar: ");
               char opcionEditar[10];
               scanf("%s", opcionEditar);
               if (strcmp(opcionEditar, "x") == 0) {
                   break;
               }
               indiceProducto = atoi(opcionEditar) - 1;
               if (indiceProducto < 0 || indiceProducto >= numProductos) {
                   printf("Opción no válida.\n");
                   break;
               }
                 limpiarBuffer();
               printf("Ingrese el nuevo nombre del producto: ");
                fgets(productos[indiceProducto].nombre, 100, stdin);
                productos[indiceProducto].nombre[strcspn(productos[indiceProducto].nombre, "\n")] = 0;
               productos[indiceProducto].cantidad = leerEnteroPositivo("Ingrese la nueva cantidad: ");
               productos[indiceProducto].precio = leerFlotantePositivo("Ingrese el nuevo precio: ");
               break;

            case 3:
                printf("========== ELIMINAR PRODUCTO ==========\n");
                if (numProductos == 0) {
                    printf("No hay productos registrados.\n");
                    break;
                }
                for (int i = 0; i < numProductos; i++) {
                    printf("%d. %s\n", i + 1, productos[i].nombre);
                }
               printf("Si desea volver al menú principal, ingrese 'x'\n");
               printf("Seleccione el número del producto a eliminar: ");
               char opcionEliminar[10];
               scanf("%s", opcionEliminar);
               if (strcmp(opcionEliminar, "x") == 0) {
                   break;
                }
                for (int i = indiceProducto; i < numProductos - 1; i++) {
                    productos[i] = productos[i + 1];
                }
                numProductos--;
                printf("Producto eliminado exitosamente.\n");
                break;

            case 4:
                printf("========== LISTA DE PRODUCTOS ==========\n");
                if (numProductos == 0) {
                    printf("No hay productos registrados.\n");
                } else {
                    for (int i = 0; i < numProductos; i++) {
                        printf("Nombre: %s\n", productos[i].nombre);
                        printf("Cantidad: %d\n", productos[i].cantidad);
                        printf("Precio: %.2f\n", productos[i].precio);
                        printf("Categoría: %s\n", productos[i].categoria);
                        printf("--------------------\n");
                    }
                }
                break;

            case 5: 
    printf("========== INGRESAR CLIENTE ==========\n");
    char cedulaTemp[11];
    
    do {
        printf("Ingrese la cédula del cliente (10 dígitos) o 'x' para cancelar: ");
        scanf("%10s", cedulaTemp); 
        limpiarBuffer(); 
        if (strcmp(cedulaTemp, "x") == 0) {
            break;
        }
        if (!esCedulaValida(cedulaTemp)) {
            printf("Número de cédula no válido. Intente nuevamente.\n");
        } else if (esCedulaRegistrada(clientes, numClientes, cedulaTemp)) {
            printf("Cédula ya está registrada. Intente con otra.\n");
        }
    } while (!esCedulaValida(cedulaTemp) || esCedulaRegistrada(clientes, numClientes, cedulaTemp));

    if (strcmp(cedulaTemp, "x") == 0) {
        break; 
    }

    
    strcpy(clientes[numClientes].cedula, cedulaTemp);

    
    printf("Ingrese el nombre del cliente: ");
    fgets(clientes[numClientes].nombre, 100, stdin);
    clientes[numClientes].nombre[strcspn(clientes[numClientes].nombre, "\n")] = 0; // Eliminar el salto de línea

    numClientes++; 
    printf("Cliente ingresado correctamente.\n");
    break; 
            case 6:
            printf("========== MODIFICAR CLIENTE ==========\n");
            int indiceCliente;
            if (numClientes == 0) {
                printf("No hay clientes registrados.\n");
                break;
            }
            for (int i = 0; i < numClientes; i++) {
                printf("%d. Cédula: %s Nombre: %s\n", i + 1, clientes[i].cedula, clientes[i].nombre);
            }
            printf("Si desea volver al menú principal, ingrese 'x'\n");
            printf("Seleccione el número del cliente a modificar: ");
            char opcionModificar[10];
            scanf("%s", opcionModificar);
            if (strcmp(opcionModificar, "x") == 0) {
                break;
            }
            indiceCliente = atoi(opcionModificar) - 1;
            if (indiceCliente < 0 || indiceCliente >= numClientes) {
                printf("Opción no válida.\n");
                break;
            }
            do {
                printf("Ingrese la nueva cédula del cliente (10 dígitos): ");
                scanf("%s", clientes[indiceCliente].cedula);
                if (!esCedulaValida(clientes[indiceCliente].cedula)) {
        printf("Número de cédula no válido o de otro país. Intente nuevamente.\n");
                }
            } while (!esCedulaValida(clientes[indiceCliente].cedula));
           limpiarBuffer();
                printf("Ingrese el nuevo nombre del cliente: ");
                fgets(clientes[indiceCliente].nombre, 100, stdin);
                clientes[indiceCliente].nombre[strcspn(clientes[indiceCliente].nombre, "\n")] = 0;
            break;
            case 7:
               printf("========== CONSULTAR CLIENTE ==========\n");
               if (numClientes == 0) {
                   printf("No hay clientes registrados.\n");
                   break;
               }
               for (int i = 0; i < numClientes; i++) {
                   printf("%d. Cédula: %s\n   Nombre: %s\n", i + 1, clientes[i].cedula, clientes[i].nombre);
               }
               printf("Si desea volver al menú principal, ingrese 'x'\n");
               printf("Seleccione el número del cliente a consultar: ");
               char opcionConsultar[10];
               scanf("%s", opcionConsultar);
               if (strcmp(opcionConsultar, "x") == 0) {
                   break;
               }
               indiceCliente = atoi(opcionConsultar) - 1;
               if (indiceCliente < 0 || indiceCliente >= numClientes) {
                   printf("Opción no válida.\n");
                   break;
               }
               printf("Cédula: %s\n", clientes[indiceCliente].cedula);
               printf("Nombre: %s\n", clientes[indiceCliente].nombre);
               break;

            case 8:
                printf("========== LISTADO DE CLIENTES ==========\n");
                if (numClientes == 0) {
                    printf("No hay clientes registrados.\n");
                } else {
                    for (int i = 0; i < numClientes; i++) {
                        printf("Cédula: %s\n", clientes[i].cedula);
                        printf("Nombre: %s\n", clientes[i].nombre);
                        printf("--------------------\n");
                    }
                }
                break;

            case 9:
                printf("========== FACTURAR ==========\n");
                if (numClientes == 0 || numProductos == 0) {
                    printf("No hay clientes o productos registrados.\n");
                } else {
                    Factura factura;
                    printf("Ingrese la fecha de la factura: ");
                    scanf("%s", factura.fecha);
                    do {
                printf("Ingrese la cédula del cliente (10 dígitos) o 'x' para cancelar: ");
                scanf("%s", factura.cedula);
                if (strcmp(factura.cedula, "x") == 0) {
                    break;
                }
                if (!esCedulaValida(factura.cedula)) {
                    printf("Número de cédula no válido. Intente nuevamente.\n");
                }
            } while (!esCedulaValida(factura.cedula));
            if (strcmp(factura.cedula, "x") == 0) {
                break;
            }
                    printf("Ingrese el nombre del cliente: ");
                    scanf("%s", factura.nombre);
                    factura.valorPagado = leerFlotantePositivo("Ingrese el valor pagado: ");
                    factura.cantidadProductos = leerEnteroPositivo("Ingrese la cantidad de productos comprados: ");
                    facturas[numFacturas] = factura;
                    numFacturas++;
                    printf("Factura generada exitosamente.\n");
                }
                break;

            case 10:
                printf("========== BUSCAR FACTURA ==========\n");
                if (numFacturas == 0) {
                    printf("No hay facturas registradas.\n");
                } else {
                    char cedulaABuscar[11];
                    printf("Ingrese la cédula del cliente para buscar la factura: ");
                    scanf("%s", cedulaABuscar);
                    int encontrada = 0;
                    for (int i = 0; i < numFacturas; i++) {
                        if (strcmp(facturas[i].cedula, cedulaABuscar) == 0) {
                            printf("Fecha: %s\n", facturas[i].fecha);
                            printf("Cédula: %s\n", facturas[i].cedula);
                            printf("Nombre: %s\n", facturas[i].nombre);
                             printf("Valor Pagado: %.2f\n", facturas[i].valorPagado);
                                                        printf("Cantidad de productos comprados: %d\n", facturas[i].cantidadProductos);
                                                        printf("--------------------\n");
                                                        encontrada = 1;
                                                    }
                                                }
                                                if (!encontrada) {
                                                    printf("No se encontraron facturas para la cédula ingresada.\n");
                                                }
                                            }
                                            break;

                                        case 11:
                                            printf("========== LISTADO DE FACTURAS ==========\n");
                                            if (numFacturas == 0) {
                                                printf("No hay facturas registradas.\n");
                                            } else {
                                                for (int i = 0; i < numFacturas; i++) {
                                                    printf("Fecha: %s\n", facturas[i].fecha);
                                                    printf("Cédula: %s\n", facturas[i].cedula);
                                                    printf("Nombre: %s\n", facturas[i].nombre);
                                                    printf("Valor Pagado: %.2f\n", facturas[i].valorPagado);
                                                    printf("Cantidad de productos comprados: %d\n", facturas[i].cantidadProductos);
                                                    printf("--------------------\n");
                                                }
                                            }
                                            break;

                                        case 12:
                                            printf("Saliendo del programa...\n");
                                            break;

                                        default:
                                            printf("Opción no válida. Por favor, seleccione una opción válida.\n");
                                            break;
                                    }
                                } while (opcion != 12);

                                return 0;
                            }

