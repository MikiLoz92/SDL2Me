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

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "graphics.h"
#include "options.h"
#include "object.h"
#include "room.h"
#include "pause.h"
#include "script.h"
#include "joystick.h"
#include "gui.h"
#include "defines.h"

using namespace std;

//! Manual S2M function for instance creation. Used by the end-user.
template <class T>
Object *S2M_CreateInstance(Sprite *sprite, float x, float y, char d) {
	Object *obj = new T(sprite, x, y, d);
	gRoom->addObject(obj);
	return obj;
}

//! Automatic S2M function for instance creation. Used in the engine.
template <class T>
Object *S2M_CreateInstance(float x, float y, Room *r = nullptr) {
	cout << x << "-----" << y << endl;
	Object *obj = new T(x, y);
	if (r) r->addObject(obj);
	else gRoom->addObject(obj);
	return obj;
}

template <class T>
Room *S2M_CreateRoom() {
	return new T();
}

template <class T>
Room *S2M_CreateRoom(int w, int h) {
	T *room = new T(w,h);
	return room;
}

template <class T>
Room *S2M_CreateRoom(string filename, string scriptname, map <string, Object *(*)(float, float, Room*)> objectMap) {
	T *room = new T(filename, scriptname);
	room->parseObjects(objectMap);
	return room;
}

void S2M_SetRoom(Room *room) {
	gRoom = room;
}

template <class T>
void S2M_GoToRoom(Room *room) {
	gGraphics->setTransition(new T(S2M_TRANSITION_CLOSE, false));
	gRoom->nextRoom = room;
}

void S2M_UpdateRoom() {
	gRoom->update();
}

void S2M_Update() {
	S2M_UpdateRoom();
	S2M_UpdateGraphics();
}