#include "MagicalEye.h"

void Picture_setObject( int , int , int , bool ) ;
void Picture_createPattern() ;
void Picture_paintObject() ;
void ShowPanel_show() ;


static void paint() ;
static void draw( int , int ) ;


static HWND hWnd ;
static int pen = 0 ;  //0:下　1:上
static int boldness = 1 ; //1,3,5
static bool script[2][MAXX-PITCH][MAXY] ;
static int mouse = 0 ;  //0:なし　1:左ボタンが押されてる　2:右ボタンが押されてる


LRESULT CALLBACK DrawPanelProc( HWND _hWnd , UINT msg , WPARAM wp , LPARAM lp )
{
	switch( msg )
	{
	case WM_CREATE :
		memset( &script , 0 , sizeof( script ) ) ;
		hWnd = _hWnd ;
		break ;
		
	case WM_LBUTTONDOWN :
		mouse = 1 ;
		draw( LOWORD( lp ) , HIWORD( lp ) ) ;
		break ;
		
	case WM_RBUTTONDOWN :
		mouse = 2 ;
		draw( LOWORD( lp ) , HIWORD( lp ) ) ;
		break ;	
	
	case WM_LBUTTONUP :
	case WM_RBUTTONUP :
		mouse = 0 ;
		break ;

	case WM_MOUSEMOVE :
		draw( LOWORD( lp ) , HIWORD( lp ) ) ;
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


void DrawPanel_sendScript()
{
	int cou , x , y ;
	for( cou = 0 ; cou <= 1 ; cou ++ )
	{
		for( x = 0 ; x <= MAXX - PITCH - 1 ; x ++ )
		{
			for( y = 0 ; y <= MAXY - 1 ; y ++ )
			{
				Picture_setObject( cou , x , y , script[cou][x][y] ) ;
			}
		}
	}

	Picture_createPattern() ;
	Picture_paintObject() ;
	ShowPanel_show() ;
}


static void draw( int x , int y )
{
	HDC hdc = GetDC( hWnd ) ;
	
	int color ;
	if( mouse == 2 )
	{
		color = RGB( 255 , 255 , 255 ) ;
	}
	else if( pen == 0 )
	{
		color = RGB( 0 , 0 , 255 ) ;
	}
	else if( pen == 1 )
	{
		color = RGB( 255 , 0 , 0 ) ;
	}


	int cou , coux , couy ;
	
	if( mouse == 1 )
	{
		for( coux = -boldness ; coux <= boldness ; coux ++ )
		{
			for( couy = -boldness ; couy <= boldness ; couy ++ )
			{
				if( coux >= 0 && coux <= MAXX-PITCH-1 && couy >= 0 && couy <= MAXY-1 )
				{
					script[pen][x+coux][y+couy] = true ;
					if( !( script[1][x+coux][y+couy] && pen == 0 ) )
					{
						SetPixel( hdc , x+coux , y+couy , color ) ;
					}
				}
			}
		}
	}
	else if( mouse == 2 )
	{
		for( cou = 0 ; cou <= 1 ; cou ++ )
		{
			for( coux = -boldness ; coux <= boldness ; coux ++ )
			{
				for( couy = -boldness ; couy <= boldness ; couy ++ )
				{
					if( coux >= 0 && coux <= MAXX-PITCH-1 && couy >= 0 && couy <= MAXY-1 )
					{
						script[cou][x+coux][y+couy] = false ;
						SetPixel( hdc , x+coux , y+couy , color ) ;
					}
				}
			}
		}
	}
	
	ReleaseDC( hWnd , hdc ) ;
}


static void paint()
{
	PAINTSTRUCT ps ;
	HDC hdc = BeginPaint( hWnd , &ps ) ;
	
	
	int x , y ;
	for( x = 0 ; x <= MAXX - PITCH - 1 ; x ++ )
	{
		for( y = 0 ; y <= MAXY ; y ++ )
		{
			if( script[1][x][y] )
			{
				SetPixel( hdc , x , y , RGB( 255 , 0 , 0 ) ) ;
			}
			else if( script[0][x][y] )
			{
				SetPixel( hdc , x , y , RGB( 0 , 0 , 255 ) ) ;
			}
		}
	}

	EndPaint( hWnd , &ps ) ;
}


void DrawPanel_changePen( int _pen )
{
	pen = _pen ;
}


void DrawPanel_setBoldness( int _boldness )
{
	boldness = _boldness ;
}


void DrawPanel_clearScript()
{
	memset( &script , 0 , sizeof( script ) ) ;
	InvalidateRect( hWnd , NULL , true ) ;
}


HWND DrawPanel_create( HWND hMainFrame )
{
	HWND hWnd = CreateWindow( "DRAWPANEL" , NULL , 
			WS_CHILD | WS_BORDER ,
            PITCH , ( ( MAXY + Y*0.5 ) * PIX ) , ( ( MAXX - PITCH * 2 ) * PIX ) , ( MAXY * PIX ) , 
            hMainFrame , ( HMENU )ID_DRAWPANEL , hInst , NULL ) ;
    ShowWindow( hWnd , SW_SHOW ) ;
    UpdateWindow( hWnd ) ;
	
	return hWnd ;
}