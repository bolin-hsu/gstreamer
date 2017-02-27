CC=clang
CFLAGS += `pkg-config --cflags gobject-2.0`
CFLAGS += -g
LDFLAGS += `pkg-config --libs gobject-2.0`
SRCS = example.c writable_interface.c main.c
OBJECTS = example.o writable_interface.o main.o

all: main

main: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

clean:
	rm -f main $(OBJECTS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ -MF ./.depend;

include .depend
