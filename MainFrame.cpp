#include "MagicalEye.h"

HWND ShowPanel_create( HWND ) ;
HWND DrawPanel_create( HWND ) ;
void DrawPanel_sendScript() ;
void DrawPanel_changePen( int ) ;
void DrawPanel_setBoldness( int ) ;
void DrawPanel_clearScript() ;
void Picture_changeBackground( int ) ;
void Picture_overUnder( bool ) ;


void Picture_paint( HDC );
static void paint() ;
static void paintCircle( HDC , int ) ;


static HWND hWnd ;
static HWND hShowPanel , hDrawPanel ;


LRESULT CALLBACK MainFrameProc( HWND _hWnd , UINT msg , WPARAM wp , LPARAM lp )
{
	switch( msg )
	{
	case WM_CREATE :
		hWnd = _hWnd ;
		hShowPanel = ShowPanel_create( hWnd ) ;
		hDrawPanel = DrawPanel_create( hWnd ) ;
		break ;

	case WM_COMMAND :
		switch( LOWORD( wp ) )
		{
		case MI_SHOW :
			DrawPanel_sendScript() ;
			break ;
			
		case MI_LOWER :
			DrawPanel_changePen( 0 ) ;
			break ;			

		case MI_UPPER :
			DrawPanel_changePen( 1 ) ;
			break ;
			
		case MI_BOLDNESS1 :
			DrawPanel_setBoldness( 1 ) ;
			break ;

		case MI_BOLDNESS2 :
			DrawPanel_setBoldness( 7 ) ;
			break ;

		case MI_BOLDNESS3 :
			DrawPanel_setBoldness( 13 ) ;
			break ;
			
		case MI_BOLDNESS4 :
			DrawPanel_setBoldness( 30 ) ;
			break ;
			
		case MI_CLEAR :
			DrawPanel_clearScript() ;
			break ;
			
		case MI_BACKGROUND1 :
			Picture_changeBackground( 1 ) ;
			break ;
			
		case MI_BACKGROUND2 :
			Picture_changeBackground( 2 ) ;
			break ;

		case MI_BACKGROUND3 :
			Picture_changeBackground( 3 ) ;
			break ;
			
		case MI_BACKGROUND4 :
			Picture_changeBackground( 4 ) ;
			break ;
			
		case MI_OVEROVER :
			Picture_overUnder( true ) ;
			break ;
			
		case MI_OVERUNDER :
			Picture_overUnder( false ) ;
			break ;
		}
		break ;
		
	case WM_PAINT :
		paint() ;
		break ;

	case WM_DESTROY :
		hWnd = NULL ;
		PostQuitMessage( 0 ) ;
		break ;
		
	default :
		return( DefWindowProc( _hWnd , msg , wp , lp ) ) ;
	}
    return 0L ;
}


static void paint()
{
	PAINTSTRUCT ps ;
	HDC hdc = BeginPaint( hWnd , &ps ) ;

	HPEN hPen , hPrePen ;
	hPen = ( HPEN )CreatePen( PS_SOLID , 1 , RGB( 0 , 0 , 0 ) ) ;
	hPrePen = ( HPEN )SelectObject( hdc , hPen ) ;
	SelectObject( hdc , GetStockObject( NULL_BRUSH ) ) ;
	Rectangle( hdc , 0 , ( ( MAXY + Y*0.5 ) * PIX ) , ( MAXX * PIX ) , ( ( MAXY * 2 + Y*0.5 ) * PIX ) ) ;
	SelectObject( hdc , hPrePen ) ;
	DeleteObject( hPen ) ;

	EndPaint( hWnd , &ps ) ;
}


void MainFrame_create( int nCmdShow )
{
	HWND hWnd = CreateWindow( "MAINFRAME" , "マジカルアイ" , 
			WS_OVERLAPPEDWINDOW ,
            CW_USEDEFAULT , 0 , ( ( MAXX + X ) * PIX ) , ( ( MAXY + Y ) * 2 * PIX ) , 
            NULL , NULL , hInst , NULL ) ;
    ShowWindow( hWnd , nCmdShow ) ;
    UpdateWindow( hWnd ) ;
}