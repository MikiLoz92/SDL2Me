//__________________________________________________________________________
//      _________________   ____    ________    _____                       |
//     /   _____/\______ \ |    |   \_____  \  /     \   ____               |
//     \_____  \  |    |  \|    |    /  ____/ /  \ /  \_/ __ \              |
//     /        \ |    `   \    |___/       \/    Y    \  ___/              |
//    /_______  //_______  /_______ \_______ \____|__  /\___ \              |
//            \/         \/        \/       \/       \/     \/              |
//__________________________________________________________________________|
//
// Copyright © 2013 Miguel Vera Belmonte AKA MikiLoz92.
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "../../src/S2M.h"
#include "../../src/S2M_Platformer.h"
#include "../../src/transitions/TFlipExpo.h"
#include "healthbar.h"

int main( int argc, char* args[] ) {

	S2M_CreateGraphics();

	map <string, Object *(*)(float, float, Room*)> objectMap {
		{ "Warp", &S2M_CreateInstance<Warp> }
	};

	Room *room = S2M_CreateRoom<Room>("res/map.tmx", "res/script.txt", objectMap);
	S2M_SetRoom(room);

	Room *room2 = S2M_CreateRoom<Room>("res/map2.tmx", "res/script.txt", objectMap);

	Background bg0 = Background("res/gfx/csbg0.png", S2M_BGSTYLE_STATIC, 0, 0, -1);
	Background bg1 = Background("res/gfx/csbg1.png", S2M_BGSTYLE_PARALLAX, -0.25, 0, 4);
	Background bg2 = Background("res/gfx/csbg2.png", S2M_BGSTYLE_PARALLAX, -0.5, 0, 3);
	Background bg3 = Background("res/gfx/csbg3.png", S2M_BGSTYLE_PARALLAX, -1, 0, 2);
	Background bg4 = Background("res/gfx/csbg4.png", S2M_BGSTYLE_PARALLAX, -1.5, 0, 1);
	S2M_Room::AddBackground(&bg3);
	S2M_Room::AddBackground(&bg1);
	S2M_Room::AddBackground(&bg4);
	S2M_Room::AddBackground(&bg2);
	S2M_Room::AddBackground(&bg0);

	Background bg20 = Background("res/gfx/bgForest0.png", S2M_BGSTYLE_STATIC, 0, 0, -1);
	room2->addBackground(&bg20);

	Sprite *sprNate = S2M_CreateSprite("res/gfx/nate.bmp",16,16);
	sprNate->setCenter(7,0);
	Sprite *sprQuote = S2M_CreateSprite("res/gfx/quote.png",16,16);
	Sprite *sprNeko = S2M_CreateSprite("res/gfx/luffy2.png",32,32);

	Entity *objNate = S2M_CreateEntity(sprNate, 192, 0,1);
	Entity *objNeko = S2M_CreateEntity(sprNeko, 16, 16,1);
	Entity *objQuote = S2M_CreateEntity(sprQuote, 8,8,1);
	objNate->bindJoystick(gJoystick);
	sprNate->addAnimation({0,1,2,3});
	objNate->setAnimation(0);

	Camera gCamera = Camera(objNate);
	gRoom->setCamera(&gCamera);

	HealthBar h = HealthBar();
	HealthBar *healthBar = &h;
	ManaBar m = ManaBar();
	ManaBar *manaBar = &m;

	SDL_Event e;

	// Game Loop
	while (true) {

		if (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				//delete gGraphics;
				break;
			}
		}

		S2M_UpdateJoystick();

		// KEYBOARD CODE
		const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
		if( currentKeyStates[ SDL_SCANCODE_UP ] ) {
			objNate->setAnimation(-1);
		} else if( currentKeyStates[ SDL_SCANCODE_DOWN ] ) {
			objNate->setAnimation(-1);
		} else if( currentKeyStates[ SDL_SCANCODE_LEFT ] ) {
			objNate->setAnimation(0);
		} else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ) {
			objNate->setAnimation(0);
		} else if( currentKeyStates[ SDL_SCANCODE_RETURN ] ) {
			break;
		} else if (currentKeyStates[SDL_SCANCODE_X]) { 
			gCamera.goTo(304+8,336+8,false);
			//gCamera.goTo(0,0,false);
		} else if (currentKeyStates[SDL_SCANCODE_C]) {
			gCamera.release();
		} else {
			objNate->setAnimation(-1);
			gCamera.setSpeed(0,0);
		}

		if (gJoystick->getBtnPressed(2)) {
			S2M_GoToRoom<TFlipExpo>(room2);
		}

	    S2M_Update();
	}

	exit(0);
}

