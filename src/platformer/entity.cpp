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

#include "entity.h"
#include "../room.h"
#include "../graphics.h"

#include <iostream>
#include <algorithm>
using namespace std;

bool tileAdd(int r) {
	if (r != 0) return true;
	else return false;
}

Entity::Entity(Sprite *sprite, float x, float y, char d) : Object(sprite, x, y, d) {
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	depth = d;
	xspeed = 0;
	yspeed = 0;
}

/*Entity::Entity(float x, float y) {
	this->sprite = nullptr;
	this->x = x;
	this->y = y;
	depth = 0;
	xspeed = 0;
	yspeed = 0;
}*/

Entity::~Entity() {

}

bool Entity::collidesOn(char dir) {
	return collision[dir];
}

void Entity::bindJoystick(Joystick *j) {
	joystick = j;
}

void Entity::update() {
	/*   MOVIMIENTO GENERAL   */
	// Ajustar cuándo se considera que está en el suelo
	if (y+sprite->getHeight() >= gRoom->getHeight()) {
		onGround = true;
		y = gRoom->getHeight() - sprite->getHeight();
	} else onGround = false;

	/*-----------------------------------------------------------------*/
	/*-----------------------CHECK COLLISIONS--------------------------*/
	/*-----------------------------------------------------------------*/
	
	// Part 1: Know how much tiles further up or left/right to check:

	/*div_t divresult = div(y+sprite->getHeight(), gRoom->tileheight);
	int ytile = divresult.quot + tileAdd(divresult.rem);
	divresult = div(x+sprite->getWidth(), gRoom->tilewidth);
	int xtile = divresult.quot + tileAdd(divresult.rem);

	div_t divresult = div(  );


	cout << "xtile: " << xtile << " ytile: " << ytile << endl;
	if (xspeed > 0) {
		if (gRoom->pmap[ytile-1][xtile+1] == gRoom->pfirstgid) {

		}
	} else if (xspeed < 0) {

	} if (yspeed > 0) {

	} else if (yspeed < 0) {

	}*/

	// Aplicar gravedad
	if (!onGround) {
		if (yspeed < 0 && joystick->getBtn(0)) {
			yspeed += JUMPING_GRAVITY;
		} else {
			yspeed += GRAVITY;
		}
	}
	// Limitar gravedad
	if (yspeed > MAX_VY) yspeed = MAX_VY;
	// Acelerar horizontalmente
	if (joystick->getDir(2)) {
		if (onGround) xspeed -= WALK_ACCEL; else xspeed -= AIR_ACCEL;
		facing = false;
	}
	if (joystick->getDir(3)) {
		if (onGround) xspeed += WALK_ACCEL; else xspeed += AIR_ACCEL;
		facing = true;
	}
	// Limitar aceleración
	if (xspeed < -MAX_VX) xspeed = -MAX_VX;
	else if (xspeed > MAX_VX) xspeed = MAX_VX;
	// Fricción con el suelo
	if (onGround) {
		if (xspeed > 0) {
		 	xspeed = max(0.0f, xspeed-FRICTION);
		} else if (xspeed < 0) {
			xspeed = min(0.0f, xspeed+FRICTION);
		}
	}
	// Saltos
	if (onGround && joystick->getBtn(0)) yspeed = -JUMP_SPEED;
	/*   MOVIMIENTO GENERAL   */
	x += xspeed;
	y += yspeed;
	//cout << "onGround: " << onGround << endl;
	//cout << "yspeed: " << yspeed << endl;
	//cout << "xspeed: " << xspeed << endl;

	if (y+sprite->getHeight() > gRoom->getHeight()) {
		y = gRoom->getHeight()-sprite->getHeight();
	}

	//! Default Sprite facing is left, so change this is it's not your case.
	/*! When facing left, \link facing \endlink is equal to false. */
	if (facing) sprFlip = SDL_FLIP_HORIZONTAL;
	else sprFlip = SDL_FLIP_NONE;

	/*Object::update();

	if (facing) rect.x += 4;*/
}

void Entity::updateSpr() {
	Object::updateSpr();
	if (facing) rect.x += 4;
}