CPP = g++
CPPFLAGS = -g -Wall

INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = 

all: reversebinary

reversebinary: reversebinary.o
	$(CPP) -o reversebinary $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CPP) -o $@ -c $(CPPFLAGS) $< $(INCFLAGS)

clean:
	rm -f *.o reversebinary

.PHONY: all
.PHONY: clean
