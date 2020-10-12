#if !defined(_WINVNC_VNCZ)
#define _WINVNC_VNCZ
#pragma once

#ifdef _INTERNALLIB
#include <zlib.h>
#ifndef ULTRAVNC_VEYON_SUPPORT
#include <zstd.h>
#endif
#else
#include "../zlib/zlib.h"
#include "../zstd-1.4.4/lib/zstd.h"
#endif

class UltraVncZ 
{
public:
	UltraVncZ();
	~UltraVncZ();
#ifndef ULTRAVNC_VEYON_SUPPORT
	UINT compressZstd(int compresslevel, UINT avail_in, UINT avail_out, BYTE * next_in, BYTE *next_out);
#endif
	UINT compressZlib(int compresslevel, UINT avail_in, UINT avail_out, BYTE * next_in, BYTE *next_out);
	UINT compress(int compresslevel, UINT avail_in, UINT avail_out, BYTE * next_in, BYTE *next_out);

#ifndef ULTRAVNC_VEYON_SUPPORT
	int decompressZstd(UINT &avail_in, UINT &avail_out, BYTE * next_in, BYTE *next_out);
#endif
	int decompressZlib(UINT &avail_in, UINT &avail_out, BYTE * next_in, BYTE *next_out);
	int decompress(UINT &avail_in, UINT &avail_out, BYTE * next_in, BYTE *next_out, bool zstd);

	UINT maxSize(UINT size);
	UINT minSize();
	void set_use_zstd(bool use_zstd);

	void endInflateStream(bool zstd);
protected:
	z_stream_s  compStream;
	z_stream decompStream;
	bool compStreamInitedZlib;
	bool decompStreamInitedZlib;
	bool compStreamInitedZstd;
	bool decompStreamInitedZstd;
	UINT MAX_SIZE;
#ifndef ULTRAVNC_VEYON_SUPPORT
	bool use_zstd;

	ZSTD_CStream* cstream;
	ZSTD_outBuffer* outBufferC;
	ZSTD_inBuffer* inBufferC;

	ZSTD_DStream* dstream;
	ZSTD_outBuffer* outBufferD;
	ZSTD_inBuffer* inBufferD;
#endif

	int compresslevel;
	/*void createCDict(int cLevel, ZSTD_CStream* cstream);
	void createDDict();
	UINT compressZstd_usingCDict(int compresslevel, UINT avail_in, UINT avail_out, BYTE * next_in, BYTE *next_out);
	int decompressZstd_usingCDict(UINT &avail_in, UINT &avail_out, BYTE * next_in, BYTE *next_out);*/
};

#endif // _WINVNC_VNCZ

