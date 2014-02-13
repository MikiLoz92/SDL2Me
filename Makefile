# This Makefile will generate a shared library (.so)

CoreSources=graphics.cpp options.cpp room.cpp object.cpp pause.cpp script.cpp gui.cpp joystick.cpp
ImplSources= entity.cpp
Lib=libS2M.so

CFlags=-std=c++11 -c -fPIC #-g #-Ofast
LDFlags=-lSDL2 -lSDL2_image
ObjectDir=obj/
CoreDir=src/
ImplDir=src/platformer/
LibDir=lib/

CC=g++
RM=rm

#!!!!!DO NOT EDIT ANYTHING UNDER THIS LINE!!!!!
Objects=$(CoreSources:.cpp=.o) $(ImplSources:.cpp=.o)
CCoreSources=$(addprefix $(CoreDir),$(CoreSources))
CImplSources=$(addprefix $(ImplDir),$(ImplSources))
CObjects=$(addprefix $(ObjectDir),$(Objects)) $(addprefix $(ObjectDir),$(Objects2))
LibFile=$(addprefix $(LibDir),$(Lib))

all: test

test: $(LibFile)

$(LibFile): $(CObjects)
	$(CC) -shared -std=c++11 -o $(LibFile) $(CObjects)

$(ObjectDir)%.o: $(CoreDir)%.cpp 
	$(CC) $(CFlags) $< $(LDFlags) -o $@
	
$(ObjectDir)%.o: $(ImplDir)%.cpp
	$(CC) $(CFlags) $< $(LDFlags) -o $@

clean:
	$(RM) -rf obj/*o game
