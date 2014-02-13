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

#include "joystick.h"

Joystick::Joystick() {

}

bool Joystick::getDir(int i) {
	return dir[i];
}

bool Joystick::getBtn(int i) {
	return btn[i];
}

bool Joystick::getDirPressed(int i) {
	return dirPressed[i];
}

bool Joystick::getBtnPressed(int i) {
	return btnPressed[i];
}

void Joystick::update() {
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	if (!dir[0] && currentKeyStates[SDL_SCANCODE_UP]) dirPressed[0] = true;
	else dirPressed[0] = false;
	if (!dir[1] && currentKeyStates[SDL_SCANCODE_DOWN]) dirPressed[1] = true;
	else dirPressed[1] = false;
	if (!dir[2] && currentKeyStates[SDL_SCANCODE_LEFT]) dirPressed[2] = true;
	else dirPressed[2] = false;
	if (!dir[3] && currentKeyStates[SDL_SCANCODE_RIGHT]) dirPressed[3] = true;
	else dirPressed[3] = false;

	if (!btn[0] && currentKeyStates[SDL_SCANCODE_Z]) btnPressed[0] = true;
	else btnPressed[0] = false;
	if (!btn[1] && currentKeyStates[SDL_SCANCODE_X]) btnPressed[1] = true;
	else btnPressed[1] = false;
	if (!btn[2] && currentKeyStates[SDL_SCANCODE_A]) btnPressed[2] = true;
	else btnPressed[2] = false;
	if (!btn[3] && currentKeyStates[SDL_SCANCODE_S]) btnPressed[3] = true;
	else btnPressed[3] = false;

	dir[0] = currentKeyStates[ SDL_SCANCODE_UP ];
	dir[1] = currentKeyStates[ SDL_SCANCODE_DOWN ];
	dir[2] = currentKeyStates[ SDL_SCANCODE_LEFT ];
	dir[3] = currentKeyStates[ SDL_SCANCODE_RIGHT ];
	btn[0] = currentKeyStates[ SDL_SCANCODE_Z ];
	btn[1] = currentKeyStates[ SDL_SCANCODE_X ];
	btn[2] = currentKeyStates[ SDL_SCANCODE_A ];
	btn[3] = currentKeyStates[ SDL_SCANCODE_S ];
}

//! Global Joystick pointer.
Joystick *gJoystick = new Joystick();

void S2M_UpdateJoystick() {
	gJoystick->update();
}