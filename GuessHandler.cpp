#include "GuessHandler.h"
#include "Entry.h"
#include "Components.h"

#include <iostream>

Guess::Guess() {
	ClueID = "";
	GuessWord = "";
	GuessNumber = 0;
}

Guess::Guess(std::string id, std::string word, int gNumber) {
	ClueID = id;
	GuessWord = word;
	GuessNumber = gNumber;
}

Guess::~Guess() {

}

GuessHandler::GuessHandler(std::vector<Entry > solution_t, std::vector<Clue > clue_t) {
	SolutionList = solution_t;
	ClueList = clue_t;

	for(int i = 0; i < solution_t.size(); i++) {
		Guess g;
		GuessList.push_back(g);
	}

	for(int i = 0; i < GuessList.size(); i++) {
		GuessList[i].ClueID = ClueList[i].Name;
	}	
}

GuessHandler::~GuessHandler() {

}

void GuessHandler::Process(Guess& guess) {
	bool valid;

	for(int i = 0; i < SolutionList.size(); i++) {
		if(ClueList[i].Name == guess.ClueID) {
			//crossword contains the clue
			if(ClueList[i].Length == guess.GuessWord.size()) {
				//guess length matches solution length
				valid = true;
			}	
		}
	}

	if(valid == true) {
		//is valid, so need to update guess list
		for (int i = 0; i < GuessList.size(); i++) {
			if(guess.ClueID == GuessList[i].ClueID) {
				GuessList[i] = guess;
			}
		}
	}	
}

bool GuessHandler::VerifySolution() {
	bool failure = false;

	for(int i = 0; i < SolutionList.size(); i++) {
		std::cout << i << ClueList[i].Name << " " << SolutionList[i].solution << " " << GuessList[i].ClueID << " " << GuessList[i].GuessWord << std::endl;

		if(SolutionList[i].solution != GuessList[i].GuessWord) {
			std::cout << i;
			failure = true;
		}
	}

	return failure;
}
