CC = g++
CCFLAGS = -std=c++11 -Wall -g -Iinc/

TARGET = main

$(TARGET): $(TARGET).o Vettore3D.o Grave.o SistemaSolare.o
	$(CC) $(CCFLAGS) -o $(TARGET) $^

$(TARGET).o: main.cpp
	$(CC) $(CCFLAGS) -c $<

%.o: src/%.cpp
	$(CC) $(CCFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o $(TARGET)
