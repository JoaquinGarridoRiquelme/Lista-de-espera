
## Descripción del Programa

Este programa permite a los usuarios gestionar la atención de pacientes en un hospital. Los usuarios pueden registrar nuevos pacientes, asignar prioridades, ver la lista de espera, eliminar pacientes ya atendidos de la lista y mostrar los pacientes según prioridad prioridad. Esta herramienta está diseñada para mejorar la eficiencia en la atención de los pacientes, asegurando que aquellos en situaciones de alta prioridad reciban atención lo más pronto posible.

## Cómo compilar y ejecutar

Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. 

Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/JoaquinGarridoRiquelme/Lista-de-espera`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. En la pestaña "Configurate Repl", sección "Configure the Compile Command", pegar el siguiente comando "gcc tdas/*.c main.c -Wno-unused-result -o main" y presionar "done".
7. Presione el boton "Run" para compilar y ejecutar la aplicación.

## Funcionalidades

### Funcionando correctamente:

- Registrar pacientes con sus datos básicos y una prioridad inicial.
- Asignar o modificar la prioridad de los pacientes.
- Ver la lista de espera de pacientes, ordenada por prioridad y hora de registro.
- Atender al siguiente paciente, respetando el orden de prioridad.

### Problemas conocidos:

- Los datos deben ser ingresados por el usuario siempre en minúsculas o siempre en mayúsculas, en caso contrario el programa sufrira problemas a la hora de manejar la busqueda de datos.
- El usuario debe manejar los datos correctamente, un ejemplo de esto sería ingresar el nombre Joaquín como Joquín (imaginando que el usuario se saltó una letra), esto haría que al buscar al usuario como Joaquín, este no sea detectado.

### A mejorar:

- Implementar una interfaz de usuario más amigable.
- Mejorar la lectura de datos para aceptar textos mezclados entre mayúsculas y minúsculas.
- El programa está pensado para medir la edad solo en años, por lo que no está considerado para medirse en medidas como dias, semanas, o meses.
- Permitir la edición de los datos de los pacientes.
- El programa no permite modificar la prioridad una vez asignada, por ejemplo, un usuario que fue asignado previamente a la prioridad media no puede ser reasignado a la prioridad alta.

## Ejemplo de uso

**Paso 1: Registrar un Nuevo Paciente**

Se comienza registrando un nuevo paciente que acaba de llegar al hospital.
````
Registrar nuevo paciente
Ingrese el nombre del paciente: 
Joaquín 
Ingrese el apellido del paciente:
Garrido
Ingrese la edad del paciente: 
29
Ingrese el síntoma del paciente: 
Dolor de cabeza
````  
````
Registrar nuevo paciente
Ingrese el nombre del paciente: 
Cecilia
Ingrese el apellido del paciente:
Torres
Ingrese la edad del paciente: 
19
Ingrese el síntoma del paciente: 
Mareos Intensos
````  
Se registra a Joaquín Garrido y a Cecilia Torres en la lista de prioridad baja, ya que hasta que el usuario cambie manualmente la prioridad del paciente, este se queda en la lista de baja prioridad.

**Paso 2: Asignar Prioridad a un Paciente**

En el momento que se desee asignar una prioridad al paciente, pasamos a esta opción para modificar la opción base (la cual es prioridad baja).
````
Asignación de prioridad
Indique el nombre del paciente:
Joaquín
Indique el apellido del paciente:
Garrido
Indique el nivel de prioridad del paciente (Elegir entre ALTA, MEDIA y BAJA):
MEDIA
````

Desde ahora encontraremos a Joaquín Garrido en la lista de espera de prioridad media

**Paso 2: Asignar Prioridad a un Paciente**

El usuario desea mostrar la lista de espera, por lo que esta se muestra por secciones
````
Pacientes en espera: 2

Pacientes de prioridad alta:

No hay pacientes en la lista

Pacientes de prioridad media:

Nombre del paciente:
Joaquín
Apellido del paciente:
Garrido
Edad del paciente:
29
Sintoma del paciente:
Dolor de cabeza
Hora de registro:
(Hora de registro del sistema)
Nivel de prioridad del paciente:
MEDIA

Pacientes de prioridad baja:

Nombre del paciente:
Cecilia
Apellido del paciente:
Torres
Edad del paciente:
19
Sintoma del paciente:
Mareos Intensos
Hora de registro:
(Hora de registro del sistema)
Nivel de prioridad del paciente:
BAJA
````

La lista muestra a los pacientes seccionados según lista de prioridad, indicando todos sus datos.

**Paso 4: Atender al siguiente Paciente**

Joaquín Garrido es llamado a la consulta del doctor, por lo que necesitamos eliminarlo de la lista de espera.

Internamente el sistema eliminará al paciente de prioridad más alta, dando a entender que fue atendido, y así pudiendo pasar al siguiente.

**Paso 5: Mostrar pacientes por prioridad**

Al seleccionar esta opción, el usuario podrá seleccionar la lista de espera que quiere mostrar, en este ejemplo mostraremos la lista de prioridad baja.

````
Ingrese la prioridad que desea mostrar:
BAJA

Lista de prioridad baja:

Nombre del paciente:
Cecilia
Apellido del paciente:
Torres
Edad del paciente:
19
Sintoma del paciente:
Mareos Intensos
Hora de registro:
(Hora de registro del sistema)
Nivel de prioridad del paciente:
BAJA
````

**Paso 6: Salir del programa**

Al terminar el turno de trabajo o simplemente no querer usar más el programa, el usuario selecciona esta opción para cerrar la aplicación.

````
Saliendo del sistema de gestión hospitalaria...
````
