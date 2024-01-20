#ifndef __SCREENBUFFER_H_INCLUDED__
#define __SCREENBUFFER_H_INCLUDED__

#include <sstream>

class ScreenBuffer {
	public:
		ScreenBuffer();
		ScreenBuffer(int, int, char);
		~ScreenBuffer();
		

		int BufferWidth = 0;
		int BufferHeight = 0;
		int BufferSize = 0;

		char FillCharacter = 0;

		std::stringstream DisplayBuffer;

		void Fill();
		void Print(int, int);
};

#endif
