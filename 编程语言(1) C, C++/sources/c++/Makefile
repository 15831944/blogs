CC = g++
EXECUTE = a.out
OBJECTS = main.o Coordinate.o

all: $(EXECUTE)
$(EXECUTE): $(OBJECTS)
	$(CC) -o $(EXECUTE) $(OBJECTS)

.PHONY: clean
clean:
	-rm -f $(EXECUTE) $(OBJECTS)
