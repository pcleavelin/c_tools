#ifndef _C_FILE_IO_
#define _C_FILE_IO_

unsigned int get_file_size(const char *filePath);
int load_file(const char *filePath, unsigned int size, void *buffer);

#endif
