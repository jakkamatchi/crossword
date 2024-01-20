#ifndef __CROSSWORDTABLE_H_INCLUDED__
#define __CROSSWORDTABLE_H_INCLUDED__

#include "Components.h"
#include "Dictionary.h"

#include <vector>

class CrosswordTable {
	public:
		CrosswordTable(std::vector<std::string>&);
		~CrosswordTable();
		
		int DisplayWidth;
		int DisplayHeight;

		int TotalClues;
		int NumberCluesAcross;
		int NumberCluesDown;
		int TotalIntersections;	

		std::vector<Clue> CrosswordClues;
		std::vector<Intersection> CrosswordIntersections;

		void PrintInfo();

		std::vector<Entry> TableEntries;
		void GenerateSolution(Dictionary&);
	private:
		bool Matches(Entry& e, Clue& c);
		void PrintSolution();
};

#endif
