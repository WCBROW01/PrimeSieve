CC=gcc

primesieve: ./src/primesievemain.c primesieve.o
	$(CC) -o primesieve ./src/primesievemain.c primesieve.o -lm -O2

primesieve.o: ./src/primesieve.c
	$(CC) -o primesieve.o ./src/primesieve.c -c -lm -O2

semiprimesieve: ./src/semiprimesievemain.c semiprimesieve.o primesieve.o
	$(CC) -o semiprimesieve ./src/semiprimesievemain.c semiprimesieve.o primesieve.o -lm -O2

semiprimesieve.o: ./src/semiprimesieve.c
	$(CC) -o semiprimesieve.o ./src/semiprimesieve.c -c -lm -O2

fast:
	$(CC) -o primesieve.o ./src/primesieve.c -c -lm -O2 -march=native
	$(MAKE) primesieve

clean:
	rm *.o
