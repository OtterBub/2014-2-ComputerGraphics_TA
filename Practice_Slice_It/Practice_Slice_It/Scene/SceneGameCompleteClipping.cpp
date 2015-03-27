#include "SceneGameCompleteClipping.h"
#include "SceneManager.h"
#include "SceneMain.h"

SceneGameCompleteClipping::SceneGameCompleteClipping()
{
	mUpdateControlShape = false;
	mMouseDrag = false;
}

SceneGameCompleteClipping::~SceneGameCompleteClipping()
{

}

void SceneGameCompleteClipping::Enter()
{
	mControlShape = std::shared_ptr<ObjectShape>( new ObjectShape() );
	Vector3 lPos;
	lPos.x = 200;
	lPos.y = -50;
	mControlShape->SetPosition( lPos );
	Scene::AddObject( std::shared_ptr<Object>( mControlShape ) );

	mGoalShape = std::shared_ptr<ObjectShape>( new ObjectShape() );
	lPos.x = -200;
	lPos.y = -50;
	mGoalShape->SetPosition( lPos );

	std::vector< Vector3 > lEmptyList;
	mClippingShape = std::shared_ptr<ObjectShape>( new ObjectShape() );
	mClippingShape->SetPointList( lEmptyList );
	mClippingShape->SetPosition( Vector3( 0, 0, 1 ) );
	mClippingShape->SetColor( Vector4( 1, 0, 0, 1 ) );
}

void SceneGameCompleteClipping::Exit()
{

}

void SceneGameCompleteClipping::Draw()
{
	// Default DrawFunc
	Scene::Draw();
	mGoalShape->Draw();
	mClippingShape->Draw();

	// Slice Line Draw
	if( mMouseDrag )
	{
		glColor4f( 1, 1, 1, 1 );
		glBegin( GL_LINES );
		glVertex2f( mMouseLineStart.x, mMouseLineStart.y );
		glVertex2f( mMouseLineEnd.x, mMouseLineEnd.y );
		glEnd();
	}
	
	float lRectSize = 10;

	glPushMatrix();
	{
		glTranslatef( mEntryPoint.x, mEntryPoint.y, 0.6 );

		glColor3f( 1.f, 1.f, 0.f );
		float lRectSize = 7;
		glRectf( -( lRectSize / 2.f ), -( lRectSize / 2.f ),
				 ( lRectSize / 2.f ), ( lRectSize / 2.f ) );
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef( mExitPoint.x, mExitPoint.y, 0.6 );

		glColor3f( 1.f, 0.f, 1.f );
		float lRectSize = 7;
		glRectf( -( lRectSize / 2.f ), -( lRectSize / 2.f ),
				 ( lRectSize / 2.f ), ( lRectSize / 2.f ) );
	}
	glPopMatrix();

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

void SceneGameCompleteClipping::Update( double dt )
{
	// Default UpdateFunc
	Scene::Update( dt );

	if( mUpdateControlShape )
	{
		float lArea = FLT_MAX;
		//SKCONSOLE << "lAreaMAX:: " + std::to_string( lArea );

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

void SceneGameCompleteClipping::Reshape( int w, int h )
{
	// Default ReshapeFunc
	Scene::Reshape( w, h );
	mClientWidth = w;
	mClientHeight = h;

}

// ------------------ INPUT ------------------
void SceneGameCompleteClipping::KeyBoard( unsigned char key, int x, int y ) 
{
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
	}
}

void SceneGameCompleteClipping::KeyBoardUp( unsigned char key, int x, int y ) 
{
}

void SceneGameCompleteClipping::KeyBoardSpecial( int key, int x, int y ) 
{
}

void SceneGameCompleteClipping::KeyBoardSpecialUp( int key, int x, int y ) 
{
}

void SceneGameCompleteClipping::Mouse( int button, int state, int x, int y ) 
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
					for( std::shared_ptr<Object> it : mObjectVec )
					{
						std::shared_ptr<ObjectShape> lobj = std::dynamic_pointer_cast<ObjectShape>( it );
						if( lobj )
						{
							mCrossPoint2 = FindCrossPointObjectToLine( lobj, mMouseLineStart, mMouseLineEnd );

							if( mCrossPoint2.size() >= 2 )
							{
								mEntryPoint = mCrossPoint2.begin()->second;
								mExitPoint = ( ++mCrossPoint2.begin() )->second;

								SliceObject( lobj, mEntryPoint, mExitPoint );
							}
						}
					}
					break;
			}
			break;
	}
}

void SceneGameCompleteClipping::MouseMotion( int x, int y ) 
{
	if( mMouseDrag )
	{
		mMouseDrag = true;
		mMouseLineEnd.x = ( x - ( mClientWidth / 2.f ) );
		mMouseLineEnd.y = -( y - ( mClientHeight / 2.f ) );
	}
}

// 2D CrossPoint
Vector3 SceneGameCompleteClipping::FindCrossPoint( Vector3 LineStart1, Vector3 LineEnd1,
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

std::map< float, Vector3 > SceneGameCompleteClipping::FindCrossPointObjectToLine( std::shared_ptr<ObjectShape> obj, Vector3 LineStart, Vector3 LineEnd )
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

std::map< float, Vector3 > SceneGameCompleteClipping::FindCrossPointObjectToObject( std::shared_ptr<ObjectShape> obj1, std::shared_ptr<ObjectShape> obj2 )
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
			{
				lObjectPoint1 = *lIt1;
			}
			else
				continue;

			lIt1++;

			if( lIt1 != lPoint1.end() )
			{
				lObjectPoint2 = *lIt1;
			}
			else if( lPoint1.size() == 2 )
			{
				break;
			}
			else
			{
				lObjectPoint2 = *lPoint1.begin();
			}

			lIt2 = lPoint2.begin();
			while( lIt2 != lPoint2.end() )
			{
				Vector3 lObjectPoint3, lObjectPoint4;

				if( lIt2 != lPoint2.end() )
				{
					lObjectPoint3 = *lIt2;
				}
				else
					continue;

				lIt2++;

				if( lIt2 != lPoint2.end() )
				{
					lObjectPoint4 = *lIt2;
				}
				else if( lPoint2.size() == 2 )
				{
					break;
				}
				else
				{
					lObjectPoint4 = *lPoint2.begin();
				}

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
					//mCrossPoint.push_back( lResult );

					for( std::pair< float, Vector3 > it : lCrossPoint )
					{
						if( it.first == lDistance )
						{
							lDistance += 0.000000000001;
						}
					}
					lCrossPoint[lDistance] = lResult;
				}
			}
		}
	}

	return lCrossPoint;
}

void SceneGameCompleteClipping::SliceObject( std::shared_ptr<ObjectShape> obj, Vector3 SliceStart, Vector3 SliceEnd )
{
	Vector3 lObjectPos = obj->GetPosition();
	Vector3 lSlicePointStart = SliceStart;
	Vector3 lSlicePointEnd = SliceEnd;

	std::vector< Vector3 > lPoint = obj->GetWorldPoints();
	std::vector< Vector3 > lOtherObjectVertex1;
	std::vector< Vector3 > lOtherObjectVertex2;

	mSliceCenter.x = ( lSlicePointStart.x + lSlicePointEnd.x ) / 2.f;
	mSliceCenter.y = ( lSlicePointStart.y + lSlicePointEnd.y ) / 2.f;

	float lRayAngle = atan2( lSlicePointStart.y - lSlicePointEnd.y, lSlicePointStart.x - lSlicePointEnd.x );
	for( Vector3 it : lPoint )
	{
		float lCutAngle = atan2( it.y - mSliceCenter.y, it.x - mSliceCenter.x ) - lRayAngle;
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

void SceneGameCompleteClipping::ClippingObject( std::shared_ptr<ObjectShape> obj, std::shared_ptr<ObjectShape> goalObject )
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