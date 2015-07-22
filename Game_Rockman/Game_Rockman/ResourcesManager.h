/*+========================================================
File:		ResourcesManager.h
Sumary:	Chứa các khai báo của các lớp quản lý resource
trong game
========================================================+*/
#pragma once
#include "Texture.h"
#include "Sprite.h"
//#include "DSUtil.h"
#include <map>
#include <fstream>

using namespace std;
/*C+==================================================================
Class:    CResourcesManager

Summary:  Lớp CResourcesManager dùng để quản lý tài nguyên chung
==================================================================-C*/
class CResourcesManager
{
protected:
	/* File text chứa đường dẫn của tất cả các file texture */
	char* m_szMetaTextureFile;
	/* Hash Map chứa thông tin của các texture */
	map<int, CTexture*> m_aTexture;
	//File chứa dữ liệu về sprite
	char* m_szSpriteFileData;
	//Danh sách các sprite đã được load
	map<int, CSprite*> m_aSprite;
	//File chứa dữ liệu âm thanh
	char* m_szMetaSoundFile;
	////Danh sách các âm thanh đã được load
	//map<int, CSound*> m_aSounds;
	////Đối tượng quản lý âm thanh
	//CSoundManager* m_pSoundManager;

	//Biến instance của resource manager
	static CResourcesManager* s_ResManagerInstance;
	/*M+==================================================================
	Method:	    CResourcesManager::CResourcesManager

	Summary:	Phương thức khởi tạo

	Param(s): metaTextFile - Đường dẫn đến file text chứa tất cả đường dẫn
	của các file texture
	==================================================================-M*/
	CResourcesManager();
public:
	/*M+==================================================================
	Method:	    CResourcesManager::~CResourcesManager

	Summary:	Phương thức hủy
	==================================================================-M*/
	virtual ~CResourcesManager();

	/*M+==================================================================
	Method:	    CResourcesManager::GetTexture

	Summary:	Phương thức lấy về Texture tương ứng với Id truyền vào

	Param(s): textureId - ID của texture muốn get về
	==================================================================-M*/
	virtual CTexture* GetTexture(int textureId);

	/*M+==================================================================
	Method:	    CResourcesManager::GetSprite

	Summary:	Phương thức lấy về Sprite tương ứng với Id truyền vào

	Param(s): spriteId - ID của sprite muốn get về
	==================================================================-M*/
	virtual CSprite* GetSprite(int spriteId);

	/*M+==================================================================
	Method:	    CResourcesManager::GetSound

	Summary:	Phương thức lấy về Sound tương ứng với Id truyền vào

	Param(s): soundId - ID của sound muốn get về
	==================================================================-M*/
	//virtual CSound* GetSound(int soundId);

	/*M+==================================================================
	Method:	    CResourcesManager::LoadResources

	Summary:	Phương thức lấy về gọi tất cả các hàm lấy resource để tiết kiệm xử lý
	==================================================================-M*/
	void LoadResources();

	/*M+==================================================================
	Method:	    CResourcesManager::GetSprite

	Summary:	Phương thức lấy về Instance của lớp Resource manager
	==================================================================-M*/
	static CResourcesManager* GetInstance();
};
