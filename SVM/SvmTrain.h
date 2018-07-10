#ifndef SVM_TRAIN
#define SVM_TRAIN

#include<stdio.h>
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include"cv.h"
#include"highgui.h"
#include"ml.h"
#include"hogTrain.h"
#include"MyFunc.h"

using namespace std;
using namespace cv;

class mySVM : public CvSVM//通过查看CvSVM源码可知decision_func参数是protected类型变量，无法直接访问到，只能继承之后通过函数访问
{
public:
  //获得SVM的决策函数中的alpha数组
  double * get_alpha_vector()
  {
    return this->decision_func->alpha;
  }

  //获得SVM的决策函数中的rho参数,即偏移量
  float get_rho()
  {
    return this->decision_func->rho;
  }
};

class CSvmTrain{
public:
	string strSVMPath;
//	vector<string> strPosLib;
//	vector<string> strNegLib;

public:
	CSvmTrain();
	~CSvmTrain();
	void SvmTrain(cv::Mat HogFeature,cv::Mat HogResult,int intPosNum,int intNegNum,cv::Size windSize,cv::Size cellSize);
};

CSvmTrain::CSvmTrain(){
	string strSVMPath = "/home/hitomi/SVM/";
}
CSvmTrain::~CSvmTrain(){

}
void CSvmTrain::SvmTrain(cv::Mat HogFeature,cv::Mat HogResult,int intPosNum,int intNegNum,cv::Size windSize,cv::Size cellSize){
	mySVM svm;CMyFunc MyFunc;
	CvSVMParams param;
	CvTermCriteria criteria;
	string w = MyFunc.int2str(windSize.width);
	string h = MyFunc.int2str(windSize.height);
	criteria = cvTermCriteria( CV_TERMCRIT_EPS, 1000, FLT_EPSILON );
	param = CvSVMParams( CvSVM::C_SVC, CvSVM::LINEAR, 0, 1, 0, 0.01, 0, 0, 0, criteria);
	svm.train(HogFeature, HogResult, Mat(), Mat(), param );
	svm.save( (strSVMPath+w+"X"+h+"SVM_DATA.XML").c_str() );
	cout<<"The path of 'XML' :"<<strSVMPath<<w+"X"+h+"SVM_DATA.XML"<<endl;
	int descriptorDim=svm.get_var_count();
	int supportVectorNum=svm.get_support_vector_count();
	Mat alphaMat=Mat::zeros(1,supportVectorNum,CV_32FC1);
	Mat supportVectorMat=Mat::zeros(supportVectorNum,descriptorDim,CV_32FC1);
	Mat svmResultMat=Mat::zeros(1,descriptorDim,CV_32FC1);

	for(int i=0;i<supportVectorNum;i++)
	{
		const float *pSVMData=svm.get_support_vector(i);
		for(int j=0;j<descriptorDim;j++)
		{
			supportVectorMat.at<float>(i,j)=pSVMData[j];
		}
	}
	double *pAlphaData=svm.get_alpha_vector();

	for(int i=0;i<supportVectorNum;i++)
	{
		alphaMat.at<float>(0,i)=pAlphaData[i];
	}

	svmResultMat=-1*alphaMat*supportVectorMat;

	vector<float> myDetector;

		for(int i=0;i<descriptorDim;i++)
		{
			myDetector.push_back(svmResultMat.at<float>(0,i));
		}
		myDetector.push_back(svm.get_rho());
//		cout<<"my detector dims:"<<myDetector.size()<<endl;
		HOGDescriptor myHOG(windSize,cvSize(cellSize.width*2,cellSize.height*2),cellSize,cellSize,9);
		myHOG.setSVMDetector(myDetector);
		string strHogPath = strSVMPath+w+"X"+h+"hog.dat";
		std::ofstream outSVM(strHogPath.c_str());///home/hitomi/picture/back_container/hog.txt
		cout<<"The path of 'txt':"<<strHogPath;
		for(unsigned int i=0;i<myDetector.size(); i++)
		{
			outSVM<<myDetector[i]<<endl;
		}
		outSVM.close();
}


#endif
