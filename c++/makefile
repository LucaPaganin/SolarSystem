SRCDIR = src
INCDIR = inc
OBJDIR = obj

CC = g++
CCFLAGS = -std=c++11 -Wall -g -I $(INCDIR)/

TARGET = main

$(TARGET): $(OBJDIR)/$(TARGET).o $(OBJDIR)/Vettore3D.o $(OBJDIR)/Grave.o $(OBJDIR)/SistemaSolare.o
	$(CC) $(CCFLAGS) -o $(TARGET) $^

$(OBJDIR)/$(TARGET).o: main.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)
