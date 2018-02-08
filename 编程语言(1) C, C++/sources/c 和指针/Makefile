CC = gcc
LIBS += -lpthread
EXECUTE = aaa

OBJECTS = \
main.o my_stdlib.o variable_argument_lists.o

all: $(EXECUTE)
$(EXECUTE): $(OBJECTS)
	@echo "start the linking operation: "
	$(CC)    -o $(EXECUTE) $(OBJECTS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(EXECUTE) $(OBJECTS)
