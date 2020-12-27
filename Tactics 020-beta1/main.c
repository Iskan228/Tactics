#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "ai.h"
#include "GEngine.h"
#include "funcs.h"
#include "minttypes.h"

void message(const char *msg)
{
	puts(msg);
	mpause();
}

int main()
{
	int ival;
	u8 dst;
	register uint pos;
	register width_t i, posx;
	register height_t j, posy;
	register int c;
	size_t sizeval;
	type_map tm;

	posx = posy = 0;
	nowIs = c_red;
	cmds[c_red].money = 10;
	cmds[c_blue].money = 10;
	cmds[c_blue].food = 10;
	cmds[c_red].food = 10;
	dst = 1;
	tm = tm_political;

	#if IS_UNIX
		tcgetattr(0, &ti);
		ti.c_lflag &= ~ICANON & ~ECHO;
		tcsetattr(0, TCSANOW, &ti);

		puts("If you want to exit from the game, use command \"kill\" and number of process");
		#if IS_C99
			printf("pid of this program = %jd", (intmax_t)getpid());
		#else
			printf("pid of this program = %ld", (long)getpid());
		#endif /* IS_C99 */
		putchar('\n');
	#endif /* IS_UNIX */

	#if IS_WINDOWS
		system("TITLE Tactics v. 0.2.0 beta 1");
	#endif /* IS_WINDOWS */
	
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
	srand(time(NULL));
	for(i = 0; i < MAP_WIDTH; i++)
	{
		for(j = 0; j < MAP_HEIGHT; j++)
		{
			map[i][j].c = (i < MAP_WIDTH / 2 ? c_red : c_blue);
			map[i][j].tl = tl_land;
			map[i][j].isArmy = false;
			map[i][j].tf = rand() % tf_max;
		}
	}

	while(1)
	{
		cls();
		print("Now is: ");
		putsColoredCommand(getCurrentCommand());
		printColoredCommand(c_red);
		printf(" money: %u\n", cmds[c_red].money);
		printColoredCommand(c_red);
		printf(" food: %u\n", cmds[c_red].food);
		printColoredCommand(c_blue);
		printf(" money: %u\n", cmds[c_blue].money);
		printColoredCommand(c_blue);
		printf(" food: %u\n", cmds[c_blue].money);
		puts("Info:");
		print("Type: ");
		putsTL(&map[posx][posy]);
		print("Color: ");
		putsColoredCommand(map[posx][posy].c);
		if(map[posx][posy].isArmy)
		{
			printf("Army XP: %u\n", map[posx][posy].a.xp + 1);
			printf("Army is active: ");
			putsBool(map[posx][posy].a.active);
		}
		else
			put2chars('\n', '\n');
		put2chars(' ', ' ');
		for(i = 0; i < MAP_WIDTH; i++)
			putchar(posx == i ? '|' : ' ');
		put3chars(' ', ' ', '\n');
		put2chars(' ', '+');
		for(i = 0; i < MAP_WIDTH; i++)
			putchar('-');
		put3chars('+', ' ', '\n');
		switch(tm)
		{
		case tm_political:
			for(j = 0; j < MAP_HEIGHT; j++)
			{
				put2chars(j == posy ? '>' : ' ', '|');
				for(i = 0; i < MAP_WIDTH; i++)
				{
					mySetTextColor(map[i][j].c == c_red ? mcRed : mcBlue);
					putchar(land2char(&map[i][j]));
				}
				mySetTextColor(mcWhite);
				put3chars('|', posy == j ? '<' : ' ', '\n');
			}
			break;
		case tm_fertility:
			for(j = 0; j < MAP_HEIGHT; j++)
			{
				put2chars(j == posy ? '>' : ' ', '|');
				for(i = 0; i < MAP_WIDTH; i++)
				{
					switch(map[i][j].tf)
					{
					case tf_good:
						mySetTextColor(mcGreen);
						break;
					case tf_normal:
						mySetTextColor(mcYellow);
						break;
					case tf_bad:
						mySetTextColor(mcRed);
						break;
					case tf_die:
						mySetTextColor(mcBlue);
						break;
					default:
						error("Unknown type of field");
					}
					putchar(land2char(&map[i][j]));
				}
				mySetTextColor(mcWhite);
				put3chars('|', posy == j ? '<' : ' ', '\n');
			}
			break;
		}
		put2chars(' ', '+');

		for(i = 0; i < MAP_WIDTH; i++)
			putchar('-');
		put3chars('+', '\n', ' ');
		putchar(' ');
		for(i = 0; i < MAP_WIDTH; i++)
			putchar(posx == i ? '|' : ' ');
		print("\nEnter command (h or Tab for help): ");
		c = tolower(_mygetc());
		switch(c)
		{
		case EOF:
		case '\0':
			my_exit_success();
		case ESC:
		case 'g':
			diediedie(0);
			break;
		case 'e':
			if(map[posx][posy].isArmy)
			{
				if(map[posx][posy].tl == tl_land)
				{
					if(readYesNo("Are you sure want to disband the army"))
						message(destroyArmy(posx, posy) ? "Army successfully disbanded" : "Failed to disband the army");
				}
				else
				{
					pos = 0;
					switch(map[posx][posy].tl)
					{
					case tl_city:
						printf("To destroy a city you need %d %s\n", NEED_DESTROY_CITY, NEED_DESTROY_CITY == 1 ? "coin" : "coins");
						while(1)
						{
							print("Disband the army|Destroy a city");
							if(pos)
								puts("                        ^");
							else
								puts("       ^");
							puts("Press \'E\' for exit");
							c = _mygetc();
							if(c == EOF || c == '\0')
								my_exit_success();
							if(c == ENTER || c == '\n' || c == ' ')
									break;
							if(c == 'e' || c == ESC)
							{
								pos = 2;
								break;
							}
							if(c == 'a' || c == 'd')
								pos = !pos;
						}
						if(pos == 2)
							break;
						if(pos)
							goto delCity;
						goto delArmy;
						break;
					case tl_field:
						printf("To destroy a field you need %d %s\n", NEED_DESTROY_FIELD, NEED_DESTROY_FIELD == 1 ? "coin" : "coins");
						while(1)
						{
							print("Disband the army|Destroy a field");
							if(pos)
								print("                         ^");
							else
								print("         ^");
							puts("Press \'E\' for exit");
							c = _mygetc();
							if(c == EOF || c == '\0')
								my_exit_success();
							if(c == ENTER || c == ' ' || c == '\n')
								break;
							if(c == 'e' || c == ESC)
							{
								pos = 2;
								break;
							}
							if(c == 'a' || c == 'd')
								pos = !pos;
						}
						if(pos == 2)
							break;
						if(pos)
							goto delField;
						goto delArmy;
					default:
						error("Unknown type of land");
					}
					delArmy:
					if(readYesNo(""))
					delCity:

					delField:
				}
			}
			else
			{
				switch(map[posx][posy].tl)
				{
				case tl_land:
					message("Nothing to destroy");
					break;
				case tl_city:
					printf("To destroy a city you need %d %s\n", NEED_DESTROY_CITY, NEED_DESTROY_CITY == 1 ? "coin" : "coins");
					if(readYesNo("Are you sure want to destroy the city"))
						message(destroyCity(posx, posy) ? "City successfully destroyed" : "Failed to destroy the city");
					break;
				case tl_field:
					printf("To destroy a field you need %d %s\n", NEED_DESTROY_FIELD, NEED_DESTROY_FIELD == 1 ? "coin" : "coins");
					if(readYesNo("Are you sure want to destroy the field"))
						message(destroyField(posx, posy) ? "Field successfully destroyed" : "Failed to destroy the field");
					break;
				default:
					error("Unknown type of land");
				}
			}
			break;
		case 'h':
		case '\t':
			pos = 0;
			while(1)
			{
				cls();
				puts("     Commands:");
				puts("  h, Tab - help");
				puts("  w - go up");
				puts("  a - go left");
				puts("  s - go down");
				puts("  d - go right");
				puts("  Esc, g - exit from the game");
				puts("  m - change perspective");
				printf("%c e - disband the army or destroy a city or field\n", pos == 0 ? '>' : ' ');
				printf("%c Enter, n, Space - end turn\n", pos == 1 ? '>' : ' ');
				printf("%c b, \\, | - build a city, hire an army or send an army on a march\n", pos == 2 ? '>' : ' ');
				printf("%c k, l, :, ; - attack an army\n", pos == 3 ? '>' : ' ');
				printf("%c Version\n", pos == 4 ? '>' : ' ');
				printf("%c Creators\n", pos == 5 ? '>' : ' ');
				printf("%c Fertility of the land\n", pos == 6 ? '>' : ' ');
				printf("%c Map view\n", pos == 7 ? '>' : ' ');
				c = tolower(_mygetc());
				switch(c)
				{
				case EOF:
				case '\0':
					my_exit_success();
				case 'g':
				case ESC:
				case 'e':
					goto end228;
				case 'w':
					if(pos == 0)
						pos = 7;
					else
						pos--;
					break;
				case 's':
					if(pos == 7)
						pos = 0;
					else
						pos++;
					break;
				case ' ':
				case ENTER:
					cls();
					switch(pos)
					{
					case 0:
						puts("If you have too many armies (more that you can afford) and you do not want to lose the armies you need, then you can disband the army yourself. It won\'t give you anything");
						puts("If you can\'t control a city or field and are sure that you can\'t get it back, then  it is better to destroy it. It costs 1 coin");
						break;
					case 1:
						puts("When you end your turn, your opponent starts playing. I recommend that you only end your turn if you have done everithing you want");
						break;
					case 2:
						printf("It costs %u coins to build city. The city gives you ", NEED_CITY);
						#if MONEY_PER_CITY == 1
							print("1 coin");
						#else
							printf("%u coins", MONEY_PER_CITY);
						#endif /* MONEY_PER_CITY */
						puts(" per round. Only in the city you can hire an army");
						puts("The sky needs an army to fight. You can hire soldiers in cities for a certain fee");
						puts("When you have an army, send send it on a campaign againist the enemy or defend a point");
						break;
					case 3:
						puts("If your army met the enemy army, then attack quickly! The one who attacks does more damage than the one who defends");
						break;
					case 4:
						puts("Tactics v. 0.2.0");
						break;
					case 5:
						puts("Create by Kutlahmetov Iskander. 2020");
						break;
					case 6:
						printf("There are %u types of soil in Tactics. It\'s good, normal, bad and dead\n", tf_max);
						puts("If you look at the ferility map, good soil is shown in green, normal in red, bad in yellow, and dead in blue");
						printf("Good soil will give you %u food per turn\n", FOOD_PER_GOOD_FIELD);
						printf("Normal soil will give you %u food per turn\n", FOOD_PER_NORMAL_FIELD);
						printf("Bad soil will give you %u food per turn\n", FOOD_PER_BAD_FIELD);
						printf("Died soil will give you %u food er turn\n", FOOD_PER_DIE_FIELD);
						puts("Food is needed to feed the army");
						break;
					case 7:
						puts("The map can ve viewer from 2 perspectives: political and fetility map");
						puts("To change perspective click \'M\'");
						break;
					default:
						error("Error");
					}
					mpause();
				}
			}
			end228:
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			dst = c - '0';
			break;
		case 'w':	
			ival = posy - dst;
			while(ival < 0)
				ival += MAP_HEIGHT;
			posy = ival;
			break;
		case 's':
			ival = posy + dst;
			while(ival >= MAP_HEIGHT)
				ival -= MAP_HEIGHT;
			posy = ival;
			break;
		case 'a':
			ival = posx - dst;
			while(ival < 0)
				ival += MAP_WIDTH;
			posx = ival;
			break;
		case 'd':
			ival = posx + dst;
			while(ival >= MAP_WIDTH)
				ival -= MAP_WIDTH;
			posx = ival;
			break;
		case 'n':
		case '\n':
		case ' ':
			cls();
			if(readYesNo("Do you really want to end tour turn"))
				nextCommand();
			break;
		case 'm':
			pos = 0;
			while(1)
			{
				cls();
				puts("Select map");
				puts("Political|Fertility");
				if(pos)
					puts("              ^");
				else
					puts("    ^");
				puts("Enter \'E\' for exit");
				c = tolower(_mygetc());
				if(c == 'a' || c == 'd')
					pos = !pos;
				if(c == 'e' || c == ESC)
				{
					pos = 2;
					break;
				}
				if(c == 'p')
				{
					pos = 0;
					break;
				}
				if(c == 'f')
				{
					pos = 1;
					break;
				}
				if(c == ENTER || c == '\n' || c == ' ')
					break;
			}
			if(pos == 2)
				break;
			tm = (pos ? tm_fertility : tm_political);
			break;
		case 'b':
		case '|':
		case '\\':
			if(!isCurrentCommand(map[posx][posy].c))
			{
				print("This is not your territory!");
				mpause();
			}
			else
			{
				if(map[posx][posy].isArmy)
				{
					if(!map[posx][posy].a.active)
						message("This army is not active!");
					else
					{
						c = putWASD(posx, posy, 1);
						if(c == 'E')
							break;
						switch(c)
						{
						case 'W':
							if(!setArmyTo(posx, posy, posx, posy - 1))
								message("You can\'t send an army here!");
							break;
						case 'A':
							if(!setArmyTo(posx, posy, posx - 1, posy))
								message("You can\'t send an army here!");
							break;
						case 'S':
							if(!setArmyTo(posx, posy, posx, posy + 1))
								message("You can\'t send an army here!");
							break;
						case 'D':
							if(!setArmyTo(posx, posy, posx + 1, posy))
								message("You can\'t send an army here!");
							break;
						default:
							error("WASD error");
						}
					}
				}
				else
				{
					switch(map[posx][posy].tl)
					{
					case tl_land:
						pos = 0;
						while(1)
						{
							cls();
							printf("Your money: %u\n", getCurrentMoney());
							puts("City|Field");
							if(pos)
								puts("       ^");
							else
								puts(" ^");
							puts("Info:");
							printf("Costs: %u\n", pos ? NEED_FIELD : NEED_CITY);
							puts("Press \'E\' for exit");
							c = tolower(_mygetc());
							if(c == 'e' || c == ESC)
							{
								pos = 2;
								break;
							}
							if(c == 'a' || c == 'd')
								pos = !pos;
							if(c == ENTER || c == '\n' || c == ' ')
								break;
						}
						if(pos == 2)
							break;
						if(!pos)
						{
							if(readYesNo("Do you want to build city"))
							{
								if(!buildCity(posx, posy))
									message("Failed to build a city!");
							}
						}
						else
						{
							if(readYesNo("Do you want to build field"))
							{
								if(!buildField(posx, posy))
									message("Failed to build a field!");
							}
						}
						break;
					case tl_city:
						pos = 0;
						while(1)
						{
							cls();
							printf("Your money: %u\n", getCurrentMoney());
							puts("Hire infantry|Hire artillery");
							if(pos == 0)
								puts("      ^");
							else
								puts("                      ^");
							puts("Info:");
							printf("Costs: %u\n", pos ? NEED_ART : NEED_INF);
							printf("Attack: %u\n", pos ? ATK_ART_ATK : ATK_INF_ATK);
							printf("Defence: %u\n", pos ? ATK_ART_DEF : ATK_INF_DEF);
							printf("Attack distance: %u\n", pos ? ART_DIST_ATK : INF_DIST_ATK);
							printf("XP: %u\n", pos ? ART_XP : INF_XP);
							puts("Press \'E\' for exit");
							c = tolower(_mygetc());
							if(c == 'e')
							{
								pos = 3;
								break;
							}
							if(c == EOF || c == '\0')
								my_exit_success();
							if(c == 'a' || c == 'd')
								pos = !pos;
							if(c == ENTER || c == '\n' || c == ' ')
								break;
						}
						if(pos == 3)
							break;
						if(!pos)
						{
							if(readYesNo("Do you really want to hire infantry"))
							{
								if(!buyArmy(posx, posy, ta_inf))
									message("Failed to hire infantry");
							}
						}
						else
						{
							if(readYesNo("Do you really want to hire artillery"))
							{
								if(!buyArmy(posx, posy, ta_art))
									message("Failed to hire artillery");
							}
						}
						break;
					}
				}
			}
			break;
		case 'k':
		case ':':
		case ';':
			if(!map[posx][posy].isArmy)
			{
				message("This is not an army!");
				break;
			}
			if(!map[posx][posy].a.active)
			{
				message("This army is not active!");
				break;
			}
			sizeval = map[posx][posy].a.ta == ta_inf ? INF_DIST_ATK : ART_DIST_ATK;
			c = putWASD(posx, posy, sizeval);
			if(c == 'E')
				break;
			if(c == 'W')
				sizeval = attackArmyTo(posx, posy, posx, posy - sizeval);
			if(c == 'A')
				sizeval = attackArmyTo(posx, posy, posx - sizeval, posy);
			if(c == 'S')
				sizeval = attackArmyTo(posx, posy, posx, posy + sizeval);
			if(c == 'D')
				sizeval = attackArmyTo(posx, posy, posx + sizeval, posy);
			if(!sizeval)
				message("Failed to attack enemy army");
			break;
		}
	}

	my_exit_success();
}
