## Compiler
CC = x86_64-w64-mingw32-g++
CC32 = i686-w64-mingw32-g++

## Delete Commmand
DC = del

## Standard
STD = c++2a

## Executables Name
EXE = proj

## Project Directories
INCDIR = include
LIBDIR = lib
OBJDIR = obj
SRCDIR = src

## Define Source
SOURCE = Application.cpp Utils.cpp Template.cpp Task.cpp Callback.cpp File.cpp Color.cpp
OBJECT = $(SOURCE:.cpp=.o)
LIBS = ESN

## Define File
SRC = $(addprefix $(SRCDIR)/, $(SOURCE))
OBJ = $(addprefix $(OBJDIR)/, $(OBJECT))
LIB = $(addprefix -l, $(LIBS))

## Define Flags
CFLAGS = -c -O2 -Wall -std=$(STD) -I$(INCDIR)
LFLAGS = -L$(LIBDIR) $(LIB)


## Define Scope
all : $(SRC) $(EXE)

## Compile C++ Files
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $< $(CFLAGS) -o $@


## Link Object Files
$(EXE) : $(OBJ)
	$(CC) $^ $(LFLAGS) -o $@

## Clean Object Files
clean : $(subst /,\,$(OBJ))
	$(DC) $^