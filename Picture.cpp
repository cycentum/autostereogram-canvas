#include "MagicalEye.h"


void Picture_paintObject() ;
void ShowPanel_show() ;


bool Object_getRange1( int , int ) ;
bool Object_getRange2( int , int ) ;


int pattern[MAXX][MAXY] ;
bool object[2][MAXX-PITCH][MAXY] ;
int minX , maxX ;
int backgroundID = 1 ;
bool overUnder = true ; //true:overover  false:overunder


void Picture_format()
{
	memset( &object , 0 , sizeof( object ) ) ;
	minX = maxX = 0 ;
}


void Picture_createPattern()
{
	int x , y ;
	for( x = 0 ; x <= MAXX - 1 ; x ++ )
	{
		for( y = 0 ; y <= MAXY - 1 ; y ++ )
		{
			pattern[x][y] = x % X ;			
		}
	}
}


void Picture_setObject( int cou , int x , int y , bool value )
{
	object[cou][x][y] = value ;
}


void Picture_drawObject()
{
	int x , y ;
	for( x = 0 ; x <= MAXX-PITCH-1 ; x ++ )
	{
		for( y = 0 ; y <= MAXY-1 ; y ++ )
		{
			if( Object_getRange1( x , y ) )
			{
				object[0][x][y] = true ;
			}
			
			if( Object_getRange2( x , y ) )
			{
				object[1][x][y] = true ;
			}
		}
	}
}


void Picture_overUnder( bool _overUnder )
{
	overUnder = _overUnder ;
}


void Picture_paintObject()
{
	int x , y ;
	int over , under ;
	if( overUnder )
	{
		over = PITCH ;
		under = PITCH ;
	}
	else
	{
		over = PITCH ;
		under = PITCH + 20 ;
	}
	
	for( x = 0 ; x <= MAXX - X  ; x ++ )
	{
		for( y = 0 ; y <= MAXY ; y ++ )
		{
			if( object[1][x][y] )
			{
				pattern[x + over][y] = pattern[x][y] ;
			}
			else if( object[0][x][y] )
			{
				pattern[x + under][y] = pattern[x][y] ;
			}
			else
			{
				pattern[x + X][y] = pattern[x][y] ;
			}
		}
	}
}


void Picture_changeBackground( int id )
{
	backgroundID = id ;
	Picture_paintObject() ;
	ShowPanel_show() ;
}


void Picture_paint( HDC hdc )
{
	HDC hmdc ;
	HBITMAP hBitmap ;
	BITMAP bmp ;
	int BMP_W, BMP_H;
	char name[20] ;
	
	wsprintf( name , "%s%d\0" , "BACKGROUND" , backgroundID ) ;
	hBitmap = LoadBitmap( hInst , name ) ;
	GetObject( hBitmap , sizeof( BITMAP ) , &bmp ) ;
	hmdc = CreateCompatibleDC( hdc ) ;
	SelectObject( hmdc , hBitmap) ;

	int x , y ;
	for( x = 0 ; x <= MAXX ; x ++ )
	{
		for( y = 0 ; y <= MAXY ; y ++ )
		{
			BitBlt( hdc , x , y , 1 , 1 , hmdc , pattern[x][y] , y%Y , SRCCOPY) ;
		}
	}

	DeleteDC( hmdc ) ;
	DeleteObject( hBitmap ) ;
	
/*	int x , y ;	
	for( x = 0 ; x <= MAXX ; x ++ )
	{
		for( y = 0 ; y <= MAXY ; y ++ )
		{
			if( object[x][y] )
			{
				SetPixel( hdc , x*PIX , y*PIX , RGB( 255 , 0 , 0 ) ) ;
			}
		}
	}
*/
}
