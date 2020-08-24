#include "GEngine.h"

#define MAX_LEN_OF_NAME_GAME 13

int main(void)
{
    register map_width_t i;
    register map_height_t j;
    register map_width_t posx;
    register map_height_t posy;
    register int c;
    char boolName[MAX_LEN_OF_BOOL_AS_STR];
    /*char nameGame[MAX_LEN_OF_NAME_GAME + 1]; */
    char types_landsName[MAX_LEN_OF_TYPES_LANDS_AS_STR];
    /*FILE *f;
    char readDateOrTimeStr[12]; */

    posx = posy = 0;
    strvals.nowIs = c_red;
    strvals.redMoney = strvals.blueMoney = 10;

    #if IS_UNIX
        /* How it work? Как это работает? */
        tcgetattr(0, &ti);
        ti.c_lflag &= ~ICANON & ~ECHO;
        tcsetattr(0, TCSANOW, &ti);

        puts("If you want to exit from game, use command \"kill\" and number of this process");
        #if IS_C99
            printf(" pid of this program = %jd\n", (intmax_t)getpid());
        #else
            printf("pid of this program = %d\n", (int)getpid());
        #endif /* IS_C99 */
        pause();
    #endif /* IS_UNIX */
    if(signal(SIGINT, diediedie) == SIG_ERR)
        print("SIGINT error");
    if(signal(SIGFPE, floaterror) == SIG_ERR)
        print("SIGFPE error");
    if(signal(SIGABRT, SIG_DFL) == SIG_ERR)
        print("SIGABRT error");
    if(signal(SIGSEGV, segverror) == SIG_ERR)
        print("SIGSEGV error");
    if(signal(SIGTERM, termerror) == SIG_ERR)
        print("SIGTERM error");
    if(signal(SIGILL, illerror) == SIG_ERR)
        print("SIGILL error");
    pause();
    mySetColor(mcWhite, mcBlack);

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
        printColoredCommand(strvals.nowIs);
        putchar('\n');
        printColoredCommand(c_red);
        printf(" money: %u\n", strvals.redMoney);
        printColoredCommand(c_blue);
        printf(" money: %u\n", strvals.blueMoney);
        puts("Info:");
        printf("Type: %s;\n", types_lands2str(map[posx][posy].tl, types_landsName));
        print("Color: ");
        printColoredCommand(map[posx][posy].c);
        putchar('\n');
        switch(map[posx][posy].tl)
        {
        case tl_army:
        case tl_armyandcity:
            printf("Army XP: %u\n", map[posx][posy].l.xp + 1);
            printf("Army is active: %s\n\n", bool2str((bool)map[posx][posy].l.active, boolName));
            break;
        case tl_city:
        case tl_land:
            put2chars('\n', '\n');
            putchar('\n');
            break;
        default:
            error("Unknown type of land!");
        }
        put2chars(' ', ' ');
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
        put3chars('+', ' ', '\n');
        put2chars(' ', ' ');
        for(i = 0; i < MAP_WIDTH; i++)
            putchar(posx == i ? '|' : ' ');
        put3chars(' ', ' ', '\n');
        print("Enter command (h or Tab for help): ");
        c = tolower(_mygetc());
        switch(c)
        {
        case EOF:
            my_exit_success();
        case 'h':
        case '\t':
            cls();
            puts("Commands:");
            puts("h, Tab - help;");
            puts("a - left;");
            puts("Esc, g - exit;");
            puts("Enter, n, Space - next;");
            puts("b, |, \\ - build/active;");
            puts("k, l, :, ; - attack army;");
            puts("v - version;");
            puts("c - creators;");
            pause();
            break;
        case ESC:
        case 'g':
            diediedie(0);
        case 'a':
            if(posx == 0)
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
        case 'w':
            if(posy == 0)
                posy = MAP_HEIGHT - 1;
            else
                posy--;
            break;
        case 'd':
            if(posx == MAP_WIDTH - 1)
                posx = 0;
            else
                posx++;
            break;
        case 'n':
        case '\n':
        case ENTER:
        case ' ':
            cls();
            if(readYesNo("Do you already want to next") == 'y')
            {
                switch(strvals.nowIs)
                {
                case c_red:
                    strvals.redMoney += getCoutOfCitiesByCommand(c_red) * MONEY_PER_CITY;
                    break;
                case c_blue:
                    strvals.blueMoney += getCoutOfCitiesByCommand(c_blue) * MONEY_PER_CITY;
                    break;
                default:
                    error("Unknown command");
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
                    if(readYesNo("Do you want to build city") == 'y')
                    {
                        if(!subCurrentMoney(NEED_MONEY_TO_BUILD_CITY))
                            message("You can\'t build city!");
                        else
                            map[posx][posy].tl = tl_city;
                    }
                    break;
                case tl_city:
                    if(readYesNo("Do you want to buy army") == 'y')
                    {
                        if(!subCurrentMoney(NEED_MONEY_TO_BUY_ARMY))
                            message("You can\'t buy army!");
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
                        if(c == 'W')
                        {
                            if(!setArmyTo(posx, posy - 1, map[posx][posy].l.xp))
                                message("You can\'t set army here!");
                            else
                                map[posx][posy].tl = (map[posx][posy].tl == tl_army ? tl_land : tl_city);
                        }
                        if(c == 'S')
                        {
                            if(!setArmyTo(posx, posy + 1, map[posx][posy].l.xp))
                                message("You can\'t set army here!");
                            else
                                map[posx][posy].tl = (map[posx][posy].tl == tl_army ? tl_land : tl_city);
                        }
                        if(c == 'A')
                        {
                            if(!setArmyTo(posx - 1, posy, map[posx][posy].l.xp))
                                message("You can\'t set army here!");
                            else
                                map[posx][posy].tl = (map[posx][posy].tl == tl_army ? tl_land : tl_city);
                        }
                        if(c == 'D')
                        {
                            if(!setArmyTo(posx + 1, posy, map[posx][posy].l.xp))
                                message("You can\'t set army here!");
                            else
                                map[posx][posy].tl = (map[posx][posy].tl == tl_army ? tl_land : tl_city);
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
                    if(c == 'W')
                    {
                        if(!attackArmyTo(posx, posy, posx, posy - 1))
                            message("You can\'t attack here!");
                    }
                    if(c == 'A')
                    {
                        if(!attackArmyTo(posx, posy, posx - 1, posy))
                            message("You can\'t attack here!");
                    }
                    if(c == 'S')
                    {
                        if(!attackArmyTo(posx, posy, posx, posy + 1))
                            message("You can\'t attack here!");
                    }
                    if(c == 'D')
                    {
                        if(!attackArmyTo(posx, posy, posx + 1, posy))
                            message("You can\'t attack here!");
                    }
                }
                else
                    message("This army is not active!");
            }
            else
                message("This is not army!");
            break;
        case 'v':
            message("Tactics v. 0.1.0");
            break;
        case 'c':
            message("Create by Kutlahmetov Iskander!");
            break;
        }
    }
    my_exit_success();
}
