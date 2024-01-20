#include "Screen.h"
#include "CrosswordTable.h"
#include "Entry.h"

#include <iostream>
#include <sstream>

//ScreenWidth = 92

ClueScreen::ClueScreen(CrosswordTable& cwt) {

}

ClueScreen::ClueScreen(CrosswordTable& cwt, int HorizontalOffset) {
	OriginX = 1 + HorizontalOffset + 4;
	OriginY = 2;	

	int MaximumHorizontalIDLength;
	int MaximumVerticalIDLength;
	int TempLength = 0;

	for(int i = 0; i < cwt.TotalClues; i++) {
		TempLength = 0;
		if(cwt.CrosswordClues[i].IsDown == true) {
			VerticalClues.push_back(cwt.TableEntries[i]);
			VerticalPanelClues.push_back(cwt.CrosswordClues[i]);
		}
		else {
			HorizontalClues.push_back(cwt.TableEntries[i]);
			HorizontalPanelClues.push_back(cwt.CrosswordClues[i]);
		}

		TempLength = 4 + cwt.TableEntries[i].clue.size() + cwt.CrosswordClues[i].Name.size();
		//FIX THIS WHEN HAVE TIME
		//LENGTH OF CLUE + LENGTH OF ID + 1 SPACE
		if( TempLength > MaximumVerticalClueLength && cwt.CrosswordClues[i].IsDown == true) {
			MaximumVerticalClueLength = TempLength;
		}
		
		if( TempLength > MaximumHorizontalClueLength && cwt.CrosswordClues[i].IsDown == false) {
			MaximumHorizontalClueLength = TempLength;
		}
	}

	if(MaximumHorizontalClueLength >= MaximumVerticalClueLength) {
		MaximumClueLength = MaximumHorizontalClueLength;
	}
	else {
		MaximumClueLength = MaximumVerticalClueLength;
	}	
	
	VerticalClueBuffer = new ScreenBuffer(MaximumClueLength, cwt.NumberCluesDown + 1, '.');
	HorizontalClueBuffer = new ScreenBuffer(MaximumClueLength, cwt.NumberCluesAcross + 1, '.');
		
	BoardWidth = 2 * MaximumClueLength + 3;
	TotalWidth = BoardWidth + 2;	

	if(VerticalClues.size() > HorizontalClues.size()) {
		BoardHeight = VerticalClues.size() + 1;
	}
	else {
		BoardHeight = HorizontalClues.size() + 1;
	}
	
	TotalHeight = BoardHeight + 2;
	
	ScreenBorder = new Border(TotalWidth, TotalHeight, OriginX, OriginY, '[', '=', ']', '|', ']', '=', '[', '|');
	Buffer = new ScreenBuffer(BoardWidth, BoardHeight, 'c');
}

ClueScreen::~ClueScreen() {
	delete Buffer;	
	delete VerticalClueBuffer;
	delete HorizontalClueBuffer;
	delete ScreenBorder;

	ScreenBorder = nullptr;
	Buffer = nullptr;
	VerticalClueBuffer = nullptr;
	HorizontalClueBuffer = nullptr;
}

void ClueScreen::Update(CrosswordTable& cwt) {
	HorizontalClueBuffer->Fill();	
	VerticalClueBuffer->Fill();	
	
	ScreenBorder->Update();

	int index = 0;

	std::string label;
	
	label = "^^^";
	VerticalClueBuffer->DisplayBuffer.seekp(index);
	VerticalClueBuffer->DisplayBuffer.write(label.c_str(), label.size());
	
	label = ">>>";	
	HorizontalClueBuffer->DisplayBuffer.seekp(index);
	HorizontalClueBuffer->DisplayBuffer.write(label.c_str(), label.size());
	
	for(int i = 0; i < VerticalClues.size(); i++) {
		index = (1 + i) * MaximumClueLength;
	
		label = VerticalPanelClues[i].Name + ")   " + VerticalClues[i].clue;	
		
		VerticalClueBuffer->DisplayBuffer.seekp(index);
		VerticalClueBuffer->DisplayBuffer.write(label.c_str(), label.size());	
	}

	for(int i = 0; i < HorizontalClues.size(); i++) {	
		index = (1 + i) * MaximumClueLength;

		label = HorizontalPanelClues[i].Name + ")   " + HorizontalClues[i].clue;	
	
		HorizontalClueBuffer->DisplayBuffer.seekp(index);
		HorizontalClueBuffer->DisplayBuffer.write(label.c_str(), label.size());
	}
}

void ClueScreen::Refresh() {
	std::cout << "\e[1m"; //Set Bold
	
	ScreenBorder->Refresh();
	VerticalClueBuffer->Print(OriginX + 1, OriginY + 1);	
	HorizontalClueBuffer->Print(OriginX + 1 + 3 + MaximumClueLength, OriginY + 1);	
}
