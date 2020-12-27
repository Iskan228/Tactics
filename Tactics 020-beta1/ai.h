/* #ifndef _AI_H
	#define _AI_H 1

	#include "funcs.h"
	#include "GEngine.h"

	/* a better than b
	inline bool isBetterTFThan(type_field a, type_field b)
	{
		return a < b;
	}

	bool getDistFromOpponent(commands c, width_t x, height_t y, size_t *dist)
	{
		bool b;
		register width_t i, posx;
		register height_t j, posy;
		size_t maxdist;

		c = map[x][y].c;
		maxdist = MAP_WIDTH + MAP_HEIGHT;
		posx = 0;
		posy = 0;
		b = false;
		for(i = 0; i < MAP_WIDTH; i++)
		{
			for(j = 0; j < MAP_HEIGHT; j++)
			{
				if(map[i][j].c == c)
					continue;
				dist = LLABS(x - i) + LLABS(y - j);
				if(dist < maxdist)
				{
					posx = i;
					posy = j;
					b = true;
					maxdist = dist;
				}
			}
		}
		if(!b)
			return false;
		dist = maxdist;
		return true;
	}

	bool getBestPlaceForField(commands c, width_t *x, height_t *y)
	{
		size_t bestdist, dist;
		type_field best_tf;
		register bool b;
		register width_t i, posx;
		register height_t j, posy;

		b = false;
		best_tf = tf_die;
		bestdest = 0;
		for(i = 0; i < MAP_WIDTH; i++)
		{
			for(j = MAP_HEIGHT - 1; 1; j--)
			{
				if(getDistFromOpponent(c, i, j, &dist))
				{
					if(map[i][j].c == c && (isBetterTFThan(map[i][j].tf, best_tf) || (map[i][j].tf == best_tf && dist > bestdist)))
					{
						posx = i;
						posy = j;
						b = true;
						best_tf = map[i][j].tf;
						maxdist = bestdist;
					}
				}
			}
			if(!j)
				break;
		}
		if(!b)
			return false;
		x = posx;
		y = posy;
		return true;
	}

	bool getBestPlaceForCity(commands c, width_t *x, height_t *y)
	{
		type_field tf;
		bool b;
		size_t bestdist, dist;
		register width_t i, posx;
		register height_t j, posy;
		for(i = 0; i < MAP_WIDTH; i++)
		{
			for(j = 0; j < MAP_HEIGHT; j++)
			{
				if(getDistFromOpponent(c, i, j, &dist))
				{
					if(map[i][j].c == c && (!isBetterTFThan(map[i][j].tf, besttf) || (dist > bestdist && map[i][j].tf == besttf)))
					{
						besttf = map[i][j].tf;
						posx = i;
						posy = j;
						bestdist = dist;
					}
				}
			}
		}
		if(!b)
			return false;
		x = posx;
		y = posy;
		return true;
	}

	bool neqCommands(commands c, commands c1, commands c2, commands c3, commands c4, commands c5, commands c6, commands c7, commands c8)
	{
		if(c != c1)
			return true;
		if(c != c2)
			return true;
		if(c != c3)
			return true;
		if(c != c4)
			return true;
		if(c != c5)
			return true;
		if(c != c6)
			return true;
		if(c != c7)
			return true;
		if(c != c8)
			return true;
		return false;
	}

	bool enemiesAtBorder(commands c)
	{
		register width_t i;
		register height_t j;
		for(i = 1; i < MAP_WIDTH - 1; i++)
		{
			for(j = 1; j < MAP_HEIGHT - 1; j++)
			{
				if(neqCommands(map[i][j].c, map[i - 1][j - 1].c, map[i][j - 1].c, map[i + 1][j - 1].c, map[i - 1][j].c, map[i + 1][j].c, map[i - 1][j + 1].c, map[i][j + 1].c, map[i + 1][j + 1].c) && map[i][j].c != c && map[i][j].isArmy)
					return true;
			}
		}
		return false;
	}

	void runAI(commands c)
	{
		if(enemiesAtBorder(c))
			buyArmiesAI(c);
	}

	void buyArmiesAI(commands c)
	{
		
	}
#endif _AI_H */
