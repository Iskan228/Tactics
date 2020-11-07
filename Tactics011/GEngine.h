#ifndef _GENGINE_H
	#define _GENGINE_H 1

	#include "funcs.h"
	#include "minttypes.h"

	#define MAP_WIDTH 22
	#define MAP_HEIGHT 5
	#define MAX_COUNT_MONEY 63
	#define MAX_ARMY_XP 3
	#define NEED_MONEY_TO_BUILD_CITY 5
	#define NEED_MONEY_TO_BUY_ARMY 2
	#define MONEY_PER_CITY 1
	#define ATTACK_ARMY_ATTACK 2
	#define ATTACK_ARMY_DEFENCE 1

	enum commands {c_red, c_blue, c_max};
	enum types_lands {tl_land, tl_army, tl_city, tl_armyandcity, tl_max};

	#if MAP_WIDTH < 256
		typedef u8 map_width_t;
	#else
		typedef u16 map_width_t;
	#endif

	#if MAP_HEIGHT < 256
		typedef u8 map_height_t;
	#else
		typedef u16 map_height_t;
	#endif

	#if MAX_COUNT_MONEY < 256
		typedef u8 count_money_t;
	#else
		typedef u16 count_money_t;
	#endif

	#if MAX_ARMY_XP < 256
		typedef u8 army_xp_t;
	#else
		typedef u16 army_xp_t;
	#endif

	struct army
	{
		#if MAX_ARMY_XP < 2
			uint xp: 1;
		#elif MAX_ARMY_XP < 4
			uint xp: 2;
		#elif MAX_ARMY_XP < 8
			uint xp: 3;
		#elif MAX_ARMY_XP < 16
			uint xp: 4;
		#elif MAX_ARMY_XP < 32
			uint xp: 5;
		#elif MAX_ARMY_XP < 64
			uint xp: 6;
		#elif MAX_ARMY_XP < 128
			uint xp: 7;
		#else
			uint xp;
		#endif
		uint active: 1;
	};

	struct coord
	{
		map_width_t posx;
		map_height_t posy;
	};

	#ifdef c
		#undef c
	#endif /* c */
	struct vals
	{
		enum commands nowIs;
		#if MAX_COUNT_MONEY < 2
			#define c : 1
		#elif MAX_COUNT_MONEY < 4
			#define c : 2
		#elif MAX_COUNT_MONEY < 8
			#define c : 3
		#elif MAX_COUNT_MONEY < 16
			#define c : 4
		#elif MAX_COUNT_MONEY < 32
			#define c : 5
		#elif MAX_COUNT_MONEY < 64
			#define c : 6
		#elif MAX_COUNT_MONEY < 128
			#define c : 7
		#else
			#define c
		#endif
		uint redMoney c;
		uint blueMoney c;
		#undef c
	};

	struct type_land
	{
		enum types_lands tl;
		enum commands c;
		struct army l;
	};

	struct vals strvals;
	struct type_land map[MAP_WIDTH][MAP_HEIGHT];

	char land2char(enum types_lands tl)
	{
		switch(tl)
		{
		case tl_army:
			return 'A';
		case tl_city:
			return 'C';
		case tl_armyandcity:
			return 'O';
		case tl_land:
			return '=';
		default:
			error("Unknown type of land");
		}
	}

	#define MAX_LEN_OF_COMMAND_AS_STR 5
	char* command2str(enum commands c, char *str, size_t len)
	{
		switch(c)
		{
		case c_red:
			strlcpy(str, "Red", len);
			break;
		case c_blue:
			strlcpy(str, "Blue", len);
			break;
		default:
			error("Unknown command");
		}
		return str;
	}

	enum commands nextCommand(enum commands c)
	{
		switch(c)
		{
		case c_red:
			return c_blue;
		case c_blue:
			return c_red;
		default:
			error("Unknwon command");
		}
	}

	#define MAX_LEN_OF_TYPE_LAND_AS_STR 14

	char* types_lands2str(enum types_lands tl, char *str, size_t len)
	{
		switch(tl)
		{
		case tl_army:
			strlcpy(str, "Army", len);
			break;
		case tl_armyandcity:
			strlcpy(str, "Army and city", len);
			break;
		case tl_city:
			strlcpy(str, "City", len);
			break;
		case tl_land:
			strlcpy(str, "Land", len);
			break;
		default:
			error("Unknwon type of land");
		}
		return str;
	}

	bool readYesNo(const char *question)
	{
		register int c;

		do {
			printf("\n%s? (y): ", question);
			c = tolower(_mygetc());
			if(c == EOF || c == '\0')
				my_exit_failure();
			if(c == ESC)
				diediedie(0);
		} while(c != 'y' && c != 'n');
		return c == 'y';
	}

	inline enum commands getCurrentCommand(void)
	{
		return strvals.nowIs;
	}

	inline bool isCurrentCommand(enum commands c)
	{
		return c == strvals.nowIs;
	}

	count_money_t getCurrentMoney(void)
	{
		switch(strvals.nowIs)
		{
		case c_red:
			return strvals.redMoney;
		case c_blue:
			return strvals.blueMoney;
		default:
			error("Unknown command");
		}
	}

	bool subCurrentMoney(count_money_t c)
	{
		if(getCurrentMoney() < c)
			return false;
		switch(strvals.nowIs)
		{
		case c_red:
			strvals.redMoney -= c;
			break;
		case c_blue:
			strvals.blueMoney -= c;
			break;
		default:
			error("Unknwon command");
		}
		return true;
	}

	#define noteq2chars(c1, c2) printf("%c/%c: ", (c1), (c2));\
		c = toupper(_mygetc());\
		if(c == EOF)\
			my_exit_failure();\
		if(c == ESC || c == '\0')\
			diediedie(0);\
		else if(c == 'E')\
			goto end;\
		else if(c != (c1) && c != (c2))\
			goto start

	#define noteq3chars(c1, c2, c3) printf("%c/%c/%c: ", (c1), (c2), (c3));\
		c = toupper(_mygetc());\
		if(c == EOF)\
			my_exit_failure();\
		if(c == ESC || c == '\0')\
			diediedie(0);\
		else if(c == 'E')\
			goto end;\
		else if(c != (c1) && c != (c2) && c != (c3))\
			goto start

	#define noteq4chars(c1, c2, c3, c4) printf("%c/%c/%c/%c", (c1), (c2), (c3), (c4));\
		c = toupper(_mygetc());\
		if(c == EOF)\
			my_exit_failure();\
		if(c == ESC || c == '\0')\
			diediedie(0);\
		else if(c == 'E')\
			goto end;\
		else if(c != (c1) && c != (c2) && c != (c3) && c != (c4))\
			goto start

	char putWASD(map_width_t x, map_height_t y)
	{
		register int c;

		puts("Enter \'E\' for exit");
		start:
		switch(y)
		{
		case 0:
			switch(x)
			{
			case 0:
				noteq2chars('S', 'D');
				break;
			case MAP_WIDTH - 1:
				noteq2chars('A', 'S');
				break;
			default:
				noteq3chars('A', 'S', 'D');
			}
			break;
		case MAP_HEIGHT - 1:
			switch(x)
			{
			case 0:
				noteq2chars('W', 'D');
				break;
			case MAP_WIDTH - 1:
				noteq2chars('W', 'A');
				break;
			default:
				noteq3chars('W', 'A', 'D');
			}
			break;
		default:
			switch(x)
			{
			case 0:
				noteq3chars('W', 'S', 'D');
				break;
			case MAP_WIDTH - 1:
				noteq3chars('W', 'A', 'D');
				break;
			default:
				noteq4chars('W', 'A', 'S', 'D');
			}
		}
		end:
		return c;
	}

	#undef noteq2chars
	#undef noteq3chars
	#undef noteq4chars

	void printColoredCommand(enum commands c)
	{
		enum mcolors t;
		enum mcolors b;

		t = myGetTextColor();
		b = myGetBgColor();
		mySetBgColor(mcBlack);
		switch(c)
		{
		case c_red:
			mySetTextColor(mcRed);
			print("Red");
			break;
		case c_blue:
			mySetTextColor(mcBlue);
			print("Blue");
			break;
		default:
			error("Unknown command");
		}
		mySetColor(t, b);
	}

	void putsColoredCommand(enum commands c)
	{
		printColoredCommand(c);
		putchar('\n');
	}

	size_t getCountOfCitiesByCommand(enum commands c)
	{
		register size_t a;
		register map_width_t i;
		register map_height_t j;

		a = 0;
		for(i = 0; i < MAP_WIDTH; i++)
		{
			for(j = 0; j < MAP_HEIGHT; j++)
			{
				if(map[i][j].c == c && (map[i][j].tl == tl_city || map[i][j].tl == tl_armyandcity))
					a++;
			}
		}
		return a;
	}

	bool setArmyTo(map_width_t posx, map_height_t posy, army_xp_t xp)
	{
		if(map[posx][posy].tl == tl_army || map[posx][posy].tl == tl_armyandcity)
			return false;
		map[posx][posy].tl = (map[posx][posy].tl == tl_city ? tl_armyandcity : tl_army);
		map[posx][posy].l.xp = xp;
		map[posx][posy].l.active = false;
		map[posx][posy].c = strvals.nowIs;
	}

	bool attackArmyTo(map_width_t posxFrom, map_height_t posyFrom, map_width_t posxTo, map_height_t posyTo)
	{
		if(map[posxFrom][posyFrom].c != strvals.nowIs)
			return false;
		if(map[posxFrom][posyFrom].tl != tl_army && map[posxFrom][posyFrom].tl != tl_armyandcity)
			return false;
		if(!map[posxFrom][posyFrom].l.active)
			return false;
		if(map[posxFrom][posyFrom].c == map[posxTo][posyTo].c)
			return false;
		if(map[posxFrom][posyFrom].l.xp < ATTACK_ARMY_DEFENCE)
			map[posxFrom][posyFrom].tl = (map[posxFrom][posyFrom].tl == tl_army ? tl_land : tl_city);
		else
		{
			#if ATTACK_ARMY_DEFENCE == 1
				map[posxFrom][posyFrom].l.xp--;
			#elif ATTACK_ARMY_DEFENCE > 1
				map[posxFrom][posyFrom].l.xp -= ATTACK_ARMY_DEFENCE;
			#endif
		}

		if(map[posxTo][posyTo].l.xp < ATTACK_ARMY_ATTACK)
			map[posxTo][posyTo].tl = (map[posxTo][posyTo].tl == tl_army ? tl_land : tl_city);
		else
		{
			#if ATTACK_ARMY_ATTACK == 1
				map[posxTo][posyTo].l.xp--;
			#elif ATTACK_ARMY_ATTACK > 1
				map[posxTo][posyTo].l.xp -= ATTACK_ARMY_ATTACK;
			#endif
		}
		map[posxFrom][posyFrom].l.active = false;
		return true;
	}

	void message(const char *msg)
	{
		puts(msg);
		mpause();
	}

	inline void printBool(bool val)
	{
		print(val ? "true" : "false");
	}

	void printTL(enum types_lands tl)
	{
		switch(tl)
		{
		case tl_army:
			print("Army");
			break;
		case tl_land:
			print("Land");
			break;
		case tl_armyandcity:
			print("Army and City");
			break;
		case tl_city:
			print("City");
		default:
			error("Unknown type of land");
		}
	}
#endif /* _GENGINE_H */
