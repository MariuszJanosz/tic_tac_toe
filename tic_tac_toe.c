#include <string.h>

#include "terminal_tictactoe.h"
#include "gui_tictactoe.h"

typedef enum {
	TERMINAL,
	GUI
} Mode_t;

int main(int argc, char** argv) {
	Mode_t mode = GUI;
	for (int i = 1; i < argc; ++i) {
		if (0 == strcmp(argv[i], "--cli")) {
			mode = TERMINAL;
		}
	}

	switch (mode) {
	case TERMINAL:
		return terminal_main(argc, argv);
	case GUI:
		return gui_main(argc, argv);
	}
	return 0;
}