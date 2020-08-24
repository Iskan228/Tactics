#ifndef _FUNCS_H
    #define _FUNCS_H 1

    #include <stdio.h>
    #include <stdlib.h>
    #include <stddef.h>
    #include <signal.h>
    #include <limits.h>
    #include <ctype.h>
    #include <string.h>

    #include "rands.h"

    #ifdef __STDC_VERSION__
        #define IS_C99 1
        #define IS_C89 1
        #define IS_C90 1
        #if __STDC_VERSION__ >= 201112L
            #define IS_C11 1
        #else
            #define IS_C11 0
        #endif /* __STDC_VERSION__ */
    #else
        #define IS_C99 0
        #define IS_C89 1
        #define IS_C90 0
        #define IS_C11 0
    #endif /* __STDC_VERSION__ */

    typedef unsigned int uint;
    typedef unsigned long int ulint;
    typedef unsigned short int usint;
    typedef unsigned char uchar;
    typedef signed long int lint;
    typedef signed char schar;
    typedef signed short int sint;
    #if IS_C99
        typedef unsigned long long int ullint;
        typedef signed long long int llint;
    #endif /* IS_C99 */

    #define IS_WINDOWS (defined(_MSC_VER) || defined(__WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINNT) || defined(__WINNT__) || defined(_WIN64))
    #define IS_LINUX (defined(__linux) || defined(linux) || defined(__gnu__linux__))
    #define IS_MACOS (defined(__APPLE__))
    #define IS_UNIX (IS_LINUX || IS_MACOS || defined(unix) || defined(__unix) || defined(__unix__))

    #ifdef __noreturn
        #undef __noreturn
    #endif /* __noreturn */

    #ifdef __GNUC__
        #if __GNUC__ >= 3
            #if !IS_C99
                #ifdef inline
                    #undef inline
                #endif /* inline */
                #define inline inline __attribute__((always_inline))
            #endif /* IS_C99 */
            #define __noinline __attribute__((noinline))
            #define __pure __attribute__((pure))
            #define __const __attribute__((const))
            #if !IS_C11
                #define __noreturn __attribute__((noreturn))
            #else
                #include <stdnoreturn.h>
                #define __noreturn noreturn
            #endif /* !IS_C11 */
            #define __malloc __attribute__((malloc))
            #define __must_check __attribute__((warn_unused_result))
            #define __deprecated __attribute__((deprecated))
            #define __used __attribute__((used))
            #define __unused __attribute__((unused))
            #define __packed __attribute__((packed))
            #define __align(x) __attribute__((aligned(x)))
            #define __align_max __attribute__((aligned))
            #ifdef likely
                #undef likely
            #endif /* likely */
            #define likely __builtin_expect(!!(x), 1)
            #ifdef unlikely
                #undef unlikely
            #endif /* unlikely */
            #define unlikely __builtin_expect(!!(x), 0)
        #else
            #if !IS_C99
                #ifdef inline
                    #undef inline
                #endif /* inline */
                #define inline
            #endif /* !IS_C99 */
            #define __noinline
            #define __pure
            #define __const
            #if IS_C11
                #include <stdnoreturn.h>
                #define __noreturn noreturn
            #else
                #define __noreturn
            #endif /* IS_C11 */
            #define __malloc
            #define __must_check
            #define __deprecated
            #define __used
            #define __unused
            #define __packed
            #define __align(x)
            #define __align_max
            #ifdef likely
                #undef likely
            #endif /* likely */
            #define likely(x) (x)
            #ifdef unlikely
                #undef unlikely
            #endif /* unlikely */
            #define unlikely(x) (x)
        #endif /* __GNUC__ */
    #else
        #if !IS_C99
            #ifdef inline
                #undef inline
            #endif /* inline */
            #define inline
        #endif /* !IS_C99 */
        #define __noinline
        #define __pure
        #define __const
        #if IS_C11
            #include <stdnoreturn.h>
            #define __noreturn noreturn
        #else
            #define __noreturn
        #endif /* IS_C11 */
        #define __malloc
        #define __must_check
        #define __deprecated
        #define __used
        #define __unused
        #define __packed
        #define __align(x)
        #define __align_max
        #ifdef likely
            #undef likely
        #endif /* likely */
        #define likely(x) (x)
        #ifdef unlikely
            #undef unlikely
        #endif /* unlikely */
        #define unlikely(x) (x)
    #endif /* __GNUC__ */

    #define tobool(x) (!!(x))
    /* прочитать у числа val бит под номером bit(0..7 для u8) */
    #define bitRead(val, bit) ((val) >> (bit) & 1UL)
    /* записать у числа val в бит под номером bit значение 1 */
    #define bitSet(val, bit) ((val) |= (1UL << (bit)))
    /* записать в бит под номером bit числа val значение 0 */
    #define bitClear(val, bit) ((val) &= ~(1UL << (bit)))
    /* ставит бит под номером bit в состояние bitval(0 или 1) в числе val */
    #define bitWrite(val, bit, bitval) (bitval ? bitSet(val, bit) : bitClear(val, bit))
    /* 2 ^ n, n > 0 */
    #define bit(n) (1UL << (n))
    /* n * (2 ^ y) */
    #define mul2n(n, y) ((n) << (y))
    /* n / (2 ^ y) */
    #define div2n(n, y) ((n) >> (y))
    /* разделить n на 2 */
    #define div2(n) ((n) >> 1)
    /* в верхний регистр */
    #define m2upper(c) ((c) & '_')
    /* ('a' & '_') => 'A'; ('A' & '_') => 'A' */
    /* в нижний регистр */
    #define m2lower(c) ((c) | ' ')
    /* ('a' | ' ') => 'a'; ('A' | ' ') => 'a' */
    /* верхний регистр в нижний, а нижний в верхний */
    #define ulswap(c) ((c) ^ ' ')
    /* ('a' ^ ' ') => 'A'; ('A' ^ ' ') => 'a' */
    /* позиция буквы в английском алфавите */
    #define posinA(c) ((c) & "\x1F")
    /* ('a' & "\x1F") => 1 */
    /* позиция заглавной буквы в английском алфавите */
    /* или #define posInA(c) ((c) ^ '@') */
    #define PosInA(c) ((c) & '?')
    /* ('C' & '?') => 3 */
    /* Позиция строчной буквы в английском алфавите */
    #define posIna(c) ((c) ^ '`')
    /* ('d' ^ '`') => 4 */

    __noreturn void my_exit_success(void)
    {
        #if IS_UNIX
            ti.c_lflag |= ICANON | ECHO;
            tcsetattr(0, TCSANOW, &ti);
        #endif /* IS_UNIX */
        #ifdef EXIT_SUCCESS
            exit(EXIT_SUCCESS);
        #else
            exit(0);
        #endif /* EXIT_SUCCESS */
    }

    __noreturn void my_exit_failure(void)
    {
        #if IS_UNIX
            ti.c_lflag |= ICANON | ECHO;
            tcsetattr(0, TCSANOW, &ti);
        #endif /* IS_UNIX */
        #ifdef EXIT_FAILURE
            exit(EXIT_FAILURE);
        #else
            exit(1);
        #endif /* EXIT_FAILURE */
    }

    __noreturn void my_exit_code(int code)
    {
        #if IS_UNIX
            ti.c_lflag |= ICANON | ECHO;
            tcsetattr(0, TCSANOW, &ti);
        #endif /* IS_UNIX */
        exit(code);
    }

    __noreturn void error(const char *msg)
    {
        fprintf(stderr, "%s: %s\n", msg, errno);
        my_exit_failure();
    }

    bool put2chars(int c, int c2)
    {
        if(putchar(c) == EOF)
            return false;
        return putchar(c2) != EOF;
    }

    bool fput2chars(FILE *f, int c, int c2)
    {
        if(fputc(c, f) == EOF)
            return false;
        return fputc(c2, f) != EOF;
    }

    bool put3chars(int c, int c2, int c3)
    {
        if(putchar(c) == EOF)
            return false;
        if(putchar(c2) == EOF)
            return false;
        return putchar(c3) != EOF;
    }

    bool fput3chars(FILE *f, int c, int c2, int c3)
    {
        if(fputc(c, f) == EOF)
            return false;
        if(fputc(c2, f) == EOF)
            return false;
        return fputc(c3, f) == EOF;
    }

    bool put2schars(const char *s)
    {
        if(putchar(s[0]) == EOF)
            return false;
        return putchar(s[1]) == EOF;
    }

    bool fput2schars(FILE *f, const char *s)
    {
        if(fputc(s[0], f) == EOF)
            return false;
        return fputc(s[1], f) == EOF;
    }

    bool put3schars(const char *s)
    {
        if(putchar(s[0]) == EOF)
            return false;
        if(putchar(s[1]) == EOF)
            return false;
        return putchar(s[2]) == EOF;
    }

    bool fput3schars(FILE *f, const char *s)
    {
        if(fputc(s[0], f) == EOF)
            return false;
        if(fputc(s[1], f) == EOF)
            return false;
        return fputc(s[2], f) == EOF;
    }

    void floaterror(int sig)
    {
        error("Float error");
    }

    void segverror(int sig)
    {
        error("Segmentation error");
    }

    void illerror(int sig)
    {
        error("ILL error");
    }

    void termerror(int sig)
    {
        my_exit_success();
    }

    /* copy from K&R */
    void reverse(char s[])
    {
        register size_t i, j;
        register char c;

        for(i = 0, j = strlen(s) - 1; i < j; i++, j--)
        {
            c = s[i];
            s[i] = s[j];
            s[j] = c;
        }
    }

    /* copy from K&R */
    void itoa(int n, char s[])
    {
        register size_t i;
        register int sign;

        i = 0;
        if((sign = n) < 0)
            n = -n;
        do {
            s[i++] = n % 10 + '0';
        } while((n /= 10) > 0);
        if(sign < 0)
            s[i++] = '-';
        s[i] = '\0';
        reverse(s);
    }

    void utoa(uint n, char s[])
    {
        register size_t i;

        i = 0;
        do {
            s[i++] = n % 10 + '0';
        } while((n /= 10) > 0);
        s[i] = '\0';
        reverse(s);
    }

    void u8toa(u8 n, char s[])
    {
        register size_t i;

        i = 0;
        do {
            s[i++] = n % 10 + '0';
        } while((n /= 10) > 0);
        s[i] = '\0';
        reverse(s);
    }

    void u16toa(u16 n, char s[])
    {
        register size_t i;

        i = 0;
        do {
            s[i++] = n % 10 + '0';
        } while((n /= 10) > 0);
        reverse(s);
    }

    void u32toa(u32 n, char s[])
    {
        register size_t i;

        i = 0;
        do {
            s[i++] = n % 10 + '0';
        } while((n /= 10) > 0);
        reverse(s);
    }

    void i8toa(i8 n, char s[])
    {
        register size_t i;
        register i8 sign;

        i = 0;
        if((sign = n) < 0)
            n = -n;
        do {
            s[i++] = n % 10 + '0';
        } while((n /= 10) > 0);
        if(sign < 0)
            s[i++] = '-';
        s[i] = '\0';
        reverse(s);
    }

    void i16toa(i16 n, char s[])
    {
        register size_t i;
        register i16 sign;

        i = 0;
        if((sign = n) < 0)
            n = -n;
        do {
            s[i++] = n % 10 + '0';
        } while((n /= 10) > 0);
        if(sign < 0)
            s[i++] = '-';
        s[i] = '\0';
        reverse(s);
    }

    void i32toa(i32 n, char s[])
    {
        register size_t i;
        register i32 sign;

        i = 0;
        if((sign = n) < 0)
            n = -n;
        do {
            s[i++] = n % 10 + '0';
        } while((n /= 10) > 0);
        if(sign < 0)
            s[i++] = '-';
        reverse(s);
    }

    bool print(const char *s)
    {
        size_t i;

        for(i = 0; s[i] != '\0'; i++)
        {
            if(putchar(s[i]) == EOF)
                return false;
        }
        return true;
    }

    #define MAX_LEN_OF_BOOL_AS_STR 6

    char* bool2str(bool val, char *str)
    {
        return val ? "true" : "false";
    }

    #define func1(t) \
        t sumOf##t(t *val, size_t len) \
        { \
            register size_t i;\
            register t sum;\
            for(i = sum = 0; i < len; i++) \
                sum += val[i];\
            return sum;\
        }

    func1(float);
    func1(double);
    func1(u8);
    func1(u16);
    func1(u32);
    func1(u64);
    func1(i8);
    func1(i16);
    func1(i32);
    func1(i64);

    #undef func1

    /* n MAX: 60 */
    u64 fact(u8 n)
    {
        register u64 res;
        res = 1;
        while(n)
            res *= (n--);
        return res;
    }

    /* n MAX: 60 */
    u64 factr(u8 n)
    {
        return n <= 1 ? 1 : factr(n) * n;
    }

    #define ESC 27
    #define ENTER 13

    #if IS_WINDOWS
        enum mcolors {mcBlack, mcBlue, mcGreen, mcCyan, mcRed, mcMagenta, mcBrown, mcLightGray, mcDarkGray, mcLightBlue, mcLightGreen, mcLightCyan, mcLightRed, mcLightMagenta, mcYellow, mcWhite};
        #define MAX_COUNT_COLORS 16

        static enum mcolors textColor = mcWhite;
        static enum mcolors bgColor = mcBlack;

        #ifndef _WINDOWS_H
            #include <windows.h>
        #endif /* _WINDOWS_H */
        #include <conio.h>
        #include <direct.h>
        #define cls() system("CLS")
        #define _mygetc() getch()

        void mySetColor(enum mcolors text, enum mcolors bg)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(bg << 4) | text);
            textColor = text;
            bgColor = bg;
        }

        void mySetBgColor(enum mcolors bg)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(bg << 4) | textColor);
            bgColor = bg;
        }

        void mySetTextColor(enum mcolors text)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(bgColor << 4) | text);
            textColor = text;
        }
        /* OK - 0, else - -1 */
        int _mychdir(const char *path)
        {
            return _chdir(path);
        }

        /* OK - 0, error - -1 */
        int _mymkdir(const char *path)
        {
            return _mkdir(path);
        }

        /* OK - 0, error - -1 */
        int _myrmdir(const char *path)
        {
            return _rmdir(path);
        }

        /* OK - not NULL, error - NULL */
        char* _mygetpwd(char *buf)
        {
            return _getcwd(buf, MAX_PATH);
        }
        /* example:
        #include <stdio.h>
        #include <stdlib.h>
        #include "funcs.h"

        int main(void)
        {
            char path[MAX_PATH];

            _mygetpwd(path);
            printf("Current directory: %s\n", path);
            return EXIT_SUCCESS;
        }
        */

        /* OK - 0, error - -1 */
        int _mychdrive(int drive)
        {
            return _chdrive(drive);
        }
        /* example:
        #include "funcs.h"
        #include <stdio.h>
        #include <stdlib.h>

        int main(void)
        {
            if(_mychdrive('C') == 0)
                printf("Changed to drive C:\n");
            else
                perror("ERROR changing to drive C:");
            return EXIT_SUCCESS;
        }
        */

        /* OK - 'A', 'B', ..., cannot be error */
        int _mygetdrive(void)
        {
            return _getdrive();
        }
        /* example:
        #include <stdio.h>
        #include <stdlib.h>
        #include "funcs.h"

        int main(void)
        {
            printf("The current drive is %c\n", _mygetdrive() + 'A' - 1);
            return EXIT_SUCCESS;
        }
        */
    #else
        #include <unistd.h>
        #include <termios.h>
        #include <sys/types.h>
        #include <sys/stat.h>
        #include <fcntl.h>

        struct termios ti;

        enum mcolors {mcBlack, mcYellow, mcCyan, mcRed, mcBlue, mcWhite, mcGreen, mcPurple};
        #define MAX_COUNT_COLORS 8

        static enum mcolors textColor = mcWhite;
        static enum mcolors bgColor = mcBlack;

        void mySetColor(enum mcolors text, enum mcolors bg)
        {
            print("\033[3")
            switch(text)
            {
            case mcBlack:
                putchar('0');
                break;
            case mcYellow:
                putchar('3');
                break;
            case mcCyan:
                putchar('6');
                break;
            case mcRed:
                putchar('1');
                break;
            case mcBlue:
                putchar('4');
                break;
            case mcWhite:
                putchar('7');
                break;
            case mcGreen:
                putchar('2');
                break;
            case mcPurple:
                putchar('5');
                break;
            default:
                error("Unknown color");
            }
            putchar('m');
            print("\033[4");
            switch(bg)
            {
            case mcBlack:
                putchar('0');
                break;
            case mcYellow:
                putchar('3');
                break;
            case mcCyan:
                putchar('6');
                break;
            case mcRed:
                putchar('1');
                break;
            case mcBlue:
                putchar('4');
                break;
            case mcWhite:
                putchar('7');
                break;
            case mcGreen:
                putchar('2');
                break;
            case mcPurple:
                putchar('5');
                break;
            default:
                error("Unknown color");
            }
            putchar('m');

            bgColor = bg;
            textColor = text;
        }

        void mySetBgColor(enum mcolors text)
        {
            print("\033[3");
            switch(text)
            {
            case mcBlack:
                putchar('0');
                break;
            case mcYellow:
                putchar('3');
                break;
            case mcCyan:
                putchar('6');
                break;
            case mcRed:
                putchar('1');
                break;
            case mcBlue:
                putchar('4');
                break;
            case mcWhite:
                putchar('7');
                break;
            case mcGreen:
                putchar('2');
                break;
            case mcPurple:
                putchar('5');
                break;
            default:
                error("Unknown color");
            }
            putchar('m');

            textColor = text;
        }

        void mySetBgColor(enum mcolors bg)
        {
            print("\033[4");
            switch(bg)
            {
            case mcBlack:
                putchar('0');
                break;
            case mcYellow:
                putchar('3');
                break;
            case mcCyan:
                putchar('6');
                break;
            case mcRed:
                putchar('1');
                break;
            case mcBlue:
                putchar('4');
                break;
            case mcWhite:
                putchar('7');
                break;
            case mcGreen:
                putchar('2');
                break;
            case mcPurple:
                putchar('5');
                break;
            default:
                error("Unknown color");
            }
            putchar('m');

            bgColor = bg;
        }

        #define resetColor() print("\033[0m")
        #define boldOn() print("\033[1m") /* жирный */
        #define boldOff() print("\033[22m") /* жирный */
        #define italicsOn() print("\033[3m") /* наклонный */
        #define italicsOff() print("\033[23m") /* наклонный */
        #define ulOn() print("\033[4m") /* с подчёркиванием */
        #define ulOff() print("\033[24m") /* с подчёркиванием */
        #define invOn() print("\033[7m") /* инвесное отображение */
        #define invOff() print("\033[27m")

        #define cls() system("clear")
        #define _mygetc() getchar()

        /* OK - 0, error - -1 */
        int _mychdir(const char *path)
        {
            return chdir(path);
        }

        /* OK - 0, error - -1 */
        int _mymkdir(const char *path)
        {
            /* я хз, как это работает */
            return mkdir(path, 0);
        }

        /* OK - 0, error - -1 */
        int _myrmdir(constc char *path)
        {
            return rmdir(path);
        }

        /* OK - not NULL, error - NULL */
        char* getcwd(char *buf)
        {
            return getcwd(buf, MAX_PATH);
        }

        /* OK - 0 */
        int _mychdrive(int drive)
        {
            return 0;
        }

        /* OK - 'A', 'B', ..., cannot be error */
        int _mygetdrive(void)
        {
            return 'C';
        }
    #endif /* IS_WINDOWS */

    void diediedie(int sig)
    {
        int c;
        cls();
        do {
            printf("Do you want to exit?(y/n): ");
            c = _mygetc();
        } while(c != 'Y' && c != 'y' && c != 'n' && c != 'N');
        if(c == 'y' || c == 'Y')
        {
            puts("Bye.");
            my_exit_success();
        }
    }

    void pause(void)
    {
        puts("Press any key on your keyboard to continue (not \"Power\" button!)...");
        _mygetc();
    }

    enum mcolors myGetBgColor(void)
    {
        return bgColor;
    };

    enum mcolors myGetTextColor(void)
    {
        return textColor;
    };
#endif /* _FUNCS_H */
