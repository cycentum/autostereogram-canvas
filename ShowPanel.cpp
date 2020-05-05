#include "MagicalEye.h"

void Picture_format() ;
void Picture_createPattern() ;
void Picture_paintObject() ;



void Picture_paint( HDC );
static void paint() ;
static void paintCircle( HDC , int ) ;

bool isShow = false ;

static HWND hWnd ;


LRESULT CALLBACK ShowPanelProc( HWND _hWnd , UINT msg , WPARAM wp , LPARAM lp )
{
	switch( msg )
	{
	case WM_CREATE :
		hWnd = _hWnd ;
		Picture_format() ;
		Picture_createPattern() ;
		Picture_paintObject() ;
		isShow = true ;
		InvalidateRect( hWnd , NULL , false ) ;
		break ;

	case WM_PAINT :
		paint() ;
		break ;

	case WM_DESTROY :
		hWnd = NULL ;
		break ;
		
	default :
		return( DefWindowProc( _hWnd , msg , wp , lp ) ) ;
	}
    return 0L ;
}


void ShowPanel_show()
{
	isShow = true ;
	InvalidateRect( hWnd , NULL , false ) ;
}


static void paint()
{
	PAINTSTRUCT ps ;
	HDC hdc = BeginPaint( hWnd , &ps ) ;
	
	if( isShow )
	{
		Picture_paint( hdc ) ;SetWindowText(hWnd,"a");
		paintCircle( hdc , 3 ) ;
	}
	
	EndPaint( hWnd , &ps ) ;
}


HWND ShowPanel_create( HWND hMainFrame )
{
	HWND hWnd = CreateWindow( "SHOWPANEL" , NULL , 
			WS_CHILD ,
            0 , 0 , ( ( MAXX + X ) * PIX ) , ( ( MAXY + Y*0.5 ) * PIX ) , 
            hMainFrame , ( HMENU )ID_SHOWPANEL , hInst , NULL ) ;
    ShowWindow( hWnd , SW_SHOW ) ;
    UpdateWindow( hWnd ) ;
	
	return hWnd ;
}


static void paintCircle( HDC hdc , int _r )
{
	int r = _r * PIX ;
	int center = MAXX * PIX / 2 ;
	int y = ( MAXY + Y / 3 ) * PIX ;

	SelectObject( hdc , GetStockObject( BLACK_BRUSH ) ) ;
	
	Ellipse( hdc , center - X*PIX / 2 - r , y - r , center - X*PIX / 2 + r , y + r ) ;
	Ellipse( hdc , center + X*PIX / 2 - r , y - r , center + X*PIX / 2 + r , y + r ) ;
}