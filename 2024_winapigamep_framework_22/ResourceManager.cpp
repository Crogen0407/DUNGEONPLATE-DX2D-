#include "pch.h"
#include "ResourceManager.h"
#include "Core.h"
#include "Texture.h"

void ResourceManager::Init()
{
	::CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_wicFactory)
	);

	::DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED, 
		__uuidof(IDWriteFactory), 
		&_writeFactory
	);

	::GetCurrentDirectory(255, m_resourcePath);
	wcscat_s(m_resourcePath, 255, L"\\Resource\\");

 	FMOD::System_Create(&m_pSoundSystem); // 시스템 생성 함수
	// 채널수, 사운드 모드
	if (m_pSoundSystem != nullptr)
		m_pSoundSystem->init((int)SOUND_CHANNEL::END, FMOD_INIT_NORMAL, nullptr);

}

Texture* ResourceManager::TextureLoad(const wstring& _key, const wstring& _path)
{
	Texture* pTex = TextureFind(_key);
	if (nullptr != pTex)
		return pTex;

	// 1. 경로 설정
	wstring texpath = m_resourcePath;
	texpath += _path;
	
	ComPtr<IWICBitmapDecoder> decoder;
	_wicFactory->CreateDecoderFromFilename(
		(L"Resource\\" + _path).c_str(),  // 불러올 이미지 파일 경로
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&decoder
	);

	// 첫 번째 프레임 가져오기
	ComPtr<IWICBitmapFrameDecode> frame;
	decoder->GetFrame(0, &frame);

	// 포맷 변환기 생성
	ComPtr<IWICFormatConverter> converter;
	_wicFactory->CreateFormatConverter(&converter);

	// 픽셀 포맷을 Direct2D 호환 포맷으로 변환
	converter->Initialize(
		frame.Get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0,
		WICBitmapPaletteTypeCustom
	);

	// Direct2D 비트맵으로 변환
	ComPtr<ID2D1Bitmap> bitmap;

	GET_SINGLE(Core)->GetRenderTarget()->CreateBitmapFromWicBitmap(
		converter.Get(),
		nullptr,
		&bitmap
	);

	pTex = new Texture;
	pTex->SetBitmap(bitmap);
	pTex->SetKey(_key);
	pTex->SetPath(texpath);
	m_mapTextures.insert({_key,pTex});
	return pTex;
}

Texture* ResourceManager::TextureFind(const wstring& _key)
{
	auto iter = m_mapTextures.find(_key);
	if (iter != m_mapTextures.end())
		return iter->second;
	return nullptr;
}

void ResourceManager::Release()
{
	map<wstring, Texture*>::iterator iter;
	for (iter = m_mapTextures.begin(); iter != m_mapTextures.end(); ++iter)
		delete iter->second;
	m_mapTextures.clear();

	// SOUND
	map<wstring, tSoundInfo*>::iterator itersod;
	for (itersod = m_mapSounds.begin(); itersod != m_mapSounds.end(); ++itersod)
	{
		if (nullptr != itersod->second)
			delete itersod->second;
	}
	m_mapSounds.clear();

	// 다 쓰고 난 후 시스템 닫고 반환
	m_pSoundSystem->close();
	m_pSoundSystem->release();
}

void ResourceManager::LoadSound(const wstring& _key, const wstring& _path, bool _isLoop)
{
	if (FindSound(_key))
		return;
	wstring strFilePath = m_resourcePath;
	strFilePath += _path;

	// wstring to string
	std::string str;
	str.assign(strFilePath.begin(), strFilePath.end());

	tSoundInfo* ptSound = new tSoundInfo;
	ptSound->sound_chanel = SOUND_CHANNEL::BGM;

	// 루프할지 말지 결정
	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // 반복 출력
	if (!_isLoop)
	{
		ptSound->sound_chanel = SOUND_CHANNEL::EFFECT0;
		eMode = FMOD_DEFAULT; // 사운드 1번만 출력
	}

	// 사운드 객체를 만드는 것은 system임.
							//파일경로,  FMOD_MODE, NULL, &sound
	m_pSoundSystem->createSound(str.c_str(), eMode, nullptr, &ptSound->pSound);
	m_mapSounds.insert({ _key, ptSound });
}

void ResourceManager::LoadSound(const wstring& _key, const wstring& _path, SOUND_CHANNEL sound_channel)
{
	if (FindSound(_key))
		return;
	wstring strFilePath = m_resourcePath;
	strFilePath += _path;

	// wstring to string
	std::string str;
	str.assign(strFilePath.begin(), strFilePath.end());

	// 루프할지 말지 결정
	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // 반복 출력
	if (sound_channel != SOUND_CHANNEL::BGM)
		eMode = FMOD_DEFAULT; // 사운드 1번만 출력

	tSoundInfo* ptSound = new tSoundInfo;
	ptSound->sound_chanel = sound_channel;
	// 사운드 객체를 만드는 것은 system임.
							//파일경로,  FMOD_MODE, NULL, &sound
	m_pSoundSystem->createSound(str.c_str(), eMode, nullptr, &ptSound->pSound);
	m_mapSounds.insert({ _key, ptSound });
}

void ResourceManager::Play(const wstring& _key)
{
	tSoundInfo* ptSound = FindSound(_key);
	if (!ptSound)
		return;
	m_pSoundSystem->update(); // play할때 update를 주기적으로 호출해야 사운드가 정지되지 않음.
	SOUND_CHANNEL eChannel = ptSound->sound_chanel;
	// 사운드 재생 함수. &channel로 어떤 채널을 통해 재생되는지 포인터 넘김
	m_pSoundSystem->playSound(ptSound->pSound, nullptr, false, &m_pChannel[(UINT)eChannel]);
}

void ResourceManager::Stop(SOUND_CHANNEL _channel)
{
	m_pChannel[(UINT)_channel]->stop();
}

void ResourceManager::Volume(SOUND_CHANNEL _channel, float _vol)
{
	// 0.0 ~ 1.0 볼륨 조절
	m_pChannel[(UINT)_channel]->setVolume(_vol);
}

void ResourceManager::Pause(SOUND_CHANNEL _channel, bool _ispause)
{
	// bool값이 true면 일시정지. 단, 이 함수를 쓰려면 Createsound할때 
// FMOD_MODE가 FMOD_LOOP_NORMAL 이어야 함.
	m_pChannel[(UINT)_channel]->setPaused(_ispause);
}

tSoundInfo* ResourceManager::FindSound(const wstring& _key)
{
	map<wstring, tSoundInfo*>::iterator iter = m_mapSounds.find(_key);

	if (iter == m_mapSounds.end())
		return nullptr;
	return iter->second;
}
