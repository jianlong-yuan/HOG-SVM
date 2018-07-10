#ifndef HOG_TRAIN
#define HOG_TRAIN

#include<stdio.h>
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include"cv.h"
#include"highgui.h"
#include"ml.h"
#include"MyFunc.h"

using namespace std;
using namespace cv;

class CHogTrain{
public:
	HOGDescriptor hog;
	Mat matHogFeature;
	Mat matHogResult;

public:

	void HogTrain(vector<string> strTrainLib,float fLabel,int intNum,cv::Size windSize,cv::Size cellSize);

};

void CHogTrain::HogTrain(vector<string> strTrainLib,float fLabel,int intNum,cv::Size windSize,cv::Size cellSize){
	CMyFunc my_func;
	HOGDescriptor hog(windSize,cvSize(cellSize.width*2,cellSize.height*2),cellSize,cellSize,9);
	int intDescripDims;
	int intTrainNum = my_func.intMin(intNum,strTrainLib.size());
	Mat matTemp;
	//…Ë÷√trainimage¥Û–°
	Mat HogImg;

	for(int j=0; j < intTrainNum;j++){
		string strHogImg = strTrainLib[j];
		cout<<"processing: "<<fLabel<< strTrainLib[j]<<endl;
		Mat trainImg = imread(strHogImg);
		if (trainImg.empty()){
			cout << strTrainLib[j] << " read error" << endl;
			continue;
		}
		resize(trainImg, HogImg, Size(64, 64));
		vector<float> descriptors;
		hog.compute(HogImg, descriptors, Size(1, 1), Size(0, 0));
		if(j == 0){
			intDescripDims = descriptors.size();
			matHogFeature = Mat::zeros(intTrainNum,intDescripDims,CV_32FC1);
			matHogResult = Mat::zeros(intTrainNum,1,CV_32FC1);
		}
		for(int i=0;i < intDescripDims; i++){
			matHogFeature.at<float>(j,i) = descriptors[i];
			matHogResult.at<float>(j,0)= fLabel;
		}
	}

}

#endif
