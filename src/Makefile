debug: format check
	@gcc -o barva -Wall *.c -lpulse -lpulse-simple -lm

release:
	@gcc -o barva -O3 *.c -lpulse -lpulse-simple -lm

format:
	@astyle --formatted --project *.c *.h

check:
	@cppcheck --suppress=missingIncludeSystem --template=gcc \
	          --quiet --platform=unix64 --enable=all *.c
