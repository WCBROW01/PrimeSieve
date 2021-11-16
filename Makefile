CC=gcc -I$(HEADER_DIR)
HEADER_DIR=src/headers

primesieve: src/primesievemain.c build/primesieve.o
	$(CC) -o primesieve src/primesievemain.c build/primesieve.o -lm -O2

build/primesieve.o: src/primesieve.c
	$(CC) -fPIC -o build/primesieve.o src/primesieve.c -c -O2

semiprimesieve: src/semiprimesievemain.c build/semiprimesieve.o build/primesieve.o
	$(CC) -o semiprimesieve src/semiprimesievemain.c build/semiprimesieve.o build/primesieve.o -lm -O2

build/semiprimesieve.o: src/semiprimesieve.c
	$(CC) -o build/semiprimesieve.o src/semiprimesieve.c -c -O2

build/primesievejni.o: src/primesievejni.c
	$(CC) -fPIC -c src/primesievejni.c -o build/primesievejni.o -I/usr/lib/jvm/default-java/include -I/usr/lib/jvm/default-java/include/linux -O2
	
build/libprimesievejni.so: build/primesievejni.o build/primesieve.o
	$(CC) -shared -fPIC -o build/libprimesievejni.so build/primesievejni.o build/primesieve.o -lm

java: build/libprimesievejni.so
	javac -d build src/PrimeSieveInterface.java src/PrimeSieve.java src/Application.java
	cd build
	jar cvfe PrimeSieve.jar Application PrimeSieveInterface.class PrimeSieve.class Application.class libprimesievejni.so

fast: src/primesieve.c
	$(CC) -o build/primesieve.o src/primesieve.c -c -O2 -march=native
	$(MAKE) primesieve

clean:
	rm build/*
