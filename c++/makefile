SRCDIR = src
INCDIR = inc
OBJDIR = obj

CC = g++
CCFLAGS = -std=c++17 -Wall -g -I $(INCDIR)/

#Get sources in the $(SRCDIR) using the wildcard
SRCS = $(wildcard $(SRCDIR)/*.cpp)

#Use patsubst to get all object files corresponding to each .cpp in $(SRCDIR)
#Syntax is:
# $(patsubst pattern,replacement,$(var))
#where var is the variable on which the pattern substitution has to be applied
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

TARGET = main
TEST_TARGET = test

$(TARGET): $(OBJDIR)/$(TARGET).o $(OBJS)
	$(CC) $(CCFLAGS) -o $(TARGET) $^

$(OBJDIR)/$(TARGET).o: main.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

$(OBJDIR)/$(TEST_TARGET).o: test.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

test: $(OBJDIR)/$(TEST_TARGET).o $(OBJS)
	$(CC) $(CCFLAGS) -o $(TEST_TARGET) $^

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
