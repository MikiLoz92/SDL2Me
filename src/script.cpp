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

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

#include "script.h"

using namespace std;

map<string, unsigned char> itnMap {
	{"lock", 0},
	{"faceplayer", 1}, 
	{"message", 2},
	{"nod", 3},
	{"transport", 4}
};

//! Scripting operations are included here.
namespace S2M_Script {

	vector<string> &SplitString(const string &s, char delim, vector<string> &elems) {
	    stringstream ss(s);
	    string item;
	    while (std::getline(ss, item, delim)) {
	        if (item != "" && item != "\n") elems.push_back(item);
	    }
	    return elems;
	}

	vector<string> SplitString(const string &s, char delim) {
	    vector<string> elems;
	    SplitString(s, delim, elems);
	    return elems;
	}

	string ReadFile(const char *filename) {
	  ifstream in(filename, std::ios::in | std::ios::binary);
	  if (in) {
	    string contents;
	    in.seekg(0, std::ios::end);
	    contents.resize(in.tellg());
	    in.seekg(0, std::ios::beg);
	    in.read(&contents[0], contents.size());
	    in.close();
	    return(contents);
	  }
	}

	vector<string> FindAllStrings(string line) {
		vector<string> strArgs;
		string lineStringFree = line;
		int end = -1;
		while (true) {
			int start = line.find('"',end+1);
			//lineStringFree = line.substr(end+1, start-end-1);
			if (start != string::npos) {
				// El END serà aquél carácter que no tenga \ antes
				int possibleEnd = start;
				while (true) {
					possibleEnd = line.find('"', possibleEnd+1);
					if ( line[possibleEnd-1] != '\\' ) {
						end = possibleEnd;
						break;
					} if (possibleEnd == string::npos) break; // Seguro anti bucle infinito
				} if ( possibleEnd == string::npos) break; // Seguro anti bucle infinito
			} else break;
			string s = line.substr(start+1, end-start-1);
			// Borramos todos los \, si los hay
			int b = -1;
			while (true) {
				b = s.find('\\',b+1);
				if (b != string::npos && s[b-1] != '\\') s.replace(b,1,"");
				else break;
			} strArgs.push_back(s);
		}
		return strArgs;
	}

	command ParseCommand(string line) {
		command cm;
		vector<string> strArgs = FindAllStrings(line);
		vector<string> tokens = SplitString(line, ' ');
		cm.itn = itnMap[tokens[0]];
		int strCounter = 0;
		//cout << "Tokens size: " << tokens.size() << endl;
		for (int i = 1; i < tokens.size(); i++) {
			if (tokens[i][0] == '"') {
				int j = i+1;
				//cout << "i: " << i << endl;
				if (tokens[i].back() != '"' || ( tokens[i].back() != '"' && tokens[i].substr(tokens[i].size()-2,1) != "\\" ) ) {
					while (true) {
						//cout << "j: " << j << endl;
						if ( tokens[j].back() == '"' && tokens[j].substr(tokens[j].size()-2,1) != "\\" ) {
							//cout << "Something wicked" << endl;
							i = j;
							break;
						} else j++;
					}
				} else i = j-1;
				cm.strArgs.push_back(strArgs[strCounter]); cm.intArgs.push_back(-1); strCounter++;
			} else { cm.intArgs.push_back(atoi(tokens[i].c_str())); cm.strArgs.push_back(""); }
		} return cm;
	}

	vector<event> ParseFile(string filename) {
		std::string archivo = S2M_Script::ReadFile(filename.c_str());
		std::vector<std::string> lines = S2M_Script::SplitString(archivo,'\n');
		std::vector<event> events;
		int i = 0;
		while (true) {
			// Buscamos una línea que empiece por #
			if (lines[i].substr(0,1) == "#") {
				// ¡Nuevo evento!
				break;
			} else {
				//
				// TODO: Lo parseamos como si fuera la cabecera del mapa
				//
			}
			i++;
		}
		int j = i;
		while (true) {
			event ev;
			cout << "Parseando un evento..." << endl;
			ev.eventNo = atoi(lines[j].substr(1).c_str());
			int k = j+1;
			while (true) {
				// Parseamos cada línea
				cout << "Parseando una línea..." << endl;
				command cm = S2M_Script::ParseCommand(lines[k]);
				ev.cmds.push_back(cm);
				// Recorremos el 
				if (lines[k].substr(0,1) == "#") {
					// ¡Nuevo evento!
					j = k;
					break;
				}
				if (k < lines.size()-1) k++;
				else break;
			} cout << "Hasta aquí llegamos" << endl;
			events.push_back(ev);
			if (k == lines.size()-1) break;
		} cout << "Hasta aquí llegamos+" << endl;
		return events;
	}

}

/*
int main( int argc, char* args[] ) {

	vector<event> events = S2M_Script::ParseFile("test2.txt");
	for (int i = 0; i < events.size(); i++) {
		cout << "### Event: " << events[i].eventNo << " ###" << endl;
		for (int j = 0; j < events[i].cmds.size(); j++) {
			cout << "itn" << events[i].cmds[j].itn;
			for (int k = 0; k < events[i].cmds[j].intArgs.size(); k++) {
				if (events[i].cmds[j].intArgs[k] != -1) cout << ". iARG" << events[i].cmds[j].intArgs[k];
				else if (events[i].cmds[j].strArgs[k] != "") cout << ". sARG\"" << events[i].cmds[j].strArgs[k] << "\"";
			} cout << endl;
		}
	}

	return 0;
}*/

/* Idea: Guardar en un vector todos los eventos cargados en cada mapa y ejecutar cada token uno por uno.
Ejemplo:
- Cargamos el mapa.
- Creamos un vector del tipo vector<vector <vector <string, 2>>>
                                    ^evento ^token  ^instruccion-argumentos
- Cada vez que se acceda a un evento (por ejemplo, pulsando Abajo en un NPC con un código de evento XXXX)
  se busca el número de ese evento en el vector y se ejecutan las instrucciones una por una.

 */