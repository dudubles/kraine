
#include "kraine/utils.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ReadFile(const char *path) {
  // Very important, this can affect A LOT the output
  setlocale(LC_ALL, "en_US.utf8");

  // Open file
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    fprintf(stderr, "[ERROR] : Error opening file %s\n", path);
    return NULL;
  }

  // Seek to the end of the file to determine its size
  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Allocate memory for the content buffer
  char *fileContent = (char *)malloc(fileSize + 1); // +1 for null terminator
  if (fileContent == NULL) {
    fprintf(stderr, "[ERROR] : Memory allocation for file '%s' failed. \n",
            path);
    fclose(file);
    return NULL;
  }

  // Read file contents into the buffer
  int i = 0, curChar;
  while ((curChar = fgetc(file)) !=
         EOF) { // Read contents until it reach the end of the file
    fileContent[i] = curChar;
    i++;
  }
  fileContent[fileSize + 1] = '\0'; // Add null terminator just in case

  // Close the file and return the buffer
  fclose(file);
  return fileContent;
}
