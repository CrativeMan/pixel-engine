#include <stdio.h>
#include <stdlib.h>

#include "logger.hpp"

const char *readFile(const char *filepath) {
  FILE *file = fopen(filepath, "rb");
  if (file == NULL) {
    LOG_ERROR("Failed to open file '%s'", filepath);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long unsigned int fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = (char *)malloc(fileSize + 1);
  if (buffer == NULL) {
    LOG_ERROR("Failed to alloc buffer");
    fclose(file);
    return NULL;
  }

  size_t readSize = fread(buffer, 1, fileSize, file);
  if (readSize != fileSize) {
    LOG_ERROR("Failed to read file");
    free(buffer);
    fclose(file);
    return NULL;
  }

  buffer[fileSize] = '\0';
  fclose(file);
  const char *fileContents = (const char *)buffer;

  LOG_INFO("Generated char* from file '%s'", filepath);
  return fileContents;
}
