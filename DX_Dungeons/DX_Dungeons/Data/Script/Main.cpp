#include "DxLib.h"
#include "SceneManager.h"
#include <memory>

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 画面サイズ設定
	SetGraphMode(1280, 720, 32);

	// ウインドウモード設定
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 裏画面に描画を行う
	SetDrawScreen(DX_SCREEN_BACK);

	SetLightEnable(FALSE);

	// フォントのロード＆変更
	LPCSTR font_path = "Data/Font/mushin.otf"; // 読み込むフォントファイルのパス
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		assert(false);
	}
	ChangeFont("無心", DX_CHARSET_DEFAULT);

	std::unique_ptr<SceneManager> pManager = std::make_unique<SceneManager>();
	pManager->Init();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// フレーム開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアにする
		ClearDrawScreen();

		// ゲームの処理
		pManager->Update();

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPSを60に固定
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16,66ミリ秒(16667マイクロ秒)経過まで待つ
		}
	}

	// フォントのアンロード
	if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
	}
	else {
		assert(false);
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}