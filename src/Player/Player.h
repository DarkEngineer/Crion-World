#ifndef Player_h
#define Player_h
#include "../Camera/Camera.h"
#include "../Object/Object.h"

class Player : public Object
{
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

	bool bCreate;
public:
	Player();
	bool ifCreated(bool state);
	virtual Camera * getCamera();
	bool move(GLFWwindow * window, int key, int scancode, int action, int mods);
	bool getCreateStatus();
	virtual ~Player();
};

#endif