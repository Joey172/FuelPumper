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
	// TODO Auto-generated constructor stub

}

GCodeInterpretor::~GCodeInterpretor() {
	// TODO Auto-generated destructor stub
}
void GetParams(string gcodeStr, float *params, string paramStr) {
    for(unsigned i = 0; i < paramStr.size(); i++) {
        auto pos = gcodeStr.find(paramStr[i], 0);
        if(pos == string::npos) {
        	params[i] = 0;
        	continue;
        }
        params[i] = std::strtof(gcodeStr.data() + (pos + 1), nullptr);
    }
}
void GCodeInterpretor::Interpret(std::string str) {
    string gcode_str =  "G02 X27 Y47 I120 J4967 E32 F20";
    string paramStr = "";
  	auto pos = gcode_str.find('G', 0);
  	pos+=1;
	float params[5] = {0};

	int code;

	code = atoi(gcode_str.data() + pos);
    printf("code: %i\n", code);
	switch(code) {
	case 1: // G01 Xnn Ynn Znn Fnn
		paramStr = "XYF";
        GetParams(gcode_str, params, paramStr);
        for(unsigned i = 0; i < paramStr.size();i++ ){
           	printf("param %c: %f\n", paramStr[i], params[i]);
        }
		break;
	case 2: case 3: // G02 Xnnn Ynnn Innn Jnnn Enn Fnnn
		// doesn't use E params.
		paramStr = "XYIJF";
        GetParams(gcode_str, params, paramStr);
        for(unsigned i = 0; i < paramStr.size();i++) {
           	printf("param %c: %f\n", paramStr[i], params[i]);
        }
		break;
	}
}

