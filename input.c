#include <stdlib.h>
#include <stdio.h>

#include "input.h"

int get_num(char* msg, char* invalid_input_msg) {
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
}