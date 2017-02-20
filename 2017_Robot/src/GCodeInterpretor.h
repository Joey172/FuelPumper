/*
 * GCodeInterpretor.h
 *
 *  Created on: Feb 18, 2017
 *      Author: colin
 */

#ifndef SRC_GCODEINTERPRETOR_H_
#define SRC_GCODEINTERPRETOR_H_
#include <string>
#include <fstream>

class GCodeInterpretor {

	std::ifstream m_file;
	float m_params[5];

	//calculates paramaters of a gcode command.
	// if no paramater is found
	void GetParams(const std::string &gcodeStr, const std::string paramStr);
public:
	GCodeInterpretor();
	virtual ~GCodeInterpretor();
	void Interpret();
};

#endif /* SRC_GCODEINTERPRETOR_H_ */
