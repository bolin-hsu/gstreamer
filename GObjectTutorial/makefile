CFLAGS += `pkg-config --cflags gobject-2.0`
LDFLAGS += `pkg-config --libs gobject-2.0`
OBJECTS = example.o main.o

all: main

main: $(OBJECTS)
	@echo $(CFLAGS)
	@echo $(LDFLAGS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

clean:
	rm -f main $(OBJECTS)
