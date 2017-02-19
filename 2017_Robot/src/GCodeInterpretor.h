/*
 * GCodeInterpretor.h
 *
 *  Created on: Feb 18, 2017
 *      Author: colin
 */

#ifndef SRC_GCODEINTERPRETOR_H_
#define SRC_GCODEINTERPRETOR_H_
#include <string>
class GCodeInterpretor {
public:
	GCodeInterpretor();
	virtual ~GCodeInterpretor();

	void Interpret(std::string str);
};

#endif /* SRC_GCODEINTERPRETOR_H_ */
