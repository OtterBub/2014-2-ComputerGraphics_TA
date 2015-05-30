#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <iostream>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>

struct Vector2
{
	GLfloat x, y;
	
	Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2( GLfloat _x, GLfloat _y )
	{
		x = _x;
		y = _y;
	}
};

struct Vector3
{
	GLfloat x, y, z;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3( GLfloat _x, GLfloat _y, GLfloat _z )
	{
		x = _x;
		y = _y;
		z = _z;
	}
};

struct Vector4
{
	GLfloat x, y, z, w;

	Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}

	Vector4( GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _w )
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
};

class Object
{
public:
	Object();
	~Object();
	virtual void Draw() = 0;
	virtual void Update( double dt ) = 0;
	virtual void Reshape( int w, int h );

private:

};

#endif