#pragma once
#define SAFE_DELETE(p) if(p) { delete p; p=NULL; }
#define SAFE_DELETE_ARRAY(p) if(p) { delete[] p; p=NULL; }

typedef enum
{
	FMT_UNKNOW = -1,
	FMT_Y = 0,
	FMT_YUV420 = 1,
	FMT_YV12 = 2,
	FMT_YUV422 = 3,
	FMT_YV16 = 4,
	FMT_YUV444 = 5,
	FMT_YUYV = 6,
	FMT_YVYU = 7,
	FMT_UYVY = 8,
	FMT_VYUY = 9,
	FMT_NV12 = 10,
	FMT_NV21 = 11,
	FMT_NV16 = 12,
	FMT_NV61 = 13,
	FMT_RGB24 = 14,
	FMT_BGR24 = 15,
}PIX_FMT;

typedef struct CONVERT_CONFIG {
	PIX_FMT pix_fmt;
	unsigned int width;
	unsigned int height;
	unsigned int bit_depth;
	unsigned int tool;
	CONVERT_CONFIG()
	{
		pix_fmt = FMT_UNKNOW;
		width = 0;
		height = 0;
		bit_depth = 8;
		tool = 0;
	}
	CONVERT_CONFIG& operator=(const CONVERT_CONFIG& c)
	{
		this->pix_fmt = c.pix_fmt;
		this->width = c.width;
		this->height = c.height;
		this->bit_depth = c.bit_depth;
		this->tool = c.tool;
		return *this;
	}
}CConfig;

class Convert
{
public:
	Convert(CConfig pConfig);
	virtual ~Convert();
	virtual int convert(const char *pInData, char* pOutData);
protected:
	CConfig m_config;
};