#ifndef __SCENEGAMECOMPLETECLIPPING_H__
#define __SCENEGAMECOMPLETECLIPPING_H__

#include "Scene.h"
#include "../Object/ObjectShape.h"
#include <list>
#include <map>

class SceneGameCompleteClipping : public Scene
{
public:
	SceneGameCompleteClipping();
	~SceneGameCompleteClipping();

	void Enter();
	void Exit();
	void Draw();
	void Update( double dt );
	void Reshape( int w, int h );

	void KeyBoard( unsigned char key, int x, int y );
	void KeyBoardUp( unsigned char key, int x, int y);
	void KeyBoardSpecial( int key, int x, int y );
	void KeyBoardSpecialUp( int key, int x, int y );
	void Mouse( int button, int state, int x, int y );
	void MouseMotion( int x, int y );

	Vector3 FindCrossPoint( Vector3 LineStart1, Vector3 LineEnd1,
							Vector3 LineStart2, Vector3 LineEnd2 );
	std::map< float, Vector3 > FindCrossPointObjectToLine( std::shared_ptr<ObjectShape> obj, Vector3 LineStart, Vector3 LineEnd );
	std::map< float, Vector3 > FindCrossPointObjectToObject( std::shared_ptr<ObjectShape> obj1, std::shared_ptr<ObjectShape> obj2 );

	void SliceObject( std::shared_ptr<ObjectShape> obj, Vector3 SliceStart, Vector3 SliceEnd );
	void ClippingObject( std::shared_ptr<ObjectShape> obj, std::shared_ptr<ObjectShape> goalObject );

private:
	int mClientWidth, mClientHeight;
	bool mMouseDrag;
	bool mUpdateControlShape;
	bool mClipping;
	bool mGoal;

	Vector3 mMouseLineStart, mMouseLineEnd;

	std::shared_ptr<ObjectShape> mControlShape;
	std::shared_ptr<ObjectShape> mClippingShape;
	std::shared_ptr<ObjectShape> mGoalShape;

	std::map< float, Vector3 > mCrossPoint2;
	Vector3 mEntryPoint;
	Vector3 mExitPoint;
	Vector3 mSliceCenter;
};
#endif