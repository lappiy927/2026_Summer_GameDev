#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
//#include "../Manager/Camera.h"
#include "../Manager/ResourceManager.h"
#include "../Application.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
	:
	imgTitle_(-1),
	SceneBase()
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	// ‰æ‘œ“Ç‚İ‚İ
	imgTitle_ = resMng_.Load(ResourceManager::SRC::TITLE).handleId_;

}

void TitleScene::Update(void)
{
	// ƒV[ƒ“‘JˆÚ
	auto const& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		sceMng_.ChangeScene(SceneManager::SCENE_ID::GAME);
	}

	
}

void TitleScene::Draw(void)
{
	

}

void TitleScene::Release(void)
{
	
}