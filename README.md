Crossword generator. Randomly generates a crossword from a supplied dictionary and table.

Written in C++.

#FILE FORMATS:
CWD File: CrossWord Dictionary File
CWT File: CrossWord Table File

##CWD FILE:
Describes a CrossWord Dictionary. Each entry is a separate solution and associated clue. CSV File with following structure:
[SOLUTION LENGTH],[SOLUTION],[CLUE],

##CWT FILE:
Describes a CrossWord Table. Split into three sections. CSV File with following structure.

###HEADER:
[Width],[Height],[NumberClues],[NumberAcross],[NumberDown],[NumberIntersections],

###CLUE LIST:
[ID],[Name],[Length],[XPos],[YPos],

###INTERSECTION LIST:
[FirstClue],[IndexCharFirst],[SecondClueID],[IndexIntersectSecond],
