// Statistic.cpp: 实现文件
//

#include "pch.h"
#include "SuperMarketManagement.h"
#include "afxdialogex.h"
#include "Statistic.h"
#include "utils.h"

// Statistic 对话框

IMPLEMENT_DYNAMIC(Statistic, CDialogEx)

Statistic::Statistic(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STATISTIC, pParent)
{

}

Statistic::~Statistic()
{
}

void Statistic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STATISTIC, Combo);
}


BEGIN_MESSAGE_MAP(Statistic, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_STATISTIC, &Statistic::OnCbnSelchangeComboStatistic)
END_MESSAGE_MAP()


// Statistic 消息处理程序


BOOL Statistic::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化列表
	Combo.AddString(_T("订单数"));
	Combo.AddString(_T("营业额"));
	//默认显示订单数
	Combo.SetCurSel(0);
	int num = 0;
	sqlite.executeSQLWithRet(L"SELECT quantity FROM Sales",
		[&](std::vector<tstring>& lst) -> void
		{
			num++;
		}
	);

	CEdit* pEdit = (CEdit*)this->GetDlgItem(IDC_EDIT_STATISTIC);
	pEdit->SetWindowTextW(std::format(L"{}", num).c_str());


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Statistic::OnCbnSelchangeComboStatistic()
{
	// TODO: 在此添加控件通知处理程序代码
	int num = 0;
	int index = Combo.GetCurSel();
	CEdit* pEdit = (CEdit*)this->GetDlgItem(IDC_EDIT_STATISTIC);

	switch (index)
	{
		// 订单数
	case 0:
		num = 0;
		sqlite.executeSQLWithRet(L"SELECT quantity FROM Sales",
			[&](std::vector<tstring>& lst) -> void
			{
				num++;
			}
		);
		pEdit->SetWindowTextW(std::format(L"{}", num).c_str());
		break;
		// 营业额
	case 1:
		num = 0;
		sqlite.executeSQLWithRet(L"SELECT price, quantity FROM Sales",
			[&](std::vector<tstring>& lst) -> void
			{
				num += std::atoi(utils::wstring2string(lst[0].c_str()).c_str()) * 
					   std::atoi(utils::wstring2string(lst[1].c_str()).c_str());
			}
		);
		pEdit->SetWindowTextW(std::format(L"{}", num).c_str());
		break;

	default:
		break;
	}
}
