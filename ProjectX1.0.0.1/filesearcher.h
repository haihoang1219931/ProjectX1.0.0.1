#ifndef FILESEARCHER_H
#define FILESEARCHER_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "structs.h"

#include "..\Common\defines.h"

#ifdef DEBUG
#define INITIAL_ALLOC 2
#else
#define INITIAL_ALLOC 512
#endif

namespace FileSearcher{
	//vector<WIN32_FIND_DATA> listFile;
	char * read_line(FILE *fin);
	bool isInFile(const char* srcFile, char * _string);
	bool isLike(char *string1, char *string2);
	void searchFile(char *dir, char *filename);
	void search(char *filename);
};
#endif