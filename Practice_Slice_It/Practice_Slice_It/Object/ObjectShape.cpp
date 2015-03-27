#include "ObjectShape.h"
#include <functional>
#include "../System/ConsoleSystem.h"

ObjectShape::ObjectShape( float rectSize )
{
	std::vector< Vector3 > lList;
	Vector3 lVector;

	float lRectHalfSize = rectSize / 2.f;
	
	/*for( int i = 0; i < 20; ++i )
	{
		lVector.x = rand() % 300;
		lVector.y = rand() % 300;
		lList.push_back( lVector );
	}*/

	lVector.x = lRectHalfSize;
	lVector.y = lRectHalfSize;
	lList.push_back( lVector );

	lVector.x = -lRectHalfSize;
	lVector.y = lRectHalfSize;
	lList.push_back( lVector );

	lVector.x = -lRectHalfSize;
	lVector.y = -lRectHalfSize;
	lList.push_back( lVector );

	lVector.x = lRectHalfSize;
	lVector.y = -lRectHalfSize;
	lList.push_back( lVector );

	mArea = 0;

	SetPointList( lList );

	mColor.x = 1.f;
	mColor.y = 1.f;
	mColor.z = 1.f;
	mColor.w = 1.f;

	mCentroid.x = 0;
	mCentroid.y = 0;
	mCentroid.z = 0;

	mScale.x = 1;
	mScale.y = 1;
	mScale.z = 1;
}

ObjectShape::ObjectShape()
{
	std::vector< Vector3 > lList;
	Vector3 lVector;

	float lRectSize = ( rand() % 400 - 200 ) + 400;
	float lRectHalfSize = lRectSize / 2.f;
	
	/*for( int i = 0; i < 20; ++i )
	{
		lVector.x = rand() % 300;
		lVector.y = rand() % 300;
		lList.push_back( lVector );
	}*/

	lVector.x = lRectHalfSize;
	lVector.y = lRectHalfSize;
	lList.push_back( lVector );

	lVector.x = -lRectHalfSize;
	lVector.y = lRectHalfSize;
	lList.push_back( lVector );

	lVector.x = -lRectHalfSize;
	lVector.y = -lRectHalfSize;
	lList.push_back( lVector );

	lVector.x = lRectHalfSize;
	lVector.y = -lRectHalfSize;
	lList.push_back( lVector );

	SetPointList( lList );

	mColor.x = 1.f;
	mColor.y = 1.f;
	mColor.z = 1.f;
	mColor.w = 1.f;

	mCentroid.x = 0;
	mCentroid.y = 0;
	mCentroid.z = 0;
	mArea = 0;

	mScale.x = 1;
	mScale.y = 1;
	mScale.z = 1;
}

ObjectShape::~ObjectShape()
{

}

void ObjectShape::Draw()
{
	glPushMatrix();
	{
		glTranslatef( mPosition.x, mPosition.y, mPosition.z );
		glRotatef( mRotate.x, 1.f, 0.f, 0.f );
		glRotatef( mRotate.y, 0.f, 1.f, 0.f );
		glRotatef( mRotate.z, 0.f, 0.f, 1.f );		
		glScalef( mScale.x, mScale.y, 1 );

		// TypeCast Vector4* To GLfloat*
		glColor4fv( reinterpret_cast< GLfloat* >(&mColor) );

		// Draw Shape
		glBegin( GL_POLYGON );
		for( Vector3 it : mPoint )
		{
			glVertex3fv( reinterpret_cast< GLfloat* >(&it) );
		}
		glEnd();

		// Draw Line Loop
		glLineWidth( 3 );
		glTranslatef( 0, 0, 0.5 );
		glColor4f( 1 - mColor.x, 1 - mColor.y, 1 - mColor.z, 1.f );
		glBegin( GL_LINE_LOOP );
		for( Vector3 it : mPoint )
		{
			glVertex3fv( reinterpret_cast< GLfloat* >(&it) );
		}
		glEnd();

		// Init LineWidth
		glLineWidth( 1 );

		// Debug
		/*glColor4f( 0.f, 1, 0.f, 1 );
		glRectf( mCentroid.x - 5, mCentroid.y - 5,  mCentroid.x + 5, mCentroid.y + 5 );*/
	}
	glPopMatrix();
}

void ObjectShape::Update( double dt )
{

}

void ObjectShape::Reshape( int w, int h )
{

}

void ObjectShape::AddPoint( Vector3 point )
{
	mPoint.push_back( point );
}

void ObjectShape::Translate( Vector3 trans )
{
	mPosition.x += trans.x;
	mPosition.y += trans.y;
	mPosition.z += trans.z;
}

void ObjectShape::Scale( Vector3 scale )
{
	mScale.x += scale.x;
	mScale.y += scale.y;
	mScale.z += scale.z;
}

void ObjectShape::Rotate( Vector3 rot )
{
	mRotate.x += rot.x;
	mRotate.y += rot.y;
	mRotate.z += rot.z;
}

// ----------- SETTER -----------

void ObjectShape::SetPosition( Vector3 Pos )
{
	mPosition = Pos;
}

void ObjectShape::SetScale( Vector3 scale )
{
	mScale = scale;
}

void ObjectShape::SetColor( Vector4 color )
{
	mColor = color;
}

void ObjectShape::SetPointList( std::vector< Vector3 > other, bool sort )
{
	mPoint.clear();

	mCentroid.x = 0;
	mCentroid.y = 0;
	mCentroid.z = 0;
	mArea = 0;

	Vector3 lMax, lMin;

	lMax.x = -FLT_MAX;
	lMax.y = -FLT_MAX;
	lMax.z = -FLT_MAX;

	lMin.x = FLT_MAX;
	lMin.y = FLT_MAX;
	lMin.z = FLT_MAX;

	for( Vector3 it : other )
	{
		lMax.x = ( lMax.x > it.x ) ?  lMax.x : it.x;
		lMax.y = ( lMax.y > it.y ) ?  lMax.y : it.y;
		lMax.z = ( lMax.z > it.z ) ?  lMax.z : it.z;
		
		lMin.x = ( lMin.x < it.x ) ?  lMin.x : it.x;
		lMin.y = ( lMin.y < it.y ) ?  lMin.y : it.y;
		lMin.z = ( lMin.z < it.z ) ?  lMin.z : it.z;
	}

	mCentroid.x = ( lMax.x + lMin.x ) / 2.f;
	mCentroid.y = ( lMax.y + lMin.y ) / 2.f;

	std::vector< Vector3 > lPoint = other;
	std::vector< Vector3 >::iterator lIt = lPoint.begin();

	// Get Area
	while( lIt != lPoint.end() )
	{
		Vector3 lObjectPoint1, lObjectPoint2;

		if( lIt != lPoint.end() )
			lObjectPoint1 = *lIt;

		else
			continue;

		lIt++;

		if( lIt != lPoint.end() )
			lObjectPoint2 = *lIt;

		else if ( lPoint.size() >= 2 )
			lObjectPoint2 = *lPoint.begin();

		else
			break;

		double lS = ( lObjectPoint1.x - mCentroid.x ) * ( lObjectPoint2.y - mCentroid.y ) 
				- ( lObjectPoint2.x - mCentroid.x ) * ( lObjectPoint1.y - mCentroid.y );
		lS = fabs( lS ) * 0.5f;
		
		mArea += lS;
	}
	mArea = fabs( mArea );

	mPoint.clear();

	if( !sort )
	{
		mPoint = other;
		return;
	}	
	
	// ReSet Middle Point
	mPosition.x = mCentroid.x;
	mPosition.y = mCentroid.y;

	// Sort Vertex
	std::map< float, Vector3 > lSort;
	for( Vector3 it : other )
	{
		float lAngle = atan2( it.y - mCentroid.y, it.x - mCentroid.x );
		lSort[lAngle] = it;	
	}

	for( std::pair< float, Vector3 > it : lSort )
	{
		it.second.x -= mCentroid.x;
		it.second.y -= mCentroid.y;

		mPoint.push_back(it.second);
	}
}

// ----------- GETTER -----------

Vector3 ObjectShape::GetPosition()
{
	return mPosition;
}

Vector3 ObjectShape::GetScale()
{
	return mScale;
}

float ObjectShape::GetArea()
{
	return mArea * mScale.x;
}

std::vector< Vector3 > ObjectShape::GetPoints()
{
	return mPoint;
}

std::vector< Vector3 > ObjectShape::GetWorldPoints()
{
	std::vector< Vector3 > lList;

	for( Vector3 it : mPoint )
	{
		it.x *= mScale.x;
		it.y *= mScale.y;
		it.z *= mScale.z;

		it.x += mPosition.x;
		it.y += mPosition.y;
		it.z += mPosition.z;

		lList.push_back( it );
	}

	return lList ;
}