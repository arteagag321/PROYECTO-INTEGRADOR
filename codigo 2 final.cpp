#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_PRODUCTOS 100
#define MAX_CLIENTES 100
#define MAX_FACTURAS 100
#define MAX_NOMBRE 100
#define MAX_CEDULA 11
#define MAX_FECHA 20

#define MAX_PRODUCTOS 100
#define MAX_CLIENTES 100
#define MAX_FACTURAS 100
#define MAX_NOMBRE 100
#define MAX_CEDULA 11
#define MAX_FECHA 20

// Variables para productos
char nombresProductos[MAX_PRODUCTOS][MAX_NOMBRE];
int cantidadesProductos[MAX_PRODUCTOS];
float preciosProductos[MAX_PRODUCTOS];
char categoriasProductos[MAX_PRODUCTOS][MAX_NOMBRE];
int numProductos = 0;

// Variables para clientes
char cedulasClientes[MAX_CLIENTES][MAX_CEDULA];
char nombresClientes[MAX_CLIENTES][MAX_NOMBRE];
int numClientes = 0;

// Variables para facturas
char fechasFacturas[MAX_FACTURAS][MAX_FECHA];
char cedulasFacturas[MAX_FACTURAS][MAX_CEDULA];
char nombresFacturas[MAX_FACTURAS][MAX_NOMBRE];
float valoresPagadosFacturas[MAX_FACTURAS];
int cantidadesProductosFacturas[MAX_FACTURAS];
int numFacturas = 0;

int esCedulaValida(char *cedula) {
    int longitud = strlen(cedula);
    if (longitud != 10) {
        return 0;
    }

    for (int i = 0; i < longitud; i++) {
        if (!isdigit(cedula[i])) {
            return 0;
        }
    }

    int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');
    if (provincia < 1 || provincia > 24) {
        return 0;
    }

    int tercerDigito = cedula[2] - '0';
    if (tercerDigito > 5) {
        return 0;
    }

    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) {
            digito = digito * 2;
            if (digito > 9) {
                digito = digito - 9;
            }
        }
        suma = suma + digito;
    }

    int digitoVerificador = (10 - suma % 10) % 10;
    if (digitoVerificador != (cedula[9] - '0')) {
        return 0;
    }

    return 1;
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int cedulaYaRegistrada(char *cedula) {
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(cedulasClientes[i], cedula) == 0) {
            return 1;
        }
    }
    return 0;
}
void mostrarCedulasClientes() {
    printf("Cédulas de clientes registradas:\n");
    for (int i = 0; i < numClientes; i++) {
        printf("%d. %s\n", i + 1, cedulasClientes[i]);
    }
}

void mostrarProductosDisponibles() {
    printf("Productos disponibles:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("%d. %s (%s) - Cantidad disponible: %d - Precio: %.2f\n",
               i + 1, nombresProductos[i], categoriasProductos[i],
               cantidadesProductos[i], preciosProductos[i]);
    }
}

void ingresarProducto() {
    char nombre[MAX_NOMBRE];
    int cantidad;
    float precio;
    char categoria[MAX_NOMBRE];

    limpiarBuffer();

    printf("¿Cuántos productos desea ingresar? ");
    int cantidadProductos;
    scanf("%d", &cantidadProductos);
    limpiarBuffer();

    for (int i = 0; i < cantidadProductos; i++) {
        printf("Ingrese el nombre del producto #%d: ", i + 1);
        fgets(nombre, MAX_NOMBRE, stdin);
        nombre[strcspn(nombre, "\n")] = 0;

        // Verificar si el producto ya existe
        int productoExistente = 0;
        for (int j = 0; j < numProductos; j++) {
            if (strcmp(nombresProductos[j], nombre) == 0) {
                productoExistente = 1;
                printf("El producto ya existe en la lista. No se ha agregado.\n");
                break;
            }
        }

        if (!productoExistente) {
            printf("Ingrese la cantidad: ");
            scanf("%d", &cantidad);

            printf("Ingrese el precio: ");
            scanf("%f", &precio);

            limpiarBuffer();

            printf("Ingrese la categoría del producto #%d: ", i + 1);
            fgets(categoria, MAX_NOMBRE, stdin);
            categoria[strcspn(categoria, "\n")] = 0;

            strcpy(nombresProductos[numProductos], nombre);
            cantidadesProductos[numProductos] = cantidad;
            preciosProductos[numProductos] = precio;
            strcpy(categoriasProductos[numProductos], categoria);

            numProductos++;

            printf("Producto ingresado correctamente.\n");
        }
    }
}

void listarCategorias() {
    printf("Categorías disponibles:\n");
    for (int i = 0; i < numProductos; i++) {
        int categoriaRepetida = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(categoriasProductos[i], categoriasProductos[j]) == 0) {
                categoriaRepetida = 1;
                break;
            }
        }
        if (!categoriaRepetida) {
            printf("%s\n", categoriasProductos[i]);
        }
    }
}

void modificarProducto() {
    int i;
    char nombre[MAX_NOMBRE];
    printf("Ingrese el nombre del producto a modificar: ");
    limpiarBuffer();
    fgets(nombre, MAX_NOMBRE, stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    for (i = 0; i < numProductos; i++) {
        if (strcmp(nombresProductos[i], nombre) == 0) {
            printf("Ingrese el nuevo nombre del producto: ");
            fgets(nombresProductos[i], MAX_NOMBRE, stdin);
            nombresProductos[i][strcspn(nombresProductos[i], "\n")] = 0;

            printf("Ingrese la nueva cantidad: ");
            scanf("%d", &cantidadesProductos[i]);

            printf("Ingrese el nuevo precio: ");
            scanf("%f", &preciosProductos[i]);
            limpiarBuffer();

            printf("Ingrese la nueva categoría: "); // Nueva categoría
            fgets(categoriasProductos[i], MAX_NOMBRE, stdin);
            categoriasProductos[i][strcspn(categoriasProductos[i], "\n")] = 0;

            printf("Producto modificado correctamente.\n");
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

void eliminarProducto() {
    int i;
    char nombre[MAX_NOMBRE];
    printf("Ingrese el nombre del producto a eliminar: ");
    limpiarBuffer();
    fgets(nombre, MAX_NOMBRE, stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    for (i = 0; i < numProductos; i++) {
        if (strcmp(nombresProductos[i], nombre) == 0) {
            for (int j = i; j < numProductos - 1; j++) {
                strcpy(nombresProductos[j], nombresProductos[j + 1]);
                cantidadesProductos[j] = cantidadesProductos[j + 1];
                preciosProductos[j] = preciosProductos[j + 1];
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
        printf("Nombre: %s\n", nombresProductos[i]);
        printf("Cantidad: %d\n", cantidadesProductos[i]);
        printf("Precio: %.2f\n", preciosProductos[i]);
       printf("Categoría: %s\n", categoriasProductos[i]);
              printf("\n");
          }
      }

      void ingresarCliente() {
          char cedula[MAX_CEDULA];
          char nombre[MAX_NOMBRE];

          do {
              printf("Ingrese la cedula del cliente (10 dígitos): ");
              scanf("%s", cedula);
              if (!esCedulaValida(cedula)) {
                  printf("Cedula no válida. Ingrese nuevamente.\n");
              } else if (cedulaYaRegistrada(cedula)) {
                  printf("La cedula ya está registrada. Ingrese una diferente.\n");
              }
          } while (!esCedulaValida(cedula) || cedulaYaRegistrada(cedula));
          limpiarBuffer();

          printf("Ingrese el nombre del cliente: ");
          fgets(nombre, MAX_NOMBRE, stdin);
          nombre[strcspn(nombre, "\n")] = 0;

          strcpy(cedulasClientes[numClientes], cedula);
          strcpy(nombresClientes[numClientes], nombre);

          numClientes++;

          printf("Cliente ingresado correctamente.\n");
      }

     void modificarCliente() {
         char cedula[MAX_CEDULA];
         printf("Ingrese la cedula del cliente a modificar: ");
         scanf("%s", cedula);
         limpiarBuffer();

         for (int i = 0; i < numClientes; i++) {
             if (strcmp(cedulasClientes[i], cedula) == 0) {
                 printf("Ingrese el nuevo nombre del cliente: ");
                 fgets(nombresClientes[i], MAX_NOMBRE, stdin);
                 nombresClientes[i][strcspn(nombresClientes[i], "\n")] = 0;
                 printf("Cliente modificado correctamente.\n");
                 return;
             }
         }
         printf("Cliente no encontrado.\n");
     }

      void listarClientes() {
          printf("Lista de clientes:\n");
          for (int i = 0; i < numClientes; i++) {
              printf("Cedula: %s\n", cedulasClientes[i]);
              printf("Nombre: %s\n", nombresClientes[i]);
              printf("\n");
          }
      }

     void facturar() {
         char fecha[MAX_FECHA];
         char cedula[MAX_CEDULA];
         char nombre[MAX_NOMBRE];
         float valorTotal = 0.0;
         int cantidadProductos = 0;

         // Obtener la fecha actual
         time_t t;
         struct tm *tm_info;
         time(&t);
         tm_info = localtime(&t);
         strftime(fecha, sizeof(fecha), "%Y-%m-%d %H:%M:%S", tm_info);

         // Mostrar cédulas de clientes registradas
         mostrarCedulasClientes();
         int seleccionCliente;
         do {
             printf("Seleccione el número de cédula del cliente: ");
             scanf("%d", &seleccionCliente);
             if (seleccionCliente < 1 || seleccionCliente > numClientes) {
                 printf("Selección inválida. Intente de nuevo.\n");
             }
         } while (seleccionCliente < 1 || seleccionCliente > numClientes);

         strcpy(cedula, cedulasClientes[seleccionCliente - 1]);
         strcpy(nombre, nombresClientes[seleccionCliente - 1]);

         printf("Cliente seleccionado: %s - %s\n", cedula, nombre);

         // Variables para la compra
         int carrito[MAX_PRODUCTOS];
         int cantidadCarrito[MAX_PRODUCTOS];
         int numProductosCarrito = 0;

         while (1) {
             // Mostrar productos disponibles
             mostrarProductosDisponibles();
             printf("Ingrese el número del producto a comprar (X para finalizar): ");
             int seleccionProducto;
             char opcionCompra[2];
             scanf("%s", opcionCompra);
             if (opcionCompra[0] == 'X' || opcionCompra[0] == 'x') {
                 break;
             }
             seleccionProducto = atoi(opcionCompra);

             if (seleccionProducto < 1 || seleccionProducto > numProductos) {
                 printf("Selección inválida. Intente de nuevo.\n");
                 continue;
             }

             printf("Ingrese la cantidad deseada: ");
             int cantidadDeseada;
             scanf("%d", &cantidadDeseada);

             if (cantidadDeseada <= 0 || cantidadDeseada > cantidadesProductos[seleccionProducto - 1]) {
                 printf("Cantidad inválida o insuficiente stock. Stock actual: %d\n",
                     cantidadesProductos[seleccionProducto - 1]);
                 continue;
             }

             // Se registra la compra en el carrito
             carrito[numProductosCarrito] = seleccionProducto;
             cantidadCarrito[numProductosCarrito] = cantidadDeseada;
             numProductosCarrito++;

             // Se actualiza el stock del producto
             cantidadesProductos[seleccionProducto - 1] -= cantidadDeseada;

             valorTotal += cantidadDeseada * preciosProductos[seleccionProducto - 1];
             cantidadProductos += cantidadDeseada;

             printf("Producto añadido al carrito.\n");
         }

         // Mostrar resumen del carrito
         printf("\nResumen del carrito de compras:\n");
         for (int i = 0; i < numProductosCarrito; i++) {
             int productoIndex = carrito[i] - 1;
             printf("%s - Cantidad: %d - Precio unitario: %.2f - Total: %.2f\n",
                 nombresProductos[productoIndex], cantidadCarrito[i],
                 preciosProductos[productoIndex],
                 cantidadCarrito[i] * preciosProductos[productoIndex]);
         }
         printf("Total a pagar: %.2f\n", valorTotal);

         // Registro de la factura
         strcpy(fechasFacturas[numFacturas], fecha);
         strcpy(cedulasFacturas[numFacturas], cedula);
         strcpy(nombresFacturas[numFacturas], nombre);
         valoresPagadosFacturas[numFacturas] = valorTotal;
         cantidadesProductosFacturas[numFacturas] = cantidadProductos;
         numFacturas++;

         printf("\nFactura generada correctamente.\n");
     }
      void buscarFactura() {
          char cedula[MAX_CEDULA];
          printf("Ingrese la cedula del cliente para buscar la factura: ");
          scanf("%s", cedula);

          for (int i = 0; i < numFacturas; i++) {
              if (strcmp(cedulasFacturas[i], cedula) == 0) {
                  printf("Fecha: %s\n", fechasFacturas[i]);
                  printf("Cedula: %s\n", cedulasFacturas[i]);
                  printf("Nombre: %s\n", nombresFacturas[i]);
                  printf("Valor pagado: %.2f\n", valoresPagadosFacturas[i]);
                  printf("Cantidad de productos comprados: %d\n", cantidadesProductosFacturas[i]);
                  printf("\n");
                  return;
              }
          }
          printf("Factura no encontrada.\n");
      }

      void listarFacturas() {
          printf("Lista de facturas:\n");
          for (int i = 0; i < numFacturas; i++) {
              printf("Fecha: %s\n", fechasFacturas[i]);
              printf("Cedula: %s\n", cedulasFacturas[i]);
              printf("Nombre: %s\n", nombresFacturas[i]);
              printf("Valor pagado: %.2f\n", valoresPagadosFacturas[i]);
              printf("Cantidad de productos comprados: %d\n", cantidadesProductosFacturas[i]);
              printf("\n");
          }
      }

      void consultarProducto() {
          char nombre[MAX_NOMBRE];
          printf("Ingrese el nombre del producto a consultar: ");
          limpiarBuffer();
          fgets(nombre, MAX_NOMBRE, stdin);
          nombre[strcspn(nombre, "\n")] = 0;

          for (int i = 0; i < numProductos; i++) {
              if (strcmp(nombresProductos[i], nombre) == 0) {
                  printf("Nombre: %s\n", nombresProductos[i]);
                  printf("Cantidad: %d\n", cantidadesProductos[i]);
                  printf("Precio: %.2f\n", preciosProductos[i]);
                  printf("Categoría: %s\n", categoriasProductos[i]);
                  printf("\n");
                  return;
              }
          }
          printf("Producto no encontrado.\n");
      }

      void consultarCliente() {
          char cedula[MAX_CEDULA];
          printf("Ingrese la cedula del cliente a consultar: ");
          scanf("%s", cedula);

          for (int i = 0; i < numClientes; i++) {
              if (strcmp(cedulasClientes[i], cedula) == 0) {
                  printf("Cedula: %s\n", cedulasClientes[i]);
                  printf("Nombre: %s\n", nombresClientes[i]);
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
                        case 1:
                            ingresarProducto();
                            break;
                        case 2:
                            modificarProducto();
                            break;
                        case 3:
                            eliminarProducto();
                            break;
                        case 4:
                            consultarProducto();
                            break;
                        case 5:
                            listarProductos();
                            break;
                        case 6:
                            ingresarCliente();
                            break;
                        case 7:
                            modificarCliente();
                            break;
                        case 8:
                            consultarCliente();
                            break;
                        case 9:
                            listarClientes();
                            break;
                        case 10:
                            facturar();
                            break;
                        case 11:
                            buscarFactura();
                            break;
                        case 12:
                            listarFacturas();
                            break;
                        case 0:
                            printf("Saliendo del programa...\n");
                            break;
                        default:
                            printf("Opción inválida.\n");
                            break;
                    }
                } while (opcion != 0);

                return 0;
            }