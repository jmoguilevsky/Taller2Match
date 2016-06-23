Application server - Documentación técnica
==========================================

Diseño de las bases de datos
----------------------------

Dado que todas las bases de datos son no relacionales, es decir tienen la forma *{clave,valor}*, todas las bases de datos utilizadas tienen como clave algún identificador de un usuario, ya sea un email o un id interno al servidor.

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

