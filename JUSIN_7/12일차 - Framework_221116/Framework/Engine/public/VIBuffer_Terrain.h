#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Terrain final : public CVIBuffer
{
protected:
	CVIBuffer_Terrain(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVIBuffer_Terrain(const CVIBuffer_Terrain& rhs);
	virtual ~CVIBuffer_Terrain() = default;

public:
	virtual HRESULT Initialize_Prototype(const _tchar* pHeightMapFilePath);
	virtual HRESULT Initialize(void* pArg);

private:
	_uint			m_iNumVerticesX = 0; // 가로 정점 개수
	_uint			m_iNumVerticesZ = 0; // 깊이 정점 개수


public:
	static CVIBuffer_Terrain* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, 
		const _tchar* pHeightMapFilePath);

	virtual CComponent* Clone(void* pArg = nullptr);
	virtual void Free() override;

};

END