#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void limpiarBuffer();
int leerEnteroPositivo(char*);
int leerEntero(char*);
int leerEnteroEntre(char*, int, int);
float leerFlotantePositivo(char*);
float leerFlotante(char*);
float leerFlotanteEntre(char*, float, float);
char leerCaracter(char*);
void guardarProductoEnArchivo(char *nombre, int cantidad, float precio, char *categoria);
int numeroFactura = 1;

#define MAX_CLIENTES 100
#define MAX_PRODUCTOS 100
#define MAX_FACTURAS 100

#define CLIENTES_FILE "clientes.txt"
#define PRODUCTOS_FILE "productos.txt"
#define FACTURAS_FILE "facturas.txt"

char cedulas[MAX_CLIENTES][11];
char nombresClientes[MAX_CLIENTES][100];
char nombresProductos[MAX_PRODUCTOS][100];
int cantidades[MAX_PRODUCTOS];
float precios[MAX_PRODUCTOS];
char categorias[MAX_PRODUCTOS][100];
char fechas[MAX_FACTURAS][20];
float valoresPagados[MAX_FACTURAS];
int cantidadesProductos[MAX_FACTURAS];

int numClientes = 0;
int numProductos = 0;
int numFacturas = 0;


int esCedulaEcuatorianaValida(char* cedula) {
    int longitud = strlen(cedula);

    if (longitud != 10) {
        return 0; 
    }

    for (int i = 0; i < longitud; i++) {
        if (!isdigit(cedula[i])) {
            return 0; 
        }
    }

    int tercerDigito = cedula[2] - '0';

    if (tercerDigito < 0 || tercerDigito > 5) {
        return 0;
    }

    int coeficientes[] = {2, 1, 2, 1, 2, 1, 2, 1, 2};
    int suma = 0;

    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        int producto = digito * coeficientes[i];
        suma += (producto >= 10) ? (producto - 9) : producto;
    }

    int digitoVerificador = suma % 10 == 0 ? 0 : 10 - (suma % 10);
    int ultimoDigito = cedula[9] - '0';

    return digitoVerificador == ultimoDigito;
}

int esCedulaRegistrada(char* cedula) {
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(cedulas[i], cedula) == 0) {
            return 1;
        }
    }
    return 0;
}
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

int verificarProductoRepetido(char* nombreProducto) {
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(nombresProductos[i], nombreProducto) == 0) {
            return 1;
        }
    }
    return 0;
}

int ingresarProductos() {
    int numProductosIngresar = leerEnteroPositivo("Ingrese el número de productos a registrar: ");

    for (int i = 0; i < numProductosIngresar; i++) {
        char nombreProducto[100];
        int cantidad;
        float precio;
        char categoria[100]; 

        limpiarBuffer();
        printf("Ingrese el nombre del producto %d: ", i + 1);
        fgets(nombreProducto, 100, stdin);
        nombreProducto[strcspn(nombreProducto, "\n")] = 0;

        if (verificarProductoRepetido(nombreProducto)) {
            printf("Este producto ya está registrado. Ingrese uno nuevo.\n");
            i--;
            continue;
        }

        printf("Ingrese la cantidad: ");
        scanf("%d", &cantidad);
        printf("Ingrese el precio: ");
        scanf("%f", &precio);
        limpiarBuffer();

        printf("Ingrese la categoría del producto: "); 
        fgets(categoria, 100, stdin);
        categoria[strcspn(categoria, "\n")] = 0;

        guardarProductoEnArchivo(nombreProducto, cantidad, precio, categoria); 

        strcpy(nombresProductos[numProductos], nombreProducto);
        cantidades[numProductos] = cantidad;
        precios[numProductos] = precio;
        strcpy(categorias[numProductos], categoria); 

        numProductos++;
        printf("Producto ingresado correctamente.\n");
    }

    return numProductosIngresar;
}
void guardarFactura(int numeroFactura, char *cedulaCliente, char *nombreCliente, float totalCompra) {
    FILE *file = fopen(FACTURAS_FILE, "a"); 
    if (file == NULL) {
        perror("Error al abrir el archivo de facturas para guardar");
        return;
    }

    fprintf(file, "=== Factura ===\n");
    fprintf(file, "Número de Factura: %d\n", numeroFactura);
    fprintf(file, "ID del Cliente: %s\n", cedulaCliente);
    fprintf(file, "Nombre del Cliente: %s\n", nombreCliente);
    fprintf(file, "Detalles de Compra: %.2f\n\n", totalCompra); 
    fclose(file);
    printf("Factura registrada y guardada en %s.\n", FACTURAS_FILE);
}
void guardarCliente(char *cedula, char *nombreCliente) {
    FILE *file = fopen(CLIENTES_FILE, "a"); 
    if (file == NULL) {
        printf("No se pudo abrir el archivo de clientes para guardar.\n");
        return;
    }
    
    fprintf(file, "Nombre del cliente: %s Cedula: %s\n", nombreCliente, cedula);
    fclose(file); 
    printf("Cliente registrado y guardado en %s.\n", CLIENTES_FILE);
}
void guardarProductoEnArchivo(char *nombre, int cantidad, float precio, char *categoria) {
    FILE *archivo = fopen(PRODUCTOS_FILE, "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de productos.\n");
        return;
    }

    fprintf(archivo, "%s,%d,%.2f,%s\n", nombre, cantidad, precio, categoria);
    fclose(archivo);
    printf("Producto registrado y guardado en %s.\n", PRODUCTOS_FILE);
}

void inicializarArchivos() {
    FILE *file;

   
    file = fopen(PRODUCTOS_FILE, "r");
    if (file == NULL) {
        
        file = fopen(PRODUCTOS_FILE, "w");
        if (file != NULL) {
            fprintf(file, "Nombre,Cantidad,Precio,Categoría\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }


    file = fopen(CLIENTES_FILE, "r");
    if (file == NULL) {
        file = fopen(CLIENTES_FILE, "w");
        if (file != NULL) {
            fprintf(file, "Cédula,Nombre\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }

  
    file = fopen(FACTURAS_FILE, "r");
    if (file == NULL) {
        file = fopen(FACTURAS_FILE, "w");
        if (file != NULL) {
            fprintf(file, "Fecha,Valor Pagado,Cantidad Productos\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }
}
void leerProductos() {
    FILE *file = fopen(PRODUCTOS_FILE, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo de productos para lectura.\n");
        return;
    }

    fscanf(file, "%*[^\n]\n");

    numProductos = 0;

    while (fscanf(file, "%99[^,],%d,%f\n", nombresProductos[numProductos], &cantidades[numProductos], &precios[numProductos]) == 3) {
        numProductos++;
        if (numProductos >= MAX_PRODUCTOS) {
            break;
        }
    }
    fclose(file);
}

void leerClientes() {
    FILE *file = fopen(CLIENTES_FILE, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo de clientes para lectura.\n");
        return;
    }
  
    fscanf(file, "%*[^\n]\n");
    while (fscanf(file, "%10[^,],%99[^\n]\n", cedulas[numClientes], nombresClientes[numClientes]) == 2) {
        numClientes++;
        if (numClientes >= MAX_CLIENTES) {
            break;
        }
    }
    fclose(file);
}
void leerFacturas() {
    FILE *file = fopen(FACTURAS_FILE, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo de facturas para lectura.\n");
        return;
    }
  
    fscanf(file, "%*[^\n]\n");
    while (fscanf(file, "%19[^,],%f,%d\n", fechas[numFacturas], &valoresPagados[numFacturas], &cantidadesProductos[numFacturas]) == 3) {
        numFacturas++;
        if (numFacturas >= MAX_FACTURAS) {
            break;
        }
    }
    fclose(file);
}





int main() {
  char nombreProducto[100];
  int cantidad;
  float precio;
  char categoria[100];

  int numeroFactura;
  char cedulaCliente[11]; 
  char nombreCliente[100]; 
  float totalCompra;

  inicializarArchivos();
  leerProductos(); 
  leerClientes();
  leerFacturas();
    int opcion;

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
          int numProductosIngresar;
          printf("Ingrese el número de productos a registrar: ");
          scanf("%d", &numProductosIngresar);
          limpiarBuffer(); 

          for (int i = 0; i < numProductosIngresar; i++) {
              char nombreProducto[100];
              int cantidad;
              float precio;
              char categoria[100];

              printf("Ingrese el nombre del producto %d: ", i + 1);
              fgets(nombreProducto, 100, stdin);
              nombreProducto[strcspn(nombreProducto, "\n")] = 0; 

              if (verificarProductoRepetido(nombreProducto)) {
                  printf("Este producto ya está registrado. Ingrese uno nuevo.\n");
                  i--;
                  continue;
              }

              printf("Ingrese la cantidad: ");
              scanf("%d", &cantidad);
              printf("Ingrese el precio: ");
              scanf("%f", &precio);
              limpiarBuffer();

              printf("Ingrese la categoría del producto: ");
              fgets(categoria, 100, stdin);
              categoria[strcspn(categoria, "\n")] = 0; 

              guardarProductoEnArchivo(nombreProducto, cantidad, precio, categoria);

              strcpy(nombresProductos[numProductos], nombreProducto);
              cantidades[numProductos] = cantidad;
              precios[numProductos] = precio;
              strcpy(categorias[numProductos], categoria);

              numProductos++; 
              printf("Producto ingresado correctamente.\n");
          }
          break;
          case 2:
          printf("========== EDITAR PRODUCTO ==========\n");
          if (numProductos == 0) {
              printf("No hay productos registrados.\n");
              break;
          }

          
          limpiarBuffer();

          char nombreProducto[100];
          printf("Ingrese el nombre del producto a modificar: ");
          fgets(nombreProducto, 100, stdin);
          nombreProducto[strcspn(nombreProducto, "\n")] = 0; 

          int indiceProducto = -1;
          for (int i = 0; i < numProductos; i++) {
              if (strcmp(nombresProductos[i], nombreProducto) == 0) {
                  indiceProducto = i;
                  break;
              }
          }

          if (indiceProducto == -1) {
              printf("Producto no encontrado.\n");
              break;
          }

          printf("Modificando el producto: %s\n", nombresProductos[indiceProducto]);

          printf("Ingrese el nuevo nombre del producto: ");
          fgets(nombresProductos[indiceProducto], 100, stdin);
          nombresProductos[indiceProducto][strcspn(nombresProductos[indiceProducto], "\n")] = 0;

          char cantidadStr[10];
          printf("Ingrese la nueva cantidad: ");
          fgets(cantidadStr, 10, stdin);
          sscanf(cantidadStr, "%d", &cantidades[indiceProducto]);

          char precioStr[20];
          printf("Ingrese el nuevo precio: ");
          fgets(precioStr, 20, stdin);
          sscanf(precioStr, "%f", &precios[indiceProducto]);

          printf("Ingrese la nueva categoría del producto: ");
          fgets(categorias[indiceProducto], 100, stdin);
          categorias[indiceProducto][strcspn(categorias[indiceProducto], "\n")] = 0;

          printf("Producto modificado correctamente.\n");
          break;
           case 3:
           printf("========== ELIMINAR PRODUCTO ==========\n");
           if (numProductos == 0) {
               printf("No hay productos registrados para eliminar.\n");
               break;
           }

           
           limpiarBuffer();

           char nombreProductoEliminar[100];
           printf("Ingrese el nombre del producto a eliminar: ");
           fgets(nombreProductoEliminar, 100, stdin);
           nombreProductoEliminar[strcspn(nombreProductoEliminar, "\n")] = 0;

           int indiceProductoEliminar = -1; 
           for (int i = 0; i < numProductos; i++) {
               if (strcmp(nombresProductos[i], nombreProductoEliminar) == 0) {
                   indiceProductoEliminar = i;
                   break;
               }
           }

           if (indiceProductoEliminar == -1) {
               printf("Producto no encontrado.\n");
               break;
           }

          
           for (int i = indiceProductoEliminar; i < numProductos - 1; i++) {
               strcpy(nombresProductos[i], nombresProductos[i + 1]);
               cantidades[i] = cantidades[i + 1];
               precios[i] = precios[i + 1];
               strcpy(categorias[i], categorias[i + 1]);
           }
           numProductos--; 
           printf("Producto eliminado correctamente.\n");
           break;
            case 4:
                printf("========== LISTA DE PRODUCTOS ==========\n");
                if (numProductos == 0) {
                    printf("No hay productos registrados.\n");
                } else {
                    for (int i = 0; i < numProductos; i++) {
                        printf("Nombre: %s\n", nombresProductos[i]);
                        printf("Cantidad: %d\n", cantidades[i]);
                        printf("Precio: %.2f\n", precios[i]);
                        printf("Categoría: %s\n", categorias[i]);
                        printf("--------------------\n");
                    }
                }
                break;

           case 5:
           printf("========== INGRESAR CLIENTE ==========\n");
           int numClientesIngresar;
           do {
               printf("Ingrese el número de clientes a registrar o 'x' para cancelar: ");
               char numClientesStr[10];
               scanf("%s", numClientesStr);
               limpiarBuffer();

               if (strcmp(numClientesStr, "x") == 0 || strcmp(numClientesStr, "X") == 0) {
                   break;
               }

               numClientesIngresar = atoi(numClientesStr);

               if (numClientesIngresar < 0) {
                   printf("Número inválido. Intente de nuevo.\n");
                   continue;
               }

               for (int i = 0; i < numClientesIngresar; i++) {
                   char cedulaTemp[11];
                   do {
                       printf("Ingrese la cédula del cliente %d (10 dígitos): ", i + 1);
                       scanf("%10s", cedulaTemp);
                       limpiarBuffer();
                       if (!esCedulaEcuatorianaValida(cedulaTemp)) {
                           printf("Número de cédula no válida o de otro país. Intente nuevamente.\n");
                       } else if (esCedulaRegistrada(cedulaTemp)) {
                           printf("Cédula ya está registrada. Intente con otra.\n");
                       } else {
                           strcpy(cedulas[numClientes], cedulaTemp);

                           printf("Ingrese el nombre del cliente: ");
                           fgets(nombresClientes[numClientes], 100, stdin);
                           nombresClientes[numClientes][strcspn(nombresClientes[numClientes], "\n")] = 0;

                           numClientes++;
                           printf("Cliente ingresado correctamente.\n");
                         guardarCliente(cedulas[numClientes-1], nombresClientes[numClientes-1]);
                           break;
                       }
                   } while (1);
               }
           } while (numClientesIngresar < 0);
           break;
           case 6:
           printf("========== MODIFICAR CLIENTE ==========\n");
           if (numClientes == 0) {
               printf("No hay clientes registrados.\n");
               break;
           }
           for (int i = 0; i < numClientes; i++) {
               printf("%d. Cédula: %s, Nombre: %s\n", i + 1, cedulas[i], nombresClientes[i]);
           }
           printf("Si desea volver al menú principal, ingrese 'x'\n");
           printf("Seleccione el número del cliente a modificar: ");
           char opcionModificar[10];
           scanf("%s", opcionModificar);
           if (strcmp(opcionModificar, "x") == 0) {
               break;
           }
           int indiceCliente = atoi(opcionModificar) - 1;
           if (indiceCliente < 0 || indiceCliente >= numClientes) {
               printf("Opción no válida.\n");
               break;
           }

           limpiarBuffer();
           printf("Ingrese el nuevo nombre del cliente: ");
           fgets(nombresClientes[indiceCliente], 100, stdin);
           nombresClientes[indiceCliente][strcspn(nombresClientes[indiceCliente], "\n")] = 0;

           printf("Nombre del cliente modificado correctamente.\n");
           break;


            case 7:
                printf("========== CONSULTAR CLIENTE ==========\n");
                if (numClientes == 0) {
                    printf("No hay clientes registrados.\n");
                    break;
                }
                for (int i = 0; i < numClientes; i++) {
                    printf("%d. Cédula: %s\n   Nombre: %s\n", i + 1, cedulas[i], nombresClientes[i]);
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
                printf("Cédula: %s\n", cedulas[indiceCliente]);
                printf("Nombre: %s\n", nombresClientes[indiceCliente]);
                break;

            case 8:
                printf("========== LISTADO DE CLIENTES ==========\n");
                if (numClientes == 0) {
                    printf("No hay clientes registrados.\n");
                } else {
                    for (int i = 0; i < numClientes; i++) {
                        printf("Cédula: %s\n", cedulas[i]);
                        printf("Nombre: %s\n", nombresClientes[i]);
                        printf("--------------------\n");
                    }
                }
                break;
          case 9:
          {
              printf("=== Proceso de Compra ===\n");
              if (numClientes == 0 || numProductos == 0) {
                  printf("Registro de clientes o inventario de productos está vacío.\n");
                  break;
              }

             
              printf("=== Clientes Registrados ===\n");
              for (int i = 0; i < numClientes; i++) {
                  printf("Nombre: %s, ID: %s\n", nombresClientes[i], cedulas[i]);
              }
              printf("===========================\n");

              
              printf("Por favor, introduzca el ID del cliente para la compra: ");
              char idClienteCompra[11];
              limpiarBuffer();
              fgets(idClienteCompra, 11, stdin);
              idClienteCompra[strcspn(idClienteCompra, "\n")] = 0;

             
              int indiceCliente = -1;
              for (int i = 0; i < numClientes; i++) {
                  if (strcmp(cedulas[i], idClienteCompra) == 0) {
                      indiceCliente = i;
                      break;
                  }
              }

              if (indiceCliente == -1) {
                  printf("ID de cliente no se encuentra en el registro.\n");
                  break;
              }

              
              char productosComprados[MAX_PRODUCTOS][100];
              int cantidadesCompradas[MAX_PRODUCTOS];
              float precioUnitarioComprado[MAX_PRODUCTOS];
              float costoTotalProducto[MAX_PRODUCTOS];
              int contadorDetalles = 0;
              float montoTotalCompra = 0.0;

              
              char eleccion;
              printf("Agregue productos a la compra, 'x' para finalizar:\n");
              do {
                  
                  for (int i = 0; i < numProductos; i++) {
                      printf("%d. Artículo: %s, Costo: $%.2f, Stock: %d\n", i + 1, nombresProductos[i], precios[i], cantidades[i]);
                  }
                  printf("Elija un artículo (o 'x' para finalizar): ");
                  scanf(" %c", &eleccion);
                  if (eleccion == 'x' || eleccion == 'X') {
                      break;
                  }

                  int indiceProductoElegido = eleccion - '1'; 
                  if (indiceProductoElegido < 0 || indiceProductoElegido >= numProductos) {
                      printf("Selección no válida.\n");
                      continue;
                  }

                 
                  printf("Usted ha elegido: %s\n", nombresProductos[indiceProductoElegido]);
                  printf("Indique la cantidad deseada: ");
                  int cantidadDeseada;
                  scanf("%d", &cantidadDeseada);
                  limpiarBuffer();

                  if (cantidadDeseada < 1 || cantidadDeseada > cantidades[indiceProductoElegido]) {
                      printf("Cantidad no permitida o excede el stock disponible.\n");
                      continue;
                  }

                  
                  strcpy(productosComprados[contadorDetalles], nombresProductos[indiceProductoElegido]);
                  cantidadesCompradas[contadorDetalles] = cantidadDeseada;
                  precioUnitarioComprado[contadorDetalles] = precios[indiceProductoElegido];
                  costoTotalProducto[contadorDetalles] = cantidadDeseada * precios[indiceProductoElegido];
                  montoTotalCompra += costoTotalProducto[contadorDetalles];

                  
                  cantidades[indiceProductoElegido] -= cantidadDeseada;

                  contadorDetalles++;
                  printf("Artículo añadido a la compra.\n");
              } while (1);

              
              printf("\n=== Resumen de Factura ===\n");
             
              time_t tiempoActual;
              time(&tiempoActual);
              struct tm *infoTiempo = localtime(&tiempoActual);
            char fechaCompra[20];
                strftime(fechaCompra, 20, "%Y-%m-%d %H:%M:%S", infoTiempo);

                printf("Fecha de la Compra: %s\n", fechaCompra);
                printf("Cliente: %s, ID: %s\n", nombresClientes[indiceCliente], idClienteCompra);
                printf("Artículos adquiridos:\n");
                for (int i = 0; i < contadorDetalles; i++) {
                    printf("%d. %s - Cantidad: %d, Precio unitario: $%.2f, Costo total: $%.2f\n",
                           i + 1,
                           productosComprados[i],
                           cantidadesCompradas[i],
                           precioUnitarioComprado[i],
                           costoTotalProducto[i]);
                }

                printf("\nMonto total de la Compra: $%.2f\n", montoTotalCompra);
                printf("=================================\n");

                
                

                
                numFacturas++;

                printf("La transacción ha sido completada exitosamente.\n"); 
            printf(" La factura ha sido registrada.\n");
            guardarFactura(numeroFactura, cedulaCliente, nombreCliente, totalCompra);
                printf("=================================\n");

                break;
            }

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
                        if (strcmp(cedulas[i], cedulaABuscar) == 0) {
                            printf("Fecha: %s\n", fechas[i]);
                            printf("Cédula: %s\n", cedulas[i]);
                            printf("Nombre: %s\n", nombresClientes[i]);
                            printf("Valor Pagado: %.2f\n", valoresPagados[i]);
                            printf("Cantidad de productos comprados: %d\n", cantidadesProductos[i]);
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
                        printf("Fecha: %s\n", fechas[i]);
                        printf("Cédula: %s\n", cedulas[i]);
                        printf("Nombre: %s\n", nombresClientes[i]);
                        printf("Valor Pagado: %.2f\n", valoresPagados[i]);
                        printf("Cantidad de productos comprados: %d\n", cantidadesProductos[i]);
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