#include<iostream>
#include"gdal.h"
#include"gdal_priv.h"
#include"gdalwarper.h"
#include"ogrsf_frmts.h"
using namespace std;
void Get(GDALDataset* GD,double & mv,double & st)
{
	GDALRasterBand    *poBand;
	int               nBlockXSize, nBlockYSize;
	int               bGotMin, bGotMax;
	//double            adfMinMax[2];
	poBand = GD->GetRasterBand(1);
	poBand->GetBlockSize(&nBlockXSize, &nBlockYSize);
	/*printf("Block=%dx%d Type=%s, ColorInterp=%s\n",
		nBlockXSize, nBlockYSize,
		GDALGetDataTypeName(poBand->GetRasterDataType()),
		GDALGetColorInterpretationName(
		poBand->GetColorInterpretation()));*/
/*
	adfMinMax[0] = poBand->GetMinimum(&bGotMin);
	adfMinMax[1] = poBand->GetMaximum(&bGotMax);
	if (!(bGotMin && bGotMax))
		GDALComputeRasterMinMax((GDALRasterBandH)poBand, TRUE, adfMinMax);

	printf("Min=%.3f, Max=%.3f\n", adfMinMax[0], adfMinMax[1]);
*/
	/*if (poBand->GetOverviewCount() > 0)
		printf("Band has %d overviews./n", poBand->GetOverviewCount());

	if (poBand->GetColorTable() != NULL)
		printf("Band has a color table with %d entries./n",
		poBand->GetColorTable()->GetColorEntryCount());
*/
	// Reading Raster Data
	float *pafScanline;
	int     nXSize = poBand->GetXSize();

	pafScanline = (float *)CPLMalloc(sizeof(float)*nXSize);
	poBand->RasterIO(GF_Read, 0, 0, nXSize, 1,
		pafScanline, nXSize, 1, GDT_Float32,
		0, 0);
	double minval, maxval, meanval, stddev;
	poBand->GetStatistics(FALSE, TRUE, &minval, &maxval, &meanval, &stddev);
	mv = meanval;
	st = stddev;
	printf("最小=%.3f,最大=%.3f\n", minval, maxval);
	printf("平均=%.3f,标准差=%.3f\n", meanval, stddev);

}
int main()
{
	GDALAllRegister();
	
# pragma region shp文件打开
	//GDALDataset   *poDS;
	//CPLSetConfigOption("SHAPE_ENCODING", "");  //解决中文乱码问题
	////读取shp文件
	//poDS = (GDALDataset*)GDALOpenEx("D:/shp/bou2_4p.shp", GDAL_OF_VECTOR, NULL, NULL, NULL);

	//if (poDS == NULL)
	//{
	//	printf("Open failed.\n%s");
	//	return 0;
	//}

	//OGRLayer  *poLayer;
	//poLayer = poDS->GetLayer(0); //读取层
	//OGRFeature *poFeature;

	//poLayer->ResetReading();
	//int i = 0;
	//while ((poFeature = poLayer->GetNextFeature()) != NULL)
	//{
	//	if (poFeature->GetFieldAsDouble("AREA")<1) continue; //去掉面积过小的polygon
	//	i = i++;
	//	cout <<i << "  ";
	//	OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
	//	int iField;
	//	int n = poFDefn->GetFieldCount(); //获得字段的数目，不包括前两个字段（FID,Shape);
	//	for (iField = 0; iField <n; iField++)
	//	{
	//		//输出每个字段的值
	//		cout << poFeature->GetFieldAsString(iField) << "    ";
	//	}
	//	cout << endl;
	//	OGRFeature::DestroyFeature(poFeature);
	//}
	//GDALClose(poDS);

#pragma endregion

#pragma region 打开GeoTiff
	GDALDataset * img[9];
	int imgWidth[9];
	int imgHeight[9];
	double m[9], s[9];
//X:\ETM
	img[0] = (GDALDataset*)GDALOpen("D:/ETM/b11.tif", GA_ReadOnly);
	/*img[1] = (GDALDataset*)GDALOpen("D:/ETM/b62.tif", GA_ReadOnly);
	img[2] = (GDALDataset*)GDALOpen("D:/ETM/b1.tif", GA_ReadOnly);
	img[3] = (GDALDataset*)GDALOpen("D:/ETM/b2.tif", GA_ReadOnly);
	img[4] = (GDALDataset*)GDALOpen("D:/ETM/b3.tif", GA_ReadOnly);
	img[5] = (GDALDataset*)GDALOpen("D:/ETM/b4.tif", GA_ReadOnly);
	img[6] = (GDALDataset*)GDALOpen("D:/ETM/b5.tif", GA_ReadOnly);
	img[7] = (GDALDataset*)GDALOpen("D:/ETM/b7.tif", GA_ReadOnly);
	img[8]=(GDALDataset*)GDALOpen("D:/ETM/b8.tif", GA_ReadOnly);*/

	/*img[0] = (GDALDataset*)GDALOpen("C:/Users/chang/Desktop/B4.tif", GA_ReadOnly);
	img[1] = (GDALDataset*)GDALOpen("C:/Users/chang/Desktop/B5.tif", GA_ReadOnly);*/
	/*if (img[0] == NULL)
	{
		return 0;
	}*/
	//int imgWidth = img[0]->GetRasterXSize();   //图像宽度
	//int imgHeight = img[0]->GetRasterYSize();  //图像高度
	//int bandNum = img[0]->GetRasterCount();    //波段数
	//int depth = GDALGetDataTypeSize(img[0]->GetRasterBand(1)->GetRasterDataType());
	/*Get(img[0],m[0],s[0]);
	Get(img[1], m[1], s[1]); 
	Get(img[2], m[2], s[2]); 
	Get(img[3], m[3], s[3]); 
	Get(img[0], m[0], s[0]); 
	Get(img[0], m[0], s[0]);
	Get(img[0], m[0], s[0]);
	Get(img[0], m[0], s[0]);*/



	/*for (int i = 0; i < 9; i++)
	{
		cout << i+1 << endl;
		Get(img[i], m[i], s[i]);

	}*/
	GDALRasterBand    *poBand;
	int               nBlockXSize, nBlockYSize;
	int               bGotMin, bGotMax;
	int Width = img[0]->GetRasterXSize();   //图像宽度
	int Height = img[0]->GetRasterYSize();  //图像高度
	poBand = img[0]->GetRasterBand(1);
	
	float adfPixel;

	adfPixel = 0.0;

	float *lineData = NULL;

	lineData = new float[1 * poBand->GetXSize()];

	for (int iLine = 0; iLine < poBand->GetYSize(); iLine++)

	{

		poBand->RasterIO(GF_Read, 0, iLine, poBand->GetXSize(), 1,

			lineData, poBand->GetXSize(), 1, GDT_Float32, 0, 0);



		for (int iPixel = 0; iPixel < poBand->GetXSize(); iPixel++)



		{

			adfPixel = lineData[iPixel];
			
		}

	}
	for (int i = 0; i < Width*Height; i++)
	{
		cout << lineData[i]<<endl;

	}
	if (lineData)

	{

		delete[]lineData;

		lineData = NULL;

	}
	
	
	cin.get();
	//cout << t1;
	//GDALRasterBand    *poBand;
	//int               nBlockXSize, nBlockYSize;
	//int               bGotMin, bGotMax;
	//double            adfMinMax[2];
	//poBand = img[0]->GetRasterBand(1);
	//poBand->GetBlockSize(&nBlockXSize, &nBlockYSize);
	//printf("Block=%dx%d Type=%s, ColorInterp=%s\n",
	//	nBlockXSize, nBlockYSize,
	//	GDALGetDataTypeName(poBand->GetRasterDataType()),
	//	GDALGetColorInterpretationName(
	//	poBand->GetColorInterpretation()));

	//adfMinMax[0] = poBand->GetMinimum(&bGotMin);
	//adfMinMax[1] = poBand->GetMaximum(&bGotMax);
	//if (!(bGotMin && bGotMax))
	//	GDALComputeRasterMinMax((GDALRasterBandH)poBand, TRUE, adfMinMax);

	//printf("Min=%.3f, Max=%.3f\n", adfMinMax[0], adfMinMax[1]);

	//if (poBand->GetOverviewCount() > 0)
	//	printf("Band has %d overviews./n", poBand->GetOverviewCount());

	//if (poBand->GetColorTable() != NULL)
	//	printf("Band has a color table with %d entries./n",
	//	poBand->GetColorTable()->GetColorEntryCount());

	//// Reading Raster Data
	//float *pafScanline;
	//int     nXSize = poBand->GetXSize();

	//pafScanline = (float *)CPLMalloc(sizeof(float)*nXSize);
	//poBand->RasterIO(GF_Read, 0, 0, nXSize, 1,
	//	pafScanline, nXSize, 1, GDT_Float32,
	//	0, 0);
	//double minval, maxval, meanval, stddev;
	//poBand->GetStatistics(FALSE, TRUE, &minval, &maxval, &meanval, &stddev);
	//printf("最小=%.3f,最大=%.3f\n", minval, maxval);
	//printf("平均=%.3f,标准差=%.3f\n", meanval, stddev);
	//cout << "最小: " << minval << "最大: " << maxval << endl<< "平均: " << meanval <<endl<< "标准差: " << stddev << endl;
#pragma endregion


	//GDALClose(img);
	system("pause");
	cin.get();
	return 1;
}