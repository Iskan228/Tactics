#ifndef _FUNCS_H
	#define _FUNCS_H 1

	#include <stdio.h>
	#include <stdlib.h>
	#include <stddef.h>
	#include <limits.h>
	#include <ctype.h>
	#include <string.h>
	#include <errno.h>

	#include "minttypes.h"

		#ifdef __STDC_VERSION__
		#define IS_C89 0
		#if __STDC_VERSION__ >= 20111L
			#define IS_C11 1
			#define IS_C99 0
		#else
			#define IS_C11 0
			#define IS_C99 1
		#endif
	#else
		#define IS_C99 0
		#define IS_C11 0
		#ifdef __STDC__
			#define IS_C89 1
		#else
			#define IS_C89 0
		#endif /* __STDC__ */
	#endif /* __STDC_VERSION__ */

	#if defined(_MSC_VER) || defined(__WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINNT) || defined(__WINNT__) || defined(_WIN64) || defined(__MINGW32__)
		#define IS_WINDOWS 1
		#define IS_LINUX 0
		#define IS_MACOS 0
		#define IS_FREEBSD 0
		#define IS_DRAGONFLY 0
		#define IS_OPENBSD 0
		#define IS_NETBSD 0
		#define IS_SUN 0
		#define IS_UNIX 0
	#elif defined(__linux__) || defined(linux) || defined(__gnu__linux)
		#define IS_WINDOWS 0
		#define IS_LINUX 1
		#define IS_MACOS 0
		#define IS_FREEBSD 0
		#define IS_DRAGONFLY 0
		#define IS_OPENBSD 0
		#define IS_NETBSD 0
		#define IS_SUN 0
		#define IS_UNIX 1
	#elif defined(__APPLE__)
		#define IS_WINDOWS 0
		#define IS_LINUX 0
		#define IS_MACOS 1
		#define IS_FREEBSD 0
		#define IS_DRAGONFLY 0
		#define IS_OPENBSD 0
		#define IS_NETBSD 0
		#define IS_SUN 0
		#define IS_UNIX 1
	#elif defined(__FreeBSD__)
		#define IS_WINDOWS 0
		#define IS_LINUX 0
		#define IS_MACOS 0
		#define IS_FREEBSD 1
		#define IS_DRAGONFLY 0
		#define IS_OPENBSD 0
		#define IS_NETBSD 0
		#define IS_SUN 0
		#define IS_UNIX 1
	#elif defined(__DragonFly__)
		#define IS_WINDOWS 0
		#define IS_LINUX 0
		#define IS_MACOS 0
		#define IS_FREEBSD 0
		#define IS_DRAGONFLY 1
		#define IS_OPENBSD 0
		#define IS_NETBSD 0
		#define IS_SUN 0
		#define IS_UNIX 1
	#elif defined(__OpenBSD__)
		#define IS_WINDOWS 0
		#define IS_LINUX 0
		#define IS_MACOS 0
		#define IS_FREEBSD 0
		#define IS_DRAGONFLY 0
		#define IS_OPENBSD 1
		#define IS_NETBSD 0
		#define IS_SUN 0
		#define IS_UNIX 1
	#elif defined(__NetBSD__)
		#define IS_WINDOWS 0
		#define IS_LINUX 0
		#define IS_MACOS 0
		#define IS_FREEBSD 0
		#define IS_DRAGONFLY 0
		#define IS_OPENBSD 0
		#define IS_NETBSD 1
		#define IS_SUN 0
		#define IS_UNIX 1
	#elif defined(__sun)
		#define IS_WINDOWS 0
		#define IS_LINUX 0
		#define IS_MACOS 0
		#define IS_FREEBSD 0
		#define IS_DRAGONFLY 0
		#define IS_OPENBSD 0
		#define IS_NETBSD 0
		#define IS_SUN 1
		#define IS_UNIX 1
	#elif defined(unix) || defined(__unix) || defined(__unix__)
		#define IS_WINDOWS 0
		#define IS_LINUX 0
		#define IS_MACOS 0
		#define IS_FREEBSD 0
		#define IS_DRAGONFLY 0
		#define IS_OPENBSD 0
		#define IS_NETBSD 0
		#define IS_SUN 0
		#define IS_UNIX 1
	#else
		#error "Unknown OS"
	#endif /* OS */

	#if defined(__MINGW32__)
		#define IS_MINGW 1
		#define IS_PCC 0
		#define IS_GCC 1
		#define IS_TCC 0
		#define IS_CLANG 0
	#elif defined(__PCC__)
		#define IS_MINGW 0
		#define IS_PCC 1
		#define IS_GCC 0
		#define IS_TCC 0
		#define IS_CLANG 0
	#elif defined(__GNUC__)
		#define IS_MINGW 0
		#define IS_PCC 0
		#define IS_GCC 1
		#define IS_TCC 0
		#define IS_CLANG 0
	#elif defined(__TINYC__)
		#define IS_MINGW 0
		#define IS_PCC 0
		#define IS_GCC 0
		#define IS_TCC 1
		#define IS_CLANG 0
	#elif defined(__clang__)
		#define IS_MINGW 0
		#define IS_PCC 0
		#define IS_GCC 0
		#define IS_TCC 0
		#define IS_CLANG 1
	#else
		#define IS_MINGW 0
		#define IS_PCC 0
		#define IS_GCC 0
		#define IS_TCC 0
		#define IS_CLANG 0
	#endif /* Compiler */

	#if IS_GCC
		#if __GNUC__ >= 3
			#define IS_GCC3 1
		#else
			#define IS_GCC3 0
		#endif
	#else
		#define IS_GCC3 0
	#endif /*IS_GCC */

	#ifdef __noreturn
		#undef __noreturn
	#endif /* __noreturn */

	#if IS_C11
		#include <stdnoreturn.h>

		#define __noreturn noreturn
	#elif IS_GCC3
		#define __noreturn __attribute__((noreturn))
	#elif defined(_MSC_VER)
		#define __noreturn __declspec(noreturn)
	#else
		#define __noreturn
	#endif

	#ifdef inline
		#undef inline
	#endif /* inline */

	#if IS_GCC
		#define inline inline __attribute__((always_inline))
	#elif IS_C99 || IS_C11

	#else
		#define inline
	#endif

	#if IS_GCC3
		#define __noinline __attribute__((noinline))
		#define __pure __attribute__((pure))
		#define __const __attribute__((const))
		#define __malloc __attribute__((malloc))
		#define __must_check __attribute__((warn_unused_result))
		#define __deprecated __attribute__((deprecated))
		#define __used __attribute__((used))
		#define __unused __attribute__((unused))
		#define __packed __attribute__((packed))
		#define __align(x) __attribute__((aigned(x)))
		#define __align_max __attribute__((aligned))
		#define likely(x) __builtin_expect(!!(x), 1)
		#define unlikely(x) __builtin_expect(!!(x), 0)
	#else
		#ifdef _MSC_VER
			#define __align(x) __declspec(align(x))
			#define __noinline __declspec(noinline)
		#else
			#define __align(x)
			#define __noinline
		#endif /* _MSC_VER */
		#define __pure
		#define __const
		#define __malloc
		#define __must_check
		#define __deprecated
		#define __used
		#define __unused
		#define __packed
		#define __align_max
		#define likely(x) (x)
		#define unlikely(x) (x)
	#endif /* IS_GCC3 */

	#define tobool(x) (!!(x))
	#define bitRead(v, b) ((v) >> (b) & 1UL)
	#define bitSet(v, b) ((v) |= (1UL << (b)))
	#define bitClear(v, b) ((v) &= ~(1UL << (b)))
	#define bitWrite(v, b, bv) (bv ? bitSet(v, b) : bitClear(v, b))
	#define bit(n) (1UL << (n))
	#define mul2n(n, y) ((n) << (y))
	#define div2n(n, y) ((n) >> (y))
	#define div2(n) ((n) >> 1UL)
	#define m2upper(c) ((c) & '_')
	#define m2lower(c) ((c) | ' ')
	#define ulswap(c) ((c) ^ ' ')
	#define posinA(c) ((c) & "\x1F")
	#define PosInA(c) ((c) & '?')
	#define posIna(c) ((c) ^ '`')

	#if IS_UNIX
		#include <unistd.h>
		#include <termios.h>
		#include <sys/types.h>
		#include <sys/stat.h>
		#include <fcntl.h>

		struct termios ti;
	#endif /* IS_UNIX */

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
		fprintf(stderr, "%s: %s\n", msg, strerror(errno));
		my_exit_failure();
	}

	void put2chars(int c, int c2)
	{
		putchar(c);
		putchar(c2);
	}

	void fput2chars(FILE *f, int c, int c2)
	{
		fputc(c, f);
		fputc(c2, f);
	}

	void put3chars(int c, int c2, int c3)
	{
		putchar(c);
		putchar(c2);
		putchar(c3);
	}

	void fput3chars(FILE *f, int c, int c2, int c3)
	{
		fputc(c, f);
		fputc(c2, f);
		fputc(c3, f);
	}

	void put2schars(const char *s)
	{
		putchar(s[0]);
		putchar(s[1]);
	}

	void fput2schars(FILE *f, const char *s)
	{
		fputc(s[0], f);
		fputc(s[1], f);
	}

	void put3schars(const char *s)
	{
		putchar(s[0]);
		putchar(s[1]);
		putchar(s[2]);
	}

	void fput3schars(FILE *f, const char *s)
	{
		fputc(s[0], f);
		fputc(s[1], f);
		fputc(s[2], f);
	}

	__noreturn void floaterror(int __unused sig)
	{
		error("Float error");
	}

	__noreturn void segverror(int __unused sig)
	{
		error("Segmentation error");
	}

	__noreturn void illerror(int __unused sig)
	{
		error("ILL error");
	}

	__noreturn void termerror(int __unused sig)
	{
		my_exit_success();
	}

	/* cope from K&R */
	void reverse(char *s)
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
	/* void itoa(int n, char s[])
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
	} */

	void utoa(uint n, char s[])
	{
		register size_t i;

		i = 0;
		do {
			s[i++] = n % 10 + '0';
		} while((n /= 10) > 0);
		reverse(s);
	}

	/* from Apple Open Source */
	size_t strlcpy(char *dst, const char *src, size_t maxlen)
	{
		const size_t srclen = strlen(src);
		if(srclen + 1 < maxlen)
			memcpy(dst, src, srclen + 1);
		else if(maxlen)
		{
			memcpy(dst, src, maxlen - 1);
			dst[maxlen - 1] = '\0';
		}
		return srclen;
	}

	/* from Apple Open Source */
	size_t strlcat(char *dst, const char *src, size_t len)
	{
		char *d = dst;
		const char *s = src;
		register size_t n = len;
		size_t dlen;

		while(n-- && *d != '\0')
			d++;
		dlen = d - dst;
		n = len - dlen;

		if(!n)
			return dlen + strlen(s);
		while(*s != '\0')
		{
			if(n != 1)
			{
				*d++ = *s;
				n--;
			}
			s++;
		}
		*d = '\0';
		return dlen + (s - src);
	}

	#define MAX_LEN_OF_BOOL_AS_STR 6
	char* bool2str(bool val, char *str, size_t len)
	{
		strlcpy(str, val ? "true" : "false", len);
		return str;
	}

	__const size_t fact(u8 n)
	{
		register size_t res;
		res = 1;
		while(n)
			res *= (n--);
		return res;
	}

	__const size_t factr(u8 n)
	{
		return n < 2 ? 1 : factr(n - 1) * n;
	}

	void print(const char *s)
	{
		size_t i;
		for(i = 0; s[i] != '\0'; i++)
			putchar(s[i]);
	}

	#define ESC 27
	#define ENTER 13

	#if IS_WINDOWS
		#include <windows.h>
		#include <conio.h>
		#include <direct.h>

		enum mcolors {mcBlack, mcBlue, mcGreen, mcCyan, mcRed, mcMagenta, mcBrown, mcLightGray, mcDarkGray, mcLightBlue, mcLightGreen, mcLightCyan, mcLightRed, mcLightMagenta, mcYellow, mcWhite, mcMax};
		enum mcolors bgColor;
		enum mcolors textColor;

		#define cls() system("CLS")
		#define _mygetc() getch()

		void mySetColor(enum mcolors text, enum mcolors bg)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(bg << 4) | text);
			textColor = text;
			bgColor = bg;
		}

		void mySetTextColor(enum mcolors text)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(bgColor << 4 | text));
			textColor = text;
		}

		void mySetBgColor(enum mcolors bg)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(bg << 4 | textColor));
			bgColor = bg;
		}

		/* 0 - OK, -1 - error */
		int _mychdir(const char *path)
		{
			return _chdir(path);
		}

		/* 0 - OK, -1 - error */
		int _mymkdir(const char *path)
		{
			return _mkdir(path);
		}

		/* 0 - OK, -1 - error */
		int _myrmdir(const char *path)
		{
			return _rmdir(path);
		}

		/* not NULL - OK, NULL - error */
		char* _mygetcwd(char *buf, size_t len)
		{
			return _getcwd(buf, len);
		}

		/*
		 * #include <stdio.h>
		 * #include "funcs.h"
		 *
		 * int main(void)
		 * {
		 * 	if(_mychdrive(3) == -1)
		 * 		puts("Error");
		 * 	else
		 * 		puts("Current drive is C:");
		 * 	return 0;
		 * }
		 * */
		/* 0 - OK, -1 - error */
		int _mychdrive(int drive)
		{
			return _chdrive(drive);
		}

		/* example:
		 * #include <stdio.h>
		 * #include "funcs.h"
		 *
		 * int main(void)
		 * {
		 * 	int drive;
		 * 	drive = _mygetdrive();
		 * 	if(drive == -1)
		 * 	{
		 *		puts("Error");
		 *		return 1;
		 * 	}
		 * 	printf("Current drive: %d\n", _mygetdrive() + 'A' - 1);
		 * 	return 0;
		 * }
		 * */
		/* 1, 2, 3, ... - OK, -1 - error */
		int _mygetdrive(void)
		{
			return _getdrive();
		}

		#define resetColor() setColor(mcWhite, mcBlack)
		#define boldOn()
		#define boldOff()
		#define italicsOn()
		#define italicsOff()
		#define ulOn()
		#define ulOff()
		#define invOn()
		#define invOff()
	#elif IS_UNIX
		enum mcolors {mcRed, mcBlue, mcWhite, mcGreen, mcYellow, mcCyan, mcPurple, mcBlack, mcMax};

		enum mcolors textColor;
		enum mcolors bgColor;
		int localDrive;

		void mySetColor(enum mcolors text, enum mcolors bg)
		{
			print("\033[3m");
			switch(text)
			{
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
			case mcBlack:
				putchar('0');
				break;
			case mcYellow:
				putchar('3');
				break;
			case mcCyan:
				putchar('6');
				break;
			case mcPurple:
				putchar('5');
				break;
			default:
				error("Unknown color");
			}
			print("m\033[4");
			switch(bg)
			{
			case mcBlack:
				putchar('0');
				break;
			case mcRed:
				putchar('1');
				break;
			case mcBlue:
				putchar('4');
				break;
			case mcGreen:
				putchar('2');
				break;
			case mcWhite:
				putchar('7');
				break;
			case mcYellow:
				putchar('3');
				break;
			case mcCyan:
				putchar('6');
				break;
			case mcPurple:
				putchar('5');
				break;
			default:
				error("Unknwon color");
			}
			putchar('m');
			textColor = text;
			bgColor = bg;
		}

		void mySetTextColor(enum mcolors text)
		{
			print("\033[3");
			switch(text)
			{
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
			case mcBlack:
				putchar('0');
				break;
			case mcYellow:
				putchar('3');
				break;
			case mcCyan:
				putchar('6');
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
			print("\033[4m");
			switch(bg)
			{
			case mcBlack:
				putchar('0');
				break;
			case mcRed:
				putchar('1');
				break;
			case mcBlue:
				putchar('4');
				break;
			case mcGreen:
				putchar('2');
				break;
			case mcWhite:
				putchar('7');
				break;
			case mcYellow:
				putchar('3');
				break;
			case mcCyan:
				putchar('6');
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
		#define boldOn() print("\033[1m") /* жирный текст */
		#define boldOff() print("\033[22m")
		#define italicsOn() print("\033[3m") /* курсивный текст */
		#define italicsOff() print("\033[23m")
		#define ulOn() print("\033[4m") /* текст с подчёркиванием */
		#define ulOff() print("\033[24m")
		#define invOn() print("\033[7m") /* инвесное изображение текста */
		#define invOff() print("\033[27m")

		#define cls() system("clear")
		#define _mygetc() getchar()

		/* 0 - OK, -1 - error */
		int _mychdir(const char *path)
		{
			return chdir(path);
		}

		/* 0 - OK, -1 - error */
		int _mymkdir(const char *path)
		{
			/* я не знаю как это работает */
			return mkdir(path, 0);
		}

		/* 0 - OK, -1 - error */
		int _myrmdir(const char *path)
		{
			return rmdir(path);
		}

		/* not NULL - OK, NULL - error */
		char* _mygetcwd(char *buf, size_t len)
		{
			return getcwd(buf, len);
		}

		/* 0 - OK */
		int _mychdrive(int drive)
		{
			localDrive = drive;
		}

		/* 1, 2, 3, ... - OK */
		int _mygetdrive(void)
		{
			return localDrive;
		}
	#endif


	void diediedie(int __unused sig)
	{
		register int c;

		cls();
		do {
			print("Do you want to exit (y/n)? ");
			c = tolower(_mygetc());
			if(c == EOF || c == '\0')
				my_exit_failure();
			if(c == ESC)
				my_exit_success();
		} while(c != 'y' && c != 'n');
		if(c == 'y')
		{
			puts("Bye.");
			my_exit_success();
		}
	}

	void mpause(void)
	{
		register int c;
		puts("Press any key on your keyboard to continue (not \"Power\" button!)...");
		c = _mygetc();
		if(c == EOF)
			my_exit_failure();
		if(c == '\0' || c == ESC)
			diediedie(0);
	}

	inline enum mcolors myGetBgColor(void)
	{
		return bgColor;
	}

	inline enum mcolors myGetTextColor(void)
	{
		return textColor;
	}
#endif /* _FUNCS_H */
