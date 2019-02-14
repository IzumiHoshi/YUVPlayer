#pragma once
#include "Convert.h"
#include <fstream>
class PlayWnd
{
public:
	PlayWnd(CWnd *pWnd);
	int SetConfig(CConfig& config);
	int Open(const char* filename);
	int Close();
	int Play();
	int Stop();
	int Pause();
	int Resume();
	int PreFrame();
	int NextFrame();
	int FastBackward() { return -1; }
	int FastForward() { return -1; }
	int SlowBackWard() { return -1; }
	int SlowForward() { return -1; }

	~PlayWnd();
private:
	int MallocInputFrame();
	int MallocRenderFrame();
	int ReadFrame();
	CWnd* m_PlayWnd;
	std::ifstream m_InFile;
	CConfig m_config;
	char* m_InputFrameData;
	char* m_RenderData;
	char m_filename[MAX_PATH];
	unsigned int m_InputFrameSize;
	unsigned int m_RenderFrameSize;
	unsigned int m_CurrentFrame;
	unsigned int m_TotalFrame;
	unsigned long long m_FileLenth;
};

