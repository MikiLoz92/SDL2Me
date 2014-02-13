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

#include "healthbar.h"
#include "../../src/graphics.h"

HealthBar::HealthBar() {
	background = gGraphics->loadTexture("res/gfx/healthbar.png",true);
	x = 8;
	y = 8;
}

HealthBar::~HealthBar() {

}

void HealthBar::draw() {
	gGraphics->drawTexture(background,x,y,64,8);
}

ManaBar::ManaBar() {
	background = gGraphics->loadTexture("res/gfx/manabar.png",true);
	x = 8;
	y = 16;
}

ManaBar::~ManaBar() {

}

void ManaBar::draw() {
	gGraphics->drawTexture(background,x,y,64,8);
}