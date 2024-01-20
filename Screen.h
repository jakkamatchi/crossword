#ifndef __SCREEN_H_INCLUDED__
#define __SCREEN_H_INCLUDED__

#include "CrosswordTable.h"
#include "ScreenBuffer.h"
#include "GuessHandler.h"

#include <vector>

class Border;

class Screen {
	public:
		Screen();
		~Screen();
		
		virtual void Update(CrosswordTable&) = 0;
		virtual void Refresh() = 0;

		int OriginX = 0;
		int OriginY = 0;
		
		int TotalWidth = 0;
		int TotalHeight = 0;

		int BoardWidth = 0;
		int BoardHeight = 0;
		
		ScreenBuffer* Buffer = nullptr;
};

class BoardScreen : Screen {
	public:
		BoardScreen(CrosswordTable&);
		~BoardScreen();

		void Update(CrosswordTable&);
		void Update(CrosswordTable&, std::vector<Guess >&);
		
		void Refresh();

		int GetWidth() { return TotalWidth; } 
		int GetHeight() { return TotalHeight; }
		
		Border* ScreenBorder = nullptr;
};

class ClueScreen : Screen {
	public:
		ClueScreen(CrosswordTable&);
		ClueScreen(CrosswordTable&, int);
		~ClueScreen();

		void Update(CrosswordTable&);
		void Refresh();
		
		int GetWidth() { return TotalWidth; } 
		int GetHeight() { return TotalHeight; }
		
		std::vector<Entry> HorizontalClues;
		std::vector<Clue> HorizontalPanelClues;

		std::vector<Entry> VerticalClues;	
		std::vector<Clue> VerticalPanelClues;

		int MaximumHorizontalClueLength = 0;
		int MaximumVerticalClueLength = 0;
		int MaximumClueLength = 0;

		ScreenBuffer* VerticalClueBuffer = nullptr;
		ScreenBuffer* HorizontalClueBuffer = nullptr;
		Border* ScreenBorder = nullptr;
};

class InputScreen : Screen {
	public:
		InputScreen(CrosswordTable&);
		InputScreen(CrosswordTable&, int, int);
		~InputScreen();

		std::string CurrentInput;
		std::vector<std::string> GuessParameters;

		std::string TargetClue;
		std::string TargetGuess;
	
		Border* ScreenBorder = nullptr;

		void Update(CrosswordTable&);
		void Refresh();
		
		int GetWidth() { return TotalWidth; } 
		int GetHeight() { return TotalHeight; }
		
		void ResetCursor();
};

class Border {
	public:
		Border(int, int, int, int, char, char, char, char, char, char, char, char);
		~Border();

		ScreenBuffer* Buffer = nullptr;

		int X = 0;
		int Y = 0;
		int W = 0;
		int H = 0;

		char TopLeft;
		char TopRight;
		char BottomLeft;
		char BottomRight;
		
		char TopBar;
		char LeftBar;
		char RightBar;
		char BottomBar;

		void Update();
		void Refresh();
};

#endif
