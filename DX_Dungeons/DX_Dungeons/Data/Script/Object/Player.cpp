#include "Player.h"
#include "Quaternion.h"
#include "Config.h"

// 一旦enum化　あとで外部ファイル化
enum Anima
{
	IDLE = 1,
	RUN = 6,
	DODGE = 15,
	ATTACK_1 = 31,
	ATTACK_2 = 30,
	ATTACK_3 = 33,
	SKILL_1 = 38

};

namespace
{
	//////////////////////////
	// アクション関連
	//////////////////////////
	/// 通常攻撃
	// 攻撃モーション全体の時間
	constexpr int kAttackTime = 20;
	// 連続攻撃の入力可能開始時間
	constexpr int kAttackPrevTime = 8;
	// 攻撃中の押し出し時間
	constexpr int kPushStartInAttack = 10;
	constexpr int kPushEndInAttack = 15;
	// フレームあたりの攻撃の押し出し距離
	// 1,2撃目
	constexpr float kAttackPow = 5.0f;
	// 3撃目
	constexpr float kAttackLastPow = 15.0f;
	/// 回避
	// 回避時間
	constexpr int kDodgeTime = 18;
	// フレームあたりの回避距離
	constexpr float kDodgePow = 15.0f;
	/// スキル攻撃
	// スキル攻撃時間
	constexpr int kSkill_1Time = 40;

	//////////////////
	// クールタイム
	//////////////////
	// 通常攻撃
	constexpr int kAttackCoolMax = 20;
	// 回避
	constexpr int kDodgeCoolMax = 60;
	// スキル技
	constexpr int kSkill_1CoolMax = 90;

	/////////////////////////
	// アニメーション速度
	/////////////////////////
	// 停止
	constexpr int kIdleSpeed = 5;
	// 通常攻撃
	constexpr int kAttackSpeed = 17;
	// 回避
	constexpr int kDodgeSpeed = 10;
	// スキル攻撃
	constexpr int kSkill_1Speed = 15;

	///////////////
	// モデル関係
	///////////////

	constexpr float kModelSize = 50;
}

Player::Player():
	m_attackCount(0),
	m_movePow(0.01f),
	m_dodgeCoolTimer(0),
	m_prevCount(0),
	m_attackCoolTimer(0),
	m_skillCoolTimer(0)
{
	m_handle = MV1LoadModel("Data/Model/Character/Knight.mv1");
	MV1SetScale(m_handle, VGet(50, 50, 50));
	m_animation.InitAnimation(m_handle, Anima::IDLE, 10, 0);
	m_dodgeVec = VGet(0, 0, 0);
	// UIハンドル
	m_hpBarHandle = LoadGraph("Data/Graph/BarV1_ProgressBar.png");
	m_handle_A = LoadGraph("Data/Graph/xbox_a_color_light.png");
	m_handle_B = LoadGraph("Data/Graph/xbox_b_color_light.png");
	m_handle_X = LoadGraph("Data/Graph/xbox_x_color_light.png");
}

Player::~Player()
{
	MV1DeleteModel(m_handle);
}

void Player::Init(VECTOR firstPos)
{
	m_pos = firstPos;
	MV1SetPosition(m_handle, m_pos);
	MV1SetRotationXYZ(m_handle, VGet(0, DX_PI_F, 0));

	///////////////////////
	// UI関連セットアップ
	///////////////////////
	UIInit();
}

void Player::Update(VECTOR cameraPos)
{
	// フレーム毎の移動量をリセット
	m_moveVecInFrame = VGet(0.0f, 0.0f, 0.0f);

	/////////////////
	// 入力時処理
	/////////////////
	inputUpdate(cameraPos);

	////////////////////
	// アニメーション
	////////////////////
	AnimationUpdate();


	////////////////////
	// 毎フレーム処理
	////////////////////
	StatusUpdate(cameraPos);


	// 移動量をまとめて更新
	m_pos = VAdd(m_pos, m_moveVecInFrame);
	// 壁の当たり判定
	HitWall(kModelSize);
	// モデルに移動を反映
	MV1SetPosition(m_handle, m_pos);

	// UI更新
	UIUpdate();
}

void Player::Draw() const
{
	// 位置反映
	MV1DrawModel(m_handle);
	
	////////////////
	// デバック文
	////////////////
	// 通常攻撃
	DrawFormatString(510, 10, 0xffffff, "%d", m_attackCount);
	DrawFormatString(500, 10, 0xffffff, "%d", m_prevCount);
	// キャラ動作状態
	if (m_state == State::IDLE)
	{
		DrawFormatString(500, 30, 0xffffff, "STATE : IDLE");
	}
	else if (m_state == State::ATTACK)
	{
		DrawFormatString(500, 30, 0xffffff, "STATE : ATTACK");
	}
	else if (m_state == State::DODGE)
	{
		DrawFormatString(500, 30, 0xffffff, "STATE : DODGE");
	}
	else if (m_state == State::MOVE)
	{
		DrawFormatString(500, 30, 0xffffff, "STATE : MOVE");
	}
	else if (m_state == State::SKILL)
	{
		DrawFormatString(500, 30, 0xffffff, "STATE : SKILL");
	}
	else if (m_state == State::DOWN)
	{
		DrawFormatString(500, 30, 0xffffff, "STATE : DOWN");
	}
	else if (m_state == State::NOCKBACK)
	{
		DrawFormatString(500, 30, 0xffffff, "STATE : KNOCKBACK");
	}
	// 簡易操作説明
	DrawFormatString(700, 10, 0xffffff, " カメラ移動 ： Rスティック");
	DrawFormatString(700, 30, 0xffffff, "　　移動　　： Lスティック");
	if (m_state == State::ATTACK || m_state == State::DODGE || m_state == State::SKILL)
	{
		DrawFormatString(700, 30, 0x303030, "　　移動　　： Lスティック");
	}
	DrawFormatString(700, 50, 0x303030, "　　攻撃　　： A（ %d／3段攻撃 ）( クールタイム：%d/%d )", m_attackCount, m_attackCoolTimer, kAttackCoolMax);
	if (m_attackCoolTimer >= kAttackCoolMax && m_state != State::DODGE && m_state != State::SKILL)
	{
		DrawFormatString(700, 50, 0xffffff, "　　攻撃　　： A（ %d／3段攻撃 ）( クールタイム：%d/%d )", m_attackCount, m_attackCoolTimer, kAttackCoolMax);
	}
	DrawFormatString(700, 70, 0x303030, "ステップ回避： B　( クールタイム：%d/%d )", m_dodgeCoolTimer, kDodgeCoolMax);
	if (m_dodgeCoolTimer >= kDodgeCoolMax && m_state != State::SKILL)
	{
		DrawFormatString(700, 70, 0xffffff, "ステップ回避： B　( クールタイム：%d/%d )", m_dodgeCoolTimer, kDodgeCoolMax);
	}
	DrawFormatString(700, 90, 0x303030, " スキル攻撃 ： X　( クールタイム：%d/%d )", m_skillCoolTimer, kSkill_1CoolMax);
	if (m_skillCoolTimer >= kSkill_1CoolMax && m_state != State::DODGE)
	{
		DrawFormatString(700, 90, 0xffffff, " スキル攻撃 ： X　( クールタイム：%d/%d )", m_skillCoolTimer, kSkill_1CoolMax);
	}
	DrawFormatString(700, 130, 0xffffff, "アクションタイマー：%d", m_actionTimer);

	DrawSphere3D(m_pos, kModelSize, 8, 0xff0000, 0xffffff, false);
}

void Player::inputUpdate(VECTOR cameraPos)
{
	////////////////////////////
	// 入力時処理
	////////////////////////////

	// 移動処理
	if ((m_config.GetStick(STICK_L).x != 0 || m_config.GetStick(STICK_L).y != 0) && m_state == State::IDLE)
	{
		m_state = State::MOVE;
	}
	else if (m_config.GetStick(STICK_L).x == 0 && m_config.GetStick(STICK_L).y == 0 && m_state == State::MOVE)
	{
		m_state = State::IDLE;
	}

	// 通常攻撃
	if (m_attackCoolTimer >= kAttackCoolMax)
	{
		if (m_config.GetInputStay(Input::A) && m_prevCount < Game::kAttackCountMax)
		{
			if (m_state == State::IDLE || m_state == State::MOVE)
			{
				m_state = State::ATTACK;
				SetPushVec(m_dir);
			}
			if (m_state == State::ATTACK)
				NormalAttack();
		}
	}
	if (m_attackCoolTimer < kAttackCoolMax)
	{
		m_attackCoolTimer++;
	}
	if ((m_attackCount != 0 || m_prevCount != 0) && m_state != State::ATTACK)
	{
		m_attackCount = 0;
		m_prevCount = 0;
	}

	// 回避
	if (m_config.GetInputDown(Input::B) && m_dodgeCoolTimer >= kDodgeCoolMax && m_state != State::SKILL)
	{
		m_state = State::DODGE;
		m_actionTimer = 0;
		m_attackCoolTimer = 0;

		/// 入力状況から方向を設定
		auto moveVec = VGet(0, 0, 0);
		//カメラから見た前方へのベクトル
		auto dirFront = VSub(m_pos, cameraPos);
		// yを０にした上で正規化することで、xz平面での向きを決める
		dirFront.y = 0;
		dirFront = VNorm(dirFront);
		// 正規化した前方ベクトルをもとに
		// 右向きベクトルの作成
		auto dirRight = VGet(-dirFront.z, 0, dirFront.x);

		// コントローラのスティック入力値を獲得
		auto stickInput = m_config.GetStick(STICK_L);

		// 入力に応じて、移動量を確定
		moveVec = VGet((dirFront.x * (-stickInput.y) + dirRight.x * (-stickInput.x)),
			0,
			(dirFront.z * (-stickInput.y) + dirRight.z * (-stickInput.x)));
		if (moveVec.x != 0 || moveVec.y != 0)
		{
			m_dir = VNorm(moveVec);
			m_dir.y = 0;
		}
		/// 押し出し方向を設定
		SetPushVec(m_dir);
		/// その方向にモデル回転
		Rotation();

		m_dodgeCoolTimer = 0;
	}
	if (m_dodgeCoolTimer < kDodgeCoolMax)
	{
		m_dodgeCoolTimer++;
		if ((m_attackCount != 0 || m_prevCount != 0) && m_state != State::ATTACK)
		{
			m_attackCount = 0;
			m_prevCount = 0;
		}
	}

	// スキル
	if (m_state != State::DODGE)
	{
		if (m_config.GetInputDown(Input::X) && m_skillCoolTimer >= kSkill_1CoolMax)
		{
			m_state = State::SKILL;
			m_actionTimer = 0;
			m_skillCoolTimer = 0;
			m_attackCoolTimer = 0;
		}
	}
	if (m_skillCoolTimer < kSkill_1CoolMax)
	{
		m_skillCoolTimer++;
	}
}

void Player::StatusUpdate(VECTOR cameraPos)
{
	/////////////////////
	// 毎フレーム処理
	/////////////////////

	// 停止,移動以外の動作時間更新
	if (m_state != State::IDLE && m_state != State::MOVE)
	{
		m_actionTimer++;
	}
	else
	{
		m_actionTimer = 0;
	}

	// 動作状態毎の処理
	if (m_state == State::IDLE)				// 停止
	{

	}
	else if (m_state == State::MOVE)		// 移動
	{
		Move(cameraPos, m_movePow);
		Rotation();
	}
	else if (m_state == State::ATTACK)		// 通常攻撃
	{
		// 通常攻撃の更新
		if (m_actionTimer >= kAttackTime)
		{
			// 継続
			if (m_prevCount != m_attackCount)
			{
				m_attackCount = m_prevCount;
			}
			// 終了
			else
			{
				m_attackCount = 0;
				m_prevCount = 0;
				m_attackCoolTimer = 0;
				m_state = State::IDLE;
			}
			m_actionTimer = 0;
		}
		else if (m_actionTimer >= kPushStartInAttack && m_actionTimer <= kPushEndInAttack)
		{
			// 攻撃中の押し出し
			if (m_attackCount != 3)
				m_moveVecInFrame = VAdd(m_moveVecInFrame, VScale(m_pushVec, kAttackPow));
			else
				m_moveVecInFrame = VAdd(m_moveVecInFrame, VScale(m_pushVec, kAttackLastPow));
		}
	}
	else if (m_state == State::DODGE)		// 回避
	{
		Dodge(cameraPos, m_movePow);
	}
	else if (m_state == State::SKILL)		// スキル攻撃
	{
		if (m_actionTimer >= kSkill_1Time)
		{
			m_state = State::IDLE;
			m_actionTimer = 0;
		}
	}
}




void Player::Move(VECTOR cameraPos, float movePow)
{
	auto moveVec = VGet(0,0,0);

	//カメラから見た前方へのベクトル
	auto dirFront = VSub(m_pos, cameraPos);
	// yを０にした上で正規化することで、xz平面での向きを決める
	dirFront.y = 0;
	dirFront = VNorm(dirFront);
	// 正規化した前方ベクトルをもとに
	// 右向きベクトルの作成
	auto dirRight = VGet(-dirFront.z, 0, dirFront.x);

	// コントローラのスティック入力値を獲得
	auto stickInput = m_config.GetStick(STICK_L);

	// 入力に応じて、移動量を確定
	moveVec = VGet((dirFront.x * (-stickInput.y) + dirRight.x * (-stickInput.x)),
				  0, 
				 (dirFront.z * (-stickInput.y) + dirRight.z * (-stickInput.x)));
	m_dir = VNorm(moveVec);
	m_dir.y = 0;
	moveVec = VScale(moveVec, movePow);
	// 移動反映
	m_moveVecInFrame = VAdd(m_moveVecInFrame, moveVec);
}


void Player::Dodge(VECTOR cameraPos, float movePow)
{
	// 移動反映
	if (m_dodgeCoolTimer <= kDodgeTime)
	{
		m_moveVecInFrame = VAdd(m_moveVecInFrame, VScale(m_pushVec, kDodgePow));
	}
	else
	{
		m_state = State::IDLE;
	}
}

void Player::NormalAttack()
{
	if (m_attackCount == m_prevCount)
	{
		if (m_attackCount == 0)
		{
			m_prevCount++;
			m_attackCount++;
		}
		else if ((m_animation.GetAnimationNum() == Anima::ATTACK_1 && m_attackCount == 1) ||
			(m_animation.GetAnimationNum() == Anima::ATTACK_2 && m_attackCount == 2))
		{
			if(m_actionTimer > kAttackPrevTime)
				m_prevCount++;
		}
	}

}

void Player::AnimationUpdate()
{
	auto stickInput = m_config.GetStick(Input::STICK_L);
	auto stickSize = sqrtf(stickInput.x * stickInput.x + stickInput.y * stickInput.y);

	// プレイヤーの状態に合わせたアニメーションを設定
	if (m_state == State::SKILL)				// スキル攻撃
	{
		m_animation.SetAnimation(Anima::SKILL_1, kSkill_1Speed);
	}
	else if (m_state == State::DODGE)			// 回避
	{
		m_animation.SetAnimation(Anima::DODGE, kDodgeSpeed);
	}
	else if (m_state == State::ATTACK)			// 通常攻撃
	{
		if (m_attackCount == 1)					// 1段目
		{
			m_animation.SetAnimation(Anima::ATTACK_1, kAttackSpeed);
		}
		else if (m_attackCount == 2)			// 2段目
		{
			m_animation.SetAnimation(Anima::ATTACK_2, kAttackSpeed);
		}
		else if (m_attackCount == 3)			// 3段目
		{
			m_animation.SetAnimation(Anima::ATTACK_3, kAttackSpeed);
		}
		
	}
	else if (m_state == State::MOVE)			// 移動
	{
		m_animation.SetAnimation(Anima::RUN, stickSize * 0.01f);
	}
	else if (m_state == State::IDLE)			// 停止
	{
		m_animation.SetAnimation(Anima::IDLE, kIdleSpeed);
	}


	// アニメーション再生
	m_animation.Play();
}

void Player::UIInit()
{
	// HPバー
	m_UI.SetUI(LoadGraph("Data/Graph/BarV1_Bar.png"),
		Game::kScreenHalfWidth * 0.75f,
		Game::kScreenHeight * 0.8f,
		Game::kScreenHalfWidth * 1.25f,
		Game::kScreenHeight * 0.82f,
		true);
	m_UI.SetUI(m_hpBarHandle,
		Game::kScreenHalfWidth * 0.75f,
		Game::kScreenHeight * 0.8f,
		Game::kScreenHalfWidth * 1.25f,
		Game::kScreenHeight * 0.82f,
		true);
	m_UI.SetUI(LoadGraph("Data/Graph/BarV1_ProgressBarBorder.png"),
		Game::kScreenHalfWidth * 0.75f,
		Game::kScreenHeight * 0.8f,
		Game::kScreenHalfWidth * 1.25f,
		Game::kScreenHeight * 0.82f,
		true);

	// 操作系統
	// Aボタン
	m_UI.SetUI(LoadGraph("Data/Graph/BarV1_Bar.png"),
		Game::kScreenWidth * 0.2f,
		Game::kScreenHeight * 0.85f,
		Game::kScreenWidth * 0.23f,
		Game::kScreenHeight * 0.90f,
		true);
	m_UI.SetUI(m_handle_A,
		Game::kScreenWidth * 0.2f,
		Game::kScreenHeight * 0.85f,
		Game::kScreenWidth * 0.23f,
		Game::kScreenHeight * 0.90f,
		true);
	// Bボタン
	m_UI.SetUI(LoadGraph("Data/Graph/BarV1_Bar.png"),
		Game::kScreenWidth * 0.4f,
		Game::kScreenHeight * 0.85f,
		Game::kScreenWidth * 0.43f,
		Game::kScreenHeight * 0.90f,
		true);
	m_UI.SetUI(m_handle_B,
		Game::kScreenWidth * 0.4f,
		Game::kScreenHeight * 0.85f,
		Game::kScreenWidth * 0.43f,
		Game::kScreenHeight * 0.90f,
		true);
	// Xボタン
	m_UI.SetUI(LoadGraph("Data/Graph/BarV1_Bar.png"),
		Game::kScreenWidth * 0.6f,
		Game::kScreenHeight * 0.85f,
		Game::kScreenWidth * 0.63f,
		Game::kScreenHeight * 0.90f,
		true);
	m_UI.SetUI(m_handle_X,
		Game::kScreenWidth * 0.6f,
		Game::kScreenHeight * 0.85f,
		Game::kScreenWidth * 0.63f,
		Game::kScreenHeight * 0.90f,
		true);

}

void Player::UIUpdate()
{
	if (m_config.GetInputStay(Input::A))
	{
		m_UI.SetIsApp(m_handle_A, false);
	}
	else
	{
		m_UI.SetIsApp(m_handle_A, true);
	}

	if (m_skillCoolTimer < kSkill_1CoolMax)
	{
		m_UI.SetIsApp(m_handle_X, false);
	}
	else
	{
		m_UI.SetIsApp(m_handle_X, true);
	}

	if (m_dodgeCoolTimer < kDodgeCoolMax)
	{
		m_UI.SetIsApp(m_handle_B, false);
	}
	else
	{
		m_UI.SetIsApp(m_handle_B, true);
	}
}
