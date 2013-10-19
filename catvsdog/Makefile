CPP = g++
CPPFLAGS = -g -Wall

INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = 

all: catvsdog

catvsdog: catvsdog.o
	$(CPP) -o catvsdog $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CPP) -o $@ -c $(CPPFLAGS) $< $(INCFLAGS)

clean:
	rm -f *.o catvsdog

.PHONY: all
.PHONY: clean
