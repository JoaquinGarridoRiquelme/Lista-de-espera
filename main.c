#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar();
}
//Estructura que contiene los datos de nuestro paciente
typedef struct {
char nombre[30];
char apellido[30];
int edad;
char sintoma[50];
char nivel_prioridad[10];
time_t hora_registro;
} nodo_paciente;

typedef struct{
  List *lista_baja;
  List *lista_media;
  List *lista_alta;
  size_t cantidad_pacientes;
} tipo_espera;

tipo_espera* iniciar_lista_espera()
{
  tipo_espera *ptr_lista =  malloc(sizeof(tipo_espera));
  ptr_lista->lista_baja = list_create();
  ptr_lista->lista_media = list_create();
  ptr_lista->lista_alta = list_create();
  ptr_lista->cantidad_pacientes = 0;
  return ptr_lista;
}
nodo_paciente *buscar_paciente(List *lista, char *nombre, char *apellido){
  nodo_paciente *ptr_aux = list_first(lista);
  while(ptr_aux != NULL)
    {
      if(strcmp(ptr_aux->nombre, nombre) == 0 && strcmp(ptr_aux->apellido, apellido)==0)
        return ptr_aux;
      ptr_aux = list_next(lista);
    }
  return NULL;
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

void registrar_paciente(tipo_espera *lista) {
  printf("Registrar nuevo paciente\n");
  nodo_paciente *nuevo_paciente = (nodo_paciente*) malloc(sizeof(nodo_paciente));
  if(nuevo_paciente == NULL)
  {
    printf("No se pudo registrar al paciente debido a un error de memoria\n");
    return;
  }
  else
  {
    printf("Ingrese el nombre del paciente:\n");
    scanf("%s", nuevo_paciente -> nombre);
    getchar();
    printf("Ingrese el apellido del paciente:\n");
    scanf("%s", nuevo_paciente -> apellido);
    getchar();
    printf("Ingrese la edad del paciente: \n");
    scanf("%i", &nuevo_paciente -> edad);
    getchar();
    printf("Ingrese el sintoma del paciente:\n");
    fscanf(stdin,"%[^\n]", nuevo_paciente -> sintoma);
    getchar();
    time(&nuevo_paciente->hora_registro);
    strcpy(nuevo_paciente->nivel_prioridad, "BAJA");
    list_pushBack(lista ->lista_baja, nuevo_paciente);
    lista->cantidad_pacientes++;
  }
}

int parametro(void *base, void *elem)
{
  nodo_paciente *ptr_base = (nodo_paciente*)base;
  nodo_paciente *ptr_elem = (nodo_paciente*)elem;
  if(ptr_base->hora_registro < ptr_elem->hora_registro) return 1;
  return 0;
}

void eliminar_nodo(List *lista, nodo_paciente *paciente)
{
  nodo_paciente *ptr_aux = list_first(lista);
  while(ptr_aux != NULL)
    {
      if(ptr_aux == paciente)
      {
        list_popCurrent(lista);
        return;
      }
      ptr_aux = list_next(lista);
    }
}

void asignar_prioridad(tipo_espera *lista){
  char nombre[50];
  char apellido[50];
  char prioridad[10];
  printf("Asignación de prioridad\n");
  printf("Indique el nombre del paciente:\n");
  scanf("%s", nombre);
  getchar();
  printf("Indique el apellido del paciente:\n");
  scanf("%s", apellido);
  getchar();
  nodo_paciente *paciente = buscar_paciente(lista->lista_baja, nombre, apellido);
  if(paciente == NULL)
  {
    printf("El paciente no se encuentra registrado\n");
    return;
  }

  printf("Indique el nivel de prioridad del paciente (Elegir entre ALTA, MEDIA y BAJA):\n");
  scanf("%s", prioridad);
  getchar();
  if(strcmp(prioridad, "MEDIA") == 0)
  {
    strcpy(paciente->nivel_prioridad, prioridad);
    eliminar_nodo(lista->lista_baja, paciente);
    list_sortedInsert(lista->lista_media, paciente, parametro);
  }

  else if(strcmp(prioridad, "ALTA") == 0)
  {
    strcpy(paciente->nivel_prioridad, prioridad);
    eliminar_nodo(lista->lista_baja, paciente);
    list_sortedInsert(lista->lista_alta, paciente, parametro);
  }
}

void mostrar_lista(List *lista){
  nodo_paciente *ptr_aux = list_first(lista);
  if(ptr_aux == NULL)
  {
    printf("No hay pacientes en la lista\n\n");
    return;
  }
  while(ptr_aux != NULL)
    {
      printf("Nombre del paciente: %s\n", ptr_aux ->nombre);
      printf("Apellido del paciente: %s\n", ptr_aux ->apellido);
      printf("Edad del paciente: %i\n", ptr_aux ->edad);
      printf("Sintoma del paciente: %s\n", ptr_aux ->sintoma);
      printf("Hora de registro: %s",ctime(&ptr_aux ->hora_registro));
      printf("Nivel de prioridad del paciente: %s\n\n", ptr_aux ->nivel_prioridad);
      ptr_aux = list_next(lista);
    }
}

void mostrar_lista_pacientes(tipo_espera *lista) {
  if(lista->cantidad_pacientes == 0)
  {
    printf("No hay pacientes en la lista de espera\n");
    return;
  }
  printf("Pacientes en espera: %zu\n\n", lista->cantidad_pacientes);
  printf("Pacientes de prioridad alta:\n\n");
  mostrar_lista(lista ->lista_alta);
  printf("Pacientes de prioridad media:\n\n");
  mostrar_lista(lista ->lista_media);
  printf("Pacientes de prioridad baja:\n\n");
  mostrar_lista(lista->lista_baja);
  return;
}

void liberar_listas(tipo_espera* lista)
{
  list_clean(lista->lista_baja);
  list_clean(lista->lista_media);
  list_clean(lista->lista_alta);
  return;
}

void mostrar_prioridad(tipo_espera *lista)
{
  char prioridad_deseada[50];
  if(lista->cantidad_pacientes == 0)
  {
    printf("No hay pacientes en la lista de espera\n");
    return;
  }
  printf("Ingrese la prioridad que desea mostrar: \n");
  scanf("%s", prioridad_deseada);
  getchar();
  if(strcmp(prioridad_deseada, "BAJA") == 0)
  {
    printf("Lista de prioridad baja:\n\n");
    mostrar_lista(lista->lista_baja);
  }
  else if(strcmp(prioridad_deseada, "MEDIA") == 0)
  {
    printf("Lista de prioridad media:\n\n");
    mostrar_lista(lista->lista_media);
  }
  else if(strcmp(prioridad_deseada, "ALTA") == 0)
  {
    printf("Lista de prioridad alta:\n\n");
    mostrar_lista(lista->lista_alta);
  }
}

void siguiente_paciente(tipo_espera *lista)
{
  nodo_paciente *ptr_aux = list_first(lista->lista_alta);
  if(ptr_aux != NULL)
  {
    list_popCurrent(lista->lista_alta);
    lista->cantidad_pacientes--;
    return;
  }

  ptr_aux = list_first(lista->lista_media);
  if(ptr_aux != NULL)
  {
    list_popCurrent(lista->lista_media);
    lista->cantidad_pacientes--;
    return;
  }

  ptr_aux = list_first(lista->lista_baja);
  if(ptr_aux != NULL)
  {
    list_popCurrent(lista->lista_baja);
    lista->cantidad_pacientes--;
    return;
  }
  printf("No quedan pacientes en espera\n");
}

int main() {
  char opcion;
  tipo_espera *lista_espera = iniciar_lista_espera(); 

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);
    getchar();

    switch (opcion) {
    case '1':
      registrar_paciente(lista_espera);
      break;
    case '2':
      asignar_prioridad(lista_espera);
      break;
    case '3':
      mostrar_lista_pacientes(lista_espera);
      break;
    case '4':
      siguiente_paciente(lista_espera);
      break;
    case '5':
      mostrar_prioridad(lista_espera);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...\n");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.\n");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  liberar_listas(lista_espera);

  return 0;
}
