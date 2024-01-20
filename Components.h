#ifndef __COMPONENTS_H_INCLUDED__
#define __COMPONENTS_H_INCLUDED__

#include <string>

class Clue {
	public:
		Clue(int, std::string, int, int, int);
		~Clue();

		int ID;
		std::string Name;
		int Length;
		int X;
		int Y;

		bool IsDown;
};

class Intersection {
	public:
		Intersection(int, int, int, int);
		~Intersection();

		int First_Intersect;
		int Second_Intersect;
		int First_ID;
		int Second_ID;
};

#endif
