#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneGame.h"
#include <string>
#include "../System/ConsoleSystem.h"

SceneManager::SceneManager()
{
	mCurrentScene = nullptr;
	SceneChange( std::shared_ptr< SceneMain >( new SceneMain() ) );
}

SceneManager::~SceneManager()
{

}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager inst;
	return &inst;
}

void SceneManager::Draw()
{
	if( mCurrentScene )
		mCurrentScene->Draw();
}

void SceneManager::Update( double dt )
{
	if( mCurrentScene )
		mCurrentScene->Update( dt );
}

void SceneManager::Reshape( int w, int h )
{
	if( mCurrentScene )
		mCurrentScene->Reshape( w, h );
	mClientWidth = w;
	mClientHeight = h;
}

void SceneManager::KeyBoard( unsigned char key, int x, int y )
{
	if( mCurrentScene )
		mCurrentScene->KeyBoard( key, x, y );
}

void SceneManager::KeyBoardUp( unsigned char key, int x, int y )
{
	if( mCurrentScene )
		mCurrentScene->KeyBoardUp( key, x, y );
}

void SceneManager::KeyBoardSpecial( int key, int x, int y )
{
	if( mCurrentScene )
		mCurrentScene->KeyBoardSpecial( key, x, y );
}

void SceneManager::KeyBoardSpecialUp( int key, int x, int y )
{
	if( mCurrentScene )
		mCurrentScene->KeyBoardSpecialUp( key, x, y );
}

void SceneManager::Mouse( int button, int state, int x, int y )
{
	if( mCurrentScene )
		mCurrentScene->Mouse( button, state, x, y );
}

void SceneManager::MouseMotion( int x, int y )
{
	if( mCurrentScene )
		mCurrentScene->MouseMotion( x, y );
}

void SceneManager::SendCommand( std::string command )
{
	if( mCurrentScene )
		mCurrentScene->SendCommand( command );
}

bool SceneManager::SceneChange( std::shared_ptr< Scene > otherScene )
{
	if( mCurrentScene && otherScene )
	{
		mCurrentScene->Exit();
		mCurrentScene = otherScene;
	}
	else if ( otherScene )
	{
		mCurrentScene = otherScene;
	}
	else
	{
		SKCONSOLE << "SceneChange Fail";
		return false;
	}
	std::string lConsoleStr = "SceneName: ";
	lConsoleStr += otherScene->GetSceneName();

	SKCONSOLE << "SceneChange Complete";
	SKCONSOLE << lConsoleStr;

	//SKCONSOLE << "SceneName: " << otherScene->GetSceneName() << std::endl;

	// Scene State Change, Enter
	if( otherScene )
	{
		otherScene->Enter();
		otherScene->Reshape( mClientWidth, mClientHeight );
	}
	return true;
}