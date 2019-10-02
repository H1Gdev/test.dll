// test.dll.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"

#include "test.dll.h"

namespace test {

class DllClassImpl
{
public:
	DllClassImpl();
	~DllClassImpl();

	int Test();
private:
	int value;
};

DllClassImpl::DllClassImpl()
	:value(100)
{
}

DllClassImpl::~DllClassImpl()
{
}

int DllClassImpl::Test()
{
	return value;
}


DllClass::DllClass()
	:pimpl(new DllClassImpl)
{
}

DllClass::~DllClass()
{
	delete pimpl;
}

int DllClass::Test()
{
	return pimpl->Test();
}

}
