#include "Components.h"

#include <string>

Clue::Clue(int ID_t, std::string Name_t, int Length_t, int X_t, int Y_t) {
	ID = ID_t;
	Name = Name_t;
	Length = Length_t;
	X = X_t;
	Y = Y_t;
	
	IsDown = true;

	if(Name[Name.size() - 1] == 'A') {
		IsDown = false;
	}
}

Clue::~Clue() {


}

Intersection::Intersection(int First_t, int First_Intersect_t, int Second_t, int Second_Intersect_t) {
	First_ID = First_t;
	Second_ID = Second_t;
	First_Intersect = First_Intersect_t;
	Second_Intersect = Second_Intersect_t;
}

Intersection::~Intersection() {

}

