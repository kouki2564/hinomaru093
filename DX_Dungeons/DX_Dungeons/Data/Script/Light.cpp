#include "Light.h"

Light::Light()
{
	m_floorDirLight.dir = VGet(0, -1, 0);
	m_cameraDirLight.dir = VGet(0, -1, 0);
	m_floorDirLight.handle = CreateDirLightHandle(m_floorDirLight.dir);
	m_cameraDirLight.handle = CreateDirLightHandle(m_cameraDirLight.dir);
	SetLightEnable(true);
	ChangeLightTypeDir(VGet(0, -1, 0));
}

Light::~Light()
{
	DeleteLightHandle(m_floorDirLight.handle);
	DeleteLightHandle(m_cameraDirLight.handle);
}

void Light::Init(VECTOR cameraPos, VECTOR frontPos)
{
	/// �W�����C�g�i�S�̓I�ȏƖ��p�j
	// �f�B�t���[�Y
	COLOR_F difColor = { 0.7f, 0.7f, 0.7f, 1.0f};
	SetLightDifColor(difColor);
	// �A���r�G���g
	COLOR_F ambColor = { 0.5f, 0.5f, 0.5f, 1.0f};
	SetLightAmbColor(ambColor);


	/// �t���A���C�g�i�J�����ڐ��Ŏ��R�ɉf���p�j
	// �f�B�t���[�Y
	m_floorDirLight.difColor = { 0.2f,0.2f,0.2f,1.0f };
	SetLightDifColorHandle(m_floorDirLight.handle, m_floorDirLight.difColor);
	// �A���r�G���g
	m_floorDirLight.ambColor = { 0.8f,0.8f,0.8f,1.0f };
	SetLightAmbColorHandle(m_floorDirLight.handle, m_floorDirLight.ambColor);


	/// �J�������C�g�i��Ƀv���C���[�p�̏Ɩ��p�j
	// �f�B�t���[�Y
	m_cameraDirLight.difColor = { 0.6f,0.6f,0.6,1.0f };
	SetLightDifColorHandle(m_cameraDirLight.handle, m_cameraDirLight.difColor);
	// �X�y�L�����[
	m_cameraDirLight.spcColor = { 0.8f,0.8f,0.8f,1.0f };
	SetLightSpcColorHandle(m_cameraDirLight.handle, m_cameraDirLight.spcColor);

	// ���C�g�����̐ݒ�
	auto cameraToPlayer = VSub(frontPos, cameraPos);
	m_floorDirLight.dir = cameraToPlayer;
	cameraToPlayer.y = 0;
	m_cameraDirLight.dir = cameraToPlayer;
	SetLightDirectionHandle(m_floorDirLight.handle, m_floorDirLight.dir);
	SetLightDirectionHandle(m_cameraDirLight.handle, m_cameraDirLight.dir);
}

void Light::Update(VECTOR cameraPos, VECTOR frontPos)
{
	auto cameraToPlayer = VSub(frontPos, cameraPos);
	m_floorDirLight.dir = cameraToPlayer;
	cameraToPlayer.y = 0;
	m_cameraDirLight.dir = cameraToPlayer;
	SetLightDirectionHandle(m_floorDirLight.handle, m_floorDirLight.dir);
	SetLightDirectionHandle(m_cameraDirLight.handle, m_cameraDirLight.dir);
}
