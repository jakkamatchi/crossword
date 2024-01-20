objects = main.o ClueScreen.o Components.o BoardScreen.o CrosswordTable.o Dictionary.o Entry.o Screen.o ScreenBuffer.o Border.o InputScreen.o InputHandler.o GuessHandler.o

args = -Wc++11 -std=c++20
cc = g++

cross: $(objects)
	$(cc) -g -v $(args) $(objects)

main.o: Components.h Dictionary.h Screen.h CrosswordTable.h Entry.h ScreenBuffer.h
ClueScreen.o: Screen.h Components.h Entry.h
Components.o: Components.h
BoardScreen.o: Screen.h
CrosswordTable.o: CrosswordTable.h Dictionary.h Entry.h
Dictionary.o: Dictionary.h Components.h
Screen.o: Screen.h ScreenBuffer.h
ScreenBuffer.o: ScreenBuffer.h
Entry.o: Entry.h
Border.o: Screen.h ScreenBuffer.h CrosswordTable.h
InputScreen.o: ScreenBuffer.h Screen.h CrosswordTable.h
InputHandler.o: InputHandler.h
GuessHandler.o: GuessHandler.h 

clean:
	rm $(objects)
