#include "pch.h"
#include "SlipStream.h"
#include <cstdlib>
#include <string.h>

CSlipStream::CSlipStream()
{
	Init();
}

CSlipStream::CSlipStream(const char* bytes, unsigned int size)
{
	Init();
	AddByte(bytes, size);
}

CSlipStream::CSlipStream(const CSlipStream & slipstream)
{
	Init();
	AddByte(slipstream.GetBuffer(), slipstream.GetBufferHead());
}

CSlipStream::~CSlipStream()
{
	ReallocBuffer(0);
}

void CSlipStream::ReallocBuffer(unsigned int size)
{
	if (0 == size)
	{
		std::free(m_Buf);
		m_Buf = NULL;
		m_BufSize = 0;
		m_BufHead = 0;
	}
	else
	{
		m_Buf = static_cast<char*>(std::realloc(m_Buf, size));
		m_BufSize = size;
	}
}

void CSlipStream::Init()
{
	m_BufSize = 0;
	m_BufHead = 0;
	m_Buf = NULL;
	ReallocBuffer(10);
}

unsigned int CSlipStream::GetBufferSize() const
{
	return m_BufSize;
}

unsigned int CSlipStream::GetBufferHead() const
{
	return m_BufHead;
}

const char* CSlipStream::GetBuffer() const
{
	return m_Buf;
}

void CSlipStream::AddByte(const char* bytes, unsigned int size)
{
	if (!(GetBufferSize() >= GetBufferHead() + size))
		ReallocBuffer((GetBufferSize() + size) * 2);

	if (size == 0)
		return;

	memcpy(m_Buf + m_BufHead, bytes, size);
	m_BufHead += size;
}

bool CSlipStream::RemoveByte(unsigned int size)
{
	if (m_BufHead < size || 0 == size)
		return false;

	memmove(m_Buf, m_Buf + size, m_BufHead - size);
	m_BufHead -= size;

	for (int i = GetBufferHead(); i < GetBufferSize(); i++)
		m_Buf[i] = 0;

	return true;
}

void CSlipStream::Claer()
{
	ReallocBuffer(0);
}
