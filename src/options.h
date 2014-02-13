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

#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
using namespace std;

//! Serves as a deposit for all the game parameters.
/*!
 * Stores all the game options and adjustments and provides methods for setting
 * and retrieving them.
 */
class Options {
public:
	//! The constructor.
	/*!
	 * \param filename the config filename from where to load all the configurations
	 */
	Options(string filename);

	//! Adjusts the scaling parameter.
	/*!
	 * \param s the scale integer
	 */
	void setScale(int s);

	//! Gets the scaling parameter.
	/*!
	 * \return The scaling integer.
	 */
	int getScale();
	
private:
	//! Loads all parameters from a file and stores them inside its variables.
	/*!
	 * \param filename the config filename from where to load all the configurations
	 */
	void loadConfigFile(string filename);
	int scale;
};

#endif