#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Dictionary.h"
#include "Entry.h"
#include "CrosswordTable.h"
#include "Components.h"
#include "Screen.h"
#include "InputHandler.h"
#include "GuessHandler.h"

const std::string CROSSWORD_1_FILE_NAME = "cwt_dir/crossword1.cwt";
const std::string CROSSWORD_2_FILE_NAME = "cwt_dir/crossword2.cwt";
const std::string CROSSWORD_3_FILE_NAME = "cwt_dir/crossword3.cwt";

const std::string DICTIONARY_FILE_NAME = "cwd_dir/solu.cwd";

void SetScreenSize(int w, int h) {
	//std::cout << "\e[8;60;60t";	
	std::cout << "\e[8;" << h << ";" << w << "t";
	
	std::cout << "\e[2J";
}

void SetCursor(bool setting) {
	if(setting == true) {
		std::cout << "\e[?25h";
	}
	else {
		std::cout << "\e[?25l";
	}
}

std::vector<std::string> ParseFile(std::string fileName) {
	std::vector<std::string> raw_data;
	
	std::ifstream infile;
	infile.open(fileName);

	if(!infile.is_open()) {
		std::cout << "FAILED TO OPEN " << fileName << std::endl;
	}
	else {
		std::string data_point;
		while(std::getline(infile, data_point, ',').good()) {
			raw_data.push_back(data_point);
		}
	}

	infile.close();

	return raw_data;
}

int main(int argc, char* argv[]) {
	//TOOO:
	//Update / Integrate CWD editor and add functionality
	//	Modify lines
	//	Clean duplicates
	//Create board designer
	//Copy metro crossword to increase testing opportunities
	//Add command line functionality
	//Answers entered over another should modify the words they cover

	std::vector<std::string> crosswordFileData = ParseFile(CROSSWORD_3_FILE_NAME);	
	std::vector<std::string> dictionaryFileData = ParseFile(DICTIONARY_FILE_NAME);

	CrosswordTable crosswordData(crosswordFileData);
	Dictionary dictionary(dictionaryFileData);	

	crosswordData.GenerateSolution(dictionary);
	//crossword2.PrintInfo();	
	std::cout << "\e[2J"; //Clear Screen
	//std::cout << "\e[7m"; //Set Inverted colour mode	
		
	//Initialise visual elements	
	BoardScreen BScreen(crosswordData);	
	ClueScreen CScreen(crosswordData, BScreen.GetWidth());
	
	int LargerScreen;

	if(BScreen.GetHeight() > CScreen.GetHeight()) {
		LargerScreen = CScreen.GetHeight();	
	}
	else {
		LargerScreen = BScreen.GetHeight();
	}
	
	InputScreen IScreen(crosswordData, LargerScreen + 2, BScreen.GetWidth() + CScreen.GetWidth());
	
	//Initialise handling elements
	InputHandler IHandler;
	GuessHandler GHandler(crosswordData.TableEntries, crosswordData.CrosswordClues);

	int TotalScreenWidth = BScreen.GetWidth() + CScreen.GetWidth() + 5;
	int TotalScreenHeight = IScreen.GetHeight() + LargerScreen + 5;
	
	SetScreenSize(TotalScreenWidth, TotalScreenHeight);
	
	//Update Elements
	CScreen.Update(crosswordData);
	BScreen.Update(crosswordData, GHandler.GuessList);
	IScreen.Update(crosswordData);

	//Refresh
	CScreen.Refresh();
	BScreen.Refresh();
	IScreen.Refresh();

	IScreen.ResetCursor();

	bool Running = true;
	int CurrentGuess = 1;

	while (Running) {
		std::string TempString;
		
		std::getline(std::cin, TempString);	
		
		IHandler.ParseInput(TempString);
		IHandler.SetState();
		
		Guess guess(IHandler.LastUserInput[0], IHandler.LastUserInput[1], CurrentGuess);
		CurrentGuess++;
		switch(IHandler.State) {
			case 0:		//INVALID INPUT
				std::cout << "";
				break;
			case 1:		//VALID INPUT
				GHandler.Process(guess);
				break;
			case 2:		//QUIT
				Running = false;
				break;
			case 3:		//REGEN
				std::cout << "";
				break;
			case 4:		//VERIFY
				Running = GHandler.VerifySolution();
				if(Running == false) {
					return 0;
				}	
				break;
		}

		SetCursor(false);

		SetScreenSize(TotalScreenWidth, TotalScreenHeight);
		
		CScreen.Update(crosswordData);
		BScreen.Update(crosswordData, GHandler.GuessList);
		IScreen.Update(crosswordData);
		
		CScreen.Refresh();
		BScreen.Refresh();
		IScreen.Refresh();

		IScreen.ResetCursor();
		SetCursor(true);
	}

	std::cout << "\e[8B";
	
	return 0;
}
