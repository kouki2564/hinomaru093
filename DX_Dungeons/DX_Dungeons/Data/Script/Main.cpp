#include "DxLib.h"
#include "SceneManager.h"
#include <memory>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ��ʃT�C�Y�ݒ�
	SetGraphMode(1280, 720, 32);

	// �E�C���h�E���[�h�ݒ�
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// ����ʂɕ`����s��
	SetDrawScreen(DX_SCREEN_BACK);

	SetLightEnable(FALSE);

	// �t�H���g�̃��[�h���ύX
	LPCSTR font_path = "Data/Font/mushin.otf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		assert(false);
	}
	ChangeFont("���S", DX_CHARSET_DEFAULT);

	std::unique_ptr<SceneManager> pManager = std::make_unique<SceneManager>();
	pManager->Init();

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// �t���[���J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A�ɂ���
		ClearDrawScreen();

		// �Q�[���̏���
		pManager->Update();

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS��60�ɌŒ�
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16,66�~���b(16667�}�C�N���b)�o�߂܂ő҂�
		}
	}

	// �t�H���g�̃A�����[�h
	if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
	}
	else {
		assert(false);
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}