CC=gcc
CFLAGS=-Wall -I$(HEADER_DIR)
HEADER_DIR=src/headers

primesieve: src/main.c build/primesieve.o build/bitops.o
	$(CC) $(CFLAGS) -o primesieve src/main.c build/primesieve.o build/bitops.o -O1

build/primesieve.o: src/primesieve.c
	$(CC) $(CFLAGS) -fPIC -o build/primesieve.o src/primesieve.c -c -Ofast

build/bitops.o: src/bitops.c
	$(CC) $(CFLAGS) -fPIC -o build/bitops.o src/bitops.c -c -O2

build/libprimesieve.so: build/primesieve.o build/bitops.o
	$(CC) $(CFLAGS) -shared -fPIC -o build/libprimesieve.so build/primesieve.o build/bitops.o

build/primesievejni.o: src/primesievejni.c
	$(CC) $(CFLAGS) -fPIC -c src/primesievejni.c -o build/primesievejni.o -I/usr/lib/jvm/default-java/include -I/usr/lib/jvm/default-java/include/linux -O2

build/libprimesievejni.so: build/primesievejni.o build/primesieve.o build/bitops.o
	$(CC) $(CFLAGS) -shared -fPIC -o build/libprimesievejni.so build/primesievejni.o build/primesieve.o build/bitops.o

java: build/libprimesievejni.so
	javac -d build src/PrimeSieveInterface.java src/PrimeSieve.java src/Application.java
	cd build
	jar cvfe PrimeSieve.jar Application PrimeSieveInterface.class PrimeSieve.class Application.class libprimesievejni.so

python: src/primesieve.py build/libprimesieve.so
	cp src/primesieve.py primesieve.py

clean:
	rm build/*
