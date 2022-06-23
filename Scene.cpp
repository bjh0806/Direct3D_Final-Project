//-----------------------------------------------------------------------------
// File: CScene.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::BuildDefaultLightsAndMaterials()
{
	m_nLights = 5;
	m_pLights = new LIGHT[m_nLights];
	::ZeroMemory(m_pLights, sizeof(LIGHT) * m_nLights);

	m_xmf4GlobalAmbient = XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);

	m_pLights[0].m_bEnable = true;
	m_pLights[0].m_nType = POINT_LIGHT;
	m_pLights[0].m_fRange = 1000.0f;
	m_pLights[0].m_xmf4Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	m_pLights[0].m_xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	m_pLights[0].m_xmf4Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.0f);
	m_pLights[0].m_xmf3Position = XMFLOAT3(30.0f, 30.0f, 30.0f);
	m_pLights[0].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pLights[0].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);
	m_pLights[1].m_bEnable = true;
	m_pLights[1].m_nType = SPOT_LIGHT;
	m_pLights[1].m_fRange = 1000.0f;
	m_pLights[1].m_xmf4Ambient = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	m_pLights[1].m_xmf4Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	m_pLights[1].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[1].m_xmf3Position = XMFLOAT3(-50.0f, 20.0f, -5.0f);
	m_pLights[1].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_pLights[1].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights[1].m_fFalloff = 8.0f;
	m_pLights[1].m_fPhi = (float)cos(XMConvertToRadians(40.0f));
	m_pLights[1].m_fTheta = (float)cos(XMConvertToRadians(20.0f));
	m_pLights[2].m_bEnable = true;
	m_pLights[2].m_nType = DIRECTIONAL_LIGHT;
	m_pLights[2].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[2].m_xmf4Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_pLights[2].m_xmf4Specular = XMFLOAT4(0.4f, 0.4f, 0.4f, 0.0f);
	m_pLights[2].m_xmf3Direction = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_pLights[3].m_bEnable = true;
	m_pLights[3].m_nType = SPOT_LIGHT;
	m_pLights[3].m_fRange = 600.0f;
	m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[3].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[3].m_xmf3Position = XMFLOAT3(50.0f, 30.0f, 30.0f);
	m_pLights[3].m_xmf3Direction = XMFLOAT3(0.0f, 1.0f, 1.0f);
	m_pLights[3].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights[3].m_fFalloff = 8.0f;
	m_pLights[3].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights[3].m_fTheta = (float)cos(XMConvertToRadians(30.0f));
	m_pLights[4].m_bEnable = true;
	m_pLights[4].m_nType = DIRECTIONAL_LIGHT;
	m_pLights[4].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[4].m_xmf4Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_pLights[4].m_xmf4Specular = XMFLOAT4(0.4f, 0.4f, 0.4f, 0.0f);
	m_pLights[4].m_xmf3Direction = XMFLOAT3(0.0f, -0.5f, 1.0f);
}

void CScene::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<> uid_h{ 10, 25 };
	std::uniform_int_distribution<> uid_car{ 1,3 };
	std::uniform_int_distribution<> uid_speed{ 10, 30 };
	std::uniform_real_distribution<> uid_position_x{ -1, 1 };
	std::uniform_real_distribution<> uid_position_z{ 5, 298 };
	std::uniform_int_distribution<> uid_rock{ 1, 3 };

	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	CMaterial::PrepareShaders(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);

	BuildDefaultLightsAndMaterials();

	m_nGameObjects = 300;
	m_ppGameObjects = new CGameObject*[m_nGameObjects];
	m_ppTreeObjects_l = new CGameObject * [m_nGameObjects];
	m_ppTreeObjects_r = new CGameObject * [m_nGameObjects];
	m_ppRoadObjects_l = new CGameObject * [m_nGameObjects];
	m_ppRoadObjects_r = new CGameObject * [m_nGameObjects];
	m_ppLineObjects_l = new CGameObject * [m_nGameObjects];
	m_ppLineObjects_r = new CGameObject * [m_nGameObjects];
	m_ppRockObjects = new CGameObject * [m_nGameObjects / 2];
	m_ppSideObject = new CGameObject * [2];
	m_ppCarObjects = new CGameObject * [10];
	m_ppSideLineObjects = new CGameObject * [2];
	m_pSpeeds = new float[10];
	m_pRock = new int[2];

	for (int i = 0; i < 10; ++i) {
		m_pSpeeds[i] = uid_speed(dre) * 0.1;
	}

	CGameObject *pRoadModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/BlackCube.bin");
	CApacheObject* pRoadObject = NULL;
	CGameObject*pSideModel=CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/Cube.bin");
	CSideObject* pSideObject = NULL;
	CGameObject* pLineModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/WhiteCube.bin");
	CLineObject* pLineObject = NULL;
	CGameObject* pSideLineModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/YellowCube.bin");
	CSideLineObject* pSideLineObject = NULL;
	CGameObject* pTreeModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/Tree.bin");
	CTreeObject* pTreeObject = NULL;

	pSideObject = new CSideObject();
	pSideObject->SetChild(pSideModel, true);
	pSideObject->OnInitialize();
	pSideObject->SetScale(10.0f, 10.0f, 100.0f * m_nGameObjects);
	pSideObject->SetPosition(-155.0f, 5.0f, 100.0f * m_nGameObjects / 2 - 150.0f);
	m_ppSideObject[0] = pSideObject;

	pSideObject = new CSideObject();
	pSideObject->SetChild(pSideModel, true);
	pSideObject->OnInitialize();
	pSideObject->SetScale(10.0f, 10.0f, 100.0f * m_nGameObjects);
	pSideObject->SetPosition(155.0f, 5.0f, 100.0f * m_nGameObjects / 2 - 150.0f);
	m_ppSideObject[1] = pSideObject;

	pSideLineObject = new CSideLineObject();
	pSideLineObject->SetChild(pSideLineModel, true);
	pSideLineObject->OnInitialize();
	pSideLineObject->SetScale(10.0f, 0.5f, 100.0f * m_nGameObjects);
	pSideLineObject->SetPosition(-145.0f, 1.0f, 100.0f * m_nGameObjects / 2 - 150.0f);
	m_ppSideLineObjects[0] = pSideLineObject;

	pSideLineObject = new CSideLineObject();
	pSideLineObject->SetChild(pSideLineModel, true);
	pSideLineObject->OnInitialize();
	pSideLineObject->SetScale(10.0f, 0.5f, 100.0f * m_nGameObjects);
	pSideLineObject->SetPosition(145.0f, 1.0f, 100.0f * m_nGameObjects / 2 - 150.0f);
	m_ppSideLineObjects[1] = pSideLineObject;

	for (int i{}; i < m_nGameObjects; ++i) {
		pRoadObject = new CApacheObject();
		pRoadObject->SetChild(pRoadModel, true);
		pRoadObject->OnInitialize();
		pRoadObject->SetScale(100.0f, 1.0f, 100.0f);
		pRoadObject->SetPosition(0.0f, 0.0f, (i - 1) * 100.0f);
		m_ppGameObjects[i] = pRoadObject;

		pRoadObject = new CApacheObject();
		pRoadObject->SetChild(pRoadModel, true);
		pRoadObject->OnInitialize();
		pRoadObject->SetScale(100.0f, 1.0f, 100.0f);
		pRoadObject->SetPosition(-100.0f, 0.0f, (i - 1) * 100.0f);
		m_ppRoadObjects_l[i] = pRoadObject;

		pRoadObject = new CApacheObject();
		pRoadObject->SetChild(pRoadModel, true);
		pRoadObject->OnInitialize();
		pRoadObject->SetScale(100.0f, 1.0f, 100.0f);
		pRoadObject->SetPosition(100.0f, 0.0f, (i - 1) * 100.0f);
		m_ppRoadObjects_r[i] = pRoadObject;

		pLineObject = new CLineObject();
		pLineObject->SetChild(pLineModel, true);
		pLineObject->OnInitialize();
		pLineObject->SetScale(10.0f, 0.5f, 60.0f);
		pLineObject->SetPosition(-50.0f, 1.0f, (i - 1) * 100.0f);
		m_ppLineObjects_l[i] = pLineObject;

		pLineObject = new CLineObject();
		pLineObject->SetChild(pLineModel, true);
		pLineObject->OnInitialize();
		pLineObject->SetScale(10.0f, 0.5f, 60.0f);
		pLineObject->SetPosition(50.0f, 1.0f, (i - 1) * 100.0f);
		m_ppLineObjects_r[i] = pLineObject;

		pTreeObject = new CTreeObject();
		pTreeObject->SetChild(pTreeModel, true);
		pTreeObject->OnInitialize();
		pTreeObject->SetPosition(-165.0f, 0.0f, (i - 1) * 100.0f);
		pTreeObject->SetScale(10.0f, uid_h(dre), 10.0f);
		pTreeObject->Rotate(0.0f, 90.0f, 0.0f);
		m_ppTreeObjects_l[i] = pTreeObject;

		pTreeObject = new CTreeObject();
		pTreeObject->SetChild(pTreeModel, true);
		pTreeObject->OnInitialize();
		pTreeObject->SetPosition(165.0f, 0.0f, (i - 1) * 100.0f);
		pTreeObject->SetScale(10.0f, uid_h(dre), 10.0f);
		pTreeObject->Rotate(0.0f, 90.0f, 0.0f);
		m_ppTreeObjects_r[i] = pTreeObject;
	}

	int RockSelect = 0;

	CGameObject* pRockModel = NULL;
	CRockObject* pRockObject = NULL;
	
	for (int i{}; i < m_nGameObjects / 2; ++i) {
		RockSelect = uid_car(dre);

		if (RockSelect == 1) {
			pRockModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/Rock.bin");
		}

		else {
			pRockModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/Rock2.bin");
		}

		pRockObject = new CRockObject();
		pRockObject->SetChild(pRockModel, true);
		pRockObject->OnInitialize();
		pRockObject->SetPosition(uid_position_x(dre) * 100.0f, 0.0f, uid_position_z(dre) * 100.0f);
		pRockObject->SetScale(30.0f, 30.0f, 30.0f);
		m_ppRockObjects[i] = pRockObject;
	}

	int CarSelect = uid_car(dre);

	CGameObject* pCarModel = NULL;

	if (CarSelect == 1) {
		pCarModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/OldCar.bin");
	}

	else if (CarSelect == 2) {
		pCarModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/PoliceCar.bin");
	}

	else {
		pCarModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/SportCar.bin");
	}
	
	CCarObject* pCarObject = NULL;

	pCarObject = new CCarObject();
	pCarObject->SetChild(pCarModel, true);
	pCarObject->OnInitialize();
	pCarObject->SetScale(10.0f, 10.0f, 10.0f);
	pCarObject->SetPosition(-105.0f, 0.0f, 0.0f);
	m_ppCarObjects[0] = pCarObject;

	CarSelect = uid_car(dre);

	if (CarSelect == 1) {
		pCarModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/OldCar.bin");
	}

	else if (CarSelect == 2) {
		pCarModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/PoliceCar.bin");
	}

	else {
		pCarModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/SportCar.bin");
	}

	pCarObject = new CCarObject();
	pCarObject->SetChild(pCarModel, true);
	pCarObject->OnInitialize();
	pCarObject->SetScale(10.0f, 10.0f, 10.0f);
	pCarObject->SetPosition(105.0f, 0.0f, 0.0f);
	m_ppCarObjects[1] = pCarObject;

	for (int i = 2; i < 10; ++i) {
		CarSelect = uid_car(dre);

		if (CarSelect == 1) {
			pCarModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/OldCar.bin");
		}

		else if (CarSelect == 2) {
			pCarModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/PoliceCar.bin");
		}

		else {
			pCarModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/SportCar.bin");
		}

		pCarObject = new CCarObject();
		pCarObject->SetChild(pCarModel, true);
		pCarObject->OnInitialize();
		pCarObject->SetScale(10.0f, 10.0f, 10.0f);
		pCarObject->SetPosition(uid_position_x(dre) * 105.0f, 0.0f, uid_position_z(dre) * 100.0f);
		m_ppCarObjects[i] = pCarObject;
	}

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();

	if (m_ppGameObjects)
	{
		for (int i = 0; i < m_nGameObjects; i++) if (m_ppGameObjects[i]) m_ppGameObjects[i]->Release();
		delete[] m_ppGameObjects;
	}

	ReleaseShaderVariables();

	if (m_pLights) delete[] m_pLights;
}

void CScene::Collision()
{
	m_pPlayer->m_xmPBoundingBox = BoundingOrientedBox(XMFLOAT3(m_pPlayer->GetPosition()), XMFLOAT3(15.0f, 20.0f, 35.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_pPlayer->m_pObjectCollided = NULL;

	for (int i = 0; i < 10; ++i) {
		m_ppCarObjects[i]->m_xmBoundingBox = BoundingBox(XMFLOAT3(m_ppCarObjects[i]->GetPosition()), XMFLOAT3(15.0f, 20.0f, 35.0f));
		m_ppCarObjects[i]->m_pObjectCollided = NULL;
	}

	for (int i = 0; i < m_nGameObjects / 2; ++i) {
		m_ppRockObjects[i]->m_xmBoundingBox = BoundingBox(XMFLOAT3(m_ppRockObjects[i]->GetPosition()), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_ppRockObjects[i]->m_pObjectCollided = NULL;
	}

	for (int i = 0; i < 10; ++i) {
		if (m_ppCarObjects[i]->m_xmBoundingBox.Intersects(m_pPlayer->m_xmPBoundingBox)) {
			m_ppCarObjects[i]->m_pObjectCollided = m_pPlayer;
			m_pPlayer->m_pObjectCollided = m_ppCarObjects[i];
		}

		for (int j = 0; j < m_nGameObjects / 2; ++j) {
			if (m_ppCarObjects[i]->m_xmBoundingBox.Intersects(m_ppRockObjects[j]->m_xmBoundingBox)) {
				m_ppCarObjects[i]->m_pObjectCollided = m_ppRockObjects[j];
				pass[j] = 1;
			}
		}
	}

	for (int i = 0; i < m_nGameObjects / 2; ++i) {
		if (m_ppRockObjects[i]->m_xmBoundingBox.Intersects(m_pPlayer->m_xmPBoundingBox)) {
			m_ppRockObjects[i]->m_pObjectCollided = m_pPlayer;
			m_pPlayer->m_pObjectCollided = m_ppRockObjects[i];
		}
	}

	if (m_pPlayer->m_pObjectCollided) {
		if (m_pPlayer->m_pObjectCollided->m_xmBoundingBox.Extents.x == 10.0f) {
			for (int i = 0; i < m_nGameObjects / 2; ++i) {
				if (m_pPlayer->m_pObjectCollided == m_ppRockObjects[i]) {
					if (pass[i] != 1) {
						count++;
						m_pPlayer->m_pObjectCollided->SetScale(0.0f, 0.0f, 0.0f);
						m_pPlayer->SetMaxVelocityXZ(150.0f + count);
					}
				}
			}
		}

		if (m_pPlayer->m_pObjectCollided->m_xmBoundingBox.Extents.x == 15.0f) {
			for (int i = 0; i < 10; ++i) {
				if (m_pPlayer->m_pObjectCollided == m_ppCarObjects[i]) {
					if (m_ppCarObjects[i]->m_xmf4x4Transform._41 < m_pPlayer->GetPosition().x && m_ppCarObjects[i]->m_xmf4x4Transform._41 > -120) {
						m_ppCarObjects[i]->m_xmf4x4Transform._41 -= 1;
					}

					else if (m_ppCarObjects[i]->m_xmf4x4Transform._41 > m_pPlayer->GetPosition().x && m_ppCarObjects[i]->m_xmf4x4Transform._41 < 120) {
						m_ppCarObjects[i]->m_xmf4x4Transform._41 += 1;
					}

					if (m_ppCarObjects[i]->m_xmf4x4Transform._41 <= -120) {
						m_pSpeeds[i] = 0;
						m_ppCarObjects[i]->m_xmf4x4Transform._41 = -120;
					}

					else if (m_ppCarObjects[i]->m_xmf4x4Transform._41 >= 120) {
						m_pSpeeds[i] = 0;
						m_ppCarObjects[i]->m_xmf4x4Transform._41 = 120;
					}
				}
			}
		}
	}

	for (int i = 0; i < 10; ++i) {
		if (m_ppCarObjects[i]->m_pObjectCollided) {
			m_ppCarObjects[i]->m_pObjectCollided->SetScale(0.0f, 0.0f, 0.0f);
		}
	}
}

ID3D12RootSignature *CScene::CreateGraphicsRootSignature(ID3D12Device *pd3dDevice)
{
	ID3D12RootSignature *pd3dGraphicsRootSignature = NULL;

	D3D12_ROOT_PARAMETER pd3dRootParameters[3];

	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[0].Descriptor.ShaderRegister = 1; //Camera
	pd3dRootParameters[0].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 32;
	pd3dRootParameters[1].Constants.ShaderRegister = 2; //GameObject
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[2].Descriptor.ShaderRegister = 4; //Lights
	pd3dRootParameters[2].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = NULL;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob *pd3dSignatureBlob = NULL;
	ID3DBlob *pd3dErrorBlob = NULL;
	D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(), pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void **)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

void CScene::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(LIGHTS) + 255) & ~255); //256ÀÇ ¹è¼ö
	m_pd3dcbLights = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbLights->Map(0, NULL, (void **)&m_pcbMappedLights);
}

void CScene::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	::memcpy(m_pcbMappedLights->m_pLights, m_pLights, sizeof(LIGHT) * m_nLights);
	::memcpy(&m_pcbMappedLights->m_xmf4GlobalAmbient, &m_xmf4GlobalAmbient, sizeof(XMFLOAT4));
	::memcpy(&m_pcbMappedLights->m_nLights, &m_nLights, sizeof(int));
}

void CScene::ReleaseShaderVariables()
{
	if (m_pd3dcbLights)
	{
		m_pd3dcbLights->Unmap(0, NULL);
		m_pd3dcbLights->Release();
	}
}

void CScene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nGameObjects; i++) m_ppGameObjects[i]->ReleaseUploadBuffers();
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		/*case 'W': m_ppGameObjects[0]->MoveForward(+1.0f); break;
		case 'S': m_ppGameObjects[0]->MoveForward(-1.0f); break;
		case 'A': m_ppGameObjects[0]->MoveStrafe(-1.0f); break;
		case 'D': m_ppGameObjects[0]->MoveStrafe(+1.0f); break;
		case 'Q': m_ppGameObjects[0]->MoveUp(+1.0f); break;
		case 'R': m_ppGameObjects[0]->MoveUp(-1.0f); break;*/
		default:
			break;
		}
		break;
	default:
		break;
	}
	return(false);
}

bool CScene::ProcessInput(UCHAR *pKeysBuffer)
{
	return(false);
}

void CScene::AnimateObjects(float fTimeElapsed)
{
	m_fElapsedTime = fTimeElapsed;

	for (int i = 0; i < m_nGameObjects; i++) m_ppGameObjects[i]->Animate(fTimeElapsed, NULL);

	for (int i = 0; i < 10; ++i) {
		if (m_ppCarObjects[i]->m_xmf4x4Transform._43 < 298 * 100.0f) {
			m_ppCarObjects[i]->m_xmf4x4Transform._43 += m_pSpeeds[i];
		}
	}

	if (m_pLights)
	{
		m_pLights[1].m_xmf3Position = m_pPlayer->GetPosition();
		m_pLights[1].m_xmf3Direction = m_pPlayer->GetLookVector();
	}

	Collision();
}

void CScene::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pCamera->UpdateShaderVariables(pd3dCommandList);

	UpdateShaderVariables(pd3dCommandList);

	D3D12_GPU_VIRTUAL_ADDRESS d3dcbLightsGpuVirtualAddress = m_pd3dcbLights->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbLightsGpuVirtualAddress); //Lights

	for (int i = 0; i < 2; ++i) {
		m_ppSideObject[i]->Animate(m_fElapsedTime, NULL);
		m_ppSideObject[i]->UpdateTransform(NULL);
		m_ppSideObject[i]->Render(pd3dCommandList, pCamera);

		m_ppSideLineObjects[i]->Animate(m_fElapsedTime, NULL);
		m_ppSideLineObjects[i]->UpdateTransform(NULL);
		m_ppSideLineObjects[i]->Render(pd3dCommandList, pCamera);
	}

	for (int i = 0; i < 10; ++i) {
		m_ppCarObjects[i]->Animate(m_fElapsedTime, NULL);
		m_ppCarObjects[i]->UpdateTransform(NULL);
		m_ppCarObjects[i]->Render(pd3dCommandList, pCamera);
	}

	for (int i = 0; i < m_nGameObjects; i++)
	{
		if (m_ppGameObjects[i])
		{
			m_ppGameObjects[i]->Animate(m_fElapsedTime, NULL);
			m_ppGameObjects[i]->UpdateTransform(NULL);
			m_ppGameObjects[i]->Render(pd3dCommandList, pCamera);

			m_ppRoadObjects_l [i] ->Animate(m_fElapsedTime, NULL);
			m_ppRoadObjects_l[i]->UpdateTransform(NULL);
			m_ppRoadObjects_l[i]->Render(pd3dCommandList, pCamera);

			m_ppRoadObjects_r[i]->Animate(m_fElapsedTime, NULL);
			m_ppRoadObjects_r[i]->UpdateTransform(NULL);
			m_ppRoadObjects_r[i]->Render(pd3dCommandList, pCamera);

			m_ppTreeObjects_l[i]->Animate(m_fElapsedTime, NULL);
			m_ppTreeObjects_l[i]->UpdateTransform(NULL);
			m_ppTreeObjects_l[i]->Render(pd3dCommandList, pCamera);

			m_ppTreeObjects_r[i]->Animate(m_fElapsedTime, NULL);
			m_ppTreeObjects_r[i]->UpdateTransform(NULL);
			m_ppTreeObjects_r[i]->Render(pd3dCommandList, pCamera);

			m_ppLineObjects_l[i]->Animate(m_fElapsedTime, NULL);
			m_ppLineObjects_l[i]->UpdateTransform(NULL);
			m_ppLineObjects_l[i]->Render(pd3dCommandList, pCamera);

			m_ppLineObjects_r[i]->Animate(m_fElapsedTime, NULL);
			m_ppLineObjects_r[i]->UpdateTransform(NULL);
			m_ppLineObjects_r[i]->Render(pd3dCommandList, pCamera);
		}
	}

	for (int i = 0; i < m_nGameObjects / 2; ++i) {
		m_ppRockObjects[i]->Animate(m_fElapsedTime, NULL);
		m_ppRockObjects[i]->UpdateTransform(NULL);
		m_ppRockObjects[i]->Render(pd3dCommandList, pCamera);
	}
}

