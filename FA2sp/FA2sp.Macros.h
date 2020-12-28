#pragma once

#define wstr(x) wstr_(x)
#define wstr_(x) L ## #x
#define str(x) str_(x)
#define str_(x) #x

#define PRODUCT_MAJOR 0
#define PRODUCT_MINOR 10
#define PRODUCT_REVISION 0
#define PRODUCT_STR "0.3"
#define DISPLAY_STR PRODUCT_STR

#define PRODUCT_NAME str(FA2sp)
#define APPLY_INFO str(Found Final Alert 2 version 1.02. Applying FA2sp - )__DATE__

#define MUTEX_HASH_VAL str(b8097bca8590a4f46c975ebb43503aab2243ce7f1c87f12f7984dbe1)
#define MUTEX_INIT_ERROR_MSG str(The program has already launched!)
#define MUTEX_INIT_ERROR_TIT str(FA2sp Init Checker)