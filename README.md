🎟️ Gestor de Sorteos y Rifas (C++)

Un sistema de gestión de rifas por consola desarrollado íntegramente en C++.
Este proyecto fue creado para administrar la venta de 200 números y realizar un sorteo final garantizando total transparencia y aleatoriedad, permitiendo auditar el código fuente utilizado para elegir al ganador.

✨ Características Principales

Gestión de Clientes: Permite registrar nuevos compradores o asignar nuevos números a clientes ya existentes mediante un sistema de índices.

Control de Números: Seguimiento en tiempo real de los números vendidos y los números disponibles (del 1 al 200).

Persistencia de Datos (Archivos Binarios): El estado del sorteo no se pierde al cerrar la consola. Utiliza operaciones a bajo nivel (fread y fwrite) para guardar automáticamente la información en archivos .dat.

Azar Auditable: Utiliza un Generador Congruencial Lineal interno (rand()) alimentado por una semilla persistente que se auto-incrementa en cada ejecución, asegurando resultados justos e impredecibles sin depender del reloj del sistema.

Eliminación Segura: Opción para dar de baja a un cliente, liberando automáticamente todos los números que tenía asignados y reajustando la base de datos.

🛠️ Tecnologías y Librerías

El programa está construido utilizando únicamente librerías estándar de C++ para mantener la eficiencia y simplicidad:

<iostream>: Manejo de flujos de entrada y salida estándar.

<cstring>: Manipulación de cadenas de caracteres estáticas para optimizar la escritura en memoria.

<cstdlib>: Funciones principales para el motor de aleatoriedad.

🚀 Cómo ejecutarlo

Para compilar y ejecutar este programa localmente, necesitas tener instalado un compilador de C++ (como MinGW o GCC).

Clona este repositorio:

git clone [https://github.com/tu-usuario/nombre-del-repo.git](https://github.com/tu-usuario/nombre-del-repo.git)


Abre una terminal en la carpeta del proyecto y compila el archivo fuente:

g++ Loteria.cpp -o Sorteo


Ejecuta el programa:

./Sorteo


(Nota: Al ejecutarse por primera vez, el programa creará automáticamente los archivos clientes.dat, rifas.dat y semilla.dat en el mismo directorio).

🔒 Transparencia (Open Source)

Este código es de código abierto para que cualquier participante del sorteo pueda revisar la lógica matemática detrás de la selección del ganador. La selección se realiza recolectando un arreglo dinámico con todos los números vendidos al momento del sorteo y aplicando una selección pseudoaleatoria justa.
