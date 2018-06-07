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
	printf("��С=%.3f,���=%.3f\n", minval, maxval);
	printf("ƽ��=%.3f,��׼��=%.3f\n", meanval, stddev);

}
int main()
{
	GDALAllRegister();
	
# pragma region shp�ļ���
	//GDALDataset   *poDS;
	//CPLSetConfigOption("SHAPE_ENCODING", "");  //���������������
	////��ȡshp�ļ�
	//poDS = (GDALDataset*)GDALOpenEx("D:/shp/bou2_4p.shp", GDAL_OF_VECTOR, NULL, NULL, NULL);

	//if (poDS == NULL)
	//{
	//	printf("Open failed.\n%s");
	//	return 0;
	//}

	//OGRLayer  *poLayer;
	//poLayer = poDS->GetLayer(0); //��ȡ��
	//OGRFeature *poFeature;

	//poLayer->ResetReading();
	//int i = 0;
	//while ((poFeature = poLayer->GetNextFeature()) != NULL)
	//{
	//	if (poFeature->GetFieldAsDouble("AREA")<1) continue; //ȥ�������С��polygon
	//	i = i++;
	//	cout <<i << "  ";
	//	OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
	//	int iField;
	//	int n = poFDefn->GetFieldCount(); //����ֶε���Ŀ��������ǰ�����ֶΣ�FID,Shape);
	//	for (iField = 0; iField <n; iField++)
	//	{
	//		//���ÿ���ֶε�ֵ
	//		cout << poFeature->GetFieldAsString(iField) << "    ";
	//	}
	//	cout << endl;
	//	OGRFeature::DestroyFeature(poFeature);
	//}
	//GDALClose(poDS);

#pragma endregion

#pragma region ��GeoTiff
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
	//int imgWidth = img[0]->GetRasterXSize();   //ͼ����
	//int imgHeight = img[0]->GetRasterYSize();  //ͼ��߶�
	//int bandNum = img[0]->GetRasterCount();    //������
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
	int Width = img[0]->GetRasterXSize();   //ͼ����
	int Height = img[0]->GetRasterYSize();  //ͼ��߶�
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
	//printf("��С=%.3f,���=%.3f\n", minval, maxval);
	//printf("ƽ��=%.3f,��׼��=%.3f\n", meanval, stddev);
	//cout << "��С: " << minval << "���: " << maxval << endl<< "ƽ��: " << meanval <<endl<< "��׼��: " << stddev << endl;
#pragma endregion


	//GDALClose(img);
	system("pause");
	cin.get();
	return 1;
}