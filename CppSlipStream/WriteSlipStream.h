#pragma once
#include "SlipStream.h"
class CWriteSlipStream : public CSlipStream
{
public:
	CWriteSlipStream();
	~CWriteSlipStream();

private:
	bool ByteToSLip(const char* datas, unsigned int size);

public:
	bool PushByte(const CSlipStream& stream);
	CSlipStream PopSlipByte();
	CSlipStream PopSlipByte2();
};

