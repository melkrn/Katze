#ifndef BIRD2_H
#define BIRD2_H

#include "TileSet.h"
#include "Animation.h"
#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites
enum birdType
{
	NORMAL_BIRD2 = 55,
};
class Bird2 :public Object {
private:
	TileSet* bird = nullptr;
	Animation* anim = nullptr;
	Color color;

public:

	Bird2(float posX, float posY, Color tint);
	~Bird2();

	void Update();
	void Draw();
};


#endif // !BIRD2_H
