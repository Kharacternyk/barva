debug:
	gcc -o barva -Wall src/*.c -lpulse -lpulse-simple -lm

release:
	gcc -o barva -DNDEBUG -O3 -Wall src/*.c -lpulse -lpulse-simple -lm
