#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include "structs.h"
#include "data.h"

#include "..\Common\defines.h"

class Config{
private:
	HashMap config;
public:
	Config();
	Config(char* pcData, int iDataSize);

	void init();
	void unit();
	HashMap getConfig();
	
	void LoadFileInResource(int name, int type, DWORD& size, char*& data);
	char*get(char*section, char*key);
	void loadData(char* pcData, int iDataSize);
	void loadDataInResource(int name, int type);
	void loadDataToCoreData(CORE_DATA* coreData);
	~Config(){ config.~HashMap();}
};
#endif