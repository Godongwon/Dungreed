#include "stdafx.h"
#include "stage.h"
#include"Object/Unit/player/Player.h"

stage::stage()
{
}

stage::~stage()
{
}

void stage::stage_Make(SCENE_KIND sceneKind)
{

	switch (sceneKind)
	{
	case START_SCENE:
		break;
	case TOWN_SCENE:
		ground = RectMake(0, 1020, 4200, WINSIZEY / 4);
		break;
	case MiNO_ROOM:
		ground = RectMake(0, 1090, 2371 / 2, WINSIZEY / 4);
		break;
	case NOMAL_ROOM:
		ground = RectMake(0, 437, 2781 / 2, WINSIZEY / 4);
		break;
	case BANSI_ROOM:
		ground = RectMake(0, 570, 2781 / 2, WINSIZEY / 4);
		break;
	case MAPTOOL:
		break;
	}
}

HRESULT stage::init()
{
	gameNode::init(true);

	//////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////


	return S_OK;
}

void stage::release()
{
}

void stage::update()
{

}

void stage::render()
{
	//Rectangle(getMemDC(), ground.left, ground.top, ground.right, ground.bottom);
}
