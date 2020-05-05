#include <windows.h>
#include <math.h>
#include "define.h"

#define PITCH 50
#define X 60
#define Y 60
#define NUMX 8
#define NUMY 5
#define MAXX (X*NUMX)
#define MAXY (Y*NUMY)
#define PIX 1


#define ID_SHOWPANEL 100
#define ID_DRAWPANEL 101


//MagicalEye
extern HINSTANCE hInst ;
void alert() ;
void alert( const char* ) ;
void alert( int ) ;
void alert( char* , int ) ;
extern HINSTANCE hInst ;