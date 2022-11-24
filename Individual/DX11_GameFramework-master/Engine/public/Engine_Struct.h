#pragma once
namespace Engine
{
	typedef struct tagGraphicDesc
	{
		enum WINMODE { WINMODE_FULL, WINMODE_WIN, WINMODE_END };

		WINMODE			eWindowMode;
		unsigned int	iViewportSizeX;
		unsigned int	iViewportSizeY;
		HWND			hWnd;		
	}GRAPHIC_DESC;

	/* ���⼺����, ������ : ���⺤�Ͱ� �ʿ��ϴ�. */
	typedef struct tagLightDesc
	{
		enum TYPE { TYPE_DIRECTIONAL, TYPE_POINT, TYPE_END };

		TYPE				eType;

		bool				isEnable;

		XMFLOAT4			vDirection;

		/* ��� ����(�ȼ�)�� �޴� ���� ���⺤�Ͱ� �� �ٸ��� ǥ���Ǿ���ϱ⶧���̴�. */
		/* ��)�̴������� ���� ���⺤�͸� ���ؼ� �����Ѵ�. */
		XMFLOAT4			vPosition;
		float				fRange;		

		XMFLOAT4			vDiffuse;
		XMFLOAT4			vAmbient;
		XMFLOAT4			vSpecular;
	}LIGHTDESC;	

	typedef struct tagFaceIndices16
	{
		unsigned short			_0, _1, _2;
	}FACEINDICES16;

	typedef struct tagFaceIndices32
	{
		unsigned long			_0, _1, _2;
	}FACEINDICES32;

	typedef struct tagVertexPositionTexture
	{
		XMFLOAT3		vPosition;
		XMFLOAT2		vTexUV;
	}VTXTEX;

	typedef struct ENGINE_DLL tagVertexPositionTexture_Declaration
	{
		static const unsigned int		iNumElements = 2;
		static D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];			
	}VTXTEX_DECLARATION;

	typedef struct tagVertexPositionNormalTexture
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vNormal;
		XMFLOAT2		vTexUV;
	}VTXNORTEX;

	typedef struct ENGINE_DLL tagVertexPositionNormalTexture_Declaration
	{
		static const unsigned int		iNumElements = 3;
		static D3D11_INPUT_ELEMENT_DESC		Elements[iNumElements];
	}VTXNORTEX_DECLARATION;

}