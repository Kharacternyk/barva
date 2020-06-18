debug: format check build
	@./barva

profile: build-profile
	@./barva && gprof barva

build:
	@gcc -o barva -Wall *.c -lpulse -lpulse-simple -lm

build-profile:
	@gcc -pg -O3 -o barva -Wall *.c -lpulse -lpulse-simple -lm

check:
	@cppcheck --suppress=missingIncludeSystem --template=gcc \
	          --quiet --platform=unix64 --enable=all *.c

format:
	@astyle --formatted --project *.c *.h

graph:
	@cinclude2dot | xdot -

