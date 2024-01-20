#include "Screen.h"
#include "ScreenBuffer.h"
#include "CrosswordTable.h"

#include <iostream>
Border::Border(int w_t, int h_t, int x_t, int y_t, char top_left, char top_bar, char top_right, char right_bar, char bottom_right, char bottom_bar, char bottom_left, char left_bar) {
	X = x_t;
	Y = y_t;
	W = w_t;
	H = h_t;

	TopLeft = top_left;
	TopBar = top_bar;
	TopRight = top_right;
	RightBar = right_bar;
	BottomRight = bottom_right;
	BottomBar = bottom_bar;
	BottomLeft = bottom_left;
	LeftBar = left_bar;

	//fill empty
	Buffer = new ScreenBuffer(W, H, '.');
	Update();
}

Border::~Border() {
	delete Buffer;
	Buffer = nullptr;
}

void Border::Update() {
	Buffer->Fill();

	char* TBar = new char[W];
	char* BBar = new char[W];

	for(int i = 0; i < W; i++) {
		TBar[i] = TopBar;
		BBar[i] = BottomBar;
	}

	for(int i = 1; i < H; i++) {
		Buffer->DisplayBuffer.seekp((i * W) - 1);
		Buffer->DisplayBuffer.put(RightBar);
		Buffer->DisplayBuffer.put(LeftBar);
	}
		
	Buffer->DisplayBuffer.seekp(0);
	Buffer->DisplayBuffer.write(TBar, W);	

	Buffer->DisplayBuffer.seekp(0);
	Buffer->DisplayBuffer.put(TopLeft);

	Buffer->DisplayBuffer.seekp(W - 1);
	Buffer->DisplayBuffer.put(TopRight);

	Buffer->DisplayBuffer.seekp((H-1) * W);	
	Buffer->DisplayBuffer.write(BBar, W);
	
	Buffer->DisplayBuffer.seekp((H-1) * W);	
	Buffer->DisplayBuffer.put(BottomLeft);

	Buffer->DisplayBuffer.seekp(H * W - 1);
	Buffer->DisplayBuffer.put(BottomRight);

	delete[] TBar;
	TBar = nullptr;

	delete[] BBar;
	BBar = nullptr;
}

void Border::Refresh() {
	Buffer->Print(X, Y);
}
