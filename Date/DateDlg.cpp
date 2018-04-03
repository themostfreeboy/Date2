
// DateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Date.h"
#include "DateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDateDlg* dlg_backup;

// CDateDlg �Ի���




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


// CDateDlg ��Ϣ�������

BOOL CDateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);//��ȡϵͳʱ��
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
	    case 0:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d��������"),year,month,day);break;}
		case 1:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d������һ"),year,month,day);break;}
		case 2:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d�����ڶ�"),year,month,day);break;}
		case 3:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d��������"),year,month,day);break;}
		case 4:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d��������"),year,month,day);break;}
		case 5:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d��������"),year,month,day);break;}
		case 6:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d��������"),year,month,day);break;}
		default:{break;}
	}
	cstr_time.Format(_T("��ǰʱ�䣺%02d:%02d:%02d"),hour,minute,second);
	SetDlgItemText(IDC_SDATE,cstr_date);
	SetDlgItemText(IDC_STIME,cstr_time);
	day1=CalculuteDay(2016,7,21,year,month,day);
	day2=CalculuteDay(2016,11,18,year,month,day);
	cstr_day1.Format(_T("%d"),day1);
	cstr_day2.Format(_T("%d"),day2);
	SetDlgItemText(IDC_EDATE1,cstr_day1);
	SetDlgItemText(IDC_EDATE2,cstr_day2);
	dlg_backup=this;
	HANDLE thread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)proc,NULL,0,NULL);//�������߳�

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDateDlg::OnPaint()
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
HCURSOR CDateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDateDlg::OnBnClickedBexit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}

UINT proc(LPVOID pParam)
{
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);//��ȡϵͳʱ��
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
	    GetLocalTime(&SystemTime);//��ȡϵͳʱ��
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
	            case 0:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d��������"),year,month,newday);break;}
		        case 1:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d������һ"),year,month,newday);break;}
		        case 2:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d�����ڶ�"),year,month,newday);break;}
		        case 3:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d��������"),year,month,newday);break;}
		        case 4:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d��������"),year,month,newday);break;}
		        case 5:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d��������"),year,month,newday);break;}
		        case 6:{cstr_date.Format(_T("��ǰ���ڣ�%04d��%02d��%02d��������"),year,month,newday);break;}
		        default:{break;}
	        }
	        cstr_time.Format(_T("��ǰʱ�䣺%02d:%02d:%02d"),hour,minute,newsecond);
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

int JudgeYear(int year)//�ж�ƽ����
{
	if(year%400==0)		            return 1;//����
	    else if(year%100==0)		return 0;//ƽ��
	    else if(year%4==0)		    return 1;//����
	    else		                return 0;//ƽ��
}

int JudgeMonth(int year,int month)//�ж�ĳ���ж�����
{
	switch(month)
	{
	       case 1:{return 31;}
		   case 2:
		   {
			   if(JudgeYear(year)==1)   return 29;//����
			       else                 return 28;//ƽ��
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

int CalculuteDay(int startyear,int startmonth,int startday,int endyear,int endmonth,int endday)//������������������
{
	if(endyear<startyear)                                                           return -1;//��������
	    else if((endyear==startyear)&&(endmonth<startmonth))                        return -1;//��������
	    else if((endyear==startyear)&&(endmonth==startmonth)&&(endday<startday))    return -1;//��������
	int days=0;
	if(endyear>startyear)
	{
		int startyearday=0;
		if(JudgeYear(startyear)==1)       startyearday=366;//����
		    else                          startyearday=365;//ƽ��
		days+=startyearday-CalculuteDayInOneYear(startyear,startmonth,startday);
		int tempyearday=0;
		for(int i=startyear+1;i<endyear;i++)
		{
			if(JudgeYear(i)==1)           tempyearday=366;//����
		        else                      tempyearday=365;//ƽ��
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

int CalculuteDayInOneYear(int year,int month,int day)//����ĳһ����Ϊ����ĵڼ���
{
	int sumdays=0;
	for(int i=1;i<month;i++)
	{
		sumdays+=JudgeMonth(year,i);
	}
	sumdays+=day;
	return sumdays;
}

int JudgeWeek(int year,int month,int day)//�ж�ĳһ�������ڼ�
{
	//1601��1��1������һ
	int days=CalculuteDay(1601,1,1,year,month,day);
	return (days%7+1);
}

void CalculuteEndDate(int startyear,int startmonth,int startday,int days,int* endyear,int* endmonth,int* endday)//�������ʱ��������ʱ��
{
	int startyearday=0;
	if(JudgeYear(startyear)==1)       startyearday=366;//����
		else                          startyearday=365;//ƽ��
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
	    if(JudgeYear(*endyear)==1)        endyearday=366;//����
		    else                          endyearday=365;//ƽ��
		while(leftdays-endyearday>0)
		{
			leftdays-=endyearday;
			(*endyear)++;
			if(JudgeYear(*endyear)==1)        endyearday=366;//����
		        else                          endyearday=365;//ƽ��
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