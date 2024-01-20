#include "ScreenBuffer.h"
#include <sstream>
#include <iostream>

ScreenBuffer::ScreenBuffer() {

}

ScreenBuffer::ScreenBuffer(int w, int h, char c) {
	BufferWidth = w;				//+1 to account for /n at eol
	BufferHeight = h;
	BufferSize = BufferHeight * BufferWidth;

	FillCharacter = c;
	DisplayBuffer.str("");
}

ScreenBuffer::~ScreenBuffer() {
}

void ScreenBuffer::Fill() {
	DisplayBuffer.str("");
	DisplayBuffer.clear();

	for(int i = 0; i < BufferHeight; i++) {
		for(int j = 0; j < BufferWidth; j++) {
			DisplayBuffer << FillCharacter;
		}
	}
}

void ScreenBuffer::Print(int X, int Y) {	
	std::cout << "\e[" << Y << ";" << X << "H";	//Move to X,Y
	
	char* t = new char[BufferWidth];

	for (int i = 0; i < BufferHeight; i++) {
		DisplayBuffer.read(t, BufferWidth);
		std::cout << t;
		std::cout << "\e[1B";	//Move down 1 row
		std::cout << "\e[" << X << "G"; //move to column X
	}

	delete[] t;
}
