/*+===================================================================
File:      ResourcesManager.cpp

Summary:   Định nghĩa các phương thức của lớp CResoucesManager
===================================================================+*/

#include "ResourcesManager.h"
#include "GameWindow.h"

#pragma region Các phương thức của lớp ResourcesManager

CResourcesManager* CResourcesManager::s_ResManagerInstance = NULL;

CResourcesManager::CResourcesManager()
{
	m_szMetaTextureFile = TEXTURE_PATH;
	m_szSpriteFileData = SPRITE_PATH;
	m_szMetaSoundFile = SOUND_PATH;
	//m_pSoundManager = new CSoundManager();
	HRESULT result;
	//result = m_pSoundManager->Initialize(CGameWindow::GetInstance()->GetHWND(), DSSCL_PRIORITY);
	/*if (result != DS_OK)
	{
		OutputDebugString("[ERROR] Can not init sound(ResourcesManager.cpp - Line 78).\n");
	}
	result = m_pSoundManager->SetPrimaryBufferFormat(2, 22050, 16);
	if (result != DS_OK)
	{
		OutputDebugString("[ERROR] Can not set sound buffer(ResourcesManager.cpp - Line 86).\n");
	}*/
}

CResourcesManager::~CResourcesManager()
{
	if (m_szMetaTextureFile)
		delete m_szMetaTextureFile;
	if (m_szSpriteFileData)
		delete m_szSpriteFileData;
	if (m_szSpriteFileData)
		delete m_szSpriteFileData;
	map<int, CTexture*>::iterator i;
	for (i = m_aTexture.begin(); i != m_aTexture.end(); i++)
	{
		if (i->second != NULL)
			delete i->second;
	}
	m_aTexture.clear();
	map<int, CSprite*>::iterator j;
	for (j = m_aSprite.begin(); j != m_aSprite.end(); j++)
	{
		if (j->second != NULL)
			delete j->second;
	}
	m_aSprite.clear();

	/*map<int, CSound*>::iterator k;
	for (k = m_aSounds.begin(); k != m_aSounds.end(); k++)
	{
		if (k->second != NULL)
			delete k->second;
	}
	m_aSounds.clear();*/
}

CTexture* CResourcesManager::GetTexture(int textureId){
	map<int, CTexture*>::iterator iTexture;
	//Lấy ra texture có texture ID giống như tham số truyền vào
	iTexture = m_aTexture.find(textureId);
	//Kiểm tra trong map chưa có texture này
	if (iTexture == m_aTexture.end())
	{
		//Mở file chứa dữ liệu texture lên
		ifstream metaTextureStream;
		metaTextureStream.open(m_szMetaTextureFile, ios::in);
		if (!metaTextureStream.is_open())
		{
			OutputDebugString("[resourcesmanager.cpp] Fail to open Meta Texture file.");
			return NULL;
		}

		int ID, rows, cols, count;

		//Duyệt từng hàng trong file để tìm dòng có Id giống với textureId
		do
		{
			metaTextureStream >> ID;
			if (ID == textureId)
				break;

			// Xuống hàng
			while (metaTextureStream.get() != '\n');
		} while (1);

		metaTextureStream >> rows >> cols >> count;

		char* fileName = new char[100];
		metaTextureStream.get();
		metaTextureStream.getline(fileName, 100);

		//Đóng file
		metaTextureStream.close();
		metaTextureStream.clear();

		CTexture* tmpTexture = new CTexture(fileName, cols, rows, count);
		m_aTexture.insert(::pair<int, CTexture*>(textureId, tmpTexture));

		iTexture = m_aTexture.find(textureId);

	}
	return iTexture->second;
}

CSprite* CResourcesManager::GetSprite(int spriteId)
{
	CSprite* result = NULL;
	map<int, CSprite*>::iterator iSprite;

	// Tìm sprite có spriteID trong mảng m_aSprite
	iSprite = m_aSprite.find(spriteId);

	if (iSprite == m_aSprite.end()) // Nếu chưa có sprite này
	{
		// Mở file chứa các dữ liệu tương ứng
		fstream spriteData;
		spriteData.open(m_szSpriteFileData, ios::in);

		if (!spriteData.is_open())
		{
			OutputDebugString("[resourcesmanager.cpp] Fail to open Meta Sprite file.");
			return NULL;
		}

		// Các thông tin cần lấy ra 
		int ID, animationTime, startIndex, endIndex, textureID;

		// Duyệt file để tìm thông tin
		do
		{
			spriteData >> ID;
			if (spriteId == ID)
				break;

			// Xuống hàng
			while (spriteData.get() != '\n');
		} while (1);

		spriteData >> animationTime >> startIndex >> endIndex >> textureID;

		// Đóng file
		spriteData.close();
		spriteData.clear();

		// Tạo sprite mới
		CSprite* tempSprite = new CSprite(GetTexture(textureID), startIndex, endIndex, animationTime);

		// Thêm sprite đó vào danh sách
		m_aSprite.insert(pair<int, CSprite*>(spriteId, tempSprite));

		// Trả về sprite vừa mới tạo
		return tempSprite;
	}
	return iSprite->second;
}

//CSound* CResourcesManager::GetSound(int soundId)
//{
//	map<int, CSound*>::iterator iSound;
//
//	// Tìm texture có ID sound ID trong mảng m_aSound
//	iSound = m_aSounds.find(soundId);
//
//	if (iSound == m_aSounds.end()) // Nếu chưa có sound này
//	{
//		// Mở file chứa các dữ liệu tương ứng
//		fstream soundData;
//		soundData.open(m_szMetaSoundFile, ios::in);
//
//		if (!soundData.is_open())
//		{
//			output_print("[ERROR] Failed to open file sound.txt\n");
//			return NULL;
//		}
//
//		// Các thông tin cần lấy
//		int ID;
//
//		do
//		{
//			soundData >> ID;
//			if (ID == soundId)
//				break;
//
//			// Xuống hàng
//			while (soundData.get() != '\n');
//		} while (1);
//
//		// Tên file âm thanh
//		char fileName[100];
//		soundData.get();
//		soundData.getline(fileName, 100);
//
//		// Đóng file
//		soundData.close();
//		soundData.clear();
//
//
//
//		CSound* tempSound;
//		HRESULT result = m_pSoundManager->Create(&tempSound, fileName);
//		if (result != S_OK)
//		{
//			output_print("[ERROR] Failed to load sound from file %s\n", fileName);
//			return NULL;
//		}
//		m_aSounds.insert(::pair<int, CSound*>(soundId, tempSound));
//
//		// Lấy về sound vừa thêm vào
//		iSound = m_aSounds.find(soundId);
//	}
//	return iSound->second;
//}

CResourcesManager* CResourcesManager::GetInstance()
{
	if (!s_ResManagerInstance)
		s_ResManagerInstance = new CResourcesManager();

	return s_ResManagerInstance;
}
#pragma endregion