#include "pch.h"
#include "ReadSlipStream.h"
#include <cstdlib>
#include <string.h>

CReadSlipStream::CReadSlipStream()
{

}

CReadSlipStream::~CReadSlipStream()
{

}

 bool CReadSlipStream::SLipToByte(CSlipStream& stream)
 {
	bool startCheck = false;
	bool endCheck = false;
	char data;
	int removesize = 0;

	const char* buf = GetBuffer();
	for (unsigned int i = 0; i < GetBufferHead(); i++)
	{
		//Start Check
		if (buf[i] == (char)0xC0 && buf[i + 1] == (char)0xC0 && false == startCheck)
			continue;

		if (buf[i] == (char)0xC0 && buf[i + 1] != (char)0xC0 && false == startCheck)
		{
			startCheck = true;
			continue;
		}

		//End Check
		if (buf[i] == (char)0xC0 && true == startCheck) {
			endCheck = true;
			removesize = i;
			break;
		}

		//Body Check
		if (buf[i] == (char)0xDB && buf[i + 1] == (char)0xDC) //0xC0
		{
			i++;
			data = (char)0xC0;
			stream.AddByte(&data, 1);
			continue;
		}

		if (buf[i] == (char)0xDB && buf[i + 1] == (char)0xDD) //0xDB
		{
			i++;
			data = (char)0xDB;
			stream.AddByte(&data, 1);
			continue;
		}

		data = buf[i];
		stream.AddByte(&data, 1);
	}

	if (true == startCheck && true == endCheck)
	{
		RemoveByte(removesize);
		return true;
	}
	else
	{
		stream.Claer();
		return false;
	}

}

bool CReadSlipStream::PushSlipByte(const CSlipStream& stream)
{
	AddByte(stream.GetBuffer(), stream.GetBufferHead());
	return true;
}

CSlipStream CReadSlipStream::PopByte()
{
	CSlipStream stream;
	SLipToByte(stream);
	return stream;
}




