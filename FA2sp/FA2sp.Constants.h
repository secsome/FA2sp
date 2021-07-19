#pragma once

#define wstr(x) wstr_(x)
#define wstr_(x) L ## #x
#define str(x) str_(x)
#define str_(x) #x

constexpr int PRODUCT_MAJOR = 0;
constexpr int PRODUCT_MINOR = 10;
constexpr int PRODUCT_REVISION = 0;
constexpr char* PRODUCT_STR = "0.4";
constexpr char* DISPLAY_STR = PRODUCT_STR;

constexpr char* PRODUCT_NAME = "FA2sp";
constexpr char* APPLY_INFO = "Found Final Alert 2 version 1.02. Applying FA2sp - "  __DATE__ " - " __TIME__;

constexpr char* MUTEX_HASH_VAL = "b8097bca8590a4f46c975ebb43503aab2243ce7f1c87f12f7984dbe1";
constexpr char* MUTEX_INIT_ERROR_MSG = "The program has already launched!";
constexpr char* MUTEX_INIT_ERROR_TIT = "FA2sp Init Checker";

