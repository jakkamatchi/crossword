#include "InputHandler.h"

#include <string>
#include <sstream>
#include <iostream>

InputHandler::InputHandler() {
	State = 0;
}

InputHandler::~InputHandler() {

}

bool InputHandler::ParseInput(std::string InputString) {
	LastUserInput.resize(0);
	
	std::stringstream InputStream(InputString);
	std::string element;
	
	while(std::getline(InputStream, element, ' ')) {
			if(element.empty() == true) {
			}	
			else {
				LastUserInput.push_back(element);
			}
	}
	
	return true;
}

int InputHandler::SetState() {
	//KEYWORDS:
	//INVALID INPUT == 0
	
	//CLUE_NAME ANSWER == 1
	//CWD_QUIT == 2
	//CWD_REGEN == 3
	
	if(LastUserInput.size() > 2) {
		State = 0;
		return 0;
	}	

	if(LastUserInput.size() == 2) {
		if(LastUserInput[0] == "CWD") {
			if(LastUserInput[1] == "QUIT") {
				State = 2;
				return 0;
			}
			else if(LastUserInput[1] == "REGEN") {
				State = 3;
				return 0;
			}
			else if(LastUserInput[1] == "VERIFY") {
				State = 4;
				return 0;
			}
			else {
				State = 0;
				return 0;
			}
		}

		int Length = LastUserInput[0].size();
		int DirectionIndex = Length - 1;
		int IDLength = Length - 1;

		std::string ID = LastUserInput[0].substr(0, IDLength);
		std::string Direction = LastUserInput[0].substr(DirectionIndex, 1);

		if(Direction == "A" || Direction == "D") {
			try {
				int i;
				std::stoi(ID);	
				State = 1;
				return 0;
			}
			catch (...) {
				State = 0;
				return 0;
			}
		}	
	}

	if (State != 1) {
		LastUserInput.resize(2);
	}

	return 0;
}
