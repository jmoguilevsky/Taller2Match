Application server - Documentación técnica
==========================================

Instalación
-----------
1. ``cd`` al directorio princial, ``ApplicationServer``
2. ``cmake .``
3. Para instalar el Application server: ``make app``
4. Para instalar Unit tests: ``make unitTests``

Ejecución
---------

- Para ejecutar el servidor: ``./app [opciones]``

Las opciones disponibles son:

======================== ==========================================================================================
        Opción                                                 Descripción                                    
======================== ==========================================================================================
  ``-h``                   Muestra esta información.                                                          
  ``-l [LOG_LEVEL]``       Setea el nivel de log a utilizar. 0: ERROR; 1: WARNING; 2: INFO; 3: DEBUG 
  ``-p [LISTEN_PORT]``     Setea el puerto en el que se escucharán las conexiones entrantes.                  
  ``-s [SHARED_SERVER]``   Setea la url del Shared Server a utilizar                                          
======================== ==========================================================================================

**Importante**: antes de ejecutar el servidor, se debe crear un directorio ``db`` si es que todavía no existe, dentro de ``Application Server``


- Para ejecutar los tests: ``./test/unitTests``

Estructura general de los módulos y clases del servidor
-------------------------------------------------------

Se dividió la aplicación en varios "módulos" con funcionalidades diferentes, de forma que sean lo más independientes posible entre sí, cada uno con funcionalidades bien claras y distintas a las de los demás.

Así, tenemos el módulo de bases de datos **DB**, que contiene las clases:

- **KeyValueDb** clase "abstracta" para una base de datos no relacional, del tipo *{clave, valor}*
- **RocksDb** derivada de KeyValueDb, una implementación específica de este tipo de base de datos con la librería RocksDb
- **JsonArrayDb** que utiliza a su vez a RocksDb, y contiene como valores a arrays Json, y tiene una interfaz amigable para trabajar con datos en este formato

Otro módulo es el módulo **Mongoose**, que contiene las clases necesarias para realizar todo lo relacionado con la conexión del servidor y sus clientes, y del Application Server como cliente del Shared Server. Contiene las clases:

- **MgServer** un server multithread, es decir, que por cada request que recibe, lanza un nuevo thread en donde se procesa el mismo, y al finalizar el procesamiento y luego de enviar la respuesta, el thread es destruido
- **MgHTTPClient** cliente HTTP, permite realizar un HTTP request a una URL y obtener una respuesta
- **MgConnectionManager** wrapper para la estructura "mg_mgr" y sus funciones relacionadas, para hacer el código más comprensible y a su vez encapsular un poco el uso de la librería Mongoose

El módulo **HTTP** tiene toda la funcionalidad requerida para manejar los requests HTTP (crear las respuestas con el código adecuado, por ejemplo 200 para "Ok", transformar la estructura de la librería Mongoose que contiene un request HTTP en un objeto más fácil de manejar, etc.).

- **HTTPResponse**
- **HTTPRequest**
- **HTTP** (*namespace*) facilita la creación de las responses HTTP, por ejemplo, con HTTP::OK(), se crea un HTTP response con el código de status adecuado según el estándar.

Por lado también hay otras dos partes que son más específicas a la aplicación particular que se desarrolló. La primera, en el directorio **MatchData** controla la lógica de la aplicación, por ejemplo, el manejo de los likes, los matches, la información del login de los usuarios, etc. , pero sin tener en cuenta cómo es que se comunican los clientes con el servidor, ni cómo se comunica éste con el *shared server*. Para esto, en el módulo **HandlersHTTP** se encuentran las clases encargadas de parsear los requests HTTP de los clientes, determinar qué se debe hacer, pedirle a la entidad que corresponda de MatchData que procese el pedido, y finalmente de generar la respuesta en el formato que espera el cliente.

(Más detalles en la documentación del código)


Estructura de las bases de datos
--------------------------------

Dado que todas las bases de datos son no relacionales, tienen la forma *{clave,valor}*, todas tienen como clave algún identificador de un usuario, ya sea un email o un id interno al servidor.

``userId``: identificador del usuario *dentro* del servidor, se utiliza para la comunicación entre los clientes y el servidor en lugar del email

``email``: email con que se registró cada usuario

1. Base de datos ``login_db``
	**clave**: ``email``

	**valor**: contraseña correspondiente a ese email

2. Base de datos ``email_userId_db``
	**clave**: ``email``

	**valor**: ``userId``

3. Base de datos ``email_sharedId_db``
	**clave**: ``email``

	**valor**: identificador del usuario en el *Shared server* en el cual está registrado

4. Base de datos ``candidate_db``
	**clave**: ``userId``

	**valor**: último candidato sugerido al usuario

5. Base de datos ``limit_db``
	**clave**: ``userId``

	**valor**: objeto Json con los siguientes campos:
		- ``lastTime``: fecha en que el usuario pidió un candidato por última vez
		- ``left``: cantidad de candidatos que tiene el usuario disponibles para el día indicado en el campo anterior

6. Base de datos ``distance_db``
	**clave**: ``userId``

	**valor**: distancia máxima a la que el usuario desea que se encuentren los candidatos sugeridos

7. Base de datos ``matches_db``
	**clave**: ``userId``

	**valor**: array Json que contiene los ids (internos) de cada uno de los usuarios con los que el usuario tiene un *match*

8. Base de datos ``likes_db``
	**clave**: ``userId``

	**valor**: array Json que contiene los ids (internos) de cada uno de los usuarios a los que el usuario *aceptó*
9. Base de datos ``dislikes_db``
	**clave**: ``userId``

	**valor**: array Json que contiene los ids (internos) de cada uno de los usuarios a los que el usuario *rechazó*

10. Base de datos ``likesReceived_db``
	**clave**: ``userId``

	**valor**: contador que aumenta en 1 cada vez que un usuario acepta a este usuario para un posible *match* futuro	
11. Base de datos ``chat_db``
	**clave**: combinación entre los ``userId`` de dos usuarios que son match

	**valor**: Json array con los mensajes que se han envíado entre los dos usuarios
