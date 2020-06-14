debug: format check build
	@./barva

format:
	@astyle --formatted --project *.c *.h

check:
	@cppcheck --suppress=missingIncludeSystem --template=gcc \
	          --quiet --platform=unix64 --enable=all *.c
build:
	@gcc -o barva -Wall *.c -lpulse -lpulse-simple -lm

