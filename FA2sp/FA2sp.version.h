#pragma once

#define _MO // this is for mo now

#ifndef _DEBUG
#define IS_RELEASE_VER
#endif

#define VERSION_MAJOR 20
#define VERSION_MINOR 0
#define VERSION_REVISION 722

#define wstr(x) wstr_(x)
#define wstr_(x) L ## #x
#define str(x) str_(x)
#define str_(x) #x

#define VERSION_PREFIX "FinalAlert 2 1.01 - FA2sp version "
#define VERSION_STR str(VERSION_MAJOR) "." str(VERSION_MINOR) "." str(VERSION_REVISION)
#define VERSION_WSTR wstr(VERSION_MAJOR) L"." wstr(VERSION_MINOR) L"." wstr(VERSION_REVISION)

#ifdef IS_RELEASE_VER

#define PRODUCT_MAJOR 0
#define PRODUCT_MINOR 10
#define PRODUCT_REVISION 0
#define PRODUCT_STR "0.1"
#define DISPLAY_STR PRODUCT_STR

#else

#define PRODUCT_MAJOR VERSION_MAJOR
#define PRODUCT_MINOR VERSION_MINOR
#define PRODUCT_REVISION VERSION_REVISION
#define PRODUCT_STR VERSION_STR
#define DISPLAY_STR VERSION_STR

#endif

#ifdef _MO
#define FILE_SUFFIX str(MO)
#else
#define FILE_SUFFIX str(MD)
#endif