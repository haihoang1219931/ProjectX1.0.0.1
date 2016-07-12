#include "filesearcher.h"
using namespace std;
char c_fileSearch[1024];

bool diskisfixed(char *disk){
	return (GetDriveTypeA(disk) == DRIVE_FIXED);
}
void printDiskInfo(char *disk){
	int diskvalue = GetDriveTypeA(disk);
	switch (diskvalue){
	case DRIVE_UNKNOWN: printf("[%03s] DRIVE_UNKNOWN\r\n", disk); break;
	case DRIVE_NO_ROOT_DIR: printf("[%03s] DRIVE_NO_ROOT_DIR\r\n", disk); break;
	case DRIVE_REMOVABLE: printf("[%03s] DRIVE_REMOVABLE\r\n", disk); break;
	case DRIVE_FIXED: printf("[%03s] DRIVE_FIXED\r\n", disk); break;
	case DRIVE_REMOTE: printf("[%03s] DRIVE_REMOTE\r\n", disk); break;
	case DRIVE_CDROM: printf("[%03s] DRIVE_CDROM\r\n", disk); break;
	case DRIVE_RAMDISK: printf("[%03s] DRIVE_RAMDISK\r\n", disk); break;
	}
}
bool FileSearcher::isLike(char *string1, char *string2){
	int size1 = strlen(string1);
	int size2 = strlen(string2);
	int i;
	int numchar = size1>size2 ? size2 : size1;
	for (i = 1; i <= numchar; i++){
		if (tolower((int)string1[size1 - i]) != tolower((int)string2[size2 - i]))
			return false;
	}
	return true;
}
char * FileSearcher::read_line(FILE *fin) {
	char *buffer;
	char *tmp;
	int read_chars = 0;
	int bufsize = INITIAL_ALLOC;
	char *line = (char*)malloc(bufsize);

	if (!line) {
		return NULL;
	}

	buffer = line;

	while (fgets(buffer, bufsize - read_chars, fin)) {
		read_chars = strlen(line);
		if (line[read_chars - 1] == '\n') {
			line[read_chars - 1] = '\0';
			/*
			for(int i==0;i<read_chars-1;i++){
			if(line[i]>='A' && line[i]<='Z'){
			line[i] = line[i] -
			}
			}*/
			return line;
		}

		else {
			bufsize = 2 * bufsize;
			tmp = (char *)realloc(line, bufsize);
			if (tmp) {
				line = tmp;
				buffer = line + read_chars;
			}
			else {
				free(line);
				return NULL;
			}
		}
	}
	return NULL;
}
bool FileSearcher::isInFile(const char* srcFile, char * _string){
	FILE *fin;
	char line[512];
	bool check = false;
	fopen_s(&fin, srcFile, "r");

	if (fin) {

		while (fgets(line, sizeof(line), fin)) {
			for (unsigned int i = 0; i<strlen(line); i++){
				if (line[i] == '\r' || line[i] == '\n'){
					line[i] = '\0';
				}
			}
			if (strstr(line, _string)){
				//fprintf(stdout, "%s\n", line);
				check = true;
			}
			//free(line);
			if (check == true) break;
		}
		fclose(fin);
	}
	return check;
}
void FileSearcher::searchFile(char *dir, char *filename){



	WIN32_FIND_DATAA data;
	HANDLE hFind;
	if (strlen(dir) >= 1024) return;
	char dirPath[1024];
	sprintf_s(dirPath, 1024, "%s/*", dir);
	hFind = FindFirstFileA(dirPath, &data);
	if (hFind == INVALID_HANDLE_VALUE)
		return;
	do {
		/**/
		if (strcmp(data.cFileName, ".") != 0 &&
			strcmp(data.cFileName, "..") != 0)
		{
			/**/
			if (data.dwFileAttributes &
				(FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_HIDDEN
				| FILE_ATTRIBUTE_SYSTEM)
				){
				//printf("before char newDirPath[1024]\r\n");
				if (strlen(dir) + strlen(data.cFileName) + 2 >= 1024) return;
				char newDirPath[1024];
				//printf("after char newDirPath[1024]\r\n");

				sprintf_s(newDirPath, 1024, "%s/%s", dir, data.cFileName);
				//printf("after sprintf_s newDirPath %s\r\n",newDirPath);
				searchFile(newDirPath, filename);
			}
			else{

				if (isLike(filename, data.cFileName)){
					//printf("before char file[1024]\r\n");
					if (strlen(dir) + strlen(data.cFileName) + 2 >= 1024) return;
					char file[1024];
					//printf("after char file[1024]\r\n");
					sprintf_s(file, 1024, "%s/%s", dir, data.cFileName);
					//printf("after sprintf_s file\r\n");
					if (!FileSearcher::isInFile(c_fileSearch, file))
					{
						printf("<fil>%s\r\n", file);
						FILE * OUTPUT;
						fopen_s(&OUTPUT, c_fileSearch, "a+");
						if (OUTPUT != NULL){
							fprintf_s(OUTPUT, "%s\n", file);
							fclose(OUTPUT);
						}
					}
				}
			}

		}
	} while (FindNextFileA(hFind, &data) != 0);
	FindClose(hFind);
	return;
}

void FileSearcher::search(char *filename){
	char filePath[MAX_PATH];
	GetModuleFileNameA(NULL, filePath, MAX_PATH);
	if (GetLastError() == ERROR_SUCCESS){
		printf("GetModuleFileName Success: %s\r\n", filePath);
	}
	else{
		printf("GetModuleFileName Failed: %d\r\n", GetLastError());
	}
	int iFilePath = strlen(filePath);
	while (iFilePath >= 0 && filePath[iFilePath] != '\\'){
		filePath[iFilePath] = 0;
		iFilePath--;
	}
	if (filePath[iFilePath] == '\\') filePath[iFilePath] = 0;

	sprintf_s(c_fileSearch, 1024, "%s\\%s", filePath, FILE_SEARCH);

	DWORD mydrives = MAX_PATH;// buffer length
	char lpBuffer[MAX_PATH];// buffer for drive string storage
	DWORD test = GetLogicalDriveStringsA(mydrives, lpBuffer);
	printf(lpBuffer);
	vector<string> listLogicalDrive;
	printf("The logical drives of this machine are:\n\n");
	unsigned int i = 0;
	while (i<MAX_PATH - 2 && (lpBuffer[i + 1] != NULL && lpBuffer[i + 2] != NULL)){
		if ('A' <= lpBuffer[i] && lpBuffer[i] <= 'Z'){
			string logicalDriveName = "";
			int numChar = 0;
			while (lpBuffer[i] != NULL){
				numChar++;
				i++;
			}

			for (int temp = 0; temp<numChar - 1; temp++){
				logicalDriveName += lpBuffer[temp + i - numChar];
			}
			if (diskisfixed((char*)logicalDriveName.c_str()))
				listLogicalDrive.push_back(logicalDriveName);
		}
		i++;
	}
	printf("ListFile Done\r\n");
	//vector<string> listFile;
	for (i = 0; i<listLogicalDrive.size(); i++){
		//printf("[%3d] %s\r\n",i,listLogicalDrive.at(i).c_str());
		printDiskInfo((char*)listLogicalDrive.at(i).c_str());
	}
	Sleep(5000);
	//HANDLE file = CreateFile(FILE_SEARCH, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	for (i = 0; i<listLogicalDrive.size(); i++){
		searchFile((char *)listLogicalDrive.at(i).c_str(), filename);
	}

	return;
}