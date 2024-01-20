#include "Screen.h"
#include "ScreenBuffer.h"
#include "CrosswordTable.h"

#include <iostream>

InputScreen::InputScreen(CrosswordTable& cwt) {

}

InputScreen::InputScreen(CrosswordTable& cwt, int VerticalOffset, int ScreenWidth) {
	OriginX = 2;
	OriginY = 2 + 1 +  VerticalOffset;

	BoardWidth = ScreenWidth + 1;
	TotalWidth = BoardWidth + 2;
	
	BoardHeight = 3;
	TotalHeight = BoardHeight + 2;
	
	Buffer = new ScreenBuffer(BoardWidth, BoardHeight, '.');
	ScreenBorder = new Border(TotalWidth, TotalHeight, OriginX, OriginY, '[', '=', ']', '|', ']', '=', '[', '|');
}

InputScreen::~InputScreen() {
	delete Buffer;
	Buffer = nullptr;

	delete ScreenBorder;
	ScreenBorder = nullptr;
}

void InputScreen::Update(CrosswordTable& cwt) {
	ScreenBorder->Update();
	
	Buffer->Fill();
	std::string PromptText = "INPUT > ";	

	Buffer->DisplayBuffer.seekp(BoardWidth);	
	Buffer->DisplayBuffer.write(PromptText.c_str(), PromptText.length());

}

void InputScreen::Refresh() {
	ScreenBorder->Refresh();
	Buffer->Print(OriginX+1, OriginY+1);
}

void InputScreen::ResetCursor() {
	std::cout << "\e[" << OriginY+2 << ";" << OriginX+9 << "H";	//Move to X,Y
}

