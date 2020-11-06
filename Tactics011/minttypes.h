#ifndef _MINTTYPES_H
    #define _MINTTYPES_H 1

    #if defined(__STDC_VERSION__)
        #include <stdint.h>
        #include <stdbool.h>

        typedef uint_least8_t u8;
        typedef uint_least16_t u16;
        typedef uint_least32_t u32;
        typedef uint_least64_t u64;

        typedef signed long long int llint;
        typedef unsigned long long int ullint;
    #else
        #if defined(__MINGW32__)
            #include <_mingw.h>

            typedef unsigned __int8 u8, uint8_t, uint_least8_t, uint_fast8_t;
            typedef unsigned __int16 u16, uint16_t, uint_least16_t, uint_fast16_t;
            typedef unsigned __int32 u32, uint32_t, uint_least32_t, uint_fast32_t;
            typedef unsigned __int64 u64, uint64_t, uint_least64_t, uint_fast64_t;
            typedef __int8 i8, int8_t, int_least8_t, int_fast8_t;
            typedef __int16 i16, int16_t, int_least16_t, int_fast16_t;
            typedef __int32 i32, int32_t, int_least32_t, int_fast32_t;
            typedef __int64 i64, int64_t, int_least64_t, int_fast64_t;
        #elif defined(_MSC_VER) || defined(__WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINNT) || defined(__WINNT__) || defined(_WIN64)
            #include <windows.h>

            typedef UINT8 u8, uint8_t, uint_least8_t, uint_fast8_t;
            typedef UINT16 u16, uint16_t, uint_least16_t, uint_fast16_t;
            typedef UINT32 u32, uint32_t, uint_least32_t, uint_fast32_t;
            typedef UINT64 u64, uint64_t, uint_least64_t, uint_fast64_t;
            typedef INT8 i8, int8_t, int_least8_t, int_fast8_t;
            typedef INT16 i16, int16_t, int_least16_t, int_fast16_t;
            typedef INT32 i32, int32_t, int_least32_t, int_fast32_t;
            typedef INT64 i64, int64_t, int_least64_t, int_fast64_t;
        #else
            #if sizeof(char) >= 1
                typedef signed char i8, int8_t, int_least8_t, int_fast8_t;
                typedef unsigned char u8, uint8_t, uint_least8_t, uint_fast8_t;
            #elif sizeof(short) >= 1
                typedef signed short int i8, int8_t, int_least8_t, int_fast8_t;
                typedef unsigned short int u8, uint8_t, uint_least8_t, uint_fast8_t;
            #elif sizeof(int) >= 1
                typedef signed int i8, int8_t, int_least8_t, int_fast8_t;
                typedef unsigned int u8, uint8_t, uint_least8_t, uint_fast8_t;
            #elif sizeof(long) >= 1
                typedef signed long int i8, int8_t, int_least8_t, int_fast8_t;
                typedef unsigned long int u8, uint8_t, uint_least8_t, uint_fast8_t;
            #else
                #ifndef NO_INT_ERRS
                    #error "No types for i8 and u8"
                #else
                    #warning "No types for i8 and u8"
                #endif /* !NO_INT_ERRS */
            #endif /* i8 and u8 */

            #if sizeof(char) >= 2
                typedef signed char i16, int16_t, int_least16_t, int_fast16_t;
                typedef unsigned char u16, uint16_t, uint_least16_t, uint_fast16_t;
            #elif sizeof(short) >= 2
                typedef signed short int i16, int16_t, int_least16_t, int_fast16_t;
                typedef unsigned short int u16, uint16_t, uint_least16_t, uint_fast16_t;
            #elif sizeof(int) >= 2
                typedef signed int i16, int16_t, int_least16_t, int_fast16_t;
                typedef unsigned int u16, uint16_t, uint_least16_t, uint_fast16_t;
            #elif sizeof(long) >= 2
                typedef signed long int i16, int16_t, int_least16_t, int_fast16_t;
                typedef unsigned long int u16, uint16_t, uint_least16_t, uint_fast16_t;
            #else
                #ifndef NO_INT_ERRS
                    #error "No types for i16 and u16"
                #else
                    #warning "No types for i16 and u16"
                #endif /* !NO_INT_ERRS */
            #endif /* i16 and u16 */

            #if sizeof(char) >= 4
                typedef signed char i32, int32_t, int_least32_t, int_fast32_t;
                typedef unsigned char u32, int32_t, uint_least32_t, uint_fast32_t;
            #elif sizeof(short) >= 4
                typedef signed short int i32, int32_t, int_least32_t, int_fast32_t;
                typedef unsigned short int u32, uint32_t, uint_least32_t, uint_fast32_t;
            #elif sizeof(int) >= 4
                typedef signed int i32, int32_t, int_least32_t, int_fast32_t;
                typedef unsigned int u32, uint32_t, uint_least32_t, uint_fast32_t;
            #elif sizeof(long) >= 4
                typedef signed long int i32, int32_t, int_least32_t, int_fast32_t;
                typedef unsigned long int u32, uint32_t, uint_least32_t, uint_fast32_t;
            #else
                #ifndef NO_INT_ERRS
                    #error "No types for i32 and u32"
                #else
                    #warning "No types for i32 and u32"
                #endif /* !NO_INT_ERRS */
            #endif /* i32 and u32 */

            #if sizeof(char) >= 8
                typedef signed char i64, int64_t, int_least64_t, int_fast64_t;
                typedef unsigned char u64, uint64_t, uint_least64_t, uint_fast64_t;
            #elif sizeof(short) >= 8
                typedef signed short int i64, int64_t, int_least64_t, int_fast64_t;
                typedef unsigned short int u64, uint64_t, uint_least64_t, uint_fast64_t;
            #elif sizeof(int) >= 8
                typedef signed int i64, int64_t, int_least64_t, int_fast64_t;
                typedef unsigned int u64, uint64_t, uint_least64_t, uint_fast64_t;
            #elif sizeof(long) >= 8
                typedef signed long int i64, int64_t, int_least64_t, int_fast64_t;
                typedef unsigned long int u64, uint64_t, uint_least64_t, uint_fast64_t;
            #else
                #ifndef NO_INT_ERRS
                    #error "No types for i64 and u64"
                #else
                    #warning "No types for i64 and u64"
                #endif /* !NO_INT_ERRS */
            #endif /* i64 and u64 */
        #endif

        #define INT8_MIN (-128L)
        #define INT8_MAX 127L
        #define INT16_MIN (-32768L)
        #define INT16_MAX 32767L
        #define INT32_MIN (-2147482646L)
        #define INT32_MAX 2147483647L
        #define INT64_MIN (-9223372036854775806L)
        #define INT64_MAX 9223372036854775807L

        #define UINT8_MAX 0xFFL
        #define UINT16_MAX 0xFFFFL
        #define UINT32_MAX 0xFFFFFFFFL
        #define UINT64_MAX 0xFFFFFFFFFFFFFFFFL

        #define INT_LEAST8_MIN INT8_MIN
        #define INT_LEAST8_MAX INT8_MAX
        #define INT_LEAST16_MIN INT16_MIN
        #define INT_LEAST16_MAX INT16_MAX
        #define INT_LEAST32_MIN INT32_MIN
        #define INT_LEAST32_MAX INT32_MAX
        #define INT_LEAST64_MIN INT64_MIN
        #define INT_LEAST64_MAX INT64_MAX

        #define UINT_LEAST8_MAX UINT8_MAX
        #define UINT_LEAST16_MAX UINT16_MAX
        #define UINT_LEAST32_MAX UINT32_MAX
        #define UINT_LEAST64_MAX UINT64_MAX

        #define INT_FAST8_MIN INT8_MIN
        #define INT_FAST8_MAX INT8_MAX
        #define INT_FAST16_MIN INT16_MIN
        #define INT_FAST16_MAX INT16_MAX
        #define INT_FAST32_MIN INT32_MIN
        #define INT_FAST32_MAX INT32_MAX
        #define INT_FAST64_MIN INT64_MIN
        #define INT_FAST64_MAX INT64_MAX

        #define UINT_FAST8_MAX UINT8_MAX
        #define UINT_FAST16_MAX UINT16_MAX
        #define UINT_FAST32_MAX UINT32_MAX
        #define UINT_FAST64_MAX UINT64_MAX

        #ifdef _WIN64
            #define INTPTR_MIN INT64_MIN
            #define INTPTR_MAX INT64_MAX
            #define UINTPTR_MAX UINT64_MAX
        #else
            #define INTPTR_MIN INT32_MIN
            #define INTPTR_MAX INT32_MAX
            #define UINTPTR_MAX UINT32_MAX
        #endif /* _WIN64 */

        #define PTRDIFF_MIN INTPTR_MIN
        #define PTRDIFF_MAX INTPTR_MAX

        #define SIG_ATOMIC_MIN INTPTR_MIN
        #define SIG_ATOMIC_MAX INTPTR_MAX

        #ifndef WCHAR_MIN
            #define WCHAR_MIN 0
            #define WHAR_MAX 0xFFFFL /* UINT16_MAX */
        #endif /* !WCHAR_MIN */

        #define WINT_MIN 0
        #define WINT_MAX 0xFFFFL /* UINT16_MAX */

        #if !(defined(INTMAX_MIN) || defined(INTMAX_MAX))
            typedef i64 intmax_t;
            #define INTMAX_MIN INT64_MIN
            #define INTMAX_MAX INT64_MAX
        #endif

        #ifndef SIZE_MAX
            typedef u64 size_t;
            #define SIZE_MAX UINT64_MAX
        #endif /* !SIZE_MAX */

        #ifndef UINTMAX_MAX
            typedef u64 uintmax_t;
            #define UINTMAX_MAX UINT64_MAX
        #endif /* !UINTMAX_MAX */

        #define INT8_C(val) (val##L)
        #define UINT8_C(val) (val##UL)
        #define INT16_C(val) (val##L)
        #define UINT16_C(val) (val##UL)

        #define INT32_C(val) (val##L)
        #define UINT32_C(val) (val##UL)
        #define INT64_C(val) (val##L)
        #define UINT64_C(val) (val##UL)

        #ifdef true
            #undef true
        #endif /* true */

        #ifdef false
            #undef false
        #endif /* false */

        #ifdef bool
            #undef bool
        #endif /* bool */

        typedef enum {false, true} bool;
    #endif /* __STDC_VERSION__ */

    typedef signed char schar;
    typedef unsigned char uchar;
    typedef signed short int sint;
    typedef unsigned short int usint;
    typedef unsigned int uint;
    typedef signed long int lint;
    typedef unsigned long int ulint;
#endif /* _MINTTYPES_H */
