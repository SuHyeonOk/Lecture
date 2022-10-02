#ifndef Export_Utility_h__
#define Export_Utility_h__

#include "Engine_Include.h"

// ������Ʈ////////////////////////
// ��¹���
#include "TriCol.h"
#include "RcCol.h"
#include "RcTex.h"
#include "TerrainTex.h"
#include "CubeTex.h"

// ��Ÿ
#include "Transform.h"
#include "Texture.h"
#include "Calculator.h"
#include "Animator.h"
//////////////////////////////////

// ������Ʈ////////////////////////
#include "Camera.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Monster.h"

#include "UI.h"
//////////////////////////////////

// ���� ��� �� �����ڵ�
#include "ProtoMgr.h"
#include "Management.h"
#include "Renderer.h"
#include "Pipeline.h"
#include "LightMgr.h"


BEGIN(Engine)

// Management
inline HRESULT	Create_Management(LPDIRECT3DDEVICE9& pGraphicDev, CManagement** ppManagement); // �̱��� ����
inline HRESULT	Set_Scene(CScene* pScene);
inline _int		Update_Scene(const _float& fTimeDelta);
inline void		LateUpdate_Scene(void);
inline void		Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev);
inline 	CComponent*				Get_Component(const _tchar* pLayerTag,
	const _tchar* pObjTag,
	const _tchar* pComponentTag,
	COMPONENTID eID);
inline 	CGameObject*			Get_GameObject(const _tchar* pLayerTag, const _tchar* pObjTag);

// ProtoMgr
inline HRESULT			Ready_Proto(const _tchar* pProtoTag, CComponent* pComponent);
inline CComponent*		Clone_Proto(const _tchar* pProtoTag);

// Renderer
inline void		Add_RenderGroup(RENDERID eID, CGameObject* pGameObject);
inline void		Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev);
inline void		Clear_RenderGroup(void);
inline void		Set_RenderState(LPDIRECT3DDEVICE9& pGraphicDev, _int _i);

// LightMgr
inline HRESULT	Ready_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9* pLightInfo, const _uint& iIndex);


inline void			Release_Utility(void);

#include "Export_Utility.inl"

END
#endif 