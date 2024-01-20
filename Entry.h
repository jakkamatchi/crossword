#ifndef __ENTRY_H_INCLUDED
#define __ENTRY_H_INCLUDED

#include <string>

class Entry {
	public:
		Entry();
		Entry(int, std::string, std::string);
		~Entry();

		void Update(int, std::string, std::string);
		//static int id = -1;
		
		int length;
		std::string solution;
		std::string clue;

		bool operator==(const Entry& rhs);
};

#endif
