#pragma once
class HexFile
{
public:
	unsigned int uiDataSize;        //���ݳ���
	unsigned short uiStartAddress;  //��ַ
	unsigned char ucDataType;		//��������
	unsigned char *pucData;			//����

	unsigned int Based_Address;		/*���Ի���ַ*/

	void ReadFile(unsigned int uiLegth, char *pFileData, CStdioFile *filename);
	void Hex_to_S19(unsigned int Length, unsigned char *pData);
};