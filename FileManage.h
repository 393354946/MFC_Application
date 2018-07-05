#pragma once
class HexFile
{
public:
	unsigned int uiDataSize;        //数据长度
	unsigned short uiStartAddress;  //地址
	unsigned char ucDataType;		//数据类型
	unsigned char *pucData;			//数据

	unsigned int Based_Address;		/*线性基地址*/

	void ReadFile(unsigned int uiLegth, char *pFileData, CStdioFile *filename);
	void Hex_to_S19(unsigned int Length, unsigned char *pData);
};