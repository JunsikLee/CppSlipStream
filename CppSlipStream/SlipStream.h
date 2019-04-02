#pragma once

class CSlipStream
{
public:
	CSlipStream();
	CSlipStream(const char* bytes, unsigned int size);
	CSlipStream(const CSlipStream & slipstream);
	virtual ~CSlipStream();

private:
	char*			m_Buf;
	unsigned int	m_BufSize;
	unsigned int	m_BufHead;

private:
	void ReallocBuffer(unsigned int size);
	void Init();

public:
	unsigned int GetBufferSize() const;
	const char* GetBuffer() const;
	unsigned int GetBufferHead() const;

public:
	void AddByte(const char* bytes, unsigned int size);
	bool RemoveByte(unsigned int size);
	void Claer();
};

