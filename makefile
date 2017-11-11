CC=g++
CC_FLAGS=-c -Wall --std=c++11 -Iinc
CC_FLAGS += -I/usr/local/include -g
LDFLAGS  := -L/usr/local/lib -F/Library/Frameworks -framework SFML -framework sfml-audio -framework sfml-system -framework sfml-window -framework sfml-graphics
PROGRAM_NAME=pl2

CPP_FILES := $(wildcard src/*.cpp)
OBJDIR=obj
BINDIR=bin
OBJ_FILES := $(addprefix $(OBJDIR)/,$(notdir $(CPP_FILES:.cpp=.o)))

all: $(BINDIR)/pl2

.PHONY: clean rebuild

$(BINDIR)/pl2: $(OBJ_FILES)
	@echo "Compiling..."
	g++ $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

clean:
	rm -rf obj/* bin/*

rebuild: clean
	$(MAKE)

run: $(BINDIR)/pl2
	./$(BINDIR)/pl2
