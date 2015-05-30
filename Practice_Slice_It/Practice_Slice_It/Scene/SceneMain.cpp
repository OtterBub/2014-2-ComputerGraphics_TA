#include "SceneMain.h"

#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneGameEasyVer.h"
#include "SceneGameCompleteClipping.h"


SceneMain::SceneMain()
{
}

SceneMain::~SceneMain()
{

}

void SceneMain::Enter()
{

}

void SceneMain::Exit()
{

}

void SceneMain::Draw()
{



	for( int i = 0; i < 3; ++i )
	{
		glBegin( GL_LINE_LOOP );
		glVertex2f( -120, 45 - ( 60 * i ) );
		glVertex2f( 120, 45 - ( 60 * i ) );
		glVertex2f( 120, 100 - ( 60 * i ) );
		glVertex2f( -120, 100 - ( 60 * i ) );
		glEnd();
	}
	DrawStrokeText( "Slice It!!", -120, 200, 0, 0.5 );
	DrawStrokeText( "PSK", 110, 180, 0, 0.1 );

	DrawStrokeText( "EasyVer", -100, 60, 0, 0.3 );
	DrawStrokeText( "RealSliceVer", -100, 0, 0, 0.3 );
	DrawStrokeText( "ClippingTest", -100, -60, 0, 0.3 );
}

void SceneMain::Update( double dt )
{

}

void SceneMain::Reshape( int w, int h )
{
	mClientWidth = w;
	mClientHeight = h;
}

void SceneMain::Mouse( int button, int state, int x, int y )
{
	Vector2 lMousePos;
	lMousePos.x = ( x - ( mClientWidth / 2.f ) );
	lMousePos.y = -( y - ( mClientHeight / 2.f ) );
	switch( state )
	{
		case GLUT_DOWN:
			switch( button )
			{
				case GLUT_LEFT_BUTTON:
					for( int i = 0; i < 3; ++i )
					{
						if( lMousePos.x < 120 &&
							lMousePos.x > -120 &&
							lMousePos.y < 100 - ( 60 * i ) &&
							lMousePos.y > 45 - ( 60 * i ) )
						{
							SKCONSOLE << std::to_string( i );
							switch( i )
							{
								case 0:
									SceneManager::GetInstance()->SceneChange( std::shared_ptr<SceneGameEasyVer> ( new SceneGameEasyVer() ) );
									return;

								case 1:
									SceneManager::GetInstance()->SceneChange( std::shared_ptr<SceneGame> ( new SceneGame() ) );
									return;

								case 2:
									SceneManager::GetInstance()->SceneChange( std::shared_ptr<SceneGameCompleteClipping> ( new SceneGameCompleteClipping() ) );
									return;
							}
						}
						
					}
					break;
			}
			break;
	}
}

void SceneMain::MouseMotion( int x, int y )
{

}