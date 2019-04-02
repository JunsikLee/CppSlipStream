// CppSlipStream.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include "ReadSlipStream.h"
#include "WriteSlipStream.h"

int main()
{
    std::cout << "Hello World!\n";

	char temp1[] = { 0xC0, 0xDB, 0x01, 0x01, 0x01, 0x01, 0x01, 0xC0, 0xDB };
	char temp2[] = { 0xC0, 0xDB, 0x02, 0x02, 0x02, 0x02, 0x02, 0xC0, 0xDB };
	char temp3[] = { 0xC0, 0xDB, 0x03, 0x03, 0x03, 0x03, 0x03, 0xC0, 0xDB };
	char temp4[] = { 0xC0, 0xDB, 0x04, 0x04, 0x04, 0x04, 0x04, 0xC0, 0xDB };

	CWriteSlipStream* w = new CWriteSlipStream();
	CReadSlipStream* r = new CReadSlipStream();

	w->PushByte(CSlipStream(temp1, sizeof(temp1)));
	CSlipStream w1 = w->PopSlipByte();
	w->PushByte(CSlipStream(temp2, sizeof(temp2)));
	CSlipStream w2 = w->PopSlipByte2();
	w->PushByte(CSlipStream(temp3, sizeof(temp3)));
	CSlipStream w3 = w->PopSlipByte();
	w->PushByte(CSlipStream(temp4, sizeof(temp4)));
	CSlipStream w4 = w->PopSlipByte();
	
	r->PushSlipByte(w1);
	r->PushSlipByte(w2);
	r->PushSlipByte(w3);
	r->PushSlipByte(w4);

	CSlipStream r1 = r->PopByte();
	CSlipStream r2 = r->PopByte();
	CSlipStream r3 = r->PopByte();
	CSlipStream r4 = r->PopByte();

	delete r;
	delete w;
}
