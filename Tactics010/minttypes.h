#ifndef _MINTTYPES_H
    #define _MINTTYPES_H 1
    #ifdef __STDC_VERSION__
        #include <stdint.h>
        #include <stdbool.h>

        typedef uint_least8_t u8;
        typedef uint_least16_t u16;
        typedef uint_least32_t u32;
        typedef uint_least64_t u64;
        typedef int_least8_t i8;
        typedef int_least16_t i16;
        typedef int_least32_t i32;
        typedef int_least64_t i64;
    #elif defined(__MINGW32__)
        #include <_mingw.h>
        typedef unsigned __int8 u8;
        typedef unsigned __int16 u16;
        typedef unsigned __int32 u32;
        typedef unsigned __int64 u64;
        typedef __int8 i8;
        typedef __int16 i16;
        typedef __int32 i32;
        typedef __int64 i64;
        typedef unsigned __int8 bool;
        #ifdef true
            #undef true
        #endif /* true */
        #define true 1
        #ifdef false
            #undef false
        #endif /* false */
        #define false 0
    #elif defined(_MSC_VER) || defined(__WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINNT) || defined(__WINNT__) || defined(_WIN64)
        #include <windows.h>
        typedef INT8 i8;
        typedef INT16 i16;
        typedef INT32 i32;
        typedef INT64 i64;
        typedef UINT8 u8;
        typedef UINT16 u16;
        typedef UINT32 u32;
        typedef UINT64 u64;
        typedef UINT8 bool;
        #ifdef true
            #undef true
        #endif /* true */
        #define true 1
        #ifdef false
            #undef false
        #endif /* false */
        #define false 0
    #else
        #if sizeof(char) >= 1
            typedef signed char i8;
            typedef unsigned char u8;
        #elif sizeof(short) >= 1
            typedef signed short int i8;
            typedef unsigned short int u8;
        #elif sizeof(int) >= 1
            typedef signed int i8;
            typedef unsigned int u8;
        #elif sizeof(long) >= 1
            typedef signed long int i8;
            typedef unsigned long int u8;
        #else
            #ifndef NO_INT_ERRS
                #error "No type for i8 and u8"
            #else
                #warning "No type for i8 and u8"
            #endif /* INT_ERRS */
        #endif /* sizeof */
        #if sizeof(char) >= 2
            typedef signed char i16;
            typedef unsigned char u16;
        #elif sizeof(short) >= 2
            typedef signed short int i16;
            typedef unsigned short int u16;
        #elif sizeof(int) >= 2
            typedef signed int i16;
            typedef unsigned int u16;
        #elif sizeof(long) >= 2
            typedef signed long int i16;
            typedef unsigned long int u16;
        #else
            #ifndef NO_INT_ERRS
                #error "No type for i16 and u16"
            #else
                #warning "No type for i16 and u16"
            #endif /* INT_ERRS */
        #endif /* sizeof */
        #if sizeof(char) >= 4
            typedef signed char i32;
            typedef unsigned char u32;
        #elif sizeof(short) >= 4
            typedef signed short int i32;
            typedef unsigned short int u32;
        #elif sizeof(int) >= 4
            typedef signed int i32;
            typedef unsigned int u32;
        #elif sizeof(long) >= 4
            typedef signed long int i32;
            typedef unsigned long int u32;
        #else
            #ifndef NO_INT_ERRS
                #error "No type for i32 and u32"
            #else
                #warning "No type for i32 and u32"
            #endif /* INT_ERRS */
        #endif /* sizeof */
        #if sizeof(char) >= 8
            typedef signed char i64;
            typedef unsigned char u64;
        #elif sizeof(short) >= 8
            typedef signed short int i64;
            typedef unsigned short int u64;
        #elif sizeof(int) >= 8
            typedef signed int i64;
            typedef unsigned int u64;
        #elif sizeof(long) >= 8
            typedef signed long int i64;
            typedef unsigned long int u64;
        #else
            #ifndef NO_INT_ERRS
                #error "No type for i64 and u64"
            #else
                #warning "No type for i64 and u64"
            #endif /* NO_INT_ERRS */
        #endif /* sizeof */
        #ifdef true
            #undef true
        #endif /* true */
        #define true 1
        #ifdef false
            #undef false
        #endif /* false */
        #define false 0
    #endif /* __STDC_VERSION__ */
#endif /* _MINTTYPES_H */
