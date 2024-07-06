/*
  MIT License

  Copyright (c) 2024 Dudubles

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/*=================================================
Path: utils/files.c

Date: 07/06/2024

Author: Dudubles

Description:
================================================*/

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
