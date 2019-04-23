CC=g++
CFLAGS=-c -Wall -Wextra -O2 -std=c++11
LDFLAGS=
SOURCES=main.cpp MovingObject.cpp World.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=missile_hit

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *.o $(EXECUTABLE)
