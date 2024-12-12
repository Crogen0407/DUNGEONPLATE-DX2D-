#pragma once
#include "fmod.hpp"
#pragma comment(lib, "fmod_vc")
enum class SOUND_CHANNEL //���帶�� ä��
{
	BGM, EFFECT0, EFFECT1, EFFECT2, EFFECT3, END
};
struct tSoundInfo
{
	FMOD::Sound* pSound; // ���� ���� �޸�
	SOUND_CHANNEL sound_chanel;		// ���帶�� ������������
};
class Texture;
class ResourceManager
{
	DECLARE_SINGLE(ResourceManager);
public:
	void Init();
	const wchar_t* GetResPath() const { return m_resourcePath; }
public:
	Texture* TextureLoad(const wstring& _key, const wstring& _path);
	Texture* TextureFind(const wstring& _key);
	void Release();
public:
	void LoadSound(const wstring& _key, const wstring& _path, bool _isLoop);
	void LoadSound(const wstring& _key, const wstring& _path, SOUND_CHANNEL sound_channel);
	void Play(const wstring& _key);
	void Stop(SOUND_CHANNEL _channel);
	void Volume(SOUND_CHANNEL _channel, float _vol);
	void Pause(SOUND_CHANNEL _channel, bool _ispause);
	bool AddFont(wstring fileName) {
		if (fontNames.find(fileName) == fontNames.end())
		{
			std::wstring path;
			path.append(L".ttf");
			AddFontResource(path.c_str());
			fontNames.insert(fileName);
			return true;
		}
		return false;
	}
private:
	tSoundInfo* FindSound(const wstring& _key);
private:
	wchar_t m_resourcePath[255] = {};
	map<wstring, Texture*> m_mapTextures;
	map<wstring, tSoundInfo*> m_mapSounds;
	FMOD::System* m_pSoundSystem; // ���� �ý���
	FMOD::Channel* m_pChannel[(UINT)SOUND_CHANNEL::END]; // ����� ä��
	std::set<wstring> fontNames;
};

