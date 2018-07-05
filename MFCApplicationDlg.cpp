
// MFCApplicationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "afxdialogex.h"
#include <assert.h>
#include "iostream"  
#include "fstream"
#include "FileManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMenu	h_Menu;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplicationDlg �Ի���
CMFCApplicationDlg::CMFCApplicationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION_DIALOG, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON4);
}

void CMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplicationDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplicationDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplicationDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplicationDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplicationDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplicationDlg::OnBnClickedButtonSave)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplicationDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplicationDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT4, &CMFCApplicationDlg::OnEnChangeEdit4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CMFCApplicationDlg::OnNMCustomdrawProgress1)
	ON_COMMAND(IDR_MENU1, &CMFCApplicationDlg::OnMenu1)
END_MESSAGE_MAP()


// CMFCApplicationDlg ��Ϣ�������

BOOL CMFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	h_Menu.LoadMenu(IDR_MENU1);  //  IDR_MENU1Ϊ�����Ĳ˵���ID����Resource��ͼ��Menu�ļ����¿����ҵ�,���������ʾ��˵IDR_MENU1û�ж���Ļ�����������������⣬IDһ����������ʾû�ж��壬���������½���һ�����̾ͽ���ˣ���
	SetMenu(&h_Menu);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplicationDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HINSTANCE hRslt = ShellExecute(NULL, _T("open"),

		_T("calc.exe"), NULL, NULL, SW_SHOWNORMAL);

	assert(hRslt > (HINSTANCE)HINSTANCE_ERROR);
}


void CMFCApplicationDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HINSTANCE hRslt = ShellExecute(NULL, _T("open"),

		_T("notepad.EXE"), NULL, NULL, SW_SHOWNORMAL);

	assert(hRslt > (HINSTANCE)HINSTANCE_ERROR);
}


void CMFCApplicationDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HINSTANCE hRslt = ShellExecute(NULL, _T("open"),

		_T("Nslookup.EXE"), NULL, NULL, SW_SHOWNORMAL);

	assert(hRslt > (HINSTANCE)HINSTANCE_ERROR);
}


void CMFCApplicationDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CMFCApplicationDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CMFCApplicationDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	BOOL isOpen = TRUE;		//�Ƿ��(����Ϊ����)
	CString defaultDir = L"E:\\FileTest";	//Ĭ�ϴ򿪵��ļ�·��
	CString fileName = L"";			//Ĭ�ϴ򿪵��ļ���
	CString filter = L"�ļ� (*.doc; *.ppt; *.xls;*.hex;*.s19)|*.doc;*.ppt;*.xls;*.hex;*.s19||";	//�ļ����ǵ�����
	CString filename;
	//��Ӷ�ȡ����ļ����ݵĴ��룬CFile::modeRead��˵��ֻ���ļ���ģʽ��
	CStdioFile file;
	HexFile HexTypeFile;

	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\test.doc";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\test.doc";
	if (result == IDOK) 
	{
		filePath = openFileDlg.GetPathName();
		filename = openFileDlg.GetFileName();

		file.Open(filePath, CFile::modeRead);
		//���ж�ȡ�ַ���
		CString szLine;
		CString strText;
		CString strData;

		int strLength2;
		char chArray[100];

		memset(chArray, 0, sizeof(bool) * 100); //������������������.

		while (file.ReadString(szLine))
		{
			strText += szLine;
			strData += szLine;
			strText += "\r\n";
			strData += "\r\n";
			strLength2 = strText.GetLength() + 1;

			/* CStringת����char* */
			USES_CONVERSION;
			char* pBuf = T2A(strText.GetBuffer(0));
			strText.ReleaseBuffer();

			/*ת��*.hex to *.s19*/
			HexTypeFile.ReadFile(strLength2, pBuf, &file);
			strText = "";
		}
		//����õ���strText�������������ڲ������ݣ��õ�����֮�����ǾͿ��Խ���������Ҫ���еĲ�����
		SetDlgItemText(IDC_EDIT3, strData);//������ʱ�����ǽ����ǵ�������ʾ��ID��ID_showBox������У�ʵ��������һ���༭��

		/*CString str;
		memcpy(chArray, pBuf, 20);
		str = chArray;
		str += "\r\n";
		SetDlgItemText(IDC_EDIT4, str);*/
		//�ر��ļ�
		file.Close();

	}
	CWnd::SetDlgItemText(IDC_EDIT1, filePath);
}


void CMFCApplicationDlg::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL isOpen = FALSE;		//�Ƿ��(����Ϊ����)
	CString defaultDir = L"E:\\FileTest";	//Ĭ�ϴ򿪵��ļ�·��
	CString fileName = L"test.doc";			//Ĭ�ϴ򿪵��ļ���
	CString filter = L"�ļ� (*.doc; *.ppt; *.xls)|*.doc;*.ppt;*.xls||";	//�ļ����ǵ�����
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\test.doc";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;
	if (result ==IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	CWnd::SetDlgItemTextW(IDC_EDIT2, filePath);

}

void CMFCApplicationDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplicationDlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplicationDlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CProgressCtrl *myProCtrl2 = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);

	myProCtrl2->SetRange(0, 100);
	for (int i = 0; i<100; i++)
	{
		//myProCtrl2->OffsetPos(1); //�˾�����ͬ�������䣬�Թ̶�����1������ʾ���ù���Ҳ��������ʵ�֣�myProCtrl2->SetPos(i); 
		//myProCtrl2->SetStep(1);
		//myProCtrl2->StepIt();
		//Sleep(100);

		myProCtrl2->OffsetPos(1);
		CString str;
		str.Format(_T("%d%%"), i); //�ٷֱ�
		(GetDlgItem(IDC_PROGRESS1))->SetWindowText(str);
		Sleep(100);
	}
}


void CMFCApplicationDlg::OnMenu1()
{
	// TODO: �ڴ���������������
}
