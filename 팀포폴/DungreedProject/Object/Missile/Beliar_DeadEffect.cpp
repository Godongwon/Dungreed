#include "stdafx.h"
#include "Beliar_DeadEffect.h"
Beliar_DeadEffect::Beliar_DeadEffect()
{
}
Beliar_DeadEffect::~Beliar_DeadEffect()
{
}
HRESULT Beliar_DeadEffect::init()
{
	_size_missile_width = 35;					//미사일 렉트 부피
	_size_missile_height = 35;					//미사일 렉트 높이
	_bDelete = false;
	_angle = NULL;
	_img_beliarDeadEffect = new image;
	_img_beliarDeadEffect->init("resource/image/Missile/DeadEffect.bmp",
		420 , 60 , 7, 1, true, RGB(255, 0, 255));
	_img_beliarDeadEffect->set_frameSection(1, 0, 6, 10, 1);
	return S_OK;
}

void Beliar_DeadEffect::release()
{
	_img_beliarDeadEffect->release();
	SAFE_DELETE(_img_beliarDeadEffect);
}

void Beliar_DeadEffect::update()
{
	if (_img_beliarDeadEffect->getFrameX() == 6)
	{
		_bDelete = true;
	}
	_img_beliarDeadEffect->frameUpdate(true);
}
void Beliar_DeadEffect::render()
{
	_img_beliarDeadEffect->frameRender(getMemDC(), _size_missile_rc.left, _size_missile_rc.top);
}
