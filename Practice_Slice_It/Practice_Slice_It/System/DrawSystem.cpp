#include "DrawSystem.h"
#include <ctime>

DrawSystem::DrawSystem()
{
}

DrawSystem::~DrawSystem()
{
}

bool DrawSystem::Init()
{
	// Initialize OpenGL ( GLUT )
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( 1000, 600 );
	glutCreateWindow( "OpenGL Frame" );
	glutDisplayFunc( DrawSystem::DrawScene );
	glutReshapeFunc( DrawSystem::Reshape );
	glutKeyboardFunc( DrawSystem::KeyBoard );
	glutKeyboardUpFunc( DrawSystem::KeyBoardUp );
	glutSpecialFunc( DrawSystem::KeyBoardSpecial );
	glutSpecialUpFunc( DrawSystem::KeyBoardSpecialUp );
	glutMouseFunc( DrawSystem::Mouse );
	glutMotionFunc( DrawSystem::MouseMotion );

	// Set Timer
	glutTimerFunc( 10, DrawSystem::Timer, 0 );

	// Set Random Seed
	srand( (unsigned int)time( NULL ) );

	// Set OpenGL Draw Mode
	glEnable( GL_DEPTH_TEST );

	// GameSystem Initialize;
	GAMESYSTEM_INST->Init();

	return true;
}

bool DrawSystem::Run()
{
	glutMainLoop();
	return true;
} 

GLvoid DrawSystem::DrawScene( GLvoid )
{
	// Screen Clear
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Game Scene Draw
	GAMESYSTEM_INST->Draw();

	// Color Initializing
	glColor4f( 1, 1, 1, 1 );

	// Swap Double Buffer
	glutSwapBuffers();
}

GLvoid DrawSystem::Reshape( int w, int h )
{
	GAMESYSTEM_INST->Reshape( w, h );

	// DrawSystem Reshape
	glViewport( 0, 0, w, h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -( w / 2.f ), ( w / 2.f ), -( h / 2.f ), ( h / 2.f ), -1.0, 1.0 );
}

GLvoid DrawSystem::KeyBoard( unsigned char key, int x, int y )
{
	GAMESYSTEM_INST->KeyBoard( key, x, y );
}

GLvoid DrawSystem::KeyBoardUp( unsigned char key, int x, int y )
{
	GAMESYSTEM_INST->KeyBoardUp( key, x, y );
}

GLvoid DrawSystem::KeyBoardSpecial( int key, int x, int y )
{
	GAMESYSTEM_INST->KeyBoardSpecial( key, x, y );
}

GLvoid DrawSystem::KeyBoardSpecialUp( int key, int x, int y )
{
	GAMESYSTEM_INST->KeyBoardSpecialUp( key, x, y );
}

GLvoid DrawSystem::Mouse( int button, int state, int x, int y )
{
	GAMESYSTEM_INST->Mouse( button, state, x, y );
}

GLvoid DrawSystem::MouseMotion( int x, int y )
{
	GAMESYSTEM_INST->MouseMotion( x, y );
}

GLvoid DrawSystem::Timer( int Value )
{
	GAMESYSTEM_INST->Update( 0 );

	// Call Timer Function
	glutTimerFunc( 33, DrawSystem::Timer, 0 );

	// Call DisplayFunction
	glutPostRedisplay();
}