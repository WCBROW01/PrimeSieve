CC=gcc

primesieve: ./src/primesievemain.c primesieve.o
	$(CC) -o primesieve ./src/primesievemain.c primesieve.o -lm -O2

primesieve.o: ./src/primesieve.c
	$(CC) -fPIC -o primesieve.o ./src/primesieve.c -c -O2

semiprimesieve: ./src/semiprimesievemain.c semiprimesieve.o primesieve.o
	$(CC) -o semiprimesieve ./src/semiprimesievemain.c semiprimesieve.o primesieve.o -lm -O2

semiprimesieve.o: ./src/semiprimesieve.c
	$(CC) -o semiprimesieve.o ./src/semiprimesieve.c -c -O2

primesievejni.o: ./src/primesievejni.c
	$(CC) -fPIC -c ./src/primesievejni.c -o primesievejni.o -I/usr/lib/jvm/default-java/include -I/usr/lib/jvm/default-java/include/linux -O2
	
libprimesievejni.so: primesievejni.o primesieve.o
	$(CC) -shared -fPIC -o libprimesievejni.so primesievejni.o primesieve.o -lm

java: libprimesievejni.so
	javac ./src/Application.java

fast: ./src/primesieve.c
	$(CC) -o primesieve.o ./src/primesieve.c -c -O2 -march=native
	$(MAKE) primesieve

clean:
	rm *.o
