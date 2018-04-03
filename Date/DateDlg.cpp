
// DateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Date.h"
#include "DateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDateDlg* dlg_backup;

// CDateDlg 对话框




CDateDlg::CDateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDateDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BEXIT, &CDateDlg::OnBnClickedBexit)
END_MESSAGE_MAP()


// CDateDlg 消息处理程序

BOOL CDateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);//获取系统时间
	int year=SystemTime.wYear;
	int month=SystemTime.wMonth;
	int day=SystemTime.wDay;
	int week=SystemTime.wDayOfWeek;
	int hour=SystemTime.wHour;
	int minute=SystemTime.wMinute;
	int second=SystemTime.wSecond;
	CString cstr_date=_T("");
	CString cstr_time=_T("");
	int day1=0;
	int day2=0;
	CString cstr_day1=_T("");
	CString cstr_day2=_T("");
	switch(week)
	{
	    case 0:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期日"),year,month,day);break;}
		case 1:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期一"),year,month,day);break;}
		case 2:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期二"),year,month,day);break;}
		case 3:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期三"),year,month,day);break;}
		case 4:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期四"),year,month,day);break;}
		case 5:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期五"),year,month,day);break;}
		case 6:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期六"),year,month,day);break;}
		default:{break;}
	}
	cstr_time.Format(_T("当前时间：%02d:%02d:%02d"),hour,minute,second);
	SetDlgItemText(IDC_SDATE,cstr_date);
	SetDlgItemText(IDC_STIME,cstr_time);
	day1=CalculuteDay(2016,7,21,year,month,day);
	day2=CalculuteDay(2016,11,18,year,month,day);
	cstr_day1.Format(_T("%d"),day1);
	cstr_day2.Format(_T("%d"),day2);
	SetDlgItemText(IDC_EDATE1,cstr_day1);
	SetDlgItemText(IDC_EDATE2,cstr_day2);
	dlg_backup=this;
	HANDLE thread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)proc,NULL,0,NULL);//启动多线程

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDateDlg::OnPaint()
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
HCURSOR CDateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDateDlg::OnBnClickedBexit()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}

UINT proc(LPVOID pParam)
{
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);//获取系统时间
	int year;
	int month;
	int week;
	int hour;
	int minute;
	int oldsecond=SystemTime.wSecond;
	int newsecond=SystemTime.wSecond;
	int oldday=SystemTime.wDay;
	int newday=SystemTime.wDay;
	CString cstr_date=_T("");
	CString cstr_time=_T("");
	int day1=0;
	int day2=0;
	CString cstr_day1=_T("");
	CString cstr_day2=_T("");
    while(1)
    {
	    GetLocalTime(&SystemTime);//获取系统时间
		newsecond=SystemTime.wSecond;
		if(newsecond!=oldsecond)
		{
			oldsecond=newsecond;
			year=SystemTime.wYear;
	        month=SystemTime.wMonth;
	        newday=SystemTime.wDay;
	        week=SystemTime.wDayOfWeek;
	        hour=SystemTime.wHour;
	        minute=SystemTime.wMinute;
			switch(week)
	        {
	            case 0:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期日"),year,month,newday);break;}
		        case 1:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期一"),year,month,newday);break;}
		        case 2:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期二"),year,month,newday);break;}
		        case 3:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期三"),year,month,newday);break;}
		        case 4:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期四"),year,month,newday);break;}
		        case 5:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期五"),year,month,newday);break;}
		        case 6:{cstr_date.Format(_T("当前日期：%04d年%02d月%02d日星期六"),year,month,newday);break;}
		        default:{break;}
	        }
	        cstr_time.Format(_T("当前时间：%02d:%02d:%02d"),hour,minute,newsecond);
	        dlg_backup->SetDlgItemText(IDC_SDATE,cstr_date);
	        dlg_backup->SetDlgItemText(IDC_STIME,cstr_time);
			if(newday!=oldday)
			{
				oldday=newday;
				day1=CalculuteDay(2016,7,21,year,month,newday);
				day2=CalculuteDay(2016,11,18,year,month,newday);
				cstr_day1.Format(_T("%d"),day1);
				cstr_day2.Format(_T("%d"),day2);
				dlg_backup->SetDlgItemText(IDC_EDATE1,cstr_day1);
				dlg_backup->SetDlgItemText(IDC_EDATE2,cstr_day2);
			}
        }
	}
}

int JudgeYear(int year)//判断平闰年
{
	if(year%400==0)		            return 1;//闰年
	    else if(year%100==0)		return 0;//平年
	    else if(year%4==0)		    return 1;//闰年
	    else		                return 0;//平年
}

int JudgeMonth(int year,int month)//判断某月有多少天
{
	switch(month)
	{
	       case 1:{return 31;}
		   case 2:
		   {
			   if(JudgeYear(year)==1)   return 29;//闰年
			       else                 return 28;//平年
		   }
		   case 3:{return 31;}
		   case 4:{return 30;}
		   case 5:{return 31;}
		   case 6:{return 30;}
		   case 7:{return 31;}
		   case 8:{return 31;}
		   case 9:{return 30;}
		   case 10:{return 31;}
		   case 11:{return 30;}
		   case 12:{return 31;}
		   default:{return -1;}
	}
}

int CalculuteDay(int startyear,int startmonth,int startday,int endyear,int endmonth,int endday)//计算两日期相距多少天
{
	if(endyear<startyear)                                                           return -1;//数据有误
	    else if((endyear==startyear)&&(endmonth<startmonth))                        return -1;//数据有误
	    else if((endyear==startyear)&&(endmonth==startmonth)&&(endday<startday))    return -1;//数据有误
	int days=0;
	if(endyear>startyear)
	{
		int startyearday=0;
		if(JudgeYear(startyear)==1)       startyearday=366;//闰年
		    else                          startyearday=365;//平年
		days+=startyearday-CalculuteDayInOneYear(startyear,startmonth,startday);
		int tempyearday=0;
		for(int i=startyear+1;i<endyear;i++)
		{
			if(JudgeYear(i)==1)           tempyearday=366;//闰年
		        else                      tempyearday=365;//平年
			days+=tempyearday;
		}
		days+=CalculuteDayInOneYear(endyear,endmonth,endday);
	}
	else//endyear==startyear
	{
		days=CalculuteDayInOneYear(endyear,endmonth,endday)-CalculuteDayInOneYear(startyear,startmonth,startday);
	}
	return days;
}

int CalculuteDayInOneYear(int year,int month,int day)//计算某一日期为该年的第几天
{
	int sumdays=0;
	for(int i=1;i<month;i++)
	{
		sumdays+=JudgeMonth(year,i);
	}
	sumdays+=day;
	return sumdays;
}

int JudgeWeek(int year,int month,int day)//判断某一日期星期几
{
	//1601年1月1日星期一
	int days=CalculuteDay(1601,1,1,year,month,day);
	return (days%7+1);
}

void CalculuteEndDate(int startyear,int startmonth,int startday,int days,int* endyear,int* endmonth,int* endday)//根据相距时间计算结束时间
{
	int startyearday=0;
	if(JudgeYear(startyear)==1)       startyearday=366;//闰年
		else                          startyearday=365;//平年
	if(CalculuteDayInOneYear(startyear,startmonth,startday)+days<=startyearday)
	{
		*endyear=startyear;
		if(startday+days<=JudgeMonth(startyear,startmonth))
		{
			*endmonth=startmonth;
			*endday=startday+days;
		}
		else
		{
			int leftdays=days-(JudgeMonth(startyear,startmonth)-startday);
			*endmonth=startmonth+1;
			while(leftdays-JudgeMonth(startyear,*endmonth)>0)
			{
				leftdays-=JudgeMonth(startyear,*endmonth);
				(*endmonth)++;
			}
			if(leftdays-JudgeMonth(startyear,*endmonth)==0)
			{
				*endday=JudgeMonth(startyear,*endmonth);
				return;
			}
			*endday=leftdays;
		}
	}
	else
	{
		int leftdays=days-(startyearday-CalculuteDayInOneYear(startyear,startmonth,startday));
		*endyear=startyear+1;
		int endyearday=0;
	    if(JudgeYear(*endyear)==1)        endyearday=366;//闰年
		    else                          endyearday=365;//平年
		while(leftdays-endyearday>0)
		{
			leftdays-=endyearday;
			(*endyear)++;
			if(JudgeYear(*endyear)==1)        endyearday=366;//闰年
		        else                          endyearday=365;//平年
		}
		if(leftdays-endyearday==0)
		{
			*endmonth=12;
			*endday=31;
			return;
		}
		*endmonth=1;
		while(leftdays-JudgeMonth(*endyear,*endmonth)>0)
		{
			leftdays-=JudgeMonth(*endyear,*endmonth);
			(*endmonth)++;
		}
		if(leftdays-JudgeMonth(*endyear,*endmonth)==0)
		{
			*endday=JudgeMonth(*endyear,*endmonth);
			return;
		}
		*endday=leftdays;
	}
}