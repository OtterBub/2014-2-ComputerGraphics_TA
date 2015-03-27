#include "SceneGame.h"
#include "SceneManager.h"
#include "SceneMain.h"

SceneGame::SceneGame()
{
	mUpdateControlShape = false;
	mMouseDrag = false;
	mSceneName = "GameScene";
}

SceneGame::~SceneGame()
{

}

void SceneGame::Enter()
{
	float lRectSize = ( rand() % 300 - 150 ) + 200;
	mControlShape = std::shared_ptr<ObjectShape>( new ObjectShape( lRectSize ) );
	mControlShape->SetPosition( Vector3( 200, -50, 0 ) );
	Scene::AddObject( std::shared_ptr<Object>( mControlShape ) );

	mGoalShape = std::shared_ptr<ObjectShape>( new ObjectShape( lRectSize / 2.f ) );
	mGoalShape->SetPosition( Vector3( -200, -50, -0.1 ) );

	// Random Wall Direction
	std::vector< Vector3 > lList = mGoalShape->GetWorldPoints();
	std::vector< Vector3 >::iterator lListIt = lList.begin();
	int lRandomNum = rand() % 10;

	// Shuffle Vertex
	for( int i = 0; i < lRandomNum; ++i )
	{
		if( lListIt != lList.end() )
			lListIt++;
		else
			lListIt = lList.begin();
	}

	for( int i = 0; i < lList.size() + 1; ++i )
	{

		if( lListIt != lList.end() )
		{
			mGoalColiisionShapeList.push_back( *lListIt );
			lListIt++;
		}
		else
			lListIt = lList.begin();
	}
	mGoalColiisionShape = std::shared_ptr<ObjectShape>( new ObjectShape() );
	mGoalColiisionShape->SetPointList( mGoalColiisionShapeList, false );

	std::vector< Vector3 > lEmptyList;
	mClippingShape = std::shared_ptr<ObjectShape>( new ObjectShape() );
	mClippingShape->SetPointList( lEmptyList );
	mClippingShape->SetPosition( Vector3( 0, 0, 1 ) );
	mClippingShape->SetColor( Vector4( 1, 0, 0, 1 ) );
}

void SceneGame::Exit()
{

}

void SceneGame::Draw()
{
	// Default DrawFunc
	Scene::Draw();
	mGoalShape->Draw();
	mClippingShape->Draw();

	glPushMatrix();
	{
		// Wall Draw
		glLineWidth( 10 );
		glColor4f( 0, 1, 0, 1 );
		glTranslatef( 0, 0, 0.1 );
		glBegin( GL_LINE_STRIP );
		for( Vector3 it : mGoalColiisionShapeList )
		{
			glVertex3fv( reinterpret_cast<GLfloat*>( &it ) );
		}
		glEnd();
		glLineWidth( 1 );
	}
	glPopMatrix();
	

	// Slice Line Draw
	if( mMouseDrag )
	{
		glPushMatrix();
		{
			glColor4f( 1, 1, 1, 1 );
			glTranslatef( 0.f, 0.f, 0.9f );
			glBegin( GL_LINES );
			glVertex2f( mMouseLineStart.x, mMouseLineStart.y );
			glVertex2f( mMouseLineEnd.x, mMouseLineEnd.y );
			glEnd();
		}
		glPopMatrix();
	}
	
	// Entry Point, Exit Point Draw
	float lRectSize = 10;
	for( Vector3 it : mEntryPoint )
	{
		glPushMatrix();
		{
			glTranslatef( it.x, it.y, 0.6 );

			glColor3f( 1.f, 1.f, 0.f );
			glRectf( -( lRectSize / 2.f ), -( lRectSize / 2.f ),
					 ( lRectSize / 2.f ), ( lRectSize / 2.f ) );
		}
		glPopMatrix();
	}

	for( Vector3 it : mExitPoint )
	{
		glPushMatrix();
		{
			glTranslatef( it.x, it.y, 0.6 );

			glColor3f( 1.f, 1.f, 0.f );
			glRectf( -( lRectSize / 2.f ), -( lRectSize / 2.f ),
					 ( lRectSize / 2.f ), ( lRectSize / 2.f ) );
		}
		glPopMatrix();
	}

	// Draw MainMenu Button
	glDisable( GL_DEPTH_TEST );

	glColor4f( 1, 1, 1, 1 );
	glBegin( GL_LINE_LOOP );
	glVertex2f( ( mClientWidth / 2.f ) - 150, -( mClientHeight / 2.f ) );
	glVertex2f( ( mClientWidth / 2.f ), -( mClientHeight / 2.f ) );
	glVertex2f( ( mClientWidth / 2.f ), -( mClientHeight / 2.f ) + 30 );
	glVertex2f( ( mClientWidth / 2.f ) - 150, -( mClientHeight / 2.f ) + 30 );
	glEnd();
	DrawStrokeText( "MainMenu", ( mClientWidth / 2.f ) - 150, -( mClientHeight / 2.f ), 0, 0.25 );

	glEnable( GL_DEPTH_TEST );
}

void SceneGame::Update( double dt )
{
	// Default UpdateFunc
	Scene::Update( dt );

	if( mUpdateControlShape )
	{
		float lArea = FLT_MAX;

		for( std::shared_ptr<Object> it : mObjectVec )
		{
			std::shared_ptr<ObjectShape> lobj = std::dynamic_pointer_cast<ObjectShape>( it );
			if( lobj )
			{
				if( lobj->GetArea() < lArea )
				{
					lArea = lobj->GetArea();
					mControlShape = lobj;
					SKCONSOLE << "Change Control Shape";
				}
			}
		}
		mUpdateControlShape = false;
	}

	if( mControlShape && mGoalShape )
		ClippingObject( mControlShape, mGoalShape );
}

void SceneGame::Reshape( int w, int h )
{
	// Default ReshapeFunc
	Scene::Reshape( w, h );
	mClientWidth = w;
	mClientHeight = h;

}

// ------------------ INPUT ------------------
void SceneGame::KeyBoard( unsigned char key, int x, int y ) 
{
	Vector3 lControlOriginPosition = mControlShape->GetPosition();
	Vector3 lControlOriginScale = mControlShape->GetScale();
	switch( key )
	{
		case 'a':
			if( mControlShape )
				mControlShape->Translate( Vector3( -10, 0, 0 ) );
			break;
		case 'd':
			if( mControlShape )
				mControlShape->Translate( Vector3( +10, 0, 0 ) );
			break;
		case 's':
			if( mControlShape )
				mControlShape->Translate( Vector3( 0, -10, 0 ) );
			break;
		case 'w':
			if( mControlShape )
				mControlShape->Translate( Vector3( 0, +10, 0 ) );
			break;

		case 'r':
			mControlShape->Scale( Vector3( -0.05, -0.05, -0.05 ) );
			break;
		case 'R':
			mControlShape->Scale( Vector3( 0.05, 0.05, 0.05 ) );
			break;
	}

	switch( key ) 
	{
		case 'a':
		case 'd':
		case 's':
		case 'w':
		case 'r':
		case 'R':
			if( mGoalColiisionShape && mControlShape )
			{
				int lCrossPointSize = FindCrossPointObjectToObject( mControlShape, mGoalColiisionShape, true, false ).size();
				if( lCrossPointSize > 0 )
				{
					mControlShape->SetPosition( lControlOriginPosition );
					mControlShape->SetScale( lControlOriginScale );
				}
			}
			break;
	}
	
}

void SceneGame::KeyBoardUp( unsigned char key, int x, int y ) 
{
}

void SceneGame::KeyBoardSpecial( int key, int x, int y ) 
{
}

void SceneGame::KeyBoardSpecialUp( int key, int x, int y ) 
{
}

void SceneGame::Mouse( int button, int state, int x, int y ) 
{
	Vector2 lMousePos;
	lMousePos.x = ( x - ( mClientWidth / 2.f ) );
	lMousePos.y = -( y - ( mClientHeight / 2.f ) );

	if( state == GLUT_DOWN )
	{
		DrawStrokeText( "MainMenu", ( mClientWidth / 2.f ) - 150, -( mClientHeight / 2.f ), 0, 0.25 );
		if( lMousePos.x > ( mClientWidth / 2.f ) - 150 &&
			lMousePos.x < ( mClientWidth / 2.f ) &&
			lMousePos.y > -( mClientHeight / 2.f ) &&
			lMousePos.y < -( mClientHeight / 2.f ) + 30)
		{
			SceneManager::GetInstance()->SceneChange( std::shared_ptr<SceneMain> ( new SceneMain() ) );
			return;
		}
	}
	

	switch( button )
	{
		case GLUT_LEFT_BUTTON:
			switch( state )
			{
				case GLUT_DOWN:
					mMouseDrag = true;
					mMouseLineStart.x = lMousePos.x;
					mMouseLineStart.y = lMousePos.y;
					mMouseLineEnd = mMouseLineStart;

					break;
				case GLUT_UP:
					mMouseDrag = false;
					mUpdateControlShape = true;
					mEntryPoint.clear();
					mExitPoint.clear();
					for( std::shared_ptr<Object> it : mObjectVec )
					{
						std::shared_ptr<ObjectShape> lobj = std::dynamic_pointer_cast<ObjectShape>( it );
						if( lobj )
						{
							mCrossPoint2 = FindCrossPointObjectToLine( lobj, mMouseLineStart, mMouseLineEnd );

							if( mCrossPoint2.size() >= 2 )
							{
								Vector3 lEntryPoint = mCrossPoint2.begin()->second;
								Vector3 lExitPoint = ( ++mCrossPoint2.begin() )->second;
								
								SliceObject( lobj, lEntryPoint, lExitPoint );

								mEntryPoint.push_back( lEntryPoint );
								mExitPoint.push_back( lExitPoint );
							}
						}
					}
					break;
			}
			break;
	}
}

void SceneGame::MouseMotion( int x, int y ) 
{
	if( mMouseDrag )
	{
		mMouseDrag = true;
		mMouseLineEnd.x = ( x - ( mClientWidth / 2.f ) );
		mMouseLineEnd.y = -( y - ( mClientHeight / 2.f ) );
	}
}

void SceneGame::SendCommand( std::string command )
{
	if( ( command == "reset" ) || command == "r" )
	{
		SceneManager::GetInstance()->SceneChange( std::shared_ptr< SceneGame >( new SceneGame() ) );
	}
}

// 2D CrossPoint
Vector3 SceneGame::FindCrossPoint( Vector3 LineStart1, Vector3 LineEnd1,
							Vector3 LineStart2, Vector3 LineEnd2 )
{
	float lUnder = ( ( LineEnd2.y - LineStart2.y) * ( LineEnd1.x - LineStart1.x ) ) - ( ( LineEnd2.x - LineStart2.x ) * ( LineEnd1.y - LineStart1.y ) );
	float lTUp = ( ( LineEnd2.x - LineStart2.x ) * ( LineStart1.y - LineStart2.y ) ) - ( ( LineEnd2.y - LineStart2.y ) * ( LineStart1.x - LineStart2.x ) );
	float lSUp = ( ( LineEnd1.x - LineStart1.x ) * ( LineStart1.y - LineStart2.y ) ) - ( ( LineEnd1.y - LineStart1.y ) * ( LineStart1.x - LineStart2.x ) );

	if( lUnder == 0 ) return Vector3();

	float lT = lTUp / lUnder;
	float lS = lSUp / lUnder;

	if( lT < 0.0 || lT > 1.0 || lS < 0.0 || lS > 1.0 ) return Vector3();
	if( lTUp == 0 && lSUp == 0 ) return Vector3();

	Vector3 result;

	result.x = LineStart1.x + ( lT * ( LineEnd1.x - LineStart1.x ) );
	result.y = LineStart1.y + ( lT * ( LineEnd1.y - LineStart1.y ) );

	return result;
}

std::map< float, Vector3 > SceneGame::FindCrossPointObjectToLine( std::shared_ptr<ObjectShape> obj, Vector3 LineStart, Vector3 LineEnd )
{
	std::vector< Vector3 > lPoint = obj->GetWorldPoints();
	std::vector< Vector3 >::iterator lIt = lPoint.begin();

	std::map< float, Vector3 > lCrossPoint;
	if( lPoint.size() >= 2 )
	{

		while( lIt != lPoint.end() )
		{
			Vector3 lObjectPoint1, lObjectPoint2;

			if( lIt != lPoint.end() )
			{
				lObjectPoint1 = *lIt;
			}
			else
				continue;

			lIt++;

			if( lIt != lPoint.end() )
			{
				lObjectPoint2 = *lIt;
			}
			else if( lPoint.size() == 2 )
			{
				break;
			}
			else
			{
				lObjectPoint2 = *lPoint.begin();
			}

			Vector3 lResult;
			lResult = FindCrossPoint( LineStart, LineEnd,
									  lObjectPoint1, lObjectPoint2 );
			float lDistance = sqrtf( powf( lResult.x - LineStart.x, 2 ) + 
									 powf( lResult.y - LineStart.y, 2 ) +
									 powf( lResult.z - LineStart.z, 2 ));

			if( lResult.x != 0 ||
				lResult.y != 0 ||
				lResult.z != 0 )
			{
				//mCrossPoint.push_back( lResult );
				lCrossPoint[lDistance] = lResult;
			}

		}
	}

	return lCrossPoint;
}

std::map< float, Vector3 > SceneGame::FindCrossPointObjectToObject( std::shared_ptr<ObjectShape> obj1, std::shared_ptr<ObjectShape> obj2, bool obj1Loop, bool obj2Loop )
{
	std::vector< Vector3 > lPoint1 = obj1->GetWorldPoints();
	std::vector< Vector3 >::iterator lIt1 = lPoint1.begin();
	std::vector< Vector3 > lPoint2 = obj2->GetWorldPoints();
	std::vector< Vector3 >::iterator lIt2 = lPoint2.begin();

	std::map< float, Vector3 > lCrossPoint;
	if( lPoint1.size() >= 2 )
	{

		while( lIt1 != lPoint1.end() )
		{
			Vector3 lObjectPoint1, lObjectPoint2;

			if( lIt1 != lPoint1.end() )
				lObjectPoint1 = *lIt1;

			else
				continue;

			lIt1++;

			if( lIt1 != lPoint1.end() )
				lObjectPoint2 = *lIt1;

			else if( lPoint1.size() == 2 || ( obj1Loop == false ) )
				break;

			else
				lObjectPoint2 = *lPoint1.begin();

			lIt2 = lPoint2.begin();
			while( lIt2 != lPoint2.end() )
			{
				Vector3 lObjectPoint3, lObjectPoint4;

				if( lIt2 != lPoint2.end() )
					lObjectPoint3 = *lIt2;

				else
					continue;

				lIt2++;

				if( lIt2 != lPoint2.end() )
					lObjectPoint4 = *lIt2;

				else if( lPoint2.size() == 2 || ( obj2Loop == false ) )
					break;

				else
					lObjectPoint4 = *lPoint2.begin();

				Vector3 lResult;
				lResult = FindCrossPoint( lObjectPoint1, lObjectPoint2,
										  lObjectPoint3, lObjectPoint4 );
				float lDistance = sqrtf( powf( lResult.x - lObjectPoint1.x, 2 ) +
										 powf( lResult.y - lObjectPoint1.y, 2 ) +
										 powf( lResult.z - lObjectPoint1.z, 2 ) );

				if( lResult.x != 0 ||
					lResult.y != 0 ||
					lResult.z != 0 )
				{
					for( std::pair< float, Vector3 > it : lCrossPoint )
					{
						if( it.first == lDistance )
							lDistance += 0.000000000001;
					}
					lCrossPoint[lDistance] = lResult;
				}
			}
		}
	}

	return lCrossPoint;
}

void SceneGame::SliceObject( std::shared_ptr<ObjectShape> obj, Vector3 SliceStart, Vector3 SliceEnd )
{
	Vector3 lObjectPos = obj->GetPosition();
	Vector3 lSlicePointStart = SliceStart;
	Vector3 lSlicePointEnd = SliceEnd;

	std::vector< Vector3 > lPoint = obj->GetWorldPoints();
	std::vector< Vector3 > lOtherObjectVertex1;
	std::vector< Vector3 > lOtherObjectVertex2;

	Vector3 lSliceCenter;
	lSliceCenter.x = ( lSlicePointStart.x + lSlicePointEnd.x ) / 2.f;
	lSliceCenter.y = ( lSlicePointStart.y + lSlicePointEnd.y ) / 2.f;

	float lRayAngle = atan2( lSlicePointStart.y - lSlicePointEnd.y, lSlicePointStart.x - lSlicePointEnd.x );
	for( Vector3 it : lPoint )
	{
		float lCutAngle = atan2( it.y - lSliceCenter.y, it.x - lSliceCenter.x ) - lRayAngle;
		if( lCutAngle < 3.14 * ( -1 ) )
		{
			lCutAngle += 2 * 3.14;
		}
		if( lCutAngle > 0 && lCutAngle <= 3.14 )
		{
			lOtherObjectVertex1.push_back( it );
		}
		else
		{
			lOtherObjectVertex2.push_back( it );
		}
	}

	lOtherObjectVertex1.push_back( lSlicePointStart );
	lOtherObjectVertex1.push_back( lSlicePointEnd );

	lOtherObjectVertex2.push_back( lSlicePointStart );
	lOtherObjectVertex2.push_back( lSlicePointEnd );

	std::shared_ptr < ObjectShape > lobj1 = std::shared_ptr< ObjectShape >( new ObjectShape() );
	std::shared_ptr < ObjectShape > lobj2 = std::shared_ptr< ObjectShape >( new ObjectShape() );
	Vector4 lColor;

	lColor.w = 1;
	lColor.x = rand() / (float)RAND_MAX;
	lColor.y = rand() / (float)RAND_MAX;
	lColor.z = rand() / (float)RAND_MAX;

	lobj1->SetPointList( lOtherObjectVertex1 );
	lobj1->SetColor( lColor );
	//lobj1->SetPosition( lObjectPos );
	
	lColor.w = 1;
	lColor.x = rand() / (float)RAND_MAX;
	lColor.y = rand() / (float)RAND_MAX;
	lColor.z = rand() / (float)RAND_MAX;
	
	lobj2->SetPointList( lOtherObjectVertex2 );
	lobj2->SetColor( lColor );
	//lobj2->SetPosition( lObjectPos );

	AddObject( lobj1 );
	AddObject( lobj2 );

	DeleteObject( obj );
}

void SceneGame::ClippingObject( std::shared_ptr<ObjectShape> obj, std::shared_ptr<ObjectShape> goalObject )
{
	std::vector< Vector3 > lObjectPoint = obj->GetWorldPoints();
	std::vector< Vector3 > lGoalPoint = goalObject->GetWorldPoints();
	std::vector< Vector3 > lClippingPoint;

	if( lGoalPoint.size() == 4 )
	{
		Vector3 Max, Min;

		Max.x = -FLT_MAX;
		Max.y = -FLT_MAX;
		Max.z = -FLT_MAX;

		Min.x = FLT_MAX;
		Min.y = FLT_MAX;
		Min.z = FLT_MAX;

		for( Vector3 it : lGoalPoint )
		{
			/*Max.x = ( Max.x > it.x ) ? Max.x : it.x;
			Max.y = ( Max.y > it.y ) ? Max.y : it.y;
			Max.z = ( Max.z > it.z ) ? Max.z : it.z;

			Min.x = ( Min.x < it.x ) ? Min.x : it.x;
			Min.y = ( Min.y < it.y ) ? Min.y : it.y;
			Min.z = ( Min.z < it.z ) ? Min.z : it.z;*/

			int lCrossNum = FindCrossPointObjectToLine( obj, Vector3( - ( mClientWidth / 2.f ) * 100, it.y, 0 ), it ).size();
			int lInShape = lCrossNum % 2;
			if( lInShape )
				lClippingPoint.push_back( it );
			
		}

		for( Vector3 it : lObjectPoint )
		{
			int lCrossNum = FindCrossPointObjectToLine( goalObject, Vector3( - ( mClientWidth / 2.f ) * 100, it.y, 0 ), it ).size();
			int lInShape = lCrossNum % 2;
			if( lInShape )
				lClippingPoint.push_back( it );
		}

		std::map< float, Vector3 > lCrossPoint = FindCrossPointObjectToObject( obj, goalObject );
		for( std::pair< float, Vector3 > it : lCrossPoint )
		{
			lClippingPoint.push_back( it.second );
		}
		mClippingShape->SetPointList( lClippingPoint );
	}
}