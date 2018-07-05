
// MFCApplicationDlg.cpp : 实现文件
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
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCApplicationDlg 对话框
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


// CMFCApplicationDlg 消息处理程序

BOOL CMFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	h_Menu.LoadMenu(IDR_MENU1);  //  IDR_MENU1为你加入的菜单的ID，在Resource视图的Menu文件夹下可以找到,如果代码提示中说IDR_MENU1没有定义的话（我遇到了这个问题，ID一样，但是提示没有定义，我是重新新建了一个工程就解决了）。
	SetMenu(&h_Menu);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplicationDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	HINSTANCE hRslt = ShellExecute(NULL, _T("open"),

		_T("calc.exe"), NULL, NULL, SW_SHOWNORMAL);

	assert(hRslt > (HINSTANCE)HINSTANCE_ERROR);
}


void CMFCApplicationDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	HINSTANCE hRslt = ShellExecute(NULL, _T("open"),

		_T("notepad.EXE"), NULL, NULL, SW_SHOWNORMAL);

	assert(hRslt > (HINSTANCE)HINSTANCE_ERROR);
}


void CMFCApplicationDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	HINSTANCE hRslt = ShellExecute(NULL, _T("open"),

		_T("Nslookup.EXE"), NULL, NULL, SW_SHOWNORMAL);

	assert(hRslt > (HINSTANCE)HINSTANCE_ERROR);
}


void CMFCApplicationDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCApplicationDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCApplicationDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码

	BOOL isOpen = TRUE;		//是否打开(否则为保存)
	CString defaultDir = L"E:\\FileTest";	//默认打开的文件路径
	CString fileName = L"";			//默认打开的文件名
	CString filter = L"文件 (*.doc; *.ppt; *.xls;*.hex;*.s19)|*.doc;*.ppt;*.xls;*.hex;*.s19||";	//文件过虑的类型
	CString filename;
	//添加读取这个文件内容的代码，CFile::modeRead是说以只读文件的模式打开
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
		//逐行读取字符串
		CString szLine;
		CString strText;
		CString strData;

		int strLength2;
		char chArray[100];

		memset(chArray, 0, sizeof(bool) * 100); //将数组的垃圾内容清空.

		while (file.ReadString(szLine))
		{
			strText += szLine;
			strData += szLine;
			strText += "\r\n";
			strData += "\r\n";
			strLength2 = strText.GetLength() + 1;

			/* CString转换成char* */
			USES_CONVERSION;
			char* pBuf = T2A(strText.GetBuffer(0));
			strText.ReleaseBuffer();

			/*转换*.hex to *.s19*/
			HexTypeFile.ReadFile(strLength2, pBuf, &file);
			strText = "";
		}
		//这里得到的strText就是我们文章内部的内容，得到内容之后我们就可以进行我们需要进行的操作了
		SetDlgItemText(IDC_EDIT3, strData);//这里是时候我们将我们的内容显示到ID是ID_showBox的组件中（实际上这是一个编辑框）

		/*CString str;
		memcpy(chArray, pBuf, 20);
		str = chArray;
		str += "\r\n";
		SetDlgItemText(IDC_EDIT4, str);*/
		//关闭文件
		file.Close();

	}
	CWnd::SetDlgItemText(IDC_EDIT1, filePath);
}


void CMFCApplicationDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL isOpen = FALSE;		//是否打开(否则为保存)
	CString defaultDir = L"E:\\FileTest";	//默认打开的文件路径
	CString fileName = L"test.doc";			//默认打开的文件名
	CString filter = L"文件 (*.doc; *.ppt; *.xls)|*.doc;*.ppt;*.xls||";	//文件过虑的类型
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplicationDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplicationDlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CProgressCtrl *myProCtrl2 = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);

	myProCtrl2->SetRange(0, 100);
	for (int i = 0; i<100; i++)
	{
		//myProCtrl2->OffsetPos(1); //此句代码等同于下两句，以固定步长1更新显示，该功能也可以这样实现：myProCtrl2->SetPos(i); 
		//myProCtrl2->SetStep(1);
		//myProCtrl2->StepIt();
		//Sleep(100);

		myProCtrl2->OffsetPos(1);
		CString str;
		str.Format(_T("%d%%"), i); //百分比
		(GetDlgItem(IDC_PROGRESS1))->SetWindowText(str);
		Sleep(100);
	}
}


void CMFCApplicationDlg::OnMenu1()
{
	// TODO: 在此添加命令处理程序代码
}
