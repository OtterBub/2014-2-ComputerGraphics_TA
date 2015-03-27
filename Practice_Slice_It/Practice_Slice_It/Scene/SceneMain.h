#ifndef __SCENEMAIN_H__
#define __SCENEMAIN_H__

#include "Scene.h"

class SceneMain : public Scene
{
public:
	SceneMain();
	~SceneMain();

	void Enter();
	void Exit();
	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );

	void KeyBoard( unsigned char key, int x, int y ) {}
	void KeyBoardUp( unsigned char key, int x, int y) {}
	void KeyBoardSpecial( int key, int x, int y ) {}
	void KeyBoardSpecialUp( int key, int x, int y ) {}
	void Mouse( int button, int state, int x, int y );
	void MouseMotion( int x, int y );

private:
	int mClientWidth  ;
	int mClientHeight ;
};

#endif