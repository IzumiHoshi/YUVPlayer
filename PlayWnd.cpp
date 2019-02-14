#include "stdafx.h"
#include "PlayWnd.h"

PlayWnd::PlayWnd(CWnd * pWnd)
	: m_PlayWnd(pWnd)
	, m_InputFrameData(NULL)
	, m_RenderData(NULL)
	, m_InputFrameSize(0)
	, m_RenderFrameSize(0)
	, m_CurrentFrame(0)
	, m_TotalFrame(0)
	, m_FileLenth(0)
{
	memset(m_filename, 0, MAX_PATH);
}

int PlayWnd::SetConfig(CConfig & config)
{
	m_config = config;
	MallocInputFrame();
	MallocRenderFrame();
	return 0;
}

int PlayWnd::Open(const char * filename)
{
	memcpy_s(m_filename, MAX_PATH, filename, strnlen_s(filename, MAX_PATH));

	m_InFile.open(m_filename, std::ios::binary);
	if (!m_InFile.is_open())
	{
		TRACE("Error opening file");
		return -1;
	}

	m_InFile.seekg(0, m_InFile.end);
	m_FileLenth = m_InFile.tellg();
	m_InFile.seekg(0, m_InFile.beg);

	if (m_FileLenth == 0)
	{
		TRACE("Error no data");
		return -1;
	}

	m_CurrentFrame = 0;
	m_TotalFrame = unsigned int(m_FileLenth / m_InputFrameSize);

	if (m_TotalFrame == 0)
	{
		TRACE("Error less than one frame");
	}
	return 0;
}

int PlayWnd::Close()
{
	return 0;
}

int PlayWnd::Play()
{
	return 0;
}

int PlayWnd::Stop()
{
	return 0;
}

int PlayWnd::Pause()
{
	return 0;
}

int PlayWnd::Resume()
{
	return 0;
}

int PlayWnd::PreFrame()
{
	if (m_CurrentFrame <= 1)
	{
		return 0;
	}
	m_CurrentFrame--;
	ReadFrame();
	return 0;
}

int PlayWnd::NextFrame()
{
	if (m_CurrentFrame == m_TotalFrame)
	{
		return 0;
	}
	ReadFrame();
	m_CurrentFrame++;
	return 0;
}

PlayWnd::~PlayWnd()
{
	m_PlayWnd = NULL;
	if (m_InFile.is_open())
	{
		m_InFile.close();
	}
	SAFE_DELETE_ARRAY(m_InputFrameData);
	SAFE_DELETE_ARRAY(m_RenderData);
}

int PlayWnd::MallocInputFrame()
{
	//malloc size
	unsigned int inputFrameSize = 0;
	unsigned int bytePerPixel = (m_config.bit_depth + 7) / 8;
	unsigned int pixPoints = m_config.width * m_config.height;
	switch (m_config.pix_fmt)
	{
	case FMT_YUV420:
	case FMT_YV12:
	case FMT_NV12:
	case FMT_NV21:
		inputFrameSize = pixPoints * bytePerPixel * 3 / 2;
		break;
	case FMT_YUV422:
	case FMT_YV16:
	case FMT_YUYV:
	case FMT_YVYU:
	case FMT_UYVY:
	case FMT_VYUY:
	case FMT_NV16:
	case FMT_NV61:
		inputFrameSize = pixPoints * bytePerPixel * 2;
		break;
	case FMT_YUV444:
	case FMT_RGB24:
	case FMT_BGR24:
		inputFrameSize = pixPoints * bytePerPixel * 3;
		break;
	case FMT_Y:
		inputFrameSize = pixPoints * bytePerPixel;
		break;
	default:
		inputFrameSize = pixPoints * bytePerPixel * 3;
		break;
	}

	if (inputFrameSize == m_InputFrameSize)
	{
		return 0;
	}

	SAFE_DELETE_ARRAY(m_InputFrameData);
	m_InputFrameData = new char[inputFrameSize];
	m_InputFrameSize = inputFrameSize;

	return 0;
}

int PlayWnd::MallocRenderFrame()
{
	unsigned int renderFrameSize = m_config.width * m_config.height;
	if (renderFrameSize == m_RenderFrameSize)
	{
		return 0;
	}

	SAFE_DELETE_ARRAY(m_RenderData);
	m_RenderData = new char[renderFrameSize];
	m_RenderFrameSize = renderFrameSize;
	return 0;
}

int PlayWnd::ReadFrame()
{
	m_InFile.seekg(0, m_CurrentFrame * m_InputFrameSize);
	m_InFile.read(m_InputFrameData, m_InputFrameSize);
	return 0;
}
