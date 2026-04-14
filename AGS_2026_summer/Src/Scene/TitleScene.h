#pragma once
#include "SceneBase.h"
class AnimationController;

class TitleScene : public SceneBase
{

public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void) override;

	// 初期化
	void Init(void) override;

	// 更新
	void Update(void) override;

	// 描画
	void Draw(void) override;

	// 解放
	void Release(void) override;

private:

	//タイトル画像のX,Y座標
	static constexpr int IMG_TITLE_POS_Y = 250;
	static constexpr int IMG_PUSH_POS_Y = 500;

	//画像ハンドル
	int imgTitle_;


	//アニメーション
	AnimationController* animationController_;

};