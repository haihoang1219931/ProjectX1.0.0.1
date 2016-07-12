#include <iostream>
#include <vector>
using namespace std;
const int TABLE_SIZE = 128;
class HashEntry {
private:
	char* section;
	char* key;
	char* value;
public:
	HashEntry(char* section, char* key, char* value) {
		this->section = section;
		this->key = key;
		this->value = value;
	}
	char* getSection(){
		return section;
	}
	char* getKey() {
		return key;
	}
	char* getValue() {
		return value;
	}
};

class HashMap {
private:
	vector<HashEntry> listHash;
public:
	HashMap() {
		;
	}
	vector<HashEntry> getListHash(){
		return listHash;
	}
	char* get(char* section, char* key) {
		char *result = NULL;
		
		for (int i = 0; i < (int)listHash.size(); i++){
			HashEntry temp = listHash[i];
			if (strcmp(section, temp.getSection()) == 0 &&
				strcmp(key, temp.getKey()) == 0){
				result = temp.getValue();
			}
		}
		return result;
	}
	void put(char* section, char* key, char* value) {
		listHash.push_back(HashEntry(section, key, value));
	}
	~HashMap() {
		listHash.~vector();
	}
};