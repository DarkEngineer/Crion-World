#ifndef Player_h
#define Player_h
#include "../Camera/Camera.h"
#include "../Object/Object.h"

class Player
{
	Object * body;
	struct
	{
		float speed; 
		float weight;
		int health;
		int level;
		int experience;
	} statistics;

public:
	Player();
	virtual ~Player();
};

#endif