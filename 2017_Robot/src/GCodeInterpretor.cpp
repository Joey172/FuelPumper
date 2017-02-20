/*
 * GCodeInterpretor.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: colin
 */

#include <GCodeInterpretor.h>
#include <cmath>
using namespace std;

GCodeInterpretor::GCodeInterpretor() {
	// TODO: Find out correct filepath.
	m_file.open("lvuser/gcode.txt");
}

GCodeInterpretor::~GCodeInterpretor() {
}
void GCodeInterpretor::GetParams(const std::string &gcodeStr, const std::string paramStr) {
    for(unsigned i = 0; i < paramStr.size(); i++) {
        auto pos = gcodeStr.find(paramStr[i], 0);
        if(pos == string::npos) {
        	m_params[i] = 0;
        	continue;
        }
        m_params[i] = std::strtof(gcodeStr.data() + (pos + 1), nullptr);
    }
}

void GCodeInterpretor::Interpret() {
	string gcode_str;
    string paramStr;
    int code;
    char commandGroup;
	//reads gcode file line by line and calls appropriate function.
	while(!m_file.eof()) {
		//TODO: Find out if code needs to be modified to be able to execute multiple commands on one line.
		//TODO: Find out if M-Code functionality should be added.
		getline(m_file, gcode_str);
		auto pos = gcode_str.find('G', 0);

		code = atoi(gcode_str.data() + pos + 1);
		printf("G%i\n", code);

		switch(code) {
			case 1: // G01: linear movement.
				paramStr = "XYF";
				GetParams(gcode_str, paramStr);
				// TODO Put function call w/ params here.
				break;
			case 2: case 3: // G02/G03: clockwise/counter clockwise movement.
				paramStr = "XYIJF";
				GetParams(gcode_str, paramStr);
				// TODO Put function call w/ params here.
				break;
			case 4: // G4 Dwell.
				paramStr = "P";
				GetParams(gcode_str, paramStr);
				break;
			default:
				printf("GCode %i not yet implemented\n", code);
		}
		for(unsigned i = 0; i < paramStr.size();i++) {
			printf("%c: %f\n", paramStr[i], m_params[i]);
		}
	}
}

