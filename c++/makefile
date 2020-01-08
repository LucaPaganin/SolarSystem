SRCDIR = src
INCDIR = inc
OBJDIR = obj

CC = g++
CCFLAGS = -std=c++11 -Wall -g -I $(INCDIR)/

#Get sources in the $(SRCDIR) using the wildcard
SRCS = $(wildcard $(SRCDIR)/*.cpp)

#Use patsubst to get all object files corresponding to each .cpp in $(SRCDIR)
#Syntax is:
# $(patsubst pattern,replacement,$(var))
#where var is the variable on which the pattern substitution has to be applied
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

TARGET = main

$(TARGET): $(OBJDIR)/$(TARGET).o $(OBJS)
	$(CC) $(CCFLAGS) -o $(TARGET) $^

$(OBJDIR)/$(TARGET).o: main.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
