// test.dll.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"

#include "test.dll.h"

namespace test {

class DllClass::Impl
{
public:
	Impl();
	~Impl();

	int Test();
private:
	int value;
};

DllClass::Impl::Impl()
	:value(100)
{
}

DllClass::Impl::~Impl()
{
}

int DllClass::Impl::Test()
{
	return value;
}


DllClass::DllClass()
	:pimpl(new Impl)
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
