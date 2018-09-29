CC=g++
IDIR=include
CFLAGS=-I$(IDIR)
DEPS= $(IDIR)/jpf/jpf.h

demo: demo.cpp $(DEPS)
	$(CC) $(CFLAGS) -o demo demo.cpp

clean:
	rm demo
