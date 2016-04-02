Taller 2 - Match App
====================   

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
