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
#include "gamedata.h"
#include "defines.h"

using namespace std;

//! Creates a Sprite and registers it on the Graphics sprite vector.
/*! \param filename the bitmap filename where all the sprite images are to be loaded
 * \param w the width of each image
 * \param h the height of each image
 * \return A pointer to the recently created Sprite. */
template <class T = Sprite>
Sprite *S2M_CreateSprite(string filename, int w, int h) {
	Sprite *sprite = new T(filename, w, h);
	return sprite;
}

//! Manual S2M function for instance creation. Used by the end-user.
template <class T>
Object *S2M_CreateInstance(Sprite *sprite, float x, float y, char d, Room *r = nullptr) {
	Object *obj = new T(sprite, x, y, d);
	if (r) r->addObject(obj);
	else gRoom->addObject(obj);
	return obj;
}

//! Automatic S2M function for instance creation. Used in the engine.
template <class T>
Object *S2M_CreateInstance(float x, float y, Room *r = nullptr) {
	Object *obj = new T(x, y);
	if (r) r->addObject(obj);
	else gRoom->addObject(obj);
	return obj;
}
/*
//! Manual S2M function for entity creation. Used by the end-user.
Object *S2M_CreateEntity(Sprite *sprite, float x, float y, char d) {
	cout << "Creating Entity!" << endl;
	Object *ent = new Entity(sprite, x, y, d);
	gRoom->addObject(ent);
	return ent;
}

//! Automatic S2M function for entity creation. Used in the engine.
Object *S2M_CreateEntity(float x, float y, Room *r = nullptr) {
	cout << "Creating Entity!" << endl;
	Object *ent = new Entity(x, y);
	if (r) r->addObject(ent);
	else gRoom->addObject(ent);
	return ent;
}*/

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
	if (!gGraphics->getTransition()) {
		gGraphics->setTransition(new T(S2M_TRANSITION_CLOSE, false));
		gRoom->nextRoom = room;
	}
}

void S2M_UpdateRoom() {
	if (gRoom) gRoom->update();
	else cerr << "Error: Trying to update Room but no Room currently set. Please use S2M_SetRoom() to define a current Room." << endl;
}

void S2M_Update() {
	S2M_UpdateRoom();
	S2M_UpdateGraphics();
}

void S2M_ExitGame() {
	delete gGraphics;
	delete gRoom;
	cout << "Exiting SDL2Me... Goodbye!" << endl;
}