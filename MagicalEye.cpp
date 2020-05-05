#include "MagicalEye.h"

void  MainFrame_create( int ) ;
LRESULT CALLBACK MainFrameProc( HWND , UINT , WPARAM , LPARAM ) ;
LRESULT CALLBACK ShowPanelProc( HWND , UINT , WPARAM , LPARAM ) ;
LRESULT CALLBACK DrawPanelProc( HWND , UINT , WPARAM , LPARAM ) ;


static void makeWindowClass() ;


HINSTANCE hInst ;


int WINAPI WinMain( HINSTANCE hCurInst , HINSTANCE hPrevInst , LPSTR lpsCmdLine , int nCmdShow )
{
	hInst = hCurInst ;
    makeWindowClass() ;

	MainFrame_create( nCmdShow ) ;

	MSG msg;
	while( GetMessage( &msg , NULL , 0 , 0 ) )
    {
		TranslateMessage( &msg ) ;
		DispatchMessage( &msg ) ;
    }
    return msg.wParam ;
}


static void makeWindowClass()
{
    WNDCLASS wc;
	
	//MainFrame
	wc.style = CS_HREDRAW | CS_VREDRAW ;
	wc.style = 0 ;
	wc.lpfnWndProc = MainFrameProc ;
	wc.cbClsExtra = 0 ;
	wc.cbWndExtra = 0 ;
	wc.hInstance = hInst ;
	wc.hIcon = LoadIcon( NULL , IDI_APPLICATION ) ;
	wc.hCursor = LoadCursor( NULL , IDC_ARROW ) ;
	wc.hbrBackground = ( HBRUSH )GetStockObject( WHITE_BRUSH ) ;
	wc.lpszMenuName = "MainFrameMenu" ;
	wc.lpszClassName = "MAINFRAME" ;
	RegisterClass( &wc ) ;

	//ShowPanel
	wc.lpfnWndProc = ShowPanelProc ;
	wc.lpszClassName = "SHOWPANEL" ;
	RegisterClass( &wc ) ;


	//ShowPanel
	wc.lpfnWndProc = DrawPanelProc ;
	wc.lpszClassName = "DRAWPANEL" ;
	RegisterClass( &wc ) ;
}



void alert()
{
	MessageBox( NULL , "" , "ColorDot" , MB_OK ) ;
}

void alert( const char* str )
{
	MessageBox( NULL , str , "ColorDot" , MB_OK ) ;
}

void alert( int num )
{
	char str[50] ;
	wsprintf( str , "%d" , num ) ;
	MessageBox( NULL , str , "ColorDot" , MB_OK ) ;
}

void alert( char* title , int num )
{
	char str[50] ;
	wsprintf( str , "%d" , num ) ;
	MessageBox( NULL , str , title , MB_OK ) ;
}