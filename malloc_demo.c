#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NUM_STRINGS 5
#define STRING_SIZE 10 /* includes null terminating character */

/* program to accept NUM_STRINGS strings, each STRING_SIZE-1 characters 
   long, storing them then printing them in a lovely format */

void array_destroy(char **);

int main(void) {
  int i, c;
  char *string;
  char **array_of_strings;

  /* malloc array of strings */
  if ((array_of_strings = (char **) malloc(NUM_STRINGS*sizeof(char *))) == NULL) {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  for (i = 0; i < NUM_STRINGS; i++) {
    /* malloc string */
    if ((string = (char *) malloc(STRING_SIZE*sizeof(char))) == NULL) { 
      fprintf(stderr, "Error: %s\n", strerror(errno));
      return EXIT_FAILURE;
    }

    /* read in string */
    printf("Enter a string no longer than %d characters: ", STRING_SIZE-1);
    fgets(string, STRING_SIZE, stdin);

    /* if length of string is equal to permitted string size, accomodating for 
     * null terminating char, i.e. string has been 'filled up' by fgets and there 
     * may still be chars left in stdin AND the last char is not newline i.e. there
     * are chars left in stdin buffer then flush stdin */
    if ((strlen(string) == STRING_SIZE-1) && (*(string+(STRING_SIZE-2)) != '\n'))
      while ((c = getchar()) != '\n' && c != EOF);

    /* remove newline, if it exists, and store string */
    if (*(string+(strlen(string)-1)) == '\n') *(string+(strlen(string)-1)) = '\0';
    *(array_of_strings+i) = string;
  }

  /* print strings */
  printf("----------------\nStrings entered:\n");
  for (i = 0; i < NUM_STRINGS; i++)
    printf("%s\n", *(array_of_strings+i));
  printf("----------------\n");
  
  /* free space taken by malloc */
  array_destroy(array_of_strings);

  return EXIT_SUCCESS;
}

void array_destroy(char **array) {
  int i;

  for (i = 0; i < NUM_STRINGS; i++)
    free(*(array+i));

  free(array);
}
