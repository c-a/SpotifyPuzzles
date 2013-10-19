CPP = g++
CPPFLAGS = -g -Wall

INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = 

all: zipfsong

zipfsong: zipfsong.o
	$(CPP) -o zipfsong $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CPP) -o $@ -c $(CPPFLAGS) $< $(INCFLAGS)

clean:
	rm -f *.o zipfsong

.PHONY: all
.PHONY: clean
