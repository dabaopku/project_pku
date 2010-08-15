; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CReplyMsgDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "fakeqq.h"
LastPage=0

ClassCount=9
Class1=CChatRecordSet
Class2=CChatSocket
Class3=CFakeQQApp
Class4=CAboutDlg
Class5=CFakeQQDlg
Class6=CLoginDlg
Class7=CReplyMsgDlg
Class8=CSendMsgDlg
Class9=CViewLogDlg

ResourceCount=8
Resource1=IDD_VIEW_LOG
Resource2=IDD_LOGIN_DLG
Resource3=IDR_TOOLBAR
Resource4=IDD_REPLY_MSG_DLG
Resource5=IDD_ABOUTBOX
Resource6=IDD_SEND_MSG_DLG
Resource7=IDD_FAKEQQ_DIALOG
Resource8=IDR_POP

[CLS:CChatRecordSet]
Type=0
HeaderFile=ChatRecordSet.h
ImplementationFile=ChatRecordSet.cpp

[CLS:CChatSocket]
Type=0
BaseClass=CSocket
HeaderFile=ChatSocket.h
ImplementationFile=ChatSocket.cpp

[CLS:CFakeQQApp]
Type=0
BaseClass=CWinApp
HeaderFile=FakeQQ.h
ImplementationFile=FakeQQ.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=FakeQQDlg.cpp
ImplementationFile=FakeQQDlg.cpp

[CLS:CFakeQQDlg]
Type=0
BaseClass=CDialog
HeaderFile=FakeQQDlg.h
ImplementationFile=FakeQQDlg.cpp

[CLS:CLoginDlg]
Type=0
BaseClass=CDialog
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp

[CLS:CReplyMsgDlg]
Type=0
BaseClass=CDialog
HeaderFile=ReplyMsgDlg.h
ImplementationFile=ReplyMsgDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_MSG_TIME

[CLS:CSendMsgDlg]
Type=0
BaseClass=CDialog
HeaderFile=SendMsgDlg.h
ImplementationFile=SendMsgDlg.cpp

[CLS:CViewLogDlg]
Type=0
BaseClass=CDialog
HeaderFile=ViewLogDlg.h
ImplementationFile=ViewLogDlg.cpp

[DB:CChatRecordSet]
DB=1

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308480

[DLG:IDD_FAKEQQ_DIALOG]
Type=1
Class=CFakeQQDlg
ControlCount=5
Control1=IDC_TOOLBAR_PANE,static,1073741839
Control2=IDC_GROUP_BOX,button,1342308359
Control3=IDC_ELAPSE,static,1342308353
Control4=IDC_COPYRIGHT,static,1342308353
Control5=IDC_USER_LIST,SysListView32,1350639620

[DLG:IDD_LOGIN_DLG]
Type=1
Class=CLoginDlg
ControlCount=10
Control1=IDC_LOGIN_NAME,edit,1350631552
Control2=IDC_FACE_LIST,combobox,1344339971
Control3=IDC_UDP_PORT,edit,1350631552
Control4=IDC_LOCAL_IP,edit,1350633600
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_USER_FACE,static,1342177283
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_REPLY_MSG_DLG]
Type=1
Class=CReplyMsgDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_USER_NAME,static,1342308352
Control6=IDC_STATIC,static,1342308364
Control7=IDC_MSG_TIME,static,1342308352
Control8=ID_CHAT_MSG,edit,1350633540
Control9=IDC_STATIC,static,1342308352
Control10=IDC_ADDRESS,static,1342308352
Control11=IDC_USER_FACE,button,1342242880
Control12=IDC_STATIC,static,1342308352

[DLG:IDD_SEND_MSG_DLG]
Type=1
Class=CSendMsgDlg
ControlCount=17
Control1=ID_SEND_MSG,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_LOGIN_NAME,static,1342308352
Control6=IDC_STATIC,static,1342308364
Control7=IDC_CHAT_MSG,edit,1350635588
Control8=IDC_STATIC,static,1342308352
Control9=IDC_LOCAL_IP,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_TO_USER,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_UDP_PORT,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_TO_IP,edit,1350631552
Control17=IDC_TO_PORT,edit,1350631552

[DLG:IDD_VIEW_LOG]
Type=1
Class=CViewLogDlg
ControlCount=12
Control1=IDOK,button,1342373889
Control2=IDC_LOG_LIST,SysListView32,1350631425
Control3=IDC_STATIC,button,1342177287
Control4=ID_CHAT_MSG,edit,1350633540
Control5=IDC_STATIC,static,1342308352
Control6=IDC_USER_NAME,static,1342308352
Control7=IDC_STATIC,static,1342308364
Control8=IDC_MSG_TIME,static,1342308352
Control9=IDC_USER_FACE,button,1342242880
Control10=IDC_STATIC,static,1342308352
Control11=IDC_ADDRESS,static,1342308352
Control12=ID_CLEAR_LOG,button,1342373889

[MNU:IDR_POP]
Type=1
Class=?
Command1=ID_SHOW_WINDOW
Command2=ID_HIDE_WINDOW
Command3=ID_SHOW_LAST_CHAT
Command4=ID_APP_EXIT
CommandCount=4

[TB:IDR_TOOLBAR]
Type=1
Class=?
Command1=ID_VIEW_LOG
Command2=ID_HIDE_WINDOW
Command3=ID_SCROLL_UP
CommandCount=3

