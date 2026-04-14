#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{
	using RES = Resource;
	using RES_T = RES::TYPE;

	static std::string PATH_IMG = Application::PATH_IMAGE;
	static std::string PATH_MDL = Application::PATH_MODEL;
	static std::string PATH_EFF = Application::PATH_EFFECT;

	Resource* res;

	// タイトル画像
	res = new RES(RES_T::IMG, PATH_IMG + "Title.png");
	resourcesMap_.emplace(SRC::TITLE, res);

	// PUSH SPACE画像
	res = new RES(RES_T::IMG, PATH_IMG + "PushSpace.png");
	resourcesMap_.emplace(SRC::PUSH_SPACE, res);

	// PITFALLPLANET画像
	res = new RES(RES_T::MODEL, PATH_MDL + "Stage/PitfallPlanet/PitfallPlanet.mv1");
	resourcesMap_.emplace(SRC::PIT_FALL_PLANET, res);

	// SPEHERE PLANET画像
	res = new RES(RES_T::MODEL, PATH_MDL + "Stage/SpherePlanet/SpherePlanet.mv1");
	resourcesMap_.emplace(SRC::SPHERE_PLANET, res);

	// PLAYERモデル
	res = new RES(RES_T::MODEL, PATH_MDL + "Player/Player.mv1");
	resourcesMap_.emplace(SRC::PLAYER, res);

	// PLAYERアニメーション
	res = new RES(RES_T::MODEL, PATH_MDL + "Player/Idle.mv1");
	resourcesMap_.emplace(SRC::PLAYER_IDLE, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Player/Run.mv1");
	resourcesMap_.emplace(SRC::PLAYER_RUN, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Player/FastRun.mv1");
	resourcesMap_.emplace(SRC::PLAYER_FAST_RUN, res);

	// プレイヤー影
	res = new RES(RES_T::IMG, PATH_IMG + "Shadow.png");
	resourcesMap_.emplace(SRC::PLAYER_SHADOW, res);

	// MAIN_STAGEモデル
	res = new RES(Resource::TYPE::MODEL, PATH_MDL + "Stage/MainStage/MainStage.mv1");
	resourcesMap_.emplace(SRC::MAIN_STAGE, res);

	// SKY_DOMEモデル
	res = new RES(Resource::TYPE::MODEL, PATH_MDL + "SkyDome/SkyDome.mv1");
	resourcesMap_.emplace(SRC::SKY_DOME, res);

	// ENEMY_RATモデル
	res = new RES(Resource::TYPE::MODEL, PATH_MDL + "Enemy/Rat/Rat.mv1");
	resourcesMap_.emplace(SRC::ENEMY_RAT, res);
}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	for (auto& res : resourcesMap_)
	{
		res.second->Release();
		delete res.second;
	}
	resourcesMap_.clear();
	delete instance_;
}

const Resource& ResourceManager::Load(SRC src)
{
	const Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
}

Resource& ResourceManager::_Load(SRC src)
{

	// ロード済みチェック
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return *resourcesMap_.find(src)->second;
	}

	// リソース登録チェック
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return dummy_;
	}

	// ロード処理
	rPair->second->Load();

	// 念のためコピーコンストラクタ
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;

}
