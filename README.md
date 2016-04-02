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
