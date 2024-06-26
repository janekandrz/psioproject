OBJDIR := obj
SRCDIR := code
LIBDIR := src/lib
INCDIR := src/include

CPPFILES := $(wildcard $(SRCDIR)/*.cpp)
OBJFILES := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(CPPFILES))

all: compile link

compile: $(OBJFILES)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ -I$(INCDIR) -c $< -o $@

link:
	g++ $(OBJFILES) -o main -L$(LIBDIR) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio