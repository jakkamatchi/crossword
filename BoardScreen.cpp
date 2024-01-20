#include "Screen.h"
#include "CrosswordTable.h"
#include "ScreenBuffer.h"
#include "GuessHandler.h"

#include <iostream>
#include <algorithm>

class Clue;

BoardScreen::BoardScreen(CrosswordTable& cwt) {
	OriginX = 2;
	OriginY = 2;
	
	BoardWidth = cwt.DisplayWidth;
	TotalWidth = BoardWidth + 2; 
	
	BoardHeight = cwt.DisplayHeight;
	TotalHeight = BoardHeight + 2;

	Buffer = new ScreenBuffer(BoardWidth, BoardHeight, ' ');
	ScreenBorder = new Border(TotalWidth, TotalHeight, OriginX, OriginY, '[', '=', ']', '|', ']', '=', '[', '|'); 
}

BoardScreen::~BoardScreen() {
	delete Buffer;
	Buffer = nullptr;

	delete ScreenBorder;
	ScreenBorder = nullptr;
}

void BoardScreen::Update(CrosswordTable& cwt) {

}

bool Compare(const Guess& lhs, const Guess& rhs) {
	bool ret = false;

	if(lhs.GuessNumber > rhs.GuessNumber) {
		ret = true;
	}

	return ret;
};

void BoardScreen::Update(CrosswordTable& cwt, std::vector<Guess >& GuessList) {
	ScreenBorder->Update();	
	Buffer->Fill();

	//NEEDS Refactoring
	//draw elements in order of entry
	//
	//1) copy guess list
	//2) reorder
	//3) draw

	std::vector<Guess > TempGuessList = GuessList;
	std::sort(TempGuessList.begin(), TempGuessList.end(), Compare);
	
	std::vector<Clue > ClueListCopy = cwt.CrosswordClues;
	std::vector<Clue > TempClueList;

	for(int i = 0; i < TempGuessList.size(); i++) {
		for(int j = 0; j < ClueListCopy.size(); j++) {
			if (ClueListCopy[j].Name == TempGuessList[i].ClueID) {
				TempClueList.push_back(ClueListCopy[j]);
				ClueListCopy.erase(ClueListCopy.begin() + j);
			}
		}
	}

	for(int i = 0; i < ClueListCopy.size(); i++) {
		TempClueList.push_back(ClueListCopy[i]);
	}
	
	//temp clue list finished
	//guess list finished
	int index;

	for(int i = cwt.TotalClues - 1; i >= 0; i--) {
		index = (TempClueList[i].Y * BoardWidth) + TempClueList[i].X;
		std::string CurrentGuess = TempGuessList[i].GuessWord;

		if(TempClueList[i].IsDown == true) {
			for(int k = 0; k < TempClueList[i].Length; k++) {	
				index = ((TempClueList[i].Y + k) * BoardWidth) + TempClueList[i].X;
			
				Buffer->DisplayBuffer.seekp(index);
				if(CurrentGuess.size() == 0) {
					Buffer->DisplayBuffer.write(".", 1);
				}
				else {
					const char* c = new char[1];
					c = &CurrentGuess.c_str()[k];
					Buffer->DisplayBuffer.write(c, 1);
				}
			}
		}
		else {
			for(int k = 0; k < TempClueList[i].Length; k++) {
				Buffer->DisplayBuffer.seekp(index);
				
				if(CurrentGuess.size() == 0) {
					Buffer->DisplayBuffer.write(".", 1);
				}
				else {
					const char* c = new char[1];
					c = &CurrentGuess.c_str()[k];
					Buffer->DisplayBuffer.write(c, 1);
				}
			
				index++;
			}
		}
	}
}

void BoardScreen::Refresh() {
	ScreenBorder->Refresh();
	Buffer->Print(OriginX + 1, OriginY + 1);	
}

