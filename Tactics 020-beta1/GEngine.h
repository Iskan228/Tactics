#ifndef _GENGINE_H
	#define _GENGINE_H 1

	#include "funcs.h"
	#include "minttypes.h"

	#define MAP_WIDTH 22
	#define MAP_HEIGHT 5
	#define MAX_COUNT_MONEY 1000
	#define MAX_COUNT_FOOD 1000
	#define MONEY_PER_CITY 1
	#define FOOD_PER_GOOD_FIELD 3
	#define FOOD_PER_NORMAL_FIELD 2
	#define FOOD_PER_BAD_FIELD 1
	#define FOOD_PER_DIE_FIELD 0

	#define NEED_CITY 5
	#define NEED_FIELD 3
	#define NEED_INF 2
	#define NEED_ART 3
	#define NEED_DESTROY_CITY 1
	#define NEED_DESTROY_FIELD 1

	#define INF_XP 4
	#define ART_XP 3
	#define ATK_INF_ATK 2
	#define ATK_INF_DEF 1
	#define ATK_ART_ATK 1
	#define ATK_ART_DEF 0
	#define FOOD_INF 2
	#define FOOD_ART 1
	#define INF_DIST_ATK 1
	#define ART_DIST_ATK 2

	typedef enum e_type_map {tm_political/* политическая */, tm_fertility/* плодородность */, tm_max} type_map;
	typedef enum e_type_field {tf_good, tf_normal, tf_bad, tf_die, tf_max} type_field;
	typedef enum e_type_army {ta_inf/* infantry */, ta_art/* artillery */, ta_max} type_army;
	typedef enum e_commands {c_red, c_blue, c_max} commands;
	typedef enum e_type_land {tl_land, tl_city, tl_field, tl_max} type_land;

	#if MAP_WIDTH < 256
		typedef u8 width_t;
	#else
		typedef u16 width_t;
	#endif /* MAP_WIDTH */

	#if MAP_HEIGHT < 256
		typedef u8 height_t;
	#else
		typedef u16 height_t;
	#endif /* MAP_HEIGHT */
	
	#if MAX_COUNT_MONEY < 256
		typedef u8 money_t;
	#else
		typedef u16 money_t;
	#endif /* MAX_COUNT_MONEY */

	#if MAX_COUNT_FOOD < 256
		typedef u8 food_t;
	#else
		typedef u16 food_t;
	#endif /* MAX_COUNT_FOOD */

	#if INF_XP > ART_XP
		#define MAX_ARMY_XP INF_XP
	#else
		#define MAX_ARMY_XP ART_XP
	#endif

	typedef struct s_army
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
		#endif /* MAX_ARMY_XP */
		uint active: 1;
		type_army ta;
	} army;

	typedef struct s_command
	{
		#if MAX_COUNT_MONEY < 2
			uint money: 1;
		#elif MAX_COUNT_MONEY < 4
			uint money: 2;
		#elif MAX_COUNT_MONEY < 8
			uint money: 3;
		#elif MAX_COUNT_MONEY < 16
			uint money: 4;
		#elif MAX_COUNT_MONEY < 32
			uint money: 5;
		#elif MAX_COUNT_MONEY < 64
			uint money: 6;
		#elif MAX_COUNT_MONEY < 128
			uint money: 7;
		#else
			uint money;
		#endif /* MAX_COUNT_MONEY */
		#if MAX_COUNT_FOOD < 2
			uint food: 1;
		#elif MAX_COUNT_FOOD < 4
			uint food: 2;
		#elif MAX_COUNT_FOOD < 8
			uint food: 3;
		#elif MAX_COUNT_FOOD < 16
			uint food: 4;
		#elif MAX_COUNT_FOOD < 32
			uint food: 5;
		#elif MAX_COUNT_FOOD < 64
			uint food: 6;
		#elif MAX_COUNT_FOOD < 128
			uint food: 7;
		#else
			uint food;
		#endif /* MAX_COUNT_FOOD */
	} command;

	typedef struct s_land
	{
		type_land tl;
		uint isArmy: 1;
		commands c;
		type_field tf;
		army a;
	} land;

	commands nowIs;
	land map[MAP_WIDTH][MAP_HEIGHT];
	command cmds[c_max];

	char land2char(const land *l)
	{
		if(l->isArmy)
		{
			switch(l->tl)
			{
			case tl_land:
			case tl_field:
				return (l->a.ta == ta_inf ? 'A': (l->c == c_red ? '>' : '<'));
			case tl_city:
				return 'O';
			default:
				error("Unknown type land");
			}
		}
		switch(l->tl)
		{
		case tl_land:
			return '=';
		case tl_city:
			return 'C';
		case tl_field:
			return '_';
		default:
			error("Unknown type land");
		}
	}

	void printCommand(commands c)
	{
		switch(c)
		{
		case c_red:
			print("Red");
		case c_blue:
			print("Blue");
		default:
			error("Unknown command");
		}
	}

	void putsCommand(commands c)
	{
		switch(c)
		{
		case c_red:
			puts("Red");
			break;
		case c_blue:
			puts("Blue");
			break;
		default:
			error("Unknown command");
		}
	}

	inline commands getCurrentCommand(void)
	{
		return nowIs;
	}

	commands getNextCommand(void)
	{
		switch(getCurrentCommand())
		{
		case c_red:
			return c_blue;
		case c_blue:
			return c_red;
		default:
			error("Unknown command");
		}
	}

	void printTL(const land *l)
	{
		if(l->isArmy)
		{
			switch(l->tl)
			{
			case tl_land:
				print(l->a.ta == ta_inf ? "infantry" : "artillery");
				break;
			case tl_city:
				printf("%s in army", l->a.ta == ta_inf ? "infantry" : "artillery");
				break;
			case tl_field:
				printf("%s on field", l->a.ta == ta_inf ? "infantry" : "artillery");
				break;
			default:
				error("Unknown type land");
			}
		}
		else
		{
			switch(l->tl)
			{
			case tl_land:
				print("Land");
				break;
			case tl_city:
				print("City");
				break;
			case tl_field:
				print("Field");
				break;
			default:
				error("Unknown type land");
			}
		}
	}

	void putsTL(const land *l)
	{
		printTL(l);
		putchar('\n');
	}

	bool readYesNo(const char *question)
	{
		register int c;

		do {
			printf("\n%s? (y/n): ", question);
			c = tolower(_mygetc());
			if(c == EOF || c == '\0')
				my_exit_success();
			if(c == ESC)
				diediedie(0);
		} while(c != 'y' && c != 'n');
		return c == 'y';
	}

	inline bool isCurrentCommand(commands c)
	{
		return c == getCurrentCommand();
	}

	inline money_t getCurrentMoney(void)
	{
		return cmds[getCurrentCommand()].money;
	}

	inline money_t getMoneyByCommand(commands c)
	{
		return cmds[c].money;
	}

	inline food_t getCurrentFood(void)
	{
		return cmds[getCurrentCommand()].food;
	}

	inline food_t getFoodByCommand(commands c)
	{
		return cmds[c].food;
	}

	void addCurrentMoney(money_t m)
	{
		commands c;
		size_t n;

		c = getCurrentCommand();
		n = cmds[c].money + m;
		if(n >= MAX_COUNT_MONEY)
			n = MAX_COUNT_MONEY - 1;
		cmds[c].money += n;
	}

	bool subCurrentMoney(money_t m)
	{
		commands c;

		c = getCurrentCommand();
		if(cmds[c].money < m)
			return false;
		cmds[c].money -= m;
		return true;
	}

	void addMoneyByCommand(commands c, money_t m)
	{
		size_t n;

		n = cmds[c].money + m;
		if(n >= MAX_COUNT_MONEY)
			n = MAX_COUNT_MONEY - 1;
		cmds[c].money += n;
	}

	bool subMoneyByCommand(commands c, money_t m)
	{
		if(cmds[c].money < m)
			return false;
		cmds[c].money -= m;
		return true;
	}

	bool buyArmy(width_t x, height_t y, type_army ta)
	{
		if(map[x][y].tl == tl_city && map[x][y].isArmy)
			return false;
		if(!subCurrentMoney(ta == ta_inf ? NEED_INF : NEED_ART))
			return false;
		map[x][y].a.ta = ta;
		map[x][y].a.active = false;
		map[x][y].a.xp = (ta == ta_inf ? INF_XP : ART_XP);
		map[x][y].isArmy = true;
		return true;
	}

	bool buildCity(width_t x, height_t y)
	{
		if(getCurrentMoney() < NEED_CITY)
			return false;
		if(map[x][y].tl != tl_land)
			return false;
		if(!subCurrentMoney(NEED_CITY))
			return false;
		map[x][y].tl = tl_city;
		return true;
	}

	bool buildField(width_t x, height_t y)
	{
		if(getCurrentMoney() < NEED_FIELD)
			return false;
		if(map[x][y].tl != tl_land)
			return false;
		if(!subCurrentMoney(NEED_FIELD))
			return false;
		map[x][y].tl = tl_field;
		return true;
	}

	#ifdef noteq2chars
		#undef noteq2chars
	#endif /* noteq2chars */

	#ifdef noteq3chars
		#undef noteq3chars
	#endif /* noteq3chars */

	#ifdef noteq4chars
		#undef noteq4chars
	#endif /* noteq4chars */

	#define noteq2chars(c1, c2) printf("%c/%c: ", (c1), (c2));\
		c = toupper(_mygetc());\
		if(c == EOF || c == '\0')\
			my_exit_success();\
		if(c == ESC)\
			diediedie(0);\
		else if(c == 'E')\
			goto end;\
		else if(c != (c1) && c != (c2))\
			goto start

	#define noteq3chars(c1, c2, c3) printf("%c/%c/%c: ", (c1), (c2), (c3));\
		c = toupper(_mygetc());\
		if(c == EOF || c == '\0')\
			my_exit_success();\
		if(c == ESC)\
			diediedie(0);\
		else if(c == 'E')\
			goto end;\
		else if(c != (c1) && c != (c2) && c != (c3))\
			goto start

	#define noteq4chars(c1, c2, c3, c4) printf("%c/%c/%c/%c: ", (c1), (c2), (c3), (c4));\
		c = toupper(_mygetc());\
		if(c == EOF || c == '\0')\
			my_exit_success();\
		if(c == ESC)\
			diediedie(0);\
		else if(c == 'E')\
			goto end;\
		else if(c != (c1) && c != (c2) && c != (c3) && c != (c4))\
			goto start

	char putWASD(width_t x, height_t y, size_t dist)
	{
		register int c;

		puts("Enter \'E\' for exit");
		start:
		if(y < dist)
		{
			if(x < dist)
			{
				noteq2chars('S', 'D');
			}	
			else if(x > MAP_WIDTH - dist)
			{
				noteq2chars('A', 'D');
			}
			else
			{
				noteq3chars('A', 'S', 'D');
			}
		}
		else if(y > MAP_HEIGHT - dist)
		{
			if(x < dist)
			{
				noteq2chars('W', 'D');
			}
			else if(x > MAP_WIDTH - dist)
			{
				noteq2chars('W', 'A');
			}
			else
			{
				noteq3chars('W', 'A', 'D');
			}
		}
		else
		{
			if(x < dist)
			{
				noteq3chars('W', 'S', 'D');
			}
			else if(x > MAP_WIDTH - dist)
			{
				noteq3chars('W', 'A', 'D');
			}
			else
			{
				noteq4chars('W', 'A', 'S', 'D');
			}
		}
		end:
		return c;
	}

	#undef noteq2chars
	#undef noteq3chars
	#undef noteq4chars

	void printColoredCommand(commands c)
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

	void putsColoredCommand(commands c)
	{
		printColoredCommand(c);
		putchar('\n');
	}

	size_t getCountOfCitiesByCommand(commands c)
	{
		size_t a;
		register width_t i;
		register height_t j;

		a = 0;
		for(i = 0; i < MAP_WIDTH; i++)
		{
			for(j = 0; j < MAP_HEIGHT; j++)
			{
				if(map[i][j].c == c && map[i][j].tl == tl_city)
					a++;
			}
		}
		return a;
	}

	size_t getCountOfFieldsByCommand(commands c)
	{
		size_t a;
		register width_t i;
		register height_t j;

		a = 0;
		for(i = 0; i < MAP_WIDTH; i++)
		{
			for(j = 0; j < MAP_HEIGHT; j++)
			{
				if(map[i][j].c == c && map[i][j].tl == tl_field)
					a++;
			}
		}
		return a;
	}

	food_t getFoodPerTF(type_field tf)
	{
		switch(tf)
		{
		case tf_good:
			return FOOD_PER_GOOD_FIELD;
		case tf_normal:
			return FOOD_PER_NORMAL_FIELD;
		case tf_bad:
			return FOOD_PER_BAD_FIELD;
		case tf_die:
			return FOOD_PER_DIE_FIELD;
		default:
			error("Unknown type of field");
		}
	}

	food_t getFoodPerArmy(type_army ta)
	{
		switch(ta)
		{
		case ta_inf:
			return FOOD_INF;
		case ta_art:
			return FOOD_ART;
		default:
			error("Unknown type of army");
		}
	}

	void lose(commands c)
	{
		/* +---+
		 * |   O
		 * |  /|\
		 * |  / \
		 * |
		 * */
		puts("+---+");
		puts("|   O");
		puts("|  /|\\");
		puts("|  / \\");
		put2chars('|', '\n');
		puts(getCurrentCommand() == c_red ? "You lose." : "You win!");
		mpause();
		my_exit_success();
	}

	void nextCommand(void)
	{
		bool ter[c_max];
		size_t m;
		llint f;
		register width_t i;
		register height_t j;
		commands c;

		for(m = 0; m < c_max; m++)
			ter[m] = false;

		for(i = 0; i < MAP_WIDTH; i++)
		{
			for(j = 0; j < MAP_HEIGHT; j++)
			{
				ter[map[i][j].c] = true;
			}
		}
		for(m = 0; m < c_max; m++)
		{
			if(!ter[m])
				lose(m);
		}

		c = getCurrentCommand();
		m = getCurrentMoney();
		f = getCurrentFood();

		for(i = 0; i < MAP_WIDTH; i++)
		{
			for(j = 0; j < MAP_HEIGHT; j++)
			{
				if(map[i][j].c == c)
				{
					switch(map[i][j].tl)
					{
					case tl_city:
						m += MONEY_PER_CITY;
						break;
					case tl_field:
						f += getFoodPerTF(map[i][j].tf);
					}
					if(map[i][j].isArmy)
					{
						map[i][j].a.active = true;
						f -= getFoodPerArmy(map[i][j].a.ta);
					}
				}
			}
		}
		if(f < 0)
		{
			for(i = 0; i < MAP_WIDTH; i++)
			{
				for(j = 0; j < MAP_HEIGHT; j++)
				{
					if(!f)
						break;
					if(map[i][j].c == c && map[i][j].isArmy)
					{
						f += getFoodPerArmy(map[i][j].a.ta);
						map[i][j].isArmy = false;
					}
				}
			}
			if(f < 0)
				lose(c);
		}
		if(f >= MAX_COUNT_FOOD)
			f = MAX_COUNT_FOOD - 1;
		cmds[c].food = f;
		if(m >= MAX_COUNT_MONEY)
			m = MAX_COUNT_MONEY - 1;
		cmds[c].money = m;
		cmds[c].food = f;
		nowIs = getNextCommand();
	}

	bool setArmyTo(width_t xFrom, height_t yFrom, width_t xTo, height_t yTo)
	{
		if(!map[xFrom][yFrom].isArmy)
			return false;
		if(map[xTo][yTo].isArmy)
			return false;
		if(!map[xFrom][yFrom].a.active)
			return false;
		map[xFrom][yFrom].isArmy = false;
		map[xTo][yTo].isArmy = true;
		map[xTo][yTo].a.active = false;
		map[xTo][yTo].c = getCurrentCommand();
		map[xTo][yTo].a.ta = map[xFrom][yFrom].a.ta;
		map[xTo][yTo].a.xp = map[xFrom][yFrom].a.xp;
		return true;
	}

	bool attackArmyTo(width_t xFrom, height_t yFrom, width_t xTo, height_t yTo)
	{
		if(!map[xFrom][yFrom].isArmy)
			return false;
		if(!map[xTo][yTo].isArmy)
			return false;
		if(!map[xFrom][yFrom].a.active)
			return false;
		if(map[xFrom][yFrom].a.xp < (map[xTo][yTo].a.ta == ta_inf ? ATK_INF_DEF : ATK_ART_DEF))
			map[xFrom][yFrom].isArmy = false;
		else
		{
			map[xFrom][yFrom].a.active = false;
			if(map[xTo][yTo].a.ta == ta_inf && map[xFrom][yFrom].a.ta != ta_art)
			{
				#if ATK_INF_DEF == 0
					
				#elif ATK_INF_DEF == 1
					map[xFrom][yFrom].a.xp--;
				#else
					map[xFrom][yFrom].a.xp -= ATK_INF_DEF;
				#endif /* ATK_INF_DEF */
			}
			else if(map[xTo][yTo].a.ta == ta_art && map[xFrom][yFrom].a.ta != ta_inf)
			{
				#if ATK_ART_DEF == 0
					
				#elif ATK_ART_DEF == 1
					map[xFrom][yFrom].a.xp--;
				#else
					map[xFrom][yFrom].a.xp -= ATK_ART_DEF;
				#endif /* ATK_ART_DEF */
			}
		}
		if(map[xTo][yTo].a.xp < (map[xFrom][yFrom].a.ta == ta_inf ? ATK_INF_ATK : ATK_ART_ATK))
			map[xTo][yTo].isArmy = false;
		else
		{
			if(map[xFrom][yFrom].a.ta == ta_inf)
			{
				#if ATK_INF_ATK == 0
					
				#elif ATK_INF_ATK == 1
					map[xTo][yTo].a.xp--;
				#else
					map[xTo][yTo].a.xp -= ATK_INF_ATK;
				#endif /* ATK_INF_ATK */
			}
			else
			{
				#if ATK_ART_ATK == 0
					
				#elif ATK_ART_ATK == 1
					map[xTo][yTo].a.xp--;
				#else
					map[xTo][yTo].a.xp -= ATK_ART_ATK;
				#endif /* ATK_ART_ATK */
			}
		}
		return true;
	}

	bool destroyArmy(width_t x, height_t y)
	{
		if(!map[x][y].isArmy)
			return false;
		map[x][y].isArmy = false;
		return true;
	}

	bool destroyCity(width_t x, height_t y)
	{
		if(getCurrentMoney() < NEED_DESTROY_CITY)
			return false;
		if(map[x][y].tl != tl_city)
			return false;
		if(!subCurrentMoney(NEED_DESTROY_CITY))
			return false;
		map[x][y].tl = tl_land;
		return true;
	}

	bool destroyField(width_t x, height_t y)
	{
		if(getCurrentMoney() < NEED_DESTROY_FIELD)
			return false;
		if(map[x][y].tl != tl_field)
			return false;
		if(!subCurrentMoney(NEED_DESTROY_FIELD))
			return false;
		map[x][y].tl = tl_land;
		return true;
	}
#endif /* _GENGINE_H */
