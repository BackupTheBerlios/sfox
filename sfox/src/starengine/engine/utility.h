#ifndef UTILITY_H
#define UTILITY_H

extern void printgl_error(const char *filename, int line);
#define PRINTGL_ERROR() printgl_error(__FILE__, __LINE__)

#endif
