#ifndef __DICTIONARY_H_INCLUDED__
#define __DICTIONARY_H_INCLUDED__

#include <vector>
#include <string>

#include "Entry.h"

class Dictionary {
	public:
		Dictionary(std::vector<std::string>&);
		~Dictionary();

		std::vector<Entry> entries;
		int DictionarySize;

		void PrintInfo();
};

#endif
