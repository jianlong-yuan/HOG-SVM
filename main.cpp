//============================================================================
// Name        : SVMTrain.cpp
// Author      : yjl9122
// Version     : version 2018/07/10
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "dirent.h"
#include <string.h>
#include<vector>
#include <stdio.h>
#include<sys/types.h>
#include<iostream>
#include <sstream>

#include"cv.h"
#include"highgui.h"
#include"ml.h"
#include"SvmTrain.h"
#include"hogTrain.h"
#include"MyFunc.h"

#include "OpenFile.h"
using namespace std;
using namespace cv;
COpenFile MyOpenFile;
CSvmTrain MySvmTrain;
CHogTrain MyposTrain;
CHogTrain MynegTrain;
CHogTrain MyhardTrain;

CMyFunc	 MyFeaturefunc,MyLabelfunc;

vector<string> strPosFile;
vector<string> strNegFile;
vector<string> strHardFile;

int PosNum = 55;
int NegNum = 206;
int HardNum = 0;

cv::Size hogWindSize(64,64);
cv::Size hogCellSize(8,8);
string MySvmPath = "C:\\Users\\work\Desktop\\jieguo\\1\\";
string MyPosDir="C:\\Users\\work\\Desktop\\muban\\11\\";
string MyNegDir="C:\\Users\\work\\Desktop\\muban\\__fail\\";
string MyHardDir = "C:\\Users\\work\\Desktop\\jieguo\\2\\";

int main() {
	strPosFile = MyOpenFile.strOpenFileDir(MyPosDir);
	strNegFile = MyOpenFile.strOpenFileDir(MyNegDir);
	strHardFile = MyOpenFile.strOpenFileDir(MyHardDir);
	MyposTrain.HogTrain(strPosFile,1,PosNum,hogWindSize,hogCellSize);
	MynegTrain.HogTrain(strNegFile,-1,NegNum,hogWindSize,hogCellSize);

	if (HardNum != 0) {
		MyhardTrain.HogTrain(strHardFile, -1, HardNum, hogWindSize, hogCellSize);
	}

	MyFeaturefunc.MatMerge(MyposTrain.matHogFeature,MynegTrain.matHogFeature);

	if (HardNum != 0) {
		MyFeaturefunc.MatMerge(MyFeaturefunc.mergeMat, MyhardTrain.matHogFeature);
	}

	MyLabelfunc.MatMerge(MyposTrain.matHogResult,MynegTrain.matHogResult);

	if (HardNum != 0) {
		MyLabelfunc.MatMerge(MyLabelfunc.mergeMat, MyhardTrain.matHogResult);
	}

	MySvmTrain.strSVMPath = MySvmPath;
	cout << MyLabelfunc.mergeMat << endl;

	MySvmTrain.SvmTrain(MyFeaturefunc.mergeMat,MyLabelfunc.mergeMat,PosNum,NegNum+HardNum,hogWindSize,hogCellSize);
	return 0;
}
