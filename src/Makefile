CFLAGS ?= -g -Wall
LDLIBS += -lpulse -lpulse-simple -lm

barva: barva.o input.o opts.o color.o output.o queue.o
barva.o: input.h opts.h color.h output.h queue.h
input.o: input.h errorcodes.h
opts.o: opts.h color.h output.h errorcodes.h
color.o: color.h
output.o: output.h color.h
queue.o: queue.h
