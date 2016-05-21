Taller 2 - Match App
====================   

master: [![Build Status](https://travis-ci.org/jmoguilevsky/Taller2Match.svg?branch=master)](https://travis-ci.org/jmoguilevsky/Taller2Match)

**RocksDB**  
1. Bajar el zip de la última versión (4.3.1) github.com/facebook/rocksdb/releases y extraerlo.  
2. Hacer cd a esa carpeta.  
3. make static_lib  
4. Mover el librocksdb.a a una de las carpetas /lib. Yo lo puse en usr/lib/x86_64-linux-gnu  
5. Mover lo que está en /include a /usr/include.  
6. sudo apt-get install libgflags-dev  
7. sudo apt-get install libsnappy-dev  
8. sudo apt-get install zlib1g-dev  
9. sudo apt-get install libbz2-dev  
10. Para compilar:  
`g++ -std=c++11 <nuestros cpp> -o <blablabla> -lrocksdb -pthread -lsnappy -lz -lbz2`  

(SIN EL `std=c++11` NO ANDA)  

**CMake v3.5.1**  
1. Ir a [https://cmake.org/download/] y bajarse el source correspondiente al S.O. Yo voy a trabajar con la .tar.gz.  
2. En una terminal, ejecutamos:  
`tar xf cmake-3.5.1.tar.gz`  
`cd cmake-3.5.1`  
`./configure`  
`make`  
3. `make install`  

**Mongoose: Ejemplo**  
_El ejemplo fue tomado del source de mongoose._  
1. Correr, en una terminal:  
`unzip mongoose-master.zip`  
2. Compilar:  
`g++ ejemploMongoose.cpp mongoose-master/mongoose.c -lpthread -DMG_ENABLE_THREADS -o ejemplo`  
3. Correr `./ejemplo` y verificar que en un web-explorer devuelva una response al entrar a _localhost:8000_  
4. Para salir basta con ejecutar ctrl+c en la terminal donde lo estamos corriendo. La lib es inteligente como para  
manejar signals, y hará que libere los recursos necesarios.  

**Sphinx**  
`sudo apt-get install python-sphinx`  

(Antes de esto yo había hecho:

1. `sudo apt-get install python-dev`  
2. `pip install sphinx`  

pero no sé si hace falta)  

Hay ejemplos para ver cómo escribir los documentos en la carpeta ejemploSphinx.  
Para crear el html:  

1. `cd ejemploSphinx`  
2. `make html`  

El html queda en la carpeta _build.  

**Docker**
1. Crearse una cuenta en Docker. Puede omitirse si es que sólo queremos obtener la imagen para correrla.  
2. Instalarlo: [https://docs.docker.com/linux/step_one/]  
3. Una vez que tenemos docker instalado, hacemos:  
`$ docker run -ti mvbattan4/applicationserver:ejemploMongoose`  
'$ sudo usermod -aG docker <username>'  
`# make`  
4. Podemos obtener la IP via el id de la imagen que estamos corriendo.  
Falta ver cómo obtenemos el id programáticamente, ya que con esto podemos averiguar la ip:  
`docker inspect --format '{{ .NetworkSettings.IPAddress }}' 70143dd46635`  
5. Ir a la direccion _IP_:_PuertoDelEjemplo_  

=======
# node-js-getting-started

A barebones Node.js app using [Express 4](http://expressjs.com/).

This application supports the [Getting Started with Node on Heroku](https://devcenter.heroku.com/articles/getting-started-with-nodejs) article - check it out.

## Running Locally

Make sure you have [Node.js](http://nodejs.org/) and the [Heroku Toolbelt](https://toolbelt.heroku.com/) installed.

```sh
$ git clone git@github.com:heroku/node-js-getting-started.git # or clone your own fork
$ cd node-js-getting-started
$ npm install
$ npm start
```

Your app should now be running on [localhost:5000](http://localhost:5000/).

## Deploying to Heroku

```
$ heroku create
$ git push heroku master
$ heroku open
```
or

[![Deploy to Heroku](https://www.herokucdn.com/deploy/button.png)](https://heroku.com/deploy)

## Documentation

For more information about using Node.js on Heroku, see these Dev Center articles:

- [Getting Started with Node.js on Heroku](https://devcenter.heroku.com/articles/getting-started-with-nodejs)
- [Heroku Node.js Support](https://devcenter.heroku.com/articles/nodejs-support)
- [Node.js on Heroku](https://devcenter.heroku.com/categories/nodejs)
- [Best Practices for Node.js Development](https://devcenter.heroku.com/articles/node-best-practices)
- [Using WebSockets on Heroku with Node.js](https://devcenter.heroku.com/articles/node-websockets)

=====================
**Volley: guia de instalacion**  
1. Tipear en la consola lo siguiente  
git clone https://android.googlesource.com/platform/frameworks/volley  
2. Asegurarse que en el proyecto de Android Studio, en el archivo Gradle Scripts->build.gradle(Module:app)   
dentro de la parte de dependencies, abajo de todo, tenga la linea:  
compile 'com.mcxiaoke.volley:library-aar:1.0.0'  
Si no esta, hay que agregarla. A mi me queda asi la parte de dependencies:  
```dependencies {  
    compile fileTree(dir: 'libs', include: ['*.jar'])  
    testCompile 'junit:junit:4.12'  
    compile 'com.android.support:appcompat-v7:23.3.0'  
    compile 'com.mcxiaoke.volley:library-aar:1.0.0'  
}```  

**GoogleTests y LCOV**  
1. Se consiguen el zip desde acá: https://github.com/google/googletest  
2. Se extrae dicho zip.  
3. Ir a /googletest y escribir `cmake`  
4. Ejecutar `make`  
5. `sudo make install`  
6. Listo ! Tenemos instalado el framework de google para testing.  
  
Para compilar, usar los flags:  
`g++ -std=c++11 ejemploGoogleTest.cpp -lgtest -lgtest_main -lpthread -g -o ejemplo`  
  
Se recomienda leer esto:  
https://github.com/google/googletest/blob/master/googletest/docs/Documentation.md  

Recuerden hacer `#include <gtest/gtest.h>` y definir las clases Tests que consideren necesarias.   

*Para LCOV,*  
1. Seguir el readme:  
http://ltp.sourceforge.net/coverage/lcov/readme.php  

En realidad lo que termina haciendo es instalar desde source con los pasos clásicos,  
`make install` después de haber descomprimido el .tar.gz  

2. Si queremos utilizar lcov, tenemos que compilar para generar archivos útiles para gcov.  
Para esto, compilamos como:  
`g++ -std=c++11 ejemploGoogleTest.cpp -lgtest -lgtest_main -lpthread -g -fprofile-arcs -ftest-coverage -o ejemplo`  
Con esto estamos agregando los flags para los tests  

_Uso_  
`lcov --directory <appdir> --zerocounters`  
`./ejemplo` # Corremos el ejemplo para poder generar el coverage. Esta info es capturada en unos archivos que se pueden ver con `ls`  
`lcov --directory <appdir> --capture --output-file app.info` # O algun otro nombre en vez de app.info  
`genhtml app.info`  
`google-chrome index.html`  

