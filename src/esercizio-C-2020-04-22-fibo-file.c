/*
 * esercizio-C-2020-04-22-fibo-file.c
 *
 *  Created on: 24 apr 2020
 *      Author: utente
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

unsigned long fibonacci(unsigned int n);
unsigned long * fibonacci_array(unsigned int n);
char * itoa_printf(int number);


int main(int argc, char *argv[]) {

  unsigned int n = 39;
	unsigned long * fibo_array;

	fibo_array = fibonacci_array(n);

  char * file_name = "/home/utente/fibonacci.txt";  // per Debian
  //char * file_name = "fibonacci.txt";
	char * text_to_write;
  unsigned int total_bytes_write = 0;
	int text_to_write_len;

	int fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);

  if (fd == -1) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

  for (int i = 0; i <= n; i++) {

	if (i == n) {
    	text_to_write = itoa_printf(fibo_array[i]);
    	//printf("%s", text_to_write);
    } else {
    	text_to_write = strcat(itoa_printf(fibo_array[i]), "\n");
    	//printf("%s", text_to_write);
    }

    text_to_write_len = strlen(text_to_write);

    int bytes_write = write(fd, text_to_write, text_to_write_len);

    // write restituisce il numero di bytes che ha scritto
    // in caso di errore, restuisce -1
    if (bytes_write == -1) {
      perror("write()");
      exit(EXIT_FAILURE);
    }

    total_bytes_write += bytes_write;
  }

	// close file
	if (close(fd) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}

  printf("total_bytes_write = %u\n", total_bytes_write);
	printf("bye!\n");

	free(fibo_array);

	exit(EXIT_SUCCESS);
}


unsigned long fibonacci(unsigned int n) {
	unsigned long fn_2 = 0;
	unsigned long fn_1 = 1;
	unsigned long result = 0;

	switch (n) {
	case 0:
		result = fn_2;
		break;
	case 1:
		result = fn_1;
		break;
	default:
		for (int i = 1; i < n; i++) {
			result = fn_1 + fn_2;
			fn_2 = fn_1;
			fn_1 = result;
		}
		break;
	}

	return result;
}

unsigned long * fibonacci_array(unsigned int n) {
	unsigned long * result;

	result = calloc(n+1, sizeof(unsigned long));

	if (result == NULL) {
		perror("calloc error!");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i <= n; i++) {
		result[i] = fibonacci(i);
	}

	return result;
}

char * itoa_printf(int number) {
	char * result;
	// include '\0'
	//printf("minimum string len: %d\n",min_string_len(number));
	result = calloc(12, sizeof(char));

	snprintf(
			result, // zona di memoria in cui snprintf scriverà la stringa di caratteri
			12, // dimensione della zona di memoria
			"%d", // stringa di formattazione
			number); // numero intero da convertire in stringa

	return result;
}


