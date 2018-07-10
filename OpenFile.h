#ifndef OPEN_FILE
#define OPEN_FILE


#include "dirent.h"
#include <string.h>
#include <stdio.h>
#include<vector>
#include<sys/types.h>
#include <iostream>
#include<fstream>


using namespace std;

class  COpenFile{
public:
	vector<string> strOpenFileDir(string strFileDirectory);
};

vector<string> COpenFile::strOpenFileDir(string strFileDirectory){
	DIR* dir = NULL;
	dirent* dirInfo = NULL;
	vector<string> strFileName;
//	ofstream sFileName((strFileDirectory).c_str());
	const char* chrTempFile= strFileDirectory.c_str();
	char chrTempName [256];
//	string strTempName;
	dir=opendir(chrTempFile);
	if(dir){
		while((dirInfo=readdir(dir))!=NULL){
			if(strcmp(dirInfo->d_name,".")==0 || strcmp(dirInfo->d_name,"..")==0) continue;
			strcpy_s(chrTempName,chrTempFile);
			strcat_s(chrTempName,dirInfo->d_name);
//			strTempName = chrTempName;
//			sFileName<<strTempName;
			strFileName.push_back(chrTempName);
//			cout<<chrTempName<<endl;
		}
//		sFileName.close();
		if(!closedir(dir)) return strFileName;
		return strFileName;

	}
	else{
		return strFileName;
	}
}

#endif
