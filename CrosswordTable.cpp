#include "CrosswordTable.h"
#include "Components.h"
#include "Dictionary.h"

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <exception>

CrosswordTable::CrosswordTable(std::vector<std::string>& raw_data) {
	DisplayWidth = std::stoi(raw_data[0]);		
	DisplayHeight = std::stoi(raw_data[1]);

	TotalClues = std::stoi(raw_data[2]);
	NumberCluesAcross = std::stoi(raw_data[3]);
	NumberCluesDown = std::stoi(raw_data[4]);
	TotalIntersections = std::stoi(raw_data[5]);

	int ClueOffset = 6;

	for(int i = ClueOffset; i < ((TotalClues + 1) * 5) + 1; i = i + 5) {
		Clue clue(std::stoi(raw_data[i]), raw_data[i+1], std::stoi(raw_data[i+2]), std::stoi(raw_data[i+3]), std::stoi(raw_data[i+4]));
		CrosswordClues.push_back(clue);
	}

	int IntersectionOffset = ClueOffset + (TotalClues * 5);

	for(int i = IntersectionOffset; i < IntersectionOffset + (TotalIntersections* 4); i = i + 4) {
		Intersection intersection(std::stoi(raw_data[i]), std::stoi(raw_data[i+1]), std::stoi(raw_data[i+2]), std::stoi(raw_data[i+3]));
		CrosswordIntersections.push_back(intersection);
	}
}

CrosswordTable::~CrosswordTable() {

}

void CrosswordTable::PrintInfo() {
	std::cout << "Display Width: " << DisplayWidth << std::endl;
	std::cout << "Display Height: " << DisplayHeight << std::endl;
	std::cout << "Total Clues: " << TotalClues << std::endl;
	std::cout << "Number Of Clues Across: " << NumberCluesAcross << std::endl;
	std::cout << "Number Of Clues Down: " << NumberCluesDown << std::endl;
	std::cout << "Total Intersections: " << TotalIntersections << std::endl;

	std::cout << std::endl << "Clue Data:" << std::endl;
	for(int i = 0; i < TotalClues; i++) {
		std::cout << CrosswordClues[i].ID << " ";
		std::cout << CrosswordClues[i].Name << " ";
		std::cout << CrosswordClues[i].Length << " ";
		std::cout << CrosswordClues[i].X << " ";
		std::cout << CrosswordClues[i].Y << std::endl;
	}

	std::cout << std::endl << "Intersection Data:" << std::endl;
	for(int i = 0; i < TotalIntersections; i++) {
		std::cout << CrosswordIntersections[i].First_ID << " ";
		std::cout << CrosswordIntersections[i].First_Intersect << " ";
		std::cout << CrosswordIntersections[i].Second_ID << " ";
		std::cout << CrosswordIntersections[i].Second_Intersect << std::endl;
	}
	
	std::cout << std::endl;
}

void CrosswordTable::GenerateSolution(Dictionary& dictionary) {
	//choose random number for initial position in dictinoary
	//satisfy first clue
	//generate second clue that fulfills intersection requirements
	//generate third clue that satisfies requirements of third
	//if cannot generate clue, regenerate last clue
	//perform recursively until table filled

	std::random_device generator;
	std::mt19937 random(generator());
	std::uniform_int_distribution<int> distribution(0, dictionary.DictionarySize);

	int startIndex = distribution(random);	
	
	int Depth = 0;
	int currentRun = 0;

	int Iterator = startIndex;
	
	std::vector<std::vector<Entry> > lastValidEntries;
	lastValidEntries.resize(TotalClues);

	Entry currentEntry;

	int duration;

	while(Depth < TotalClues) {
		currentEntry = dictionary.entries[Iterator];
		/*
		for(int i = 0; i < lastValidEntries.size() - 1; i++) {
			std::cout << i << ": ";
			for(int j = 0; j < lastValidEntries[i].size(); j++) {
				std::cout << lastValidEntries[i][j].solution << " ";		
			}
			std::cout << std::endl;	
		}	

		*/	
		//This  code is supposed to ensure that no duplicates are added
		//Fix it.
		//25 dec 0257 it works ?			
		for(int i = 0; i < lastValidEntries.size() - 1; i++) {
			if(!lastValidEntries[i].empty()) {
				int t = lastValidEntries[i].size() - 1;

				if(lastValidEntries[i][t] == currentEntry) {
					Iterator++;
					break;
				}
			}
		}
		
		currentEntry = dictionary.entries[Iterator];
		//for stuff**	
		for (int i = 0; i < lastValidEntries[Depth].size(); i++) {
			if(currentEntry.solution == lastValidEntries[Depth][i].solution) {
				Iterator++;
				currentEntry = dictionary.entries[Iterator];
			}
		}
		
		currentEntry = dictionary.entries[Iterator];

		if(Matches(currentEntry, CrosswordClues[Depth])) {
			TableEntries.push_back(currentEntry);		
			lastValidEntries[Depth].push_back(currentEntry);
			
			Depth++;

			currentRun = 0;	
			Iterator = distribution(random);
		}
		else {
			currentRun++;
		}

		//Increment loop
		Iterator++;

		//If one complete loop, restart loop;
		if (Iterator >= dictionary.DictionarySize) {
			Iterator = 0;	
		}	

		//if one whole loop of dictionary completed and nothing found
		//decrease depth.
		if(currentRun >= dictionary.DictionarySize) {	
			lastValidEntries[Depth].resize(0);
			TableEntries.pop_back();
			
			if(Depth > 0) {	
				Depth--;
			}
			
			currentRun = 0;
		}
	duration++;

	}

	PrintSolution();
	std::cout << "t: " << duration << std::endl;
}

void CrosswordTable::PrintSolution() {
	for(int i = 0; i < TableEntries.size(); i++) {
		std::cout << i << ": " << TableEntries[i].solution << std::endl;
	}
}

bool CrosswordTable::Matches(Entry& e, Clue& c) {
	//1) ensure no duplicates
	//2) if runs once and cannot find, pop back and retry
	bool result = false;
	bool testedIntersections = false;
	
	if(e.length == c.Length) {
		result = true;
		testedIntersections = false;

		for (int i = 0; i < TotalIntersections; i++) {
			if(CrosswordIntersections[i].Second_ID == c.ID && result == true) {	
				testedIntersections = true;
				try {
					char firstCharacter = e.solution[CrosswordIntersections[i].Second_Intersect];
					char secondCharacter = TableEntries[CrosswordIntersections[i].First_ID].solution[CrosswordIntersections[i].First_Intersect];
					
					if(firstCharacter == secondCharacter) {
						result = true;
					}
					else {
						result = false;
					}
				}
				catch(std::out_of_range& e) {
				}
			}	
		}
		if(!testedIntersections) {
			result = true;
		}
	}
	
	return result;
}
