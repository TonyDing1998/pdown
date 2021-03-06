// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include <event/SNotifyCenter.h>
#include "AppEvent.h"
#include <helper/SDpiHelper.hpp>

class CMainDlg : public SHostWnd
	, public TAutoEventMapReg<CMainDlg>//通知中心自动注册
	, public SDpiHandler<CMainDlg>
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose();
	void OnMinimize();
	void OnShowWindow(BOOL bShow, UINT nStatus);
	//托盘通知消息处理函数
	//LRESULT OnIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/);
	//演示如何响应菜单事件
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnTimer(char cTimerID);

	bool OnEventUI(EventArgs* e);
	bool EvtLinkReportClick(EventArgs* pEvt);

protected:
	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		//<--通知中心事件
		EVENT_HANDLER(EventUI::EventID, OnEventUI)
		//-->
	EVENT_MAP_END()
		
	//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SHOWWINDOW(OnShowWindow)
	//托盘消息处理
		//MESSAGE_HANDLER(WM_ICONNOTIFY, OnIconNotify)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(SHostWnd)
		CHAIN_MSG_MAP(SDpiHandler<CMainDlg>)
		REFLECT_NOTIFICATIONS_EX()
		MSG_WM_TIMER_EX(OnTimer)
	END_MSG_MAP()
private:
	/*启动后的总秒数*/
	int64_t	_TimeTotal=0;
	/*周期秒数，15分钟为一周期,每15分钟置零*/
	int64_t	_TimeTick=0;
};
