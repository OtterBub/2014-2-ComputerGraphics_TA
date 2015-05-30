#ifndef __OBJECTRECT_H__
#define __OBJECTRECT_H__

#include "Object.h"
#include <vector>
#include <map>

class ObjectShape : public Object
{
public:
	ObjectShape();
	ObjectShape( float rectSize );
	~ObjectShape();

	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );

	void Translate( Vector3 trans );
	void Scale( Vector3 scale );
	void Rotate( Vector3 rot );

	void AddPoint( Vector3 point );

	void SetPosition( Vector3 Pos );
	void SetScale( Vector3 scale );
	void SetColor( Vector4 color );
	void SetPointList( std::vector< Vector3 > other, bool sort = true );

	Vector3 GetPosition();
	Vector3 GetScale();
	float GetArea();

	std::vector< Vector3 > GetPoints();
	std::vector< Vector3 > GetWorldPoints();

private:
	Vector3 mPosition;
	Vector3 mScale;
	Vector3 mRotate;
	Vector4 mColor;
	std::vector< Vector3 > mPoint;

	// Debug
	Vector3 mCentroid;
	float mArea;
};

#endif