#ifndef Player_h
#define Player_h
#include "../Camera/Camera.h"
#include "../Object/Object.h"

class Player
{
	Object * body;
	Camera * player_camera;

	enum Status
	{
		STANDING,
		MOVING,
		RUNNING,
		DEAD,
		SHOOTING,
		SITTING
	} state;

	struct Statistics
	{
		float speed; 
		float weight;
		int health;
		int level;
		int experience;
	} statistics;

public:
	Player();
	
	virtual void create(const char * sourceMesh, const char * fileStructure);
	virtual void create(glm::vec3 positon, const char * sourceMesh, const char * fileStructure);
	virtual Object * getBody();
	virtual Camera * getCamera();
	virtual ~Player();
};

#endif