#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "input.h"

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
		int len = strlen(buffer);
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