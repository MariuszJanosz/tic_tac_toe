#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "input.h"
#include "players.h"

int get_num(const char* msg, const char* invalid_input_msg) {
	int num;
	while (1) {
		printf("%s", msg);
		int scanned = scanf("%d", &num);
		if (scanned == 0) {
			printf("%s", invalid_input_msg);
			while (getchar() != '\n');
			continue;
		}
		int tail_len = 0;
		while (getchar() != '\n') ++tail_len;
		if (tail_len != 0) {
			printf("%s", invalid_input_msg);
			continue;
		}
		return num;
	}
	assert(0);
}

char* get_string(const char* msg, const char* invalid_input_msg) {
	char buffer[1024];
	while (1) {
		printf("%s", msg);
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			printf("%s", invalid_input_msg);
			while (getchar() != '\n');
			continue;
		}
		if (strchr(buffer, '\n') == NULL) {
			printf("%s", invalid_input_msg);
			while (getchar() != '\n');
			continue;
		}
		int len = (int)strlen(buffer);
		if (len == 1) {
			printf("%s", invalid_input_msg);
			continue;
		}
		buffer[len - 1] = '\0'; //Remove \n
		char* string = (char*)malloc(len * sizeof(*string));
		if (!string) {
			fprintf(stderr, "String allocation failed!\n");
			exit(1);
		}
		strcpy(string, buffer);
		return string;
	}
	assert(0);
}

char* get_player_name() {
#define _MSG_(x, y, z) x #y z
#define MSG(x, y, z) _MSG_(x, y, z)
	const char* msg = MSG("Enter your name (max ", MAX_NAME_LEN, " characters): ");
#undef MSG
#undef _MSG_
	const char* invalid_input_msg = "Invalid input! Try again.\n";
	char* name = NULL;
	while (1) {
		name = get_string(msg, invalid_input_msg);
		if (strlen(name) > MAX_NAME_LEN) {
			printf("Invalid input, name to long! Try again.\n");
			free(name);
			continue;
		}
		return name;
	}
}