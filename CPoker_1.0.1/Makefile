CFLAGS  =  -Wall

LDFLAGS = -lm -lSDL2 -lSDL2_image -lSDL2_ttf

PATH_TO_SRC = ./Source/CPoker.c

PATH_TO_SRC_DATA = ./CPoker

BIN = ./Source/CPoker

all : $(PATH_TO_SRC)
	$(CC) $(CFLAGS) $(PATH_TO_SRC) $(LDFLAGS) -o $(BIN)

install :
	@if `test ! -d /usr/share/CPoker` ; then \
	cp -R --preserve=mode,ownership $(PATH_TO_SRC_DATA) /usr/share/ ; fi \


	@if `test ! -f /usr/bin/CPoker` ; then     \
		install -m 0755 $(BIN) /usr/bin ; fi

	@if `test -d /usr/share/applications` && ! `test -f /usr/share/applications/CPoker.desktop` ; then \
	cp --preserve=mode CPoker.desktop /usr/share/applications/ ; fi
	@echo CPoker installation successfull...
	@echo Enjoy to play with CPoker !!!

uninstall :
	rm /usr/bin/CPoker
	rm -R /usr/share/CPoker
	@if `test -d /usr/share/applications` && `test -f /usr/share/applications/CPoker.desktop` ; then \
	rm /usr/share/applications/CPoker.desktop ; fi
	@echo CPoker successfull remove from your system !!!

clean :
	@if `test -f CPoker` ; then \
	rm CPoker ; fi
	@echo cleaned
