#include "pch.h"
#include "WriteSlipStream.h"


CWriteSlipStream::CWriteSlipStream() : CSlipStream()
{
}


CWriteSlipStream::~CWriteSlipStream()
{
}

bool CWriteSlipStream::ByteToSLip(const char* datas, unsigned int size)
{
	char data;

	//패킷 시작
	data = (char)0xC0;
	AddByte(&data, 1);

	//데이터 변환
	for (unsigned int i = 0; i < size; i++)
	{
		if ((char)0xC0 == datas[i])
		{
			data = (char)0xDB;
			AddByte(&data, 1);
			data = (char)0xDC;
			AddByte(&data, 1);
		}
		else if ((char)0xDB == datas[i])
		{
			data = (char)0xDB;
			AddByte(&data, 1);
			data = (char)0xDD;
			AddByte(&data, 1);
		}
		else
		{
			data = datas[i];
			AddByte(&data, 1);
		}
	}

	//패킷 종료
	data = (char)0xC0;
	AddByte(&data, 1);
	return true;
}

bool CWriteSlipStream::PushByte(const CSlipStream& stream)
{
	ByteToSLip(stream.GetBuffer(), stream.GetBufferHead());
	return true;
}

CSlipStream CWriteSlipStream::PopSlipByte()
{
	CSlipStream stream (GetBuffer(), GetBufferHead());
	Claer();
	return stream;
}

CSlipStream CWriteSlipStream::PopSlipByte2()
{
	CSlipStream stream(GetBuffer(), GetBufferHead() - 2);
	Claer();
	return stream;
}





