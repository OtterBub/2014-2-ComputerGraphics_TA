#ifndef __GAMESYSTEM_H__
#define __GAMESYSTEM_H__

#include <Windows.h>
#include <stdlib.h>
#include <vector>
#include <memory>
#include <ctime>
#include "../Object/Object.h"
#include "ConsoleSystem.h"


// Singleton
class GameSystem
{
public:
	~GameSystem();
	static GameSystem* GetInstance();

	// DrawSystem
	void Init();
	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );
	void KeyBoard( unsigned char key, int x, int y );
	void KeyBoardUp( unsigned char key, int x, int y );
	void KeyBoardSpecial( int key, int x, int y );
	void KeyBoardSpecialUp( int key, int x, int y );
	void Mouse( int button, int state, int x, int y );
	void MouseMotion( int x, int y );

private:
	GameSystem();
	GameSystem( const GameSystem& other );

private:
	double mCurrentTime;
	double mDeltaTime;

	bool mActivateConsole;
};

#endif