#pragma once

#define _MO // this is for mo now


#define wstr(x) wstr_(x)
#define wstr_(x) L ## #x
#define str(x) str_(x)
#define str_(x) #x

#define PRODUCT_MAJOR 0
#define PRODUCT_MINOR 10
#define PRODUCT_REVISION 0
#define PRODUCT_STR "0.1"
#define DISPLAY_STR PRODUCT_STR

#define APPLY_INFO str(Found Final Alert 2 version 1.02. Applying FA2sp 2020-10-08.)

#ifdef _MO
#define FILE_SUFFIX str(MO)
#else
#define FILE_SUFFIX str(MD)
#endif