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

using namespace std;

int main( int argc, char* args[] ) {

	S2M_CreateGraphics(320,240,"Sprite Test");

	GameData gData = GameData();
	gData.setInt("sprites", 9);
	cout << gData.getInt("sprites") << endl;

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