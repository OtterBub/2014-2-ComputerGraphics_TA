#include "Scene.h"
#include <algorithm>

Scene::Scene()
{
	mSceneName = "NONE";
}
Scene::~Scene()
{
}

void Scene::Draw()
{
	Scene::ObjectDraw();
}

void Scene::Update( double dt )
{
	Scene::ObjectUpdate( dt );
	if( mDeleteObjVec.size() > 0 )
	{
		std::vector<std::shared_ptr<Object>>::iterator lDelObj;
		for( std::shared_ptr<Object> it : mDeleteObjVec )
		{
			lDelObj = std::find( mObjectVec.begin(), mObjectVec.end(), it );
			mObjectVec.erase( lDelObj );
		}
		mDeleteObjVec.clear();
	}
	if( mAddObjVec.size() > 0 )
	{
		std::vector<std::shared_ptr<Object>>::iterator lAddObj;
		for( std::shared_ptr<Object> it : mAddObjVec )
		{
			mObjectVec.push_back( it );
		}
		mAddObjVec.clear();
	}
}

void Scene::Reshape( int w, int h )
{
	Scene::ObjectReshape( w, h );
}

// For Object
void Scene::ObjectDraw()
{
	for( std::shared_ptr<Object> it : mObjectVec )
	{
		it->Draw();
	}
}

void Scene::ObjectUpdate( double dt )
{
	for( std::shared_ptr<Object> it : mObjectVec )
	{
		it->Update( dt );
	}
}

void Scene::ObjectReshape( int w, int h )
{
	for( std::shared_ptr<Object> it : mObjectVec )
	{
		it->Reshape( w, h );
	}
}

void Scene::AddObject( std::shared_ptr<Object> obj )
{
	mAddObjVec.push_back( obj );
}

void Scene::DeleteObject( std::shared_ptr<Object> obj )
{
	mDeleteObjVec.push_back( obj );
}

// ---------------- GETTER ----------------

std::string Scene::GetSceneName()
{
	return mSceneName;
}