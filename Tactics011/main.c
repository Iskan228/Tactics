#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "GEngine.h"
#include "funcs.h"
#include "minttypes.h"

int main(void)
{
	register map_width_t i, posx;
	register map_height_t j, posy;
	register int c;
	register size_t sizeval;
	char boolName[MAX_LEN_OF_BOOL_AS_STR];
	char types_landsName[MAX_LEN_OF_TYPE_LAND_AS_STR];

	posx = posy = 0;
	strvals.nowIs = c_red;
	strvals.redMoney = strvals.blueMoney = 10;

	#if IS_UNIX
		/* Как это работает? */
		tcgetattr(0, &ti);
		ti.c_lflag &= ~ICANON & ~ECHO;
		tcsetattr(0, TCSANOW, &ti);

		puts("If you want to exit from the game, use command \"kill\" and numbern of process");
		#if IS_C99
			printf("pid of this program = %jd\n", (intmax_t)getpid());
		#else
			printf("pid of this program = %d", (int)getpid());
		#endif /* IS_C99 */
	#endif /* IS_UNIX */

	if(signal(SIGINT, diediedie) == SIG_ERR)
		puts("SIGINT error");
	if(signal(SIGFPE, floaterror) == SIG_ERR)
		puts("SIGFPE error");
	if(signal(SIGABRT, SIG_DFL) == SIG_ERR)
		puts("SIGABRT error");
	if(signal(SIGSEGV, segverror) == SIG_ERR)
		puts("SIGSEGV error");
	if(signal(SIGTERM, termerror) == SIG_ERR)
		puts("SIGTERM error");
	if(signal(SIGILL, illerror) == SIG_ERR)
		puts("SIGILL error");
	mpause();
	mySetColor(mcWhite, mcBlack);
	#if IS_WINDOWS
		system("TITLE Tactics v.0.1.1");
	#endif /* IS_WINDOWS */
	for(i = 0; i < MAP_WIDTH; i++)
	{
		for(j = 0; j < MAP_HEIGHT; j++)
		{
			map[i][j].c = (i < MAP_WIDTH / 2 ? c_red : c_blue);
			map[i][j].tl = tl_land;
		}
	}

	while(1)
	{
		cls();
		print("Now is: ");
		putsColoredCommand(strvals.nowIs);
		printColoredCommand(c_red);
		printf(" money: %u\n", strvals.redMoney);
		printColoredCommand(c_blue);
		printf(" money: %u\n", strvals.blueMoney);
		puts("Info:");
		printf("Type: %s;\n", types_lands2str(map[posx][posy].tl, types_landsName, MAX_LEN_OF_TYPE_LAND_AS_STR));
		print("Color: ");
		putsColoredCommand(map[posx][posy].c);
		switch(map[posx][posy].tl)
		{
		case tl_army:
		case tl_armyandcity:
			printf("Army XP: %u\n", map[posx][posy].l.xp + 1);
			printf("Army is active: %s", bool2str((bool)map[posx][posy].l.active, boolName, 6));
			break;
		case tl_city:
		case tl_land:
			putchar('\n');
			break;
		default:
			error("Unknown type of land");
		}
		putchar('\n');
		put3chars('\n', ' ', ' ');
		for(i = 0; i < MAP_WIDTH; i++)
			putchar(posx == i ? '|' : ' ');
		put3chars(' ', ' ', '\n');
		put2chars(' ', '+');
		for(i = 0; i < MAP_WIDTH; i++)
			putchar('-');
		put3chars('+', ' ', '\n');
		for(j = 0; j < MAP_HEIGHT; j++)
		{
			put2chars(j == posy ? '>' : ' ', '|');
			for(i = 0; i < MAP_WIDTH; i++)
			{
				mySetTextColor(map[i][j].c == c_red ? mcRed : mcBlue);
				putchar(land2char(map[i][j].tl));
			}
			mySetTextColor(mcWhite);
			put3chars('|', posy == j ? '<' : ' ', '\n');
		}
		put2chars(' ', '+');
		for(i = 0; i < MAP_WIDTH; i++)
			putchar('-');
		put3chars('+', '-', '\n');
		put2chars(' ', ' ');
		for(i = 0; i < MAP_WIDTH; i++)
			putchar(posx == i ? '|' : ' ');
		print("  \nEnter command (h or Tab for help): ");
		c = tolower(_mygetc());
		switch(c)
		{
		case EOF:
			my_exit_failure();
		case ESC:
		case 'g':
		case '\0':
			diediedie(0);
			break;
		case 'h':
		case '\t':
			cls();
			puts("Commands:");
			puts("h, Tab - help;");
			puts("w - up;");
			puts("a - left;");
			puts("s - down;");
			puts("d - right;");
			puts("Esc, g - exit");
			puts("Enter, n, Space - next command;");
			puts("b, |, \\ - build/active;");
			puts("k, l, :, ; - attack army;");
			puts("v - version;");
			puts("c - creators.");
			mpause();
			break;
		case 'w':
			if(!posy)
				posy = MAP_HEIGHT - 1;
			else
				posy--;
			break;
		case 'a':
			if(!posx)
				posx = MAP_WIDTH - 1;
			else
				posx--;
			break;
		case 's':
			if(posy == MAP_HEIGHT - 1)
				posy = 0;
			else
				posy++;
			break;
		case 'd':
			if(posx == MAP_WIDTH - 1)
				posx = 0;
			else
				posx++;
			break;
		case 'n':
		case ENTER:
		case '\n':
		case ' ':
			cls();
			if(readYesNo("Do you really want to go future"))
			{
				switch(strvals.nowIs)
				{
				case c_red:
					sizeval = strvals.redMoney + getCountOfCitiesByCommand(c_red) * MONEY_PER_CITY;
					if(sizeval >= MAX_COUNT_MONEY)
						sizeval = MAX_COUNT_MONEY - 1;
					strvals.redMoney = sizeval;
					break;
				case c_blue:
					sizeval = strvals.blueMoney + getCountOfCitiesByCommand(c_blue) * MONEY_PER_CITY;
					if(sizeval >= MAX_COUNT_MONEY)
						sizeval = MAX_COUNT_MONEY - 1;
					strvals.blueMoney = sizeval;
					break;
				default:
					error("Unknwon command");
				}
				for(i = 0; i < MAP_WIDTH; i++)
				{
					for(j = 0; j < MAP_HEIGHT; j++)
					{
						if(map[i][j].c == strvals.nowIs && (map[i][j].tl == tl_army || map[i][j].tl == tl_armyandcity))
							map[i][j].l.active = true;
					}
				}
				strvals.nowIs = nextCommand(strvals.nowIs);
			}
			break;
		case 'b':
		case '|':
		case '\\':
			if(strvals.nowIs == map[posx][posy].c)
			{
				switch(map[posx][posy].tl)
				{
				case tl_land:
					if(readYesNo("Do you want to build a city"))
					{
						if(!subCurrentMoney(NEED_MONEY_TO_BUILD_CITY))
							message("You can\'t build a city!");
						else
							map[posx][posy].tl = tl_city;
					}
					break;
				case tl_city:
					if(readYesNo("Do you want to buy an army"))
					{
						if(!subCurrentMoney(NEED_MONEY_TO_BUY_ARMY))
							message("You can\'t buy an army!");
						else
						{
							map[posx][posy].tl = tl_armyandcity;
							map[posx][posy].l.xp = MAX_ARMY_XP;
							map[posx][posy].l.active = false;
						}
					}
					break;
				case tl_army:
				case tl_armyandcity:
					if(map[posx][posy].l.active)
					{
						c = putWASD(posx, posy);
						if(c == 'E')
							break;
						switch(c)
						{
						case 'W':
							if(!setArmyTo(posx, posy - 1, map[posx][posy].l.xp))
								message("You can\'t set army here!");
							else
								map[posx][posy].tl = (map[posx][posy].tl == tl_army ? tl_land : tl_city);
							break;
						case 'A':
							if(!setArmyTo(posx - 1, posy, map[posx][posy].l.xp))
								message("You can\'t set army here!");
							else
								map[posx][posy].tl = (map[posx][posy].tl == tl_army ? tl_land : tl_city);
							break;
						case 'S':
							if(!setArmyTo(posx, posy + 1, map[posx][posy].l.xp))
								message("You can\'t set army here!");
							else
								map[posx][posy].tl = (map[posx][posy].tl == tl_army ? tl_land : tl_city);
							break;
						case 'D':
							if(!setArmyTo(posx + 1, posy, map[posx][posy].l.xp))
								message("You can\'t set army here!");
							else
								map[posx][posy].tl = (map[posx][posy].tl == tl_army ? tl_land : tl_city);
							break;
						default:
							error("Error WASD");
						}
					}
					else
						message("This army is not active!");
				}
			}
			else
				message("It\'s not your land!");
			break;
		case 'k':
		case ':':
		case ';':
			if(map[posx][posy].tl == tl_army || map[posx][posy].tl == tl_armyandcity)
			{
				if(map[posx][posy].l.active)
				{
					c = putWASD(posx, posy);
					if(c == 'E')
						break;
					switch(c)
					{
					case 'W':
						if(!attackArmyTo(posx, posy, posx, posy - 1))
							message("You can\'t attack here!");
						break;
					case 'A':
						if(!attackArmyTo(posx, posy, posx - 1, posy))
							message("You can\'t attack here!");
						break;
					case 'S':
						if(!attackArmyTo(posx, posy, posx, posy + 1))
							message("You can\'t attack here!");
						break;
					case 'D':
						if(!attackArmyTo(posx, posy, posx + 1, posy))
							message("You can\'t attack here!");
						break;
					default:
						error("Error WASD");
					}
				}
				else
					message("This army is not active!");
			}
			else
				message("This is not an army!");
			break;
		case 'v':
			message("Tactics v. 0.1.1");
			break;
		case 'c':
			message("Create by Kutlakhmetov Iskander");
			break;
		}
	}
	my_exit_success();
}
