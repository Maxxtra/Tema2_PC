all: problema1 problema2 problema3

problema1: problema1.c
	gcc -Wall -std=c99 problema1.c -o problema1

problema2: problema2.c
	gcc -Wall -std=c99 problema2.c -o problema2

problema3: problema3.c
	gcc -Wall -std=c99 problema3.c -o problema3

clean:
	rm problema1
	rm problema2
	rm problema3
