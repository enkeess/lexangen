#ifndef STATE_NAME_H
#define STATE_NAME_H

#include <map>
#include<string>

enum STATE_NAME {
	MAIN,
	MAIN_A,
	MAIN_B,
	ERROR,
	EMPTY_STR,
	FILE_END
};

extern std::map<STATE_NAME, std::string> mapStateName;

#endif