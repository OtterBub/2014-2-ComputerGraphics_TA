#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Scene.h"

// Singleton
class SceneManager
{
public:
	~SceneManager();

	static SceneManager* GetInstance();

	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );
	void KeyBoard( unsigned char key, int x, int y );
	void KeyBoardUp( unsigned char key, int x, int y );
	void KeyBoardSpecial( int key, int x, int y );
	void KeyBoardSpecialUp( int key, int x, int y );
	void Mouse( int button, int state, int x, int y );
	void MouseMotion( int x, int y );
	void SendCommand( std::string command );

	bool SceneChange( std::shared_ptr< Scene > otherScene );

private:
	SceneManager();

private:
	std::shared_ptr< Scene > mCurrentScene;
	int mClientWidth, mClientHeight;

};

#endif