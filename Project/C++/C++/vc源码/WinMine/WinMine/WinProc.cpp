/*//////////////////////�ļ�˵��//////////////////////////
//														//
//�ļ���: WinProc.cpp					       			//
//��  ��: ���ܺ����Ķ����ʵ��							//
//��  ��:												//
//														//
////////////////////////////////////////////////////////*/

#include "WinProc.h"

/*###########################################################
���ܣ������ڵ���Ϣ����ص�����
������
����ֵ��
###########################################################*/
LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC							hDC,hDCMem;		
	static	HICON				hIcon;						//����ͼ����
	static	HINSTANCE			hInstance;					//����ʵ�����
	static	HMENU				hMenu;						//�������˵����
	PAINTSTRUCT					ps;
	HBRUSH						hBrush;
	HPEN						hPen;
	HBITMAP						hBmp;
	int							ix=0,iy=0;
	RECT						rcWnd,rcRefresh;			//���������ˢ������
	static tagMouseState		NowMousePos;				//���״̬�ṹ��
	static int					mStartMousePos;
	HRSRC						hrWare;						//wave��Դ���
	HGLOBAL						hGlobal;					
	LPCTSTR						keyWinMine=TEXT("Software\\Microsoft\\winmine\\");	//ע�������
	HKEY						hKey,hKeySub;				//ע�������
	DWORD						dwTemp;						//��ʱ����
	LPCTSTR						lpsTime[3]={TEXT("Time1"),TEXT("Time2"),TEXT("Time3")};
	LPCTSTR						lpsName[3]={TEXT("Name1"),TEXT("Name2"),TEXT("Name3")};
	TCHAR						lpAnonymity[255];			//��ʱ����
	DWORD 						dwSize1=sizeof(DWORD),dwType1=REG_DWORD,dwType2=REG_SZ,dwSize2=sizeof(lpAnonymity);
//###########################################################################################################
	switch (message)
	{
	case WM_CREATE:
		hDC=GetDC(hWnd);
		hInstance=((LPCREATESTRUCT)lParam)->hInstance;
		hMenu=((LPCREATESTRUCT)lParam)->hMenu;
		//ע����ȡ�ѱ������Ϣ�������ؼ�ֵ�������򴴽�
		if (RegOpenKeyEx(HKEY_CURRENT_USER,keyWinMine,0,KEY_ALL_ACCESS,&hKey)!=ERROR_SUCCESS){
			RegCreateKey(HKEY_CURRENT_USER,keyWinMine,&hKey);			
		}			
		if (RegQueryValueEx(hKey,TEXT("Height"),NULL,&dwType1,(LPBYTE)&mineLineNum,&dwSize1)!=ERROR_SUCCESS){
			mineLineNum=BEGINER_LN_NUM;
			RegSetValueEx(hKey,TEXT("Height"),NULL,REG_DWORD,(LPBYTE)&mineLineNum,dwSize1);
		}
		if (RegQueryValueEx(hKey,TEXT("Width"),NULL,&dwType1,(LPBYTE)&mineRowNum,&dwSize1)!=ERROR_SUCCESS){
			mineRowNum=BEGINER_COL_NUM;
			RegSetValueEx(hKey,TEXT("Width"),NULL,REG_DWORD,(LPBYTE)&mineRowNum,dwSize1);
		}			
		if (RegQueryValueEx(hKey,TEXT("Mines"),NULL,&dwType1,(LPBYTE)&mineBomb,&dwSize1)!=ERROR_SUCCESS){
			mineBomb=BEGINER_BOMB_NUM;
			RegSetValueEx(hKey,TEXT("Mines"),NULL,REG_DWORD,(LPBYTE)&mineBomb,dwSize1);
		}			
		if (RegQueryValueEx(hKey,TEXT("Sound"),NULL,&dwType1,(LPBYTE)&dwTemp,&dwSize1)!=ERROR_SUCCESS){
			dwTemp=0;
			RegSetValueEx(hKey,TEXT("Sound"),NULL,REG_DWORD,(LPBYTE)&dwTemp,dwSize1);
		}
		flagState=(flagState&0xffef)+dwTemp*FLAG_SOUND;
		if (RegQueryValueEx(hKey,TEXT("Difficulty"),NULL,&dwType1,(LPBYTE)&dwTemp,&dwSize1)!=ERROR_SUCCESS){
			dwTemp=0;
			RegSetValueEx(hKey,TEXT("Difficulty"),NULL,REG_DWORD,(LPBYTE)&dwTemp,dwSize1);
		}		
		flagState=(flagState&0xf0ff)+dwTemp*0x0100;	
		if (RegQueryValueEx(hKey,TEXT("Mark"),NULL,&dwType1,(LPBYTE)&dwTemp,&dwSize1)!=ERROR_SUCCESS){
			dwTemp=1;
			RegSetValueEx(hKey,TEXT("Mark"),NULL,REG_DWORD,(LPBYTE)&dwTemp,dwSize1);
		}
		flagState=(flagState&0xfff7)+dwTemp*FLAG_MARK;
		if (RegQueryValueEx(hKey,TEXT("Color"),NULL,&dwType1,(LPBYTE)&dwTemp,&dwSize1)!=ERROR_SUCCESS){
			dwTemp=1;
			RegSetValueEx(hKey,TEXT("Color"),NULL,REG_DWORD,(LPBYTE)&dwTemp,dwSize1);
		}
		flagState=(flagState&0xfffb)+dwTemp*FLAG_COLOR;
		if (RegQueryValueEx(hKey,TEXT("AlreadyPlayed"),NULL,&dwType1,(LPBYTE)&dwTemp,&dwSize1)!=ERROR_SUCCESS){
			dwTemp=1;
			RegSetValueEx(hKey,TEXT("AlreadyPlayed"),NULL,REG_DWORD,(LPBYTE)&dwTemp,dwSize1);
		}
		flagState=(flagState&0xfffe)+1*FLAG_ALREADPLAYED;	dwTemp=999;	
		LoadString(hInstance,IDS_NORMAL_NAME,lpAnonymity,sizeof(lpAnonymity));	
		for (ix=0;ix<3;ix++){				
			if (RegOpenKeyEx(hKey,lpsTime[ix],NULL,KEY_WRITE,&hKeySub)!=ERROR_SUCCESS){
				RegSetValueEx(hKey,lpsTime[ix],NULL,REG_DWORD,(LPBYTE)&dwTemp,dwSize1);
				RegCloseKey(hKeySub);
			}
			if (RegOpenKeyEx(hKey,lpsName[ix],NULL,KEY_WRITE,&hKeySub)!=ERROR_SUCCESS){		
				RegSetValueEx(hKey,lpsName[ix],NULL,REG_SZ,(LPBYTE)&lpAnonymity,dwSize2);
				RegCloseKey(hKeySub);
			}
		}//��ʼ��������Ϣ			
		IinitializeMapInfo(hWnd,(flagState&0x0f00)/0x0100,mineRowNum,mineLineNum,mineBomb);	
		CheckMenuItem(hMenu,IDM_MARK,((flagState&0x0008)==FLAG_MARK) ? MF_CHECKED:MF_UNCHECKED);
		CheckMenuItem(hMenu,IDM_COLOR,((flagState&0x0004)==FLAG_COLOR) ? MF_CHECKED:MF_UNCHECKED);
		CheckMenuItem(hMenu,IDM_SOUND,((flagState&0x0010)==FLAG_SOUND) ? MF_CHECKED:MF_UNCHECKED);			
		OnCheckLevelMenu(hMenu,(flagState&0x0f00)/0x0100);				
		rcWnd=getLevelWindowSize(hWnd);//���㴰�ڴ�С����ʼ����ͼ����
		if (RegQueryValueEx(hKey,TEXT("Xpos"),NULL,&dwType1,(LPBYTE)&dwTemp,&dwSize1)==ERROR_SUCCESS) rcWnd.left=dwTemp;
		if (RegQueryValueEx(hKey,TEXT("Ypos"),NULL,&dwType1,(LPBYTE)&dwTemp,&dwSize1)==ERROR_SUCCESS) rcWnd.top=dwTemp;				
		CreateRandomMap(hWnd);
		MoveWindow(hWnd,rcWnd.left,rcWnd.top,rcWnd.right,rcWnd.bottom,TRUE);
		RegCloseKey(hKey);
		ReleaseDC(hWnd,hDC);
		hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDC_APPICON)) ;
		return 0;
	case WM_PAINT:
		hDC = BeginPaint (hWnd, &ps);
		hDCMem= CreateCompatibleDC(hDC);
		GetClientRect(hWnd,&rcWnd);
		hPen=(HPEN)GetStockObject(NULL_PEN);
		SelectObject(hDC,hPen);
		hBrush=CreateSolidBrush(RGB(192,192,192));
		SelectObject(hDC,hBrush);
		Rectangle(hDC,3,3,rcWnd.right+1,rcWnd.bottom+1);//���Ƶײ㱳��		
		DeleteObject(hBrush);
		hBrush=CreateSolidBrush(RGB(8+(flagState&0x0004)*30,8+(flagState&0x0004)*30,8+(flagState&0x0004)*30));
		SelectObject(hDC,hBrush);	
		Rectangle(hDC,MAIN_LEFTSTND+(mineRowNum*MINE_BITMAP_WIDTH-FACE_BITMAP_WIDTH)/2-1,(MAIN_TOPSTND-FACE_BITMAP_HEIGHT)/2-1,MAIN_LEFTSTND+(mineRowNum*MINE_BITMAP_WIDTH-FACE_BITMAP_WIDTH)/2+FACE_BITMAP_WIDTH+2,(MAIN_TOPSTND-FACE_BITMAP_HEIGHT)/2+FACE_BITMAP_HEIGHT+2);	//���Ʊ��鱳��
		DeleteObject(hBrush);
		DeleteObject(hPen);
		//������ͼ
		hBmp=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SMILE_BLACK+(flagState&0x0004)/0x0004));
		SelectObject(hDCMem,hBmp);
		BitBlt(hDC,MAIN_LEFTSTND+(mineRowNum*MINE_BITMAP_WIDTH-FACE_BITMAP_WIDTH)/2,(MAIN_TOPSTND-FACE_BITMAP_HEIGHT)/2,FACE_BITMAP_WIDTH,FACE_BITMAP_HEIGHT,hDCMem,0, ((flagState & 0xf000)/0x1000) *FACE_BITMAP_HEIGHT,SRCCOPY);
		DeleteObject(hBmp);
		//��������ͼ
		hBmp=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_NUM_BLACK+(flagState&0x0004)/0x0004));
		SelectObject(hDCMem,hBmp);
		BitBlt(hDC,COUNT_LEFTPOS,COUNT_TOPPOS,NUM_BITMAP_WIDTH,NUM_BITMAP_HEIGHT,hDCMem,0,NUM_BITMAP_HEIGHT*(bombCount<0?0:11-(int)floor(bombCount/100)),SRCCOPY);
		BitBlt(hDC,COUNT_LEFTPOS+NUM_BITMAP_WIDTH,COUNT_TOPPOS,NUM_BITMAP_WIDTH,NUM_BITMAP_HEIGHT,hDCMem,0,NUM_BITMAP_HEIGHT*(11-(int)floor((abs(bombCount)-(int)floor(abs(bombCount)/100)*100)/10)),SRCCOPY);
		BitBlt(hDC,COUNT_LEFTPOS+NUM_BITMAP_WIDTH*2,COUNT_TOPPOS,NUM_BITMAP_WIDTH,NUM_BITMAP_HEIGHT,hDCMem,0,NUM_BITMAP_HEIGHT*(11-(abs(bombCount)-(int)floor(abs(bombCount)/10)*10)),SRCCOPY);
		//��ʱ����ͼ
		BitBlt(hDC,rcWnd.right-TIME_RIGHTSTND-TIME_WIDTH,TIME_TOPPOS,NUM_BITMAP_WIDTH,NUM_BITMAP_HEIGHT,hDCMem,0,NUM_BITMAP_HEIGHT*(11-(timeCount<1000?(int)floor(timeCount/100):9)),SRCCOPY);
		BitBlt(hDC,rcWnd.right-TIME_RIGHTSTND-TIME_WIDTH+NUM_BITMAP_WIDTH,TIME_TOPPOS,NUM_BITMAP_WIDTH,NUM_BITMAP_HEIGHT,hDCMem,0,NUM_BITMAP_HEIGHT*(11-(timeCount<1000?(int)floor((timeCount-(int)floor(timeCount/100)*100)/10):9)),SRCCOPY);
		BitBlt(hDC,rcWnd.right-TIME_RIGHTSTND-TIME_WIDTH+NUM_BITMAP_WIDTH*2,TIME_TOPPOS,NUM_BITMAP_WIDTH,NUM_BITMAP_HEIGHT,hDCMem,0,NUM_BITMAP_HEIGHT*(11-(timeCount<1000?(timeCount-(int)floor(timeCount/10)*10):9)),SRCCOPY);
		DeleteObject(hBmp);	
		//����߿����
		rcRefresh=CreateRect(MAIN_LEFTSTND-LINE_LIGHTEN_THICK,MAIN_TOPSTND-LINE_LIGHTEN_THICK,rcWnd.right-MAIN_RIGHTSTND-MAIN_LEFTSTND+2*LINE_LIGHTEN_THICK,rcWnd.bottom-MAIN_TOPSTND-MAIN_BOTTOMSTND+2*LINE_LIGHTEN_THICK,FALSE);
		DrawSolidFrame(hDC,rcRefresh,LINE_LIGHTEN_THICK);
		rcRefresh=CreateRect(FUN_LEFTPOS-LINE_LIGHTEN_THICK,FUN_TOPPOS-LINE_LIGHTEN_THICK,rcWnd.right-FUN_LEFTPOS-FUN_RIGHTSTND+2*LINE_LIGHTEN_THICK,MAIN_TOPSTND-FUN_TOPPOS-FUN_BOTTOMSTND+2*LINE_LIGHTEN_THICK,FALSE);
		DrawSolidFrame(hDC,rcRefresh,LINE_LIGHTEN_NORMAL);		
		rcRefresh=CreateRect(COUNT_LEFTPOS-LINE_LIGHTEN_THIN,COUNT_TOPPOS-LINE_LIGHTEN_THIN,COUNT_WIDTH+2*LINE_LIGHTEN_THIN,COUNT_HEIGHT+2*LINE_LIGHTEN_THIN,FALSE);
		DrawSolidFrame(hDC,rcRefresh,LINE_LIGHTEN_THIN);
		rcRefresh=CreateRect(rcWnd.right-TIME_RIGHTSTND-TIME_WIDTH-LINE_LIGHTEN_THIN,TIME_TOPPOS-LINE_LIGHTEN_THIN,TIME_WIDTH+2*LINE_LIGHTEN_THIN,TIME_HEIGHT+2*LINE_LIGHTEN_THIN,FALSE);
		DrawSolidFrame(hDC,rcRefresh,LINE_LIGHTEN_THIN);
		//������ͼ
		hBmp=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_MINE_BLACK+(flagState&0x0004)/0x0004));
		SelectObject(hDCMem,hBmp);
		for(ix=0;ix<mineRowNum;ix++)
			for(iy=0;iy<mineLineNum;iy++) BitBlt(hDC,MAIN_LEFTSTND+MINE_BITMAP_WIDTH*ix,MAIN_TOPSTND+MINE_BITMAP_HEIGHT*iy,MINE_BITMAP_WIDTH,MINE_BITMAP_HEIGHT,hDCMem,0,MINE_BITMAP_HEIGHT* (btLandmineMapinfo[ix][iy]%0x10),SRCCOPY);		
		DeleteObject(hBmp);
		ReleaseDC(hWnd,hDCMem);
		DeleteObject(hDCMem);
		EndPaint (hWnd, &ps) ;
		return 0 ;
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
			case IDM_BEGIN:				//��ʼ
				IinitializeMapInfo(hWnd,(flagState & 0x0f00)/0x0100,mineRowNum,mineLineNum,mineBomb); //??
				CreateRandomMap(hWnd);
				InvalidateRect(hWnd,NULL,TRUE);
				break;
			case IDM_BEGINNER:			//����
				IinitializeMapInfo(hWnd,0x0000,BEGINER_COL_NUM,BEGINER_LN_NUM,BEGINER_BOMB_NUM); //??
				rcWnd=getLevelWindowSize(hWnd);
				CreateRandomMap(hWnd);
				MoveWindow(hWnd,rcWnd.left,rcWnd.top,rcWnd.right,rcWnd.bottom,TRUE);
				OnCheckLevelMenu(hMenu,LEVEL_BEGINNER);
				break;
			case IDM_INTERMEDIATE:		//�м�
				IinitializeMapInfo(hWnd,0x0001,INTER_COL_NUM,INTER_LN_NUM,INTER_BOMB_NUM); //??
				rcWnd=getLevelWindowSize(hWnd);
				CreateRandomMap(hWnd);
				MoveWindow(hWnd,rcWnd.left,rcWnd.top,rcWnd.right,rcWnd.bottom,TRUE);
				OnCheckLevelMenu(hMenu,LEVEL_INTER);			
				break;
			case IDM_ADVANCED:			//�߼�
				IinitializeMapInfo(hWnd,0x0002,ADVANCED_COL_NUM,ADVANCED_LN_NUM,ADVANCED_BOMB_NUM); //??
				rcWnd=getLevelWindowSize(hWnd);
				CreateRandomMap(hWnd);
				MoveWindow(hWnd,rcWnd.left,rcWnd.top,rcWnd.right,rcWnd.bottom,TRUE);
				OnCheckLevelMenu(hMenu,LEVEL_ADVANCED);
				break;
			case IDM_CUSTOMDEFINE:		//�Զ���ȼ��Զ��崰��				
				if (DialogBox(hInstance,MAKEINTRESOURCE(IDD_CUSTOMDLG),hWnd,WinDlgProc)){ //��������� TRUE,��"ȷ��"									
					IinitializeMapInfo(hWnd,0x0003,mineRowNum,mineLineNum,mineBomb); //??
					rcWnd=getLevelWindowSize(hWnd);
					CreateRandomMap(hWnd);
					MoveWindow(hWnd,rcWnd.left,rcWnd.top,rcWnd.right,rcWnd.bottom,TRUE);
					OnCheckLevelMenu(hMenu,LEVEL_CUSTOM);
				}
				break;
			case IDM_MARK:				//���ñ�� flagState & FLAG_MARK == FLAG_MARK Ϊ��� 
				flagState=(((flagState&0x0008)==FLAG_MARK)?0:0x0008)+(flagState&0xfff7);
				CheckMenuItem(hMenu,IDM_MARK,((flagState&0x0008)==FLAG_MARK) ? MF_CHECKED:MF_UNCHECKED);
				break;
			case IDM_COLOR:				//������ɫ	flagState & FLAG_COLOR == FLAG_COLOR Ϊ��ɫ
				flagState=(((flagState&0x0004)==FLAG_COLOR)?0:0x0004)+(flagState&0xfffb);
				CheckMenuItem(hMenu,IDM_COLOR,((flagState&0x0004)==FLAG_COLOR) ? MF_CHECKED:MF_UNCHECKED);
				InvalidateRect(hWnd,NULL,TRUE);
				break;
			case IDM_SOUND:				//��������	flagState & FLAG_SOUND == FLAG_SOUND Ϊ����
				flagState=(((flagState&0x0010)==FLAG_SOUND)?0:0x0030)+(flagState&0xffef);
				CheckMenuItem(hMenu,IDM_SOUND,((flagState&0x0010)==FLAG_SOUND) ? MF_CHECKED:MF_UNCHECKED);
				break;
			case IDM_HEROLIST:			//��ʾ���а�
				DialogBox(hInstance,MAKEINTRESOURCE(IDD_HEROLISTDLG),hWnd,WinDlgProc);
				break;
			case IDM_EXIT:				//�˳�
				SendMessage(hWnd,WM_DESTROY,wParam,lParam);
				break;
			case IDM_ABOUT:				//����
				LoadString(hInstance,IDS_AUTHER,lpAnonymity,sizeof(lpAnonymity));
				ShellAbout(hWnd,TEXT("ɨ�� ..."),lpAnonymity,hIcon);
				break;
			case IDM_CONTENTS:			//������Ŀ¼
				LoadString(hInstance,IDS_HELPFILEPATH_WIN,lpAnonymity,sizeof(lpAnonymity));
				if (HtmlHelp(NULL,lpAnonymity,HH_DISPLAY_TOC,NULL)==0){		//ϵͳ���������ڣ��ڵ�ǰĿ¼Ѱ��	
					GetCurrentDirectory(sizeof(lpAnonymity),lpAnonymity);
					strcat(lpAnonymity,TEXT("\\help\\winmine.chm"));
					if (HtmlHelp(NULL,lpAnonymity,HH_DISPLAY_TOC,NULL)==0)	//��Ȼ�޷��򿪣���ʾ������Ϣ
						MessageBox(hWnd,TEXT("Sorry!\r\nYou have not the help file of \"WinMine.chm\"\t\r\n"),TEXT("Help Information"),MB_ICONINFORMATION);
				}
				break;
			case IDM_SEARCHHELP:		//����������
				LoadString(hInstance,IDS_HELPFILEPATH_WIN,lpAnonymity,sizeof(lpAnonymity));
				if (HtmlHelp(NULL, lpAnonymity, HH_DISPLAY_INDEX,0)==0){				
					GetCurrentDirectory(sizeof(lpAnonymity),lpAnonymity);
					strcat(lpAnonymity,TEXT("\\help\\winmine.chm"));
					if (HtmlHelp(NULL,lpAnonymity,HH_DISPLAY_INDEX,NULL)==0)
						MessageBox(hWnd,TEXT("Sorry!\r\nYou have not the help file of \"winmine.chm\"\t\r\n"),TEXT("Help Information"),MB_ICONINFORMATION);
				}				
				break;
			case IDM_USEHELP:			//����: ʹ�ð���
				LoadString(hInstance,IDS_HELPFILEPATH_HELP,lpAnonymity,sizeof(lpAnonymity));
				if (HtmlHelp(NULL, lpAnonymity, HH_DISPLAY_TOC,0)==0){
					GetCurrentDirectory(sizeof(lpAnonymity),lpAnonymity);
					strcat(lpAnonymity,TEXT("\\help\\nthelp.chm"));
					if (HtmlHelp(NULL,lpAnonymity,HH_DISPLAY_INDEX,NULL)==0) 
						MessageBox(hWnd,TEXT("Sorry!\r\nYou have not the help file of \"nthelp.chm\"\t\r\n"),TEXT("Help Information"),MB_ICONINFORMATION);
				}	
				break;
		}	
		return 0;
	case WM_LBUTTONDOWN:								//�������
		SetCapture(hWnd);								//�������
		NowMousePos=getMousePosition(hWnd,hInstance,LOWORD(lParam),HIWORD(lParam));			//�õ����λ����Ϣ
		if (wParam&MK_RBUTTON)							//ͬʱ�Ҽ��Ѿ�����
			NowMousePos.mButtonMode=BTN_DBBUTTONDOWN;	//����˫��������Ϣ
		else 
			NowMousePos.mButtonMode=BTN_LBUTTONDOWN;
		mStartMousePos=NowMousePos.mNowPostion;
		OnMouseClick(hWnd,hInstance,NowMousePos,mStartMousePos);
		return 0;
	case WM_LBUTTONUP:									//�������
		ReleaseCapture();								//�ͷ���겶��
		NowMousePos=getMousePosition(hWnd,hInstance,LOWORD(lParam),HIWORD(lParam));			//�õ����λ����Ϣ
		if (wParam&MK_RBUTTON||NowMousePos.mButtonMode==BTN_DBBUTTONDOWN)							//ͬʱ�Ҽ��Ѿ�����
			NowMousePos.mButtonMode=BTN_DBBUTTONUP;		//����˫��������Ϣ
		else 
			NowMousePos.mButtonMode=BTN_LBUTTONUP;
		OnMouseClick(hWnd,hInstance,NowMousePos,mStartMousePos);
		return 0;
	case WM_MOUSEMOVE:			//����ƶ�
		NowMousePos=getMousePosition(hWnd,hInstance,LOWORD(lParam),HIWORD(lParam));			//�õ����λ����Ϣ
		if (wParam&MK_LBUTTON){
			if (wParam&MK_RBUTTON)
				NowMousePos.mButtonMode=BTN_DBBUTTONMOVING;
			else
				NowMousePos.mButtonMode=BTN_LBUTTONMOVING;			
			OnMouseClick(hWnd,hInstance,NowMousePos,mStartMousePos);
		}
		return 0;
	case WM_RBUTTONDOWN:		//����Ҽ�����
		NowMousePos=getMousePosition(hWnd,hInstance,LOWORD(lParam),HIWORD(lParam));			//�õ����λ����Ϣ
		if (wParam&MK_LBUTTON)							//ͬʱ�Ҽ��Ѿ�����
			NowMousePos.mButtonMode=BTN_DBBUTTONDOWN;	//����˫��������Ϣ
		else
			NowMousePos.mButtonMode=BTN_RBUTTONDOWN;
		mStartMousePos=NowMousePos.mNowPostion;
		OnMouseClick(hWnd,hInstance,NowMousePos,mStartMousePos);		
		return 0;
	case WM_RBUTTONUP:			//����Ҽ�����
		ReleaseCapture();
		NowMousePos=getMousePosition(hWnd,hInstance,LOWORD(lParam),HIWORD(lParam));			//�õ����λ����Ϣ
		if (wParam&MK_LBUTTON||NowMousePos.mButtonMode==BTN_DBBUTTONDOWN)							//ͬʱ�Ҽ��Ѿ�����
			NowMousePos.mButtonMode=BTN_DBBUTTONUP;		//����˫��������Ϣ
		else 
			NowMousePos.mButtonMode=BTN_RBUTTONUP;
		OnMouseClick(hWnd,hInstance,NowMousePos,mStartMousePos);
		return 0;
	case WM_TIMER:				//��ʱ����Ϣ
		timeCount++;			//ʱ������
		//�õ���ʱ����С��ˢ�¸�����
		GetClientRect(hWnd,&rcWnd);
		rcRefresh=CreateRect(rcWnd.right-TIME_RIGHTSTND-TIME_WIDTH,TIME_TOPPOS,TIME_WIDTH,TIME_HEIGHT,FALSE);
		InvalidateRect(hWnd,&rcRefresh,FALSE);
		if (flagState & 0x0010){		//�����������
			hrWare=FindResource(hInstance,MAKEINTRESOURCE(IDW_WAVE_TIME),TEXT("WAVE"));
			hGlobal=LoadResource(hInstance,hrWare);
			PlaySoundW((LPCWSTR)LockResource(hGlobal),NULL,SND_MEMORY|SND_ASYNC);
			DeleteObject(hrWare);
			DeleteObject(hGlobal);
		}
		return 0;
	case WM_ACTIVATEAPP:
		if (!wParam) KillTimer(hWnd,FLAG_TIMECOUNT);
			else if ((flagState &0x0001)&&(flagState&0x0002)) SetTimer(hWnd,FLAG_TIMECOUNT,1000,NULL);
		break;
	case WM_DESTROY:			//����ر�ʱ
		//дע���û�еļ�ֵͬʱ����
		if (RegOpenKeyEx(HKEY_CURRENT_USER,keyWinMine,0,KEY_ALL_ACCESS,&hKey)!=ERROR_SUCCESS) 
			RegCreateKey(HKEY_CURRENT_USER,keyWinMine,&hKey);
		RegSetValueEx(hKey,TEXT("Height"),NULL,REG_DWORD,(LPBYTE)&mineLineNum,dwSize1);
		RegSetValueEx(hKey,TEXT("Width"),NULL,REG_DWORD,(LPBYTE)&mineRowNum,dwSize1);
		RegSetValueEx(hKey,TEXT("Mines"),NULL,REG_DWORD,(LPBYTE)&mineBomb,dwSize1);
		dwTemp=(flagState&0x0f00)/0x0100;
		RegSetValueEx(hKey,TEXT("Difficulty"),NULL,REG_DWORD,(LPBYTE)&dwTemp,dwSize1);
		dwTemp=(flagState&0x0008)/0x0008;
		RegSetValueEx(hKey,TEXT("Mark"),NULL,REG_DWORD,(LPBYTE)&dwTemp,dwSize1);
		dwTemp=(flagState&0x0004)/0x0004;
		RegSetValueEx(hKey,TEXT("Color"),NULL,REG_DWORD,(LPBYTE)&dwTemp,dwSize1);
		dwTemp=(flagState&0x0010)/0x0010;
		RegSetValueEx(hKey,TEXT("Sound"),NULL,REG_DWORD,(LPBYTE)&dwTemp,dwSize1);
		dwTemp=(flagState&0x0001)/0x0001;
		RegSetValueEx(hKey,TEXT("AlreadyPlayed"),NULL,REG_DWORD,(LPBYTE)&dwTemp,dwSize1);
		dwTemp=getLevelWindowSize(hWnd).left;
		RegSetValueEx(hKey,TEXT("Xpos"),NULL,REG_DWORD,(LPBYTE)&dwTemp,dwSize1);
		dwTemp=getLevelWindowSize(hWnd).top;
		RegSetValueEx(hKey,TEXT("Ypos"),NULL,REG_DWORD,(LPBYTE)&dwTemp,dwSize1);
		dwTemp=999;	
		LoadString(hInstance,IDS_NORMAL_NAME,lpAnonymity,sizeof(lpAnonymity));	
		//���а񲿷�
		for (ix=0;ix<3;ix++){				
			if (RegOpenKeyEx(hKey,lpsTime[ix],NULL,KEY_WRITE,&hKeySub)!=ERROR_SUCCESS){
				RegSetValueEx(hKey,lpsTime[ix],NULL,dwType1,(LPBYTE)&dwTemp,dwSize1);
				RegCloseKey(hKeySub);
			}
			if (RegOpenKeyEx(hKey,lpsName[ix],NULL,KEY_WRITE,&hKeySub)!=ERROR_SUCCESS){		
				RegSetValueEx(hKey,lpsName[ix],NULL,dwType2,(LPBYTE)&lpAnonymity,dwSize2);
				RegCloseKey(hKeySub);
			}
		}
		RegCloseKey(hKey);
		PostQuitMessage (0) ;
		return 0 ;
	}
	return DefWindowProc (hWnd, message, wParam, lParam) ;
}

/*###########################################################
//���ܣ��Ի�����Ϣ����
//������
//����ֵ��
//#########################################################*/
BOOL CALLBACK WinDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	int						width,height,bomb;
	static HINSTANCE		hInstance;
	LPCSTR					keyWinMine=TEXT("Software\\Microsoft\\winmine\\");
	HKEY					hKey;
	DWORD					dwTime;
	TCHAR					lpBuff[255],lpAnonymity[255],lpOutput[255],lpFormat[255];
	LPCTSTR					lpsTime[3]={TEXT("Time1"),TEXT("Time2"),TEXT("Time3")};
	LPCTSTR					lpsName[3]={TEXT("Name1"),TEXT("Name2"),TEXT("Name3")};
	int						i;
	DWORD 					dwSize1=sizeof(DWORD),dwType1=REG_DWORD,dwType2=REG_SZ,dwSize2=sizeof(lpBuff);
	switch (message){
	case WM_CREATE:			//����
		hInstance=((LPCREATESTRUCT)lParam)->hInstance;	//ʵ�����
		break;
	case WM_INITDIALOG:		//��ʼ��
		//��ʼ�� �Զ���Ի��� Ϊ��ǰ����
		SetDlgItemInt(hDlg,IDC_CUSTOM_HEIGHT,mineRowNum,TRUE);	
		SetDlgItemInt(hDlg,IDC_CUSTOM_WIDTH,mineLineNum,TRUE);
		SetDlgItemInt(hDlg,IDC_CUSTOM_BOMB,mineBomb,TRUE);
		//��ʼ�����а�Ϊע��������ݣ����û�м�ֵ ����Ĭ��
		LoadString(hInstance,IDS_SECOND,lpFormat,sizeof(lpFormat));
		if (RegOpenKeyEx(HKEY_CURRENT_USER,keyWinMine,0,KEY_READ,&hKey)==ERROR_SUCCESS){
			for (i=0;i<3;i++){
				if (RegQueryValueEx(hKey,lpsTime[i],NULL,&dwType1,(LPBYTE)&dwTime,&dwSize1)!=ERROR_SUCCESS)//ʱ��
					dwTime=999;
				sprintf(lpOutput,lpFormat,dwTime);			//��ʽ��
				SetDlgItemText(hDlg,IDC_BEGINER_TIME+i,(LPCSTR)lpOutput);		//��ʾʱ�䵽���а�Ի���	
				if (RegQueryValueEx(hKey,lpsName[i],NULL,&dwType2,(LPBYTE)&lpBuff,&dwSize2)!=ERROR_SUCCESS)//����
					LoadString(hInstance,IDS_NORMAL_NAME,lpBuff,sizeof(lpBuff));			
				SetDlgItemText(hDlg,IDC_BEGINER_NAME+i,(LPCSTR)lpBuff);			//��ʾ���������а�Ի���
			}
			RegCloseKey(hKey);
		}
		//��ʼ�������¼�¼�Ի���
		LoadString(hInstance,IDS_RECORD_BEGINER+(flagState&0x0f00)/0x0100,lpBuff,sizeof(lpBuff));
		SetDlgItemText(hDlg,IDC_RECORD_MSG,lpBuff);
		LoadString(hInstance,IDS_NORMAL_NAME,lpBuff,sizeof(lpBuff));
		SetDlgItemText(hDlg,IDC_RECORD_NAME,lpBuff);
		break;
	case WM_COMMAND:		//�ؼ���Ϣ����
		switch(LOWORD(wParam)){
		case IDC_CUSTOM_OK:		//�Զ���ȷ��
			//���ó�������Ϊ�Ի������룬���Խ����Ϊ��ֵ
			width=(GetDlgItemInt(hDlg,IDC_CUSTOM_WIDTH,FALSE,TRUE)<MAX_LN_NUM)?GetDlgItemInt(hDlg,IDC_CUSTOM_WIDTH,FALSE,TRUE):MAX_LN_NUM;
			mineLineNum=width>MIN_LN_NUM?width:MIN_LN_NUM;
			height=GetDlgItemInt(hDlg,IDC_CUSTOM_HEIGHT,FALSE,TRUE)<MAX_COL_NUM?GetDlgItemInt(hDlg,IDC_CUSTOM_HEIGHT,FALSE,TRUE):MAX_COL_NUM;
			mineRowNum=height>MIN_COL_NUM?height:MIN_COL_NUM;
			bomb=GetDlgItemInt(hDlg,IDC_CUSTOM_BOMB,FALSE,TRUE)<MAX_BOMB_NUM?GetDlgItemInt(hDlg,IDC_CUSTOM_BOMB,FALSE,TRUE):MAX_BOMB_NUM;
			mineBomb=bomb>MIN_BOMB_NUM?bomb:MIN_BOMB_NUM;
			mineBomb=mineBomb<(mineRowNum*mineLineNum*0.8)?mineBomb:(int)floor(mineRowNum*mineLineNum*0.8);
			EndDialog(hDlg,TRUE);
			break;
		case IDC_CUSTOM_CANCEL:	//�Զ���ȡ�����������ر�
			EndDialog(hDlg,FALSE);
			break;
		case IDC_HEROLIST_OK:	//���а�ȷ�����������ر�
			EndDialog(hDlg,TRUE);
			break;
		case IDC_HEROLIST_RENEW:	//���а����ã���д��ע���
			LoadString(hInstance,IDS_NORMAL_NAME,lpAnonymity,sizeof(lpAnonymity));
			if (RegOpenKeyEx(HKEY_CURRENT_USER,keyWinMine,0,KEY_WRITE,&hKey)==ERROR_SUCCESS){			
				for (i=0;i<3;i++){	
					dwTime=999;
					RegSetValueEx(hKey,lpsTime[i],NULL,dwType1,(LPBYTE)&dwTime,dwSize1);
					RegSetValueEx(hKey,lpsName[i],NULL,dwType2,(LPBYTE)&lpAnonymity,dwSize2);
				}
				RegCloseKey(hKey);
				SendMessage(hDlg,WM_INITDIALOG,wParam,lParam);
			}
			break;
		case IDC_RECORD_OK:			//�����¼�¼ȷ��
			GetDlgItemText(hDlg,IDC_RECORD_NAME,lpBuff,sizeof(lpBuff));
			if (strlen(lpBuff)>0){	//���벻Ϊ��		
				if (RegOpenKeyEx(HKEY_CURRENT_USER,keyWinMine,0,KEY_WRITE,&hKey)==ERROR_SUCCESS){
					RegSetValueEx(hKey,lpsTime[(flagState&0x0f00)/0x0100],NULL,dwType1,(LPBYTE)&timeCount,dwSize1);
					RegSetValueEx(hKey,lpsName[(flagState&0x0f00)/0x0100],NULL,dwType2,(LPBYTE)&lpBuff,dwSize2);
					RegCloseKey(hKey);
				}
			}
			EndDialog(hDlg,TRUE);			
			break;
		}
	}
	return FALSE;				//���������Ϣ����FALSE
}

/*###########################################################
���ܣ���ʼ����ͼ������Ϣ
���������ھ�����ȼ������ߡ��ס���־����ʱ�������־�������־
����ֵ���ɹ� ����TRUE
###########################################################*/

BOOL IinitializeMapInfo(HWND hWnd,int level,int col,int ln,int bomb){	
	mineRowNum=(col<MAX_COL_NUM) ? col:MAX_COL_NUM;		//Խ����Ϊ��ֵ
	mineRowNum=(col>MIN_COL_NUM) ? col:MIN_COL_NUM;
	mineLineNum=(ln<MAX_LN_NUM) ? ln:MAX_LN_NUM;
	mineLineNum=(ln>MIN_LN_NUM) ? ln:MIN_LN_NUM;
	mineBomb=(bomb<MAX_BOMB_NUM) ? bomb:MAX_BOMB_NUM;
	mineBomb=(bomb>MIN_BOMB_NUM) ? bomb:MIN_BOMB_NUM;	
	flagState=(flagState & 0xf0ff)+level*0x0100;		//���ñ�־λ
	flagState=(flagState & 0xfffe)+0x0001;
	flagState=flagState & 0xfffd;
	flagState=(flagState & 0x0fff)+0x4000;
	bombCount=bomb;
	timeCount=0;
	openCount=mineRowNum*mineLineNum-mineBomb;	
	KillTimer(hWnd,FLAG_TIMECOUNT);						//ֹͣ��ǰ���еļ�ʱ��
	return TRUE; 
}
/*###########################################################
//���ܣ����������ͼ
//���������ھ��
//����ֵ��
//###########################################################*/
BOOL CreateRandomMap(HWND hWnd){
	btLandmineMapinfo[0][0]=(BYTE)0;
	DWORD ixMine,iyMine,iMineBomb,icBomb=0,x,y;
	RECT rcMine;	
	for(int i=0;i<mineRowNum;i++)//��ʼΪ0
		for(int j=0;j<mineLineNum;j++) btLandmineMapinfo[i][j]=(BYTE)0;
	ixMine=(int)floor(mineRowNum/2);	//��4����
	iyMine=(int)floor(mineLineNum/2);
	iMineBomb=(int)floor(mineBomb/4);
    srand((unsigned)time(NULL));		//�õ�ʱ�����	
	while (icBomb<iMineBomb) {//��������
		x=rand()%ixMine;
		y=rand()%iyMine;
		if (btLandmineMapinfo[x][y]!=0x10) {
			btLandmineMapinfo[x][y]=(BYTE)0x10;
			icBomb++;
		}	 
	}
	icBomb=0;	
	while (icBomb<iMineBomb) {//��������
		x=rand()%(mineRowNum-ixMine)+ixMine;
		y=rand()%iyMine;
		if (btLandmineMapinfo[x][y]!=0x10) {
			btLandmineMapinfo[x][y]=(BYTE)0x10;
			icBomb++;
		}
	}
	icBomb=0;	
	while (icBomb<iMineBomb) {//��������
		x=rand()%ixMine;
		y=rand()%(mineLineNum-iyMine)+iyMine;
		if (btLandmineMapinfo[x][y]!=0x10) {
			btLandmineMapinfo[x][y]=(BYTE)0x10;
			icBomb++;
		}
	}
	icBomb=0;	
	while (icBomb<(mineBomb-3*iMineBomb)) {//��������
		x=rand()%(mineRowNum-ixMine)+ixMine;
		y=rand()%(mineLineNum-iyMine)+iyMine;
		if (btLandmineMapinfo[x][y]!=0x10) {
			btLandmineMapinfo[x][y]=(BYTE)0x10;
			icBomb++;
		}	
	}
	rcMine=CreateRect(MAIN_LEFTSTND,MAIN_TOPSTND,mineRowNum*MINE_BITMAP_WIDTH,mineLineNum*MINE_BITMAP_HEIGHT,FALSE);
	InvalidateRect(hWnd,&rcMine,FALSE);
	return TRUE;
}


/*###########################################################
���ܣ��õ�����λ�ú�״̬
���������ھ����ʵ�������x���ꡢy���ꡢ��ǰ����
����ֵ����ǰ������Ϣ�ṹ��
###########################################################*/
tagMouseState getMousePosition(HWND hWnd,HINSTANCE hInstance,int cxMousePos,int cyMousePos){
	tagMouseState state;
	//�������õ�������λ��
	if (cxMousePos>MAIN_LEFTSTND&&cxMousePos<(MAIN_LEFTSTND+mineRowNum*MINE_BITMAP_WIDTH)&&cyMousePos>MAIN_TOPSTND&&cyMousePos<(MAIN_TOPSTND+mineLineNum*MINE_BITMAP_HEIGHT)){	
		state.mXpos=(int)floor((cxMousePos-MAIN_LEFTSTND)/MINE_BITMAP_WIDTH);
		state.mYpos=(int)floor((cyMousePos-MAIN_TOPSTND)/MINE_BITMAP_HEIGHT);
		state.mNowPostion=MOUSE_ON_MINE;
	} else if (cxMousePos>=(MAIN_LEFTSTND+(mineRowNum*MINE_BITMAP_WIDTH-FACE_BITMAP_WIDTH)/2)&&cxMousePos<=(MAIN_LEFTSTND+(mineRowNum*MINE_BITMAP_WIDTH-FACE_BITMAP_WIDTH)/2+FACE_BITMAP_WIDTH)&&cyMousePos>=((MAIN_TOPSTND-FACE_BITMAP_HEIGHT)/2)&&cyMousePos<=((MAIN_TOPSTND-FACE_BITMAP_HEIGHT)/2+FACE_BITMAP_HEIGHT)) {
		state.mNowPostion=MOUSE_ON_FACE;//������
	}else{//��������
		state.mXpos=cxMousePos>MAIN_LEFTSTND?(int)floor((cxMousePos-MAIN_LEFTSTND)/MINE_BITMAP_WIDTH):-2;
		state.mXpos=cxMousePos<(MAIN_LEFTSTND+mineRowNum*MINE_BITMAP_WIDTH)?state.mXpos:mineRowNum+1;
		state.mYpos=cyMousePos>MAIN_TOPSTND?(int)floor((cyMousePos-MAIN_TOPSTND)/MINE_BITMAP_HEIGHT):-2;
		state.mYpos=cyMousePos<(MAIN_TOPSTND+mineLineNum*MINE_BITMAP_HEIGHT)?state.mYpos:mineLineNum+1;
		state.mNowPostion=MOUSE_ON_OTHER;
	}
	return state;
}

/*###########################################################
���ܣ���������ı��ͼ�Ϸ������Ϣ
���������ھ����ʵ������������Ϣ
����ֵ��
###########################################################*/
BOOL OnChangeMineInfo(HWND hWnd,HINSTANCE hInstance,tagMouseState mouse){
	tagMouseState lastMouse;	//�ϴε������Ϣ
	RECT rcRefresh=CreateRect(mouse.mXpos,mouse.mYpos,1,1,TRUE);	//ˢ������
	if (mouse.mXpos<0||mouse.mYpos<0||mouse.mXpos>=mineRowNum||mouse.mYpos>=mineLineNum) //��������������
		return FALSE;
	if (btLandmineMapinfo[mouse.mXpos][mouse.mYpos]>=0x20)		//����0x20����ԭ
		OnChangeMineUpon(hWnd,mouse.mXpos,mouse.mYpos,0);	
	if (btLandmineMapinfo[mouse.mXpos][mouse.mYpos]%0x10==0x01||btLandmineMapinfo[mouse.mXpos][mouse.mYpos]%0x10>0x02)
		return FALSE;//���ӻ������֣��ѷ������׵ȣ�������
	if (btLandmineMapinfo[mouse.mXpos][mouse.mYpos]==0x10||btLandmineMapinfo[mouse.mXpos][mouse.mYpos]==0x12) 	{	
		btLandmineMapinfo[mouse.mXpos][mouse.mYpos]=(BYTE)0x13;	//		����Ϊ��ը����
		setGameLost(hWnd,hInstance);								//		��Ϸʧ��
	}	
	else if (btLandmineMapinfo[mouse.mXpos][mouse.mYpos]==0x00||btLandmineMapinfo[mouse.mXpos][mouse.mYpos]==0x02){//������
		btLandmineMapinfo[mouse.mXpos][mouse.mYpos]=0x0f-getRoundMineNum(hWnd,mouse.mXpos,mouse.mYpos);//�õ���Χ������
		openCount--;//�ո�������
		if (btLandmineMapinfo[mouse.mXpos][mouse.mYpos]==0x0f){ //�����0
			lastMouse=mouse;
			for (int i=0;i<3;i++)
				for (int j=0;j<3;j++){	
					lastMouse.mXpos=mouse.mXpos-1+i;
					lastMouse.mYpos=mouse.mYpos-1+j;
					OnChangeMineInfo(hWnd,hInstance,lastMouse); //�ݹ�չ����Χ��ֱ�����ֱ߽�
				}
		}
	}	
	InvalidateRect(hWnd,&rcRefresh,FALSE);	
	return TRUE;
}

/*###########################################################
���ܣ���Ϸʧ��
���������ھ����ʵ�����
����ֵ��
###########################################################*/

BOOL setGameLost(HWND hWnd,HINSTANCE hInstance){
	RECT rcRefrush=CreateRect(MAIN_LEFTSTND,MAIN_TOPSTND,mineRowNum*MINE_BITMAP_WIDTH,mineLineNum*MINE_BITMAP_HEIGHT,FALSE);
	KillTimer(hWnd,FLAG_TIMECOUNT);	//������ʱ��
	if ((flagState&0x0010)!=0x0000){	// ��������	
		HRSRC hrWare=FindResource(hInstance,MAKEINTRESOURCE(IDW_WAVE_BOMB),TEXT("WAVE"));
		HGLOBAL hGlobal=LoadResource(hInstance,hrWare);
		PlaySoundW((LPCWSTR)LockResource(hGlobal),NULL,SND_MEMORY|SND_ASYNC);
	}
	for(int i=0;i<mineRowNum;i++){	//չ��������
		for(int j=0;j<mineLineNum;j++){
			if (btLandmineMapinfo[i][j]==0x10) btLandmineMapinfo[i][j]=0x15;	//δ������
			if (btLandmineMapinfo[i][j]==0x01) btLandmineMapinfo[i][j]=0x04;	//��������
		}
	}
	flagState=flagState&0xfffe;
	InvalidateRect(hWnd,&rcRefrush,FALSE);	
	RefreshSmileFaceBmp(hWnd,FACE_TYPE_GRIEF);
	return TRUE;
}

/*###########################################################
���ܣ���õ�ǰ�ȼ����ڵ�λ�úʹ�С��Ϣ
���������ھ��
����ֵ������ ���ϵ����꣨left��top����С��right��bottom��
###########################################################*/
RECT getLevelWindowSize(HWND hWnd){
	RECT rcFrame,rcWindow,rcClient;
	GetWindowRect(hWnd,&rcWindow);
	GetClientRect(hWnd,&rcClient);
	rcFrame.left=rcWindow.left;		//�������λ��
	rcFrame.top=rcWindow.top;		//�����ϱ�λ��		
	rcFrame.right=rcClient.left-rcWindow.left+rcWindow.right-rcClient.right+mineRowNum*MINE_BITMAP_WIDTH+MAIN_LEFTSTND+MAIN_RIGHTSTND;//���ڵĿ��		
	rcFrame.bottom=rcClient.top-rcWindow.top+rcWindow.bottom-rcClient.bottom+mineLineNum*MINE_BITMAP_HEIGHT+MAIN_TOPSTND+MAIN_BOTTOMSTND;//���ڵĸ߶�
	return rcFrame;
}
/*###########################################################
���ܣ����3D�߿�
������HDC�������߿�
����ֵ��
###########################################################*/
BOOL DrawSolidFrame(HDC hDC,RECT rcFrame,int iLighten){
	HPEN hPen;
	for(int iCount=0;iCount<iLighten;iCount++){	
		hPen=CreatePen(PS_SOLID,0,RGB(250,250,250));
		SelectObject(hDC,hPen);
		MoveToEx(hDC,rcFrame.right-iCount-1,rcFrame.top+iCount,NULL);	//����
		LineTo(hDC,rcFrame.right-iCount-1,rcFrame.bottom-iCount-1);		//����
		LineTo(hDC,rcFrame.left+iCount,rcFrame.bottom-iCount-1);		//����
		DeleteObject(hPen);
		hPen=CreatePen(PS_SOLID,0,RGB(8+(flagState&0x0004)*30,8+(flagState&0x0004)*30,8+(flagState&0x0004)*30));
		SelectObject(hDC,hPen);
		LineTo(hDC,rcFrame.left+iCount,rcFrame.top+iCount);				//����
		LineTo(hDC,rcFrame.right-iCount,rcFrame.top+iCount);			//����
		DeleteObject(hPen);
	}
	return TRUE;
}

/*###########################################################
���ܣ�	����һ�����������������������Ϊ0���õ�����һ���׵Ĵ�С�����򣬷������������������
������		
����ֵ��
###########################################################*/
RECT CreateRect(int left,int top,int width,int height,bool bMine){
	RECT rcReturn;
	rcReturn.left=bMine?MAIN_LEFTSTND+(left-width/2)*MINE_BITMAP_WIDTH:left;
	rcReturn.top=bMine?MAIN_TOPSTND+(top-height/2)*MINE_BITMAP_HEIGHT:top;
	rcReturn.right=bMine?rcReturn.left+width*MINE_BITMAP_WIDTH:left+width;
	rcReturn.bottom=bMine?rcReturn.top+MINE_BITMAP_HEIGHT+height*MINE_BITMAP_HEIGHT:top+height;
	return rcReturn;
}

/*###########################################################
���ܣ������Χ�׵���Ŀ
���������ھ��������λ��
����ֵ����Χ�׵���Ŀ
###########################################################*/
BYTE getRoundMineNum(HWND hWnd,int iCol,int iLn){
	BYTE btNum=0;
	for(int i=iCol-1;i<=iCol+1;i++)
		for(int j=iLn-1;j<=iLn+1;j++)	//����0x10Ϊ��
			if (btLandmineMapinfo[i][j]>=0x10&&i>=0&&j>=0&&i<mineRowNum&&j<mineLineNum) btNum++;
	return btNum;	
}

/*###########################################################
���ܣ������Χ���ӵ���Ŀ
���������ھ��������λ��
����ֵ����Χ���ӵ���Ŀ
###########################################################*/
BYTE getRoundFlagNum(HWND hWnd,int iCol,int iLn){
	BYTE btNum=0;
	for(int i=iCol-1;i<=iCol+1;i++)
		for(int j=iLn-1;j<=iLn+1;j++)
			if (btLandmineMapinfo[i][j]%0x10==0x01&&i>=0&&j>=0&&i<mineRowNum&&j<mineLineNum) 
				btNum++;		
	return btNum;	
}

/*###########################################################
���ܣ�ˢ�±���ͼƬ����
���������ھ������������
����ֵ��
###########################################################*/

BOOL RefreshSmileFaceBmp(HWND hWnd,int iFaceType){
	RECT rcRefresh=CreateRect(MAIN_LEFTSTND+(mineRowNum*MINE_BITMAP_WIDTH-FACE_BITMAP_WIDTH)/2,(MAIN_TOPSTND-FACE_BITMAP_HEIGHT)/2,FACE_BITMAP_WIDTH,FACE_BITMAP_HEIGHT,FALSE);
	if ((flagState&0xf000)==iFaceType*0x1000) return FALSE;
	flagState = (flagState&0x0fff)+iFaceType*0x1000;
	InvalidateRect(hWnd,&rcRefresh,FALSE);
	return TRUE;
}

/*###########################################################
���ܣ������Ϣ����
���������ھ����ʵ���������ǰ���ṹ�塢�Զ�����Ϣ����
����ֵ��
###########################################################*/

BOOL OnMouseClick(HWND hWnd,HINSTANCE hInstance,tagMouseState nowMouse,int startMouse){
	static int				lastFace=0,lastXpos,lastYpos;
	static tagMouseState    lastMouse;
	tagMouseState			tempMouse;				//��ʱ���ṹ��
	TCHAR					lpMessage[255];			//��Ϣ�ַ���
	int						i;					//��ʱ����
	BYTE					temp;					//��ʱ����
	RECT					rcRefresh,rcWnd;				//ˢ������
	switch(nowMouse.mNowPostion){
	case MOUSE_ON_MINE:
		if (!(flagState&0x0001)||startMouse==MOUSE_ON_FACE) return 0;
		switch(nowMouse.mButtonMode)
		{
		case BTN_LBUTTONDOWN:
			OnChangeMineDown(hWnd,nowMouse.mXpos,nowMouse.mYpos,0);
			lastXpos=nowMouse.mXpos;
			lastYpos=nowMouse.mYpos;
			RefreshSmileFaceBmp(hWnd,FACE_TYPE_EXCLAIM);
			break;
		case BTN_LBUTTONUP:
			if (!(flagState & 0x0002)){		//δ��ʼ��ʱ
				timeCount=1;
				GetClientRect(hWnd,&rcWnd);
				rcRefresh=CreateRect(rcWnd.right-TIME_RIGHTSTND-TIME_WIDTH,TIME_TOPPOS,TIME_WIDTH,TIME_HEIGHT,FALSE);
				InvalidateRect(hWnd,&rcRefresh,FALSE);
				if (SetTimer(hWnd,FLAG_TIMECOUNT,1000,NULL)==0){ //��ʱ������ʧ��	
					LoadString(hInstance,IDS_TIMER_ERROR,lpMessage,sizeof(lpMessage));
					if (MessageBox(hWnd,lpMessage,"���ش���!",MB_ICONSTOP)==IDOK) SendMessage(hWnd,WM_DESTROY,NULL,NULL); //�˳�����
				}

				OnChangeMineUpon(hWnd,nowMouse.mXpos,nowMouse.mYpos,0);
				if (btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]==0x10||btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]==0x12){
					i=0;	//��һ������
					do{	
						if (nowMouse.mYpos+i>=mineRowNum||nowMouse.mXpos+i>=mineLineNum) //�������ܽ�����������ɵ�ͼ
							CreateRandomMap(hWnd);i=0;//����λ��
						temp=btLandmineMapinfo[mineRowNum-nowMouse.mXpos-i][mineLineNum-nowMouse.mYpos-i];
						btLandmineMapinfo[mineRowNum-nowMouse.mXpos-i][mineLineNum-nowMouse.mYpos-i]=btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos];
						btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]=temp;
						i++;
					}while (btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]>=0x10);		
				}
				flagState = (flagState & 0xfffd)+0x0002; //��ʼ��ʱ��
			}
			RefreshSmileFaceBmp(hWnd,FACE_TYPE_SMILE_POP);
			OnChangeMineInfo(hWnd,hInstance,nowMouse);			//�ı��ͼ��Ϣ
			break;
		case BTN_RBUTTONDOWN:
			if (btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]%0x10>0x02)	break;//�Ѿ�����������
			if ((btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]%0x10)<0x01+(flagState & 0x0008)/0x0008) 
				btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]++;//�����ǣ�δ���� -������-���ʺţ��������ǣ�δ���� -������
			else if ((btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]%0x10)==0x01+(flagState & 0x0008)/0x0008)
				btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]-=(1+(flagState & 0x0008)/0x0008);//����Ϊδ������״̬
			else if (btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]%0x10==0x02&&(flagState & 0x0008)==0)	{
				btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]-=2;
				bombCount--;
			}
			bombCount=bombCount-((btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]%0x10)%2)*(0x01+(((flagState & 0x0008)/0x0008+0x01)%0x02))+(btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]%0x10)/0x02+((flagState & 0x0008)/0x0008+0x01)%0x02;
			rcRefresh=CreateRect(nowMouse.mXpos,nowMouse.mYpos,1,1,TRUE);
			InvalidateRect(hWnd,&rcRefresh,FALSE);
			rcRefresh=CreateRect(COUNT_LEFTPOS,COUNT_TOPPOS,COUNT_WIDTH,COUNT_HEIGHT,FALSE);
			InvalidateRect(hWnd,&rcRefresh,FALSE);
		    break;			
		case BTN_DBBUTTONDOWN:
			OnChangeMineDown(hWnd,nowMouse.mXpos,nowMouse.mYpos,1);
			break;
		case BTN_DBBUTTONUP:
			OnChangeMineUpon(hWnd,nowMouse.mXpos,nowMouse.mYpos,1);	
			RefreshSmileFaceBmp(hWnd,FACE_TYPE_SMILE_POP);
			if (btLandmineMapinfo[nowMouse.mXpos][nowMouse.mYpos]%0x10>6){		//����Ƿ���������		
				if (getRoundFlagNum(hWnd,nowMouse.mXpos,nowMouse.mYpos)==getRoundMineNum(hWnd,nowMouse.mXpos,nowMouse.mYpos)){	//�������
					for (int i=0;i<3;i++)								//������Χ9�񣨻�ݹ飩{
						for (int j=0;j<3;j++){								
							tempMouse.mXpos=nowMouse.mXpos-1+i;
							tempMouse.mYpos=nowMouse.mYpos-1+j;
							OnChangeMineInfo(hWnd,hInstance,tempMouse);
						}
					}
				}

			break;
		case BTN_LBUTTONMOVING:
			if (lastXpos!=nowMouse.mXpos||lastYpos!=nowMouse.mYpos){
				OnChangeMineUpon(hWnd,lastXpos,lastYpos,0);
				OnChangeMineDown(hWnd,nowMouse.mXpos,nowMouse.mYpos,0);
				lastXpos=nowMouse.mXpos;
				lastYpos=nowMouse.mYpos;
			}	
		    break;
		case BTN_DBBUTTONMOVING:
			if (lastXpos!=nowMouse.mXpos||lastYpos!=nowMouse.mYpos){
				OnChangeMineUpon(hWnd,lastXpos,lastYpos,1);
				OnChangeMineDown(hWnd,nowMouse.mXpos,nowMouse.mYpos,1);
				lastXpos=nowMouse.mXpos;
				lastYpos=nowMouse.mYpos;
			}	
			break;
		}
		break;
/////////////////////////////////////////////
	case MOUSE_ON_FACE:
	    switch(nowMouse.mButtonMode)
		{
		case BTN_LBUTTONDOWN:
			lastFace=(flagState&0xf000)/0x1000;
			RefreshSmileFaceBmp(hWnd,FACE_TYPE_SMILE_PUSH);			
			break;
		case BTN_LBUTTONUP:	
		case BTN_DBBUTTONUP:
			if (flagState&0x0001==0x0000)			//��Ϸδ��ʼ��ʼ
				flagState=(flagState&0xfffe)+0x0001;
			RefreshSmileFaceBmp(hWnd,FACE_TYPE_SMILE_POP);
			IinitializeMapInfo(hWnd,(flagState&0x0f00)/0x0100,mineRowNum,mineLineNum,mineBomb); //??
			CreateRandomMap(hWnd);
			InvalidateRect(hWnd,NULL,FALSE);
			lastFace=0x0004;
			break;
		}
	    break;
/////////////////////////////////////////////
	case MOUSE_ON_OTHER:

		if (startMouse==MOUSE_ON_FACE){
			RefreshSmileFaceBmp(hWnd,lastFace);
			return FALSE;
		}
		if (!(flagState&0x0001)) return 0;
	    switch(nowMouse.mButtonMode)
		{
		case BTN_LBUTTONDOWN:
		case BTN_DBBUTTONDOWN:
			RefreshSmileFaceBmp(hWnd,FACE_TYPE_EXCLAIM);			
			break;
		case BTN_RBUTTONUP:
		case BTN_LBUTTONUP:			
			RefreshSmileFaceBmp(hWnd,FACE_TYPE_SMILE_POP);
			break;
		case BTN_LBUTTONMOVING:
			if (lastXpos!=nowMouse.mXpos||lastYpos!=nowMouse.mYpos){
				OnChangeMineUpon(hWnd,lastXpos,lastYpos,0);
				OnChangeMineDown(hWnd,nowMouse.mXpos,nowMouse.mYpos,0);
				lastXpos=nowMouse.mXpos;
				lastYpos=nowMouse.mYpos;
			}	
		    break;
		case BTN_DBBUTTONMOVING:
			if (lastXpos!=nowMouse.mXpos||lastYpos!=nowMouse.mYpos){
				OnChangeMineUpon(hWnd,lastXpos,lastYpos,1);
				OnChangeMineDown(hWnd,nowMouse.mXpos,nowMouse.mYpos,1);
				lastXpos=nowMouse.mXpos;
				lastYpos=nowMouse.mYpos;
			}	
			break;
		}
		break;
	}
	if (openCount==0) setGameSucceed(hWnd,hInstance);	//�жϽ������ո�Ϊ0��ʣ�µĶ����ף���Ǻ�Ϊ������ӵģ�������Ϸ�ɹ�
	return FALSE;
}

/*###########################################################
���ܣ����õȼ��ı��˵���check
�������˵�������ȼ�
����ֵ��
###########################################################*/
BOOL OnCheckLevelMenu(HMENU hMenu,int level){
	CheckMenuItem(hMenu,IDM_ADVANCED,MF_UNCHECKED);//����δ��
	CheckMenuItem(hMenu,IDM_INTERMEDIATE,MF_UNCHECKED);
	CheckMenuItem(hMenu,IDM_BEGINNER,MF_UNCHECKED);
	CheckMenuItem(hMenu,IDM_CUSTOMDEFINE,MF_UNCHECKED);
	CheckMenuItem(hMenu,IDM_BEGINNER+level,MF_CHECKED); //��ѡ��ǰ�ȼ�
	flagState=((flagState&0xf0ff)+level*0x0100);		//�ı�״̬
	return TRUE;
}
/*###########################################################
���ܣ�������Ϸ�ɹ�
������
����ֵ��
###########################################################*/

BOOL setGameSucceed(HWND hWnd,HINSTANCE hInstance){
	RECT			rcRefresh;	
	LPCTSTR			keyWinMine=TEXT("Software\\Microsoft\\winmine\\");
	LONG			lErrorID=0;
	DWORD 			dwSize=sizeof(DWORD);
	HKEY			hKey;
	DWORD			dwTime;											
	LPCTSTR			lpsLevel[3]={TEXT("Time1"),TEXT("Time2"),TEXT("Time3")};
	openCount=-1;							//���ÿո����
	bombCount=0;
	rcRefresh=CreateRect(COUNT_LEFTPOS,COUNT_TOPPOS,COUNT_WIDTH,COUNT_HEIGHT,FALSE);	InvalidateRect(hWnd,&rcRefresh,FALSE);
	KillTimer(hWnd,FLAG_TIMECOUNT);		//��������
	if ((flagState&0x0010)!=0){
		HRSRC			hrWare=FindResource(hInstance,MAKEINTRESOURCE(IDW_WAVE_DONE),TEXT("WAVE")); //����������Դ
		HGLOBAL			hGlobal=LoadResource(hInstance,hrWare);
		PlaySoundW((LPCWSTR)LockResource(hGlobal),NULL,SND_MEMORY|SND_ASYNC);
	}
	flagState=flagState& 0xfffe;				//���ý���״̬��δ��ʱ
	RefreshSmileFaceBmp(hWnd,FACE_TYPE_COOL);	//����-��
	for (int i=0;i<mineRowNum;i++){				//���δ��ǵ���Ϊ����
		for (int j=0;j<mineLineNum;j++){		
			if (btLandmineMapinfo[i][j]>=0x10)
			{
				btLandmineMapinfo[i][j]=0x11;
				rcRefresh=CreateRect(i,j,1,1,TRUE);
				InvalidateRect(hWnd,&rcRefresh,FALSE);
			}
		}
	}
	if ((flagState&0x0f00)>0x0200)	return FALSE;//����Ǽ�Ϊ�Զ��壬���أ����������к�ע���
	lErrorID=RegOpenKeyEx(HKEY_CURRENT_USER,keyWinMine,0,KEY_READ,&hKey);//��ȡ��ǰ������Ϣ
	if (lErrorID==ERROR_SUCCESS){
		lErrorID=RegQueryValueEx(hKey,lpsLevel[(flagState&0x0f00)/0x0100],NULL,NULL,(LPBYTE)&dwTime,&dwSize);
		if (lErrorID==ERROR_SUCCESS){
			if (timeCount<(int)dwTime)DialogBox(hInstance,MAKEINTRESOURCE(IDD_RECORDDLG),hWnd,WinDlgProc);   //�Ƽ�¼��//�����¼�¼
		} 
		else ErrorMessageBox(hWnd,hInstance,IDS_ERRORID,lErrorID);	
	}else ErrorMessageBox(hWnd,hInstance,IDS_ERRORID,lErrorID);
	RegCloseKey(hKey);
	return TRUE;
}

/*###########################################################
���ܣ�������Ϣ�Ի���
���������ھ����ʵ���������Ϣ����Ϣid
����ֵ��
###########################################################*/

BOOL ErrorMessageBox(HWND hWnd,HINSTANCE hInstance,UINT IDMessage,UINT IDError){
	TCHAR lpFormat[255],lpOutput[255];
	if (IDError!=0){
		LoadString(hInstance,IDMessage,lpFormat,sizeof(lpFormat));
		sprintf(lpOutput,lpFormat,IDError);
	}
	else LoadString(hInstance,IDMessage,lpOutput,sizeof(lpOutput));
	MessageBox(hWnd,lpOutput,"����",MB_ICONERROR);
	return TRUE;
}

/*###########################################################
���ܣ��Ƿ�����ʾΪ���µ�״̬
���������λ�ýṹ��
����ֵ��
###########################################################*/

BOOL OnChangeMineDown(HWND hWnd,int xPos,int yPos,int mNum){
	RECT rcRefresh;
	for (int i=xPos-mNum;i<=xPos+mNum;i++){
		for (int j=yPos-mNum;j<=yPos+mNum;j++){
			if (i>=0&&i<mineRowNum&&j>=0&&j<mineLineNum&&btLandmineMapinfo[i][j]<0x20){ //Խ�磬������
				if (btLandmineMapinfo[i][j]%0x10==0) btLandmineMapinfo[i][j]+=0x2f;		//0x2f ��ʾΪ 0��״̬ 0x
				if (btLandmineMapinfo[i][j]%0x10==2) btLandmineMapinfo[i][j]+=0x24;
				rcRefresh=CreateRect(i,j,mNum+1,mNum+1,TRUE);
				InvalidateRect(hWnd,&rcRefresh,FALSE);
			}
		}
	}
	return TRUE;
}

/*###########################################################
���ܣ���ԭ��ʾΪ����״̬�ķ���
���������λ�ýṹ��
����ֵ��
###########################################################*/

BOOL OnChangeMineUpon(HWND hWnd,int xPos,int yPos,int mNum){
	RECT rcRefresh;
	for (int i=xPos-mNum;i<=xPos+mNum;i++){
		for (int j=yPos-mNum;j<=yPos+mNum;j++){
			if (i>=0&&i<mineRowNum&&j>=0&&j<mineLineNum){ //Խ�磬������			
				if (btLandmineMapinfo[i][j]>=0x20){					
					if (btLandmineMapinfo[i][j]%0x10==0x0f)	btLandmineMapinfo[i][j]-=0x2f;		//0x2f ��ʾΪ 0��״̬ 0x
					if (btLandmineMapinfo[i][j]%0x10==0x06) btLandmineMapinfo[i][j]-=0x24;
					rcRefresh=CreateRect(i,j,mNum+1,mNum+1,TRUE);
					InvalidateRect(hWnd,&rcRefresh,FALSE);
				}
			}
		}
	}
	return TRUE;
}
