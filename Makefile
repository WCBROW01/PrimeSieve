primesieve: ./src/primesieve.c ./src/primesievemain.c
	gcc -o primesieve ./src/primesieve.c ./src/primesievemain.c -lm -O2
	
primesievebool: ./src/primesievebool.c
	gcc -o primesievebool ./src/primesievebool.c -lm -O2

semiprimesieve: ./src/semiprimesievemain.c ./src/semiprimesieve.c ./src/primesieve.c
	gcc -o semiprimesieve ./src/semiprimesievemain.c ./src/semiprimesieve.c ./src/primesieve.c -lm -O2
