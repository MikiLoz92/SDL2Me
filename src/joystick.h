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

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <SDL2/SDL.h>
//#include "../core/input.h"

//! Representation of game buttons/keys.
/*! A Joystick is a representation of the game buttons.
 * It is useful if we bond it to a Hero instance: then it will follow the
 * user's input. When we bond a VirtualJoystick to a Hero it will stop following
 * our input and start following game compiled (or scripted) directives. */
class Joystick {
public:
	Joystick();
	bool getDir(int i);
	bool getBtn(int i);
	bool getDirPressed(int i);
	bool getBtnPressed(int i);
	void update();
private:
	//! Main directions of a 2D game.
	bool dir[4] = {false,false,false,false};
	//! Amount of buttons that will be used.
	bool btn[4] = {false,false,false,false};
	//! Main directions of a 2D game (Just pressed state).
	bool dirPressed[4] = {false,false,false,false};
	//! Amount of buttons that will be used (Just pressed state).
	bool btnPressed[4] = {false,false,false,false};
};

extern Joystick *gJoystick;

void S2M_UpdateJoystick();

//! Virtual representation of game buttons/keys.
/*! Careful, because this may be confusing:
 * A VirtualJoystick is a virtual representation of the game buttons.
 * It is useful whenever we want to make an Entity move, because assigning
 * a Joystick to it (if it doesn't already have one, which is probable since
 * it is created by the constructor) we can code the Joystick's buttons pressed 
 * and, therefore, make the Entity move. */
class VirtualJoystick: Joystick {

};

#endif