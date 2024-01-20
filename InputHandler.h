#ifndef __INPUTHANDLER_H_DEFINED__
#define __INPUTHANDLER_H_DEFINED__

#include <vector>
#include <string>
#include <sstream>

class InputHandler {
	public:
		InputHandler();
		~InputHandler();

		int State;

		bool ParseInput(std::string);
		int SetState();

		std::vector<std::string> LastUserInput;
};

#endif
