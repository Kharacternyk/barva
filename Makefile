release:
	@gcc -o barva -O3 -march=native src/*.c -lpulse -lpulse-simple -lm

