debug: format check
	gcc -o barva -Wall *.c -lpulse -lpulse-simple -lm

release: format check
	gcc -o barva -DNDEBUG -O3 -Wall *.c -lpulse -lpulse-simple -lm

format:
	astyle --formatted --project *.c *.h

check:
	cppcheck --template=gcc --quiet --platform=unix64 --enable=all *.c
