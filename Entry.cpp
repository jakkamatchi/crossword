#include "Entry.h"

#include <string>

Entry::Entry() {

}

Entry::Entry(int length_t, std::string solution_t, std::string clue_t) {
	length = length_t;
	solution = solution_t;
	clue = clue_t;
}

Entry::~Entry() {

}

void Entry::Update(int length_t, std::string solution_t, std::string clue_t) {
	length = length_t;
	solution = solution_t;
	clue = clue_t;
}

bool Entry::operator== (const Entry& rhs) {
	bool ret = true;

	if(this->length != rhs.length || this->solution != rhs.solution || this->clue != rhs.clue) {
		ret = false;
	}

	return ret;
};

