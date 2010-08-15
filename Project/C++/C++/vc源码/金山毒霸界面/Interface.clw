; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInterfaceDlg
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Interface.h"

ClassCount=5
Class1=CInterfaceApp
Class2=CInterfaceDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CColorStatic
Class5=CColorButton
Resource3=IDD_INTERFACE_DIALOG

[CLS:CInterfaceApp]
Type=0
HeaderFile=Interface.h
ImplementationFile=Interface.cpp
Filter=N

[CLS:CInterfaceDlg]
Type=0
HeaderFile=InterfaceDlg.h
ImplementationFile=InterfaceDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BITMAPBTN

[CLS:CAboutDlg]
Type=0
HeaderFile=InterfaceDlg.h
ImplementationFile=InterfaceDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_INTERFACE_DIALOG]
Type=1
Class=CInterfaceDlg
ControlCount=19
Control1=IDC_BITMAPBTN,button,1342244235
Control2=IDC_CLOSEBTN,button,1342242955
Control3=IDC_STATIC10,static,1342308364
Control4=IDC_EDIT1,edit,1342242944
Control5=IDC_CHECK1,button,1342275587
Control6=IDC_CHECK2,button,1342275587
Control7=IDC_CHECK3,button,1342275587
Control8=IDC_STATIC9,static,1342308363
Control9=IDC_STATIC8,static,1342312448
Control10=IDC_STATIC4,static,1342308352
Control11=IDC_STATIC5,static,1342308352
Control12=IDC_STATIC6,static,1342308352
Control13=IDC_STATIC7,static,1342308352
Control14=IDC_STARTBTN,button,1342242955
Control15=IDC_LIST1,SysListView32,1342242817
Control16=IDC_STATIC1,static,1342308352
Control17=IDC_STATIC2,static,1342308352
Control18=IDC_STATIC3,static,1342308352
Control19=IDC_HOMEBTN,button,1342242955

[CLS:CColorStatic]
Type=0
HeaderFile=ColorStatic.h
ImplementationFile=ColorStatic.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CColorStatic

[CLS:CColorButton]
Type=0
HeaderFile=ColorButton.h
ImplementationFile=ColorButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CColorButton

