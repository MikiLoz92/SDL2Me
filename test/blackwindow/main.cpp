#include "../../src/S2M.h"
#include "../../src/S2M_Platformer.h"

int main( int argc, char* args[] ) {

	S2M_CreateGraphics();
	Room *room = S2M_CreateRoom<Room>();
	S2M_SetRoom(room);

	SDL_Event e;

	while (true) {

		if (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}

	S2M_Update();

	}

	return 0;

}