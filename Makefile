# This Makefile will generate a shared library (.so) and a static library (.a)

CoreSources=graphics.cpp options.cpp room.cpp object.cpp pause.cpp script.cpp gui.cpp joystick.cpp
ImplSources= entity.cpp
Lib=libS2M.so

CFlags=-std=c++11 -c -fPIC #-g #-Ofast
LDFlags=-lSDL2 -lSDL2_image
ObjDir=obj/
CoreDir=src/
ImplDir=src/platformer/
LibDir=lib/

CC=g++
RM=rm

#!!!!!DO NOT EDIT ANYTHING UNDER THIS LINE!!!!!
Objects=$(CoreSources:.cpp=.o) $(ImplSources:.cpp=.o)
CCoreSources=$(addprefix $(CoreDir),$(CoreSources))
CImplSources=$(addprefix $(ImplDir),$(ImplSources))
CObjects=$(addprefix $(ObjDir),$(Objects)) $(addprefix $(ObjDir),$(Objects2))
LibFile=$(addprefix $(LibDir),$(Lib))

all: directories test

test: $(LibFile)

directories: $(ObjDir) $(LibDir)

$(ObjDir):
	mkdir -p $(ObjDir)

$(LibDir):
	mkdir -p $(LibDir)

$(LibFile): $(CObjects)
	$(CC) -shared -std=c++11 -o $(LibFile) $(CObjects)
	ar ruv lib/libS2M.a $(CObjects)

$(ObjDir)%.o: $(CoreDir)%.cpp 
	$(CC) $(CFlags) $< $(LDFlags) -o $@
	
$(ObjDir)%.o: $(ImplDir)%.cpp
	$(CC) $(CFlags) $< $(LDFlags) -o $@

clean:
	$(RM) -rf obj/*o lib/*
	rmdir lib obj
