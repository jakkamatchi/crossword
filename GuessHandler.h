#ifndef __GUESSHANDLER_H_INCLUDED__
#define __GUESSHANDLER_H_INCLUDED__

#include <vector>
#include <string>

#include "Entry.h"
#include "Components.h"

class Guess {
	public:
		Guess();
		Guess(std::string, std::string, int);
		~Guess();

		std::string ClueID;
		std::string GuessWord;
		
		int GuessNumber = 0;
};

class GuessHandler {
	public:
		GuessHandler(std::vector<Entry >, std::vector<Clue >);
		~GuessHandler();

		std::vector<Clue> ClueList;
		std::vector<Entry> SolutionList;
		std::vector<Guess> GuessList;

		void Process(Guess&);
		bool VerifySolution();
};

#endif
