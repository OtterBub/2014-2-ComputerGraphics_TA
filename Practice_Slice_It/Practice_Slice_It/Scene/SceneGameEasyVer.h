#ifndef __SCENEGAMEEASYVER_H__
#define __SCENEGAMEEASYVER_H__

#include "Scene.h"
#include "../Object/ObjectShape.h"
#include <list>
#include <map>

class SceneGameEasyVer : public Scene
{
public:
	SceneGameEasyVer();
	~SceneGameEasyVer();

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
	void SendCommand( std::string command );

	Vector3 FindCrossPoint( Vector3 LineStart1, Vector3 LineEnd1,
							Vector3 LineStart2, Vector3 LineEnd2 );
	std::map< float, Vector3 > FindCrossPointObjectToLine( std::shared_ptr<ObjectShape> obj, Vector3 LineStart, Vector3 LineEnd );
	std::map< float, Vector3 > FindCrossPointObjectToObject( std::shared_ptr<ObjectShape> obj1, std::shared_ptr<ObjectShape> obj2, bool obj1Loop = true, bool obj2Loop = true );

	// Change return One Slice object
	std::shared_ptr<ObjectShape> SliceObject( std::shared_ptr<ObjectShape> obj, Vector3 SliceStart, Vector3 SliceEnd );
	void ClippingObject( std::shared_ptr<ObjectShape> obj, std::shared_ptr<ObjectShape> goalObject );

private:

	int mClientWidth, mClientHeight;
	int mSliceCount;
	bool mMouseDrag;
	bool mUpdateControlShape;
	bool mClipping;
	bool mGoal;

	Vector3 mMouseLineStart, mMouseLineEnd;

	std::shared_ptr<ObjectShape> mControlShape;
	std::shared_ptr<ObjectShape> mClippingShape;
	std::shared_ptr<ObjectShape> mGoalShape;
	std::shared_ptr<ObjectShape> mGoalColiisionShape;

	std::vector< Vector3 > mGoalColiisionShapeList;

	std::map< float, Vector3 > mCrossPoint2;
	std::vector< Vector3 > mEntryPoint;
	std::vector< Vector3 > mExitPoint;
	std::vector< Vector3 > mSliceCenter;
};
#endif