primesieve: ./src/primesieve.c ./src/primesievemain.c
	gcc -o primesieve ./src/primesieve.c ./src/primesievemain.c -lm -O2
	
primesievebool: ./src/primesievebool.c
	gcc -o primesievebool ./src/primesievebool.c -lm -O2
