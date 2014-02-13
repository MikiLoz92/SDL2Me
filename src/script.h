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

#include <string>
#include <map>
#include <vector>
using namespace std;

//! \cond HIDDEN_SYMBOLS
struct command {
	// The instruction (may be PRN, MSG, TRA, whatever).
	int itn;
	std::vector<int> intArgs;
	std::vector<std::string> strArgs;
};

struct event {
	// The event number defined in the script.
	int eventNo;
	// The commands vector.
	std::vector<command> cmds;
};
//! \endcond

extern map<string, unsigned char> itnMap;

namespace S2M_Script {
	vector<string> &SplitString(const string &s, char delim, vector<string> &elems);
	vector<string> SplitString(const string &s, char delim);
	string ReadFile(const char *filename);
	vector<string> FindAllStrings(string line) ;
	command ParseCommand(string line);
	vector<event> ParseFile(string filename);
}