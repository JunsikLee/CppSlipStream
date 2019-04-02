#pragma once
#include "SlipStream.h"
class CReadSlipStream : public CSlipStream
{
public:
	CReadSlipStream();
	~CReadSlipStream();

private:
	bool SLipToByte(CSlipStream& stream);

public:
	bool PushSlipByte(const CSlipStream& stream);
	CSlipStream PopByte();
};

