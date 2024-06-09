#include "Shader.h"

CShader::CShader()
{
}

CShader::~CShader()
{
	if (m_ppd3dPipelineStates)
	{
		for (int i = 0; i < m_nPipelineStates; i++) if (m_ppd3dPipelineStates[i])
			m_ppd3dPipelineStates[i]->Release();
		delete[] m_ppd3dPipelineStates;
	}
}
//래스터라이저 상태를 설정하기 위한 구조체를 반환한다. 
D3D12_RASTERIZER_DESC CShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
	d3dRasterizerDesc.DepthBias = 0;
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	return(d3dRasterizerDesc);
}
//깊이-스텐실 검사를 위한 상태를 설정하기 위한 구조체를 반환한다. 
D3D12_DEPTH_STENCIL_DESC CShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = TRUE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	return(d3dDepthStencilDesc);
}
//블렌딩 상태를 설정하기 위한 구조체를 반환한다. 
D3D12_BLEND_DESC CShader::CreateBlendState()
{
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	return(d3dBlendDesc);
}
D3D12_INPUT_LAYOUT_DESC CShader::CreateInputLayout()
{
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = NULL;
	d3dInputLayoutDesc.NumElements = 0;
	return(d3dInputLayoutDesc);
}
D3D12_SHADER_BYTECODE CShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;
	return(d3dShaderByteCode);
}
D3D12_SHADER_BYTECODE CShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;
	return(d3dShaderByteCode);
}

//셰이더 소스 코드를 컴파일하여 바이트 코드 구조체를 반환한다. 
D3D12_SHADER_BYTECODE CShader::CompileShaderFromFile(WCHAR* pszFileName, LPCSTR
	pszShaderName, LPCSTR pszShaderProfile, ID3DBlob** ppd3dShaderBlob)
{
	UINT nCompileFlags = 0;
#if defined(_DEBUG)
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	::D3DCompileFromFile(pszFileName, NULL, NULL, pszShaderName, pszShaderProfile,
		nCompileFlags, 0, ppd3dShaderBlob, NULL);
	D3D12_SHADER_BYTECODE d3dShaderByteCode;

	d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
	d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();

	return(d3dShaderByteCode);
}
//그래픽스 파이프라인 상태 객체를 생성한다. 
void CShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature
	* pd3dGraphicsRootSignature)
{
	ID3DBlob* pd3dVertexShaderBlob = NULL, * pd3dPixelShaderBlob = NULL;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader(&pd3dVertexShaderBlob);
	d3dPipelineStateDesc.PS = CreatePixelShader(&pd3dPixelShaderBlob);
	d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc,
		__uuidof(ID3D12PipelineState), (void**)&m_ppd3dPipelineStates[0]);
	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();
	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[]
		d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}
//셰이더 객체가 포함하는 게임 객체들을 생성한다. 
void CShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, void* pContext)
{
	CTriangleMesh* pTriangleMesh = new CTriangleMesh(pd3dDevice, pd3dCommandList);
	m_nObjects = 1;
	m_ppObjects = new CGameObject * [m_nObjects];
	m_ppObjects[0] = new CGameObject();
	m_ppObjects[0]->SetMesh(pTriangleMesh);
}
void CShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) if (m_ppObjects[j]) delete m_ppObjects[j];
		delete[] m_ppObjects;
	}
}
void CShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}
}
void CShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) if (m_ppObjects[j])
			m_ppObjects[j]->ReleaseUploadBuffers();
	}
}
void CShader::OnPrepareRender(ID3D12GraphicsCommandList* pd3dCommandList)
{
	//파이프라인에 그래픽스 상태 객체를 설정한다. 
	pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
}
void CShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	OnPrepareRender(pd3dCommandList);
}

void CShader::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
}
void CShader::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
}
void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList* pd3dCommandList, XMFLOAT4X4
	* pxmf4x4World)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(pxmf4x4World)));
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
}
void CShader::ReleaseShaderVariables()
{
}
CPlayerShader::CPlayerShader()
{
}
CPlayerShader::~CPlayerShader()
{
}
D3D12_INPUT_LAYOUT_DESC CPlayerShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}
D3D12_SHADER_BYTECODE CPlayerShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(const_cast<WCHAR*>(L"Shaders.hlsl"), "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CPlayerShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(const_cast < WCHAR*>(L"Shaders.hlsl"), "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}
void CPlayerShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature
	* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

///////////////////////////////////////////////////////////////////////////////

CObjectsShader::CObjectsShader()
{
}
CObjectsShader::~CObjectsShader()
{
}
D3D12_INPUT_LAYOUT_DESC CObjectsShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}
D3D12_SHADER_BYTECODE CObjectsShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1", ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CObjectsShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1", ppd3dShaderBlob));
}
void CObjectsShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature
	* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}
void CObjectsShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	//가로x세로x높이가 12x12x12인 정육면체 메쉬를 생성한다.
	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		12.0f, 12.0f, 12.0f);

	m_nObjects = 10;
	m_ppObjects = new CGameObject * [m_nObjects];
	{
		CRotatingObject* pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(-13.5f, 0.0f, -14.0f);
		pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
		pRotatingObject->SetRotationSpeed(90.0f);
		pRotatingObject->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
		pRotatingObject->SetMovingSpeed(20.5f);
		m_ppObjects[0] = pRotatingObject;

		pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(+13.5f, 0.0f, -14.0f);
		pRotatingObject->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
		pRotatingObject->SetRotationSpeed(180.0f);
		pRotatingObject->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
		pRotatingObject->SetMovingSpeed(8.8f);
		m_ppObjects[1] = pRotatingObject;

		pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(0.0f, +5.0f, 20.0f);
		pRotatingObject->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
		pRotatingObject->SetRotationSpeed(30.15f);
		pRotatingObject->SetMovingDirection(XMFLOAT3(1.0f, -1.0f, 0.0f));
		pRotatingObject->SetMovingSpeed(5.2f);
		m_ppObjects[2] = pRotatingObject;

		pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(0.0f, 0.0f, 0.0f);
		pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
		pRotatingObject->SetRotationSpeed(40.6f);
		pRotatingObject->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
		pRotatingObject->SetMovingSpeed(20.4f);
		m_ppObjects[3] = pRotatingObject;

		pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(10.0f, 0.0f, 0.0f);
		pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pRotatingObject->SetRotationSpeed(50.06f);
		pRotatingObject->SetMovingDirection(XMFLOAT3(0.0f, 1.0f, 1.0f));
		pRotatingObject->SetMovingSpeed(6.4f);
		m_ppObjects[4] = pRotatingObject;

		pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(-10.0f, 0.0f, -10.0f);
		pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pRotatingObject->SetRotationSpeed(60.06f);
		pRotatingObject->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 1.0f));
		pRotatingObject->SetMovingSpeed(8.9f);
		m_ppObjects[5] = pRotatingObject;

		pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(-10.0f, 10.0f, -10.0f);
		pRotatingObject->SetMovingDirection(XMFLOAT3(1.0f, 1.0f, 1.0f));
		pRotatingObject->SetMovingSpeed(9.7f);
		m_ppObjects[6] = pRotatingObject;

		pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(-10.0f, 10.0f, -20.0f);
		pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pRotatingObject->SetRotationSpeed(70.06f);
		pRotatingObject->SetMovingDirection(XMFLOAT3(-1.0f, 1.0f, 1.0f));
		pRotatingObject->SetMovingSpeed(15.6f);
		m_ppObjects[7] = pRotatingObject;

		pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(-15.0f, 10.0f, -30.0f);
		pRotatingObject->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
		pRotatingObject->SetRotationSpeed(90.06f);
		pRotatingObject->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, -1.0f));
		pRotatingObject->SetMovingSpeed(15.0f);
		m_ppObjects[8] = pRotatingObject;

		pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(+15.0f, 10.0f, 0.0f);
		pRotatingObject->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
		pRotatingObject->SetRotationSpeed(90.06f);
		pRotatingObject->SetMovingDirection(XMFLOAT3(-0.0f, 0.0f, -1.0f));
		pRotatingObject->SetMovingSpeed(15.0f);
		m_ppObjects[9] = pRotatingObject;
	}

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}
void CObjectsShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++)
		{
			if (m_ppObjects[j]) delete m_ppObjects[j];
		}
		delete[] m_ppObjects;
	}
}
void CObjectsShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}
}
void CObjectsShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) m_ppObjects[j]->ReleaseUploadBuffers();
	}
}
void CObjectsShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}
}

CGameObject* CObjectsShader::PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition, 
	XMFLOAT4X4& xmf4x4View, float* pfNearHitDistance)
{
	int nIntersected = 0;
	*pfNearHitDistance = FLT_MAX;
	float fHitDistance = FLT_MAX;
	CGameObject* pSelectedObject = NULL;
	for (int j = 0; j < m_nObjects; j++)
	{
		nIntersected = m_ppObjects[j]->PickObjectByRayIntersection(xmf3PickPosition,
			xmf4x4View, &fHitDistance);
		if ((nIntersected > 0) && (fHitDistance < *pfNearHitDistance))
		{
			*pfNearHitDistance = fHitDistance;
			pSelectedObject = m_ppObjects[j];
		}
	}
	return(pSelectedObject);
}

/// /////////////////////////////////////////////////////////////////////////////////
struct S {
	float x[11] = { -10,-9,-8,-8,-8,-9,-10,-10,-10,-9,-8 };
	float z[11]{};
	float y[11] = { 0,0,0,1,2,2,2,3,4,4,4 };
}s;
struct T {
	float x[7] = { -6,-5,-4,-5,-5,-5,-5 };
	float z[7]{};
	float y[7] = { 4,4,4,3,2,1,0 };
}t;
struct A {
	float x[12] = { -2,-1,0,-2,0,-2,-1,0,-2,0,-2,0 };
	float z[12]{};
	float y[12] = { 4,4,4,3,3,2,2,2,1,1,0,0 };
}a;
struct R {
	float x[12] = { 2,3,4,2,4,2,3,4,2,3.5,2,4 };
	float z[12]{};
	float y[12] = { 4,4,4,3,3,2,2,2,1,1,0,0 };
}r;
CTitleObjectsShader::CTitleObjectsShader()
{
}

CTitleObjectsShader::~CTitleObjectsShader()
{
}

void CTitleObjectsShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	//가로x세로x높이가 12x12x12인 정육면체 메쉬를 생성한다.
	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		1.0f, 1.0f, 1.0f);
	m_nObjects = 49;
	m_ppObjects = new CGameObject * [m_nObjects];

	int objectIndex = 0;

	auto createRotatingObject = [&](float x, float y, float z, int r, int g, int b) {
		CRotatingObject* pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh(pCubeMesh);
		//pRotatingObject->SetColor(RGB(r, g, b));
		pRotatingObject->SetPosition(x, y, z);
		pRotatingObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pRotatingObject->SetRotationSpeed(90.0f);
		m_ppObjects[objectIndex++] = pRotatingObject;
		};

	// s 구조체
	for (int i = 0; i < 11; ++i)
		createRotatingObject(s.x[i], s.y[i], s.z[i], 255, 0, 0);

	// t 구조체
	for (int i = 0; i < 7; ++i) {
		createRotatingObject(t.x[i], t.y[i], t.z[i], 255, 255, 0);
		createRotatingObject(t.x[i] + 12, t.y[i], t.z[i], 255, 0, 255);
	}

	// a 구조체
	for (int i = 0; i < 12; ++i)
		createRotatingObject(a.x[i], a.y[i], a.z[i], 0, 255, 0);

	// r 구조체
	for (int i = 0; i < 12; ++i)
		createRotatingObject(r.x[i], r.y[i], r.z[i], 0, 0, 255);

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CTitleObjectsShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}
}

void CTitleObjectsShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++)
		{
			if (m_ppObjects[j]) delete m_ppObjects[j];
		}
		delete[] m_ppObjects;
	}
}

D3D12_INPUT_LAYOUT_DESC CTitleObjectsShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CTitleObjectsShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CTitleObjectsShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1", ppd3dShaderBlob));
}

void CTitleObjectsShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CTitleObjectsShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) m_ppObjects[j]->ReleaseUploadBuffers();
	}
}

void CTitleObjectsShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}
}
