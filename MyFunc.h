#ifndef MY_FUNC
#define MY_FUNC

#include<cv.h>

using namespace cv;

class CMyFunc{
public:
	int intMin(int intA,int intB);
	int intMax(int intA,int intB);
	Mat mergeMat;
public:
	string int2str(int A);
	void MatMerge(Mat srcMat1,Mat srcMat2);

};

string CMyFunc::int2str(int A){
	string strA;
	std::stringstream  temp;
	temp << A;
	temp >> strA;
	return strA;
}

int CMyFunc::intMin(int intA,int intB){
	int intMin;
	if(intA >= intB) intMin = intB;
	if(intB >= intA) intMin = intA;
	return intMin;
}
int CMyFunc::intMax(int intA,int intB){
	int intMax;
	if(intA <= intB) intMax = intB;
	if(intB <= intA) intMax = intA;
	return intMax;
}

void CMyFunc::MatMerge(Mat srcMat1,Mat srcMat2){
	int dstRow = srcMat1.rows+srcMat2.rows;
	int dstCol = srcMat1.cols;
	mergeMat = Mat::zeros(dstRow,dstCol,CV_32FC1);
	for(int i=0;i<intMax(srcMat1.cols,srcMat2.cols);i++){
		for(int j=0; j<intMax(srcMat1.rows,srcMat2.rows);j++){
			if((i<srcMat1.cols)&&(j<srcMat1.rows))	mergeMat.at<float>(j,i)=srcMat1.at<float>(j,i);
			if((i<srcMat2.cols)&&(j<srcMat2.rows))	mergeMat.at<float>(j+srcMat1.rows,i)=srcMat2.at<float>(j,i);
		}
	}
}

#endif
