#include "stdafx.h"
#include "tools.h"
#include <iostream>
#include "fstream" 
#include "FileManage.h"

using namespace std;

//unsigned char Updated_Content[102400];
unsigned int uiCounter = 0;
unsigned int data_length;
unsigned int uiIndex = 0;

void HexFile::ReadFile(unsigned int uiLegth,char *pFileData, CStdioFile *filename)
{
	unsigned int uidex;
	unsigned char aucLength[2], aucAddress[4], aucType[2], aucData[64];
	unsigned char aucTempLenth[1], aucTempAddress[2], aucTempType[1], aucTempData[16];

	for (uidex = 0; uidex < uiLegth; uidex++)
	{
		memset(aucTempData, 0x00, 16);
		memset(aucData, 0x00, 64);

		HexFile::uiDataSize = 0;
		HexFile::uiStartAddress = 0;
		HexFile::ucDataType = 0;
		//HexFile::pucData = ((void *)0);

		if (pFileData[uidex] == ':')
		{
			/*Get the data length*/
			memcpy(&aucLength, &pFileData[uidex + 1], 2);
			CONV_AscHex(aucTempLenth, 1, aucLength, 2);
			HexFile::uiDataSize = aucTempLenth[0];

			/*Get the start address*/
			memcpy(&aucAddress, &pFileData[uidex + 3], 4);
			CONV_AscHex(aucTempAddress, 2, aucAddress, 4);
			HexFile::uiStartAddress = (unsigned short)aucTempAddress[1] + ((unsigned short)aucTempAddress[0] << 8);

			/*Get the data type*/
			memcpy(&aucType, &pFileData[uidex + 7], 2);
			CONV_AscHex(aucTempType, 1, aucType, 2);
			HexFile::ucDataType = aucTempType[0];

			if (HexFile::ucDataType == 0x04)
			{
				/*Get the data */
				memcpy(&aucData, &pFileData[uidex + 9], HexFile::uiDataSize * 2);
				CONV_AscHex(aucTempData, HexFile::uiDataSize, aucData, HexFile::uiDataSize * 2);
				HexFile::pucData = aucTempData;
				/*基地址*/
				HexFile::Based_Address = (((unsigned short)aucTempData[0] << 8) + (unsigned short)aucTempData[1]) << 16;
			}
			if (HexFile::ucDataType == 0x05)
			{
				/*Get the data */
				memcpy(&aucData, &pFileData[uidex + 9], HexFile::uiDataSize * 2);
				CONV_AscHex(aucTempData, HexFile::uiDataSize, aucData, HexFile::uiDataSize * 2);
				HexFile::pucData = aucTempData;
			}
			else if (HexFile::ucDataType == 0x00)
			{
				/*Get the data */
				memcpy(&aucData, &pFileData[uidex + 9], HexFile::uiDataSize * 2);
				CONV_AscHex(aucTempData, HexFile::uiDataSize, aucData, HexFile::uiDataSize * 2);
				HexFile::pucData = aucTempData;

				if (HexFile::uiDataSize == 0x10)
				{
					//memcpy(&Updated_Content[uiCounter*HexFile::uiDataSize], aucTempData, HexFile::uiDataSize);
				}
				else
				{
					//memcpy(&Updated_Content[uiCounter * 0x10], aucTempData, HexFile::uiDataSize);
					data_length = uiCounter * 0x10 + HexFile::uiDataSize;
				}
				uiCounter++;
				Hex_to_S19(HexFile::uiDataSize, aucData);
				//OutputFile << aucData << endl;
			}
			
			else if (HexFile::ucDataType == 0x01)
			{
				uiCounter = 0;
				if ((HexFile::uiDataSize == 0x00) && (HexFile::uiStartAddress == 0x0000))
				{
					//filename->Close();
				}
			}
			
		}
	}
}

void HexFile::Hex_to_S19(unsigned int Length, unsigned char *pData)
{
	unsigned int uiAddress;
	unsigned char ucIndex, ucLength, *pTempData, ucCheckSum, ucSumOfAddress, ucSumOfData;
	unsigned char aucS19Data[32], aucTempAddress[4], aucTempLenth[32], aucAddBuff[32], aucTempCheckSum[32];
	string DataType = "S3";

	pTempData = pData;
	ucSumOfData = 0x00;
	ofstream S19File;

	//S19File.open("F:\\VC++\\MFC_Application\\MFCApplication\\Release\\S19File.s19", ios::out | ios::app);
	S19File.open("S19File.s19", ios::out | ios::app);
	if (!S19File)//或者写成myfile.fail()  
	{
		//cout << "文件创建失败,磁盘不可写或者文件为只读!";
		system("pause");
		exit(1);
	}

	memset(aucTempLenth, 0x00, 32);
	memset(aucAddBuff, 0x00, 32);
	memset(aucS19Data, 0x00, 32);
	memset(aucTempCheckSum, 0x00, 32);

	ucLength = Length + 0x05;
	/* 0x25-->"25" */
	CONV_HexAsc(aucTempLenth, &ucLength, 2);

	/*转换地址数据十六进制数到ASCII码*/
	uiAddress = HexFile::Based_Address + uiIndex * 16;
	aucTempAddress[0] = (unsigned char)(uiAddress >> 24);
	aucTempAddress[1] = (unsigned char)(uiAddress >> 16);
	aucTempAddress[2] = (unsigned char)(uiAddress >> 8);
	aucTempAddress[3] = (unsigned char)uiAddress;
	CONV_HexAsc(aucAddBuff, aucTempAddress, 8);

	/*计算地址数据和*/
	ucSumOfAddress = aucTempAddress[0] + aucTempAddress[1] + aucTempAddress[2] + aucTempAddress[3];

	/*转换数据ASCII码到十六进制数*/
	CONV_AscHex(aucS19Data, 16, pTempData, 32);
	/*计算数据和*/
	for (ucIndex = 0x00; ucIndex<0x10; ucIndex++)
	{
		ucSumOfData += aucS19Data[ucIndex];
	}
	/*计算校验和*/
	ucCheckSum = 0xFF - (ucSumOfAddress + ucSumOfData);
	CONV_HexAsc(aucTempCheckSum, &ucCheckSum, 2);

	uiIndex++;
	/*将转换后的数据写入S19文件*/
	S19File << "S3" << aucTempLenth << aucAddBuff << pTempData << aucTempCheckSum << endl;
	S19File.close();
}