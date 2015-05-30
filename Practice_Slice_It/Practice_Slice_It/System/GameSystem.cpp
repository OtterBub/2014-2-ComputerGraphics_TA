#include "GameSystem.h"
#include "../Scene/SceneManager.h"

// other Scenes
#include "../Scene/SceneGame.h"
#include "../Scene/SceneGameEasyVer.h"

#include <iostream>
#include <string>

// Game Scene Instance
#define SCENEMGR_INST SceneManager::GetInstance()

GameSystem* GameSystem::GetInstance()
{
	static GameSystem* instance = new GameSystem();
	return instance;
}

GameSystem::GameSystem()
{
	mCurrentTime = clock();
	mDeltaTime = clock();

	mActivateConsole = false;
}

GameSystem::~GameSystem()
{
}

void GameSystem::Init()
{
	// SceneMgr Initailize
	SCENEMGR_INST;
}

void GameSystem::Draw()
{
	// Game Scene Draw
	SCENEMGR_INST->Draw();

	// Console Draw
	if( mActivateConsole )
		SKCONSOLE.Draw();
}

void GameSystem::Update( double dt )
{
	// Delta Time Calculator
	mDeltaTime = ( clock() - mCurrentTime ) / 1000.0;
	mCurrentTime = clock();

	// Game Scene Update
	SCENEMGR_INST->Update( mDeltaTime );
}

void GameSystem::Reshape( int w, int h )
{
	// Game Scene Reshape
	SCENEMGR_INST->Reshape( w, h );

	// Console Reshape
	SKCONSOLE.Reshape( w, h );
}

void GameSystem::KeyBoard( unsigned char key, int x, int y )
{
	std::string lCommand;
	std::string lTestStr;

	if( mActivateConsole && ( key != '`' ) && ( key != 13 ) && ( key != 8 ) )
		SKCONSOLE.AddCharToCurrentStr( key );

	switch( key )
	{
		case 13: // Enter
			if( mActivateConsole )
			{
				lCommand = SKCONSOLE.NextLine();
				//SKCONSOLE << "Activate Command Window";
			}
			break;

		case 8: // Back Space
			if( mActivateConsole )
			{
				//SKCONSOLE << "Back Space";
				SKCONSOLE.DeleteCharToCurrentStr();
			}
			break;

		case '`':
			mActivateConsole = !mActivateConsole;
			/*if( mActivateConsole )
			{
				SKCONSOLE << "Activate";
			}*/
			break;
	}

	if( mActivateConsole )
	{
		/*lTestStr += "Key: ";
		lTestStr += std::to_string( key );
		SKCONSOLE << lTestStr;*/

		bool lSceneChange = false;		

		if( lCommand == "1" )
			lSceneChange = SCENEMGR_INST->SceneChange( std::shared_ptr< SceneGame >( new SceneGame() ) );

		else if( lCommand == "2" )
			lSceneChange = SCENEMGR_INST->SceneChange( std::shared_ptr< SceneGameEasyVer >( new SceneGameEasyVer() ) );

		if( lSceneChange )
		{
			mDeltaTime = clock();
			mCurrentTime = clock();
		}
	}

	if( !mActivateConsole )
		SCENEMGR_INST->KeyBoard( key, x, y );
	else
		SCENEMGR_INST->SendCommand( lCommand );
}

void GameSystem::KeyBoardUp( unsigned char key, int x, int y )
{
	SCENEMGR_INST->KeyBoardUp( key, x, y );
}

void GameSystem::KeyBoardSpecial( int key, int x, int y )
{
	SCENEMGR_INST->KeyBoardSpecial( key, x, y );
}

void GameSystem::KeyBoardSpecialUp( int key, int x, int y )
{
	SCENEMGR_INST->KeyBoardSpecialUp( key, x, y );
}

void GameSystem::Mouse( int button, int state, int x, int y )
{
	SCENEMGR_INST->Mouse( button, state, x, y );
}

void GameSystem::MouseMotion( int x, int y )
{
	SCENEMGR_INST->MouseMotion( x, y );
}