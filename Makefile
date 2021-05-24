# Sum Parallelization using Threads Makefile
#
#  Copyright (C) 2021 Richi Dubey <richidubey@gmail.com>
# 
#  This work is licensed under the terms of the GNU GPL, version 2.  See
#  the LICENSE file in the top-level directory.
#

CC = gcc
CFLAGS = -g
DEPS = main.h
LIBS = -lpthread

%.o: %.c $(DEPS)
	$(CC) $< $(CFLAGS) -c -o $@	

main: main.o sum_subset.o input.txt
	$(CC) -o main main.o sum_subset.o $(LIBS)

clean:
	rm main.o
	rm sum_subset.o
	rm main
