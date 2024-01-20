#include "Dictionary.h"
#include "Entry.h"

#include <vector>
#include <string>
#include <iostream>

Dictionary::Dictionary(std::vector<std::string>& raw_data) {
	Entry new_entry;

	for(int i = 0; i < raw_data.size(); i = i + 3) {
		new_entry.Update(std::stoi(raw_data[i]), raw_data[i+1], raw_data[i+2]);
		entries.push_back(new_entry);	
	}

	DictionarySize = entries.size();
}

Dictionary::~Dictionary() {

}

void Dictionary::PrintInfo() {
	for(int i = 0; i < DictionarySize; i++) {
		std::cout << entries[i].length << " " << entries[i].solution << " " <<  entries[i].clue << std::endl;
	}
}
