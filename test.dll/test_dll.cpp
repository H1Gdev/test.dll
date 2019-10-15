// test.dll.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"

#include "test_dll.h"

namespace test {

class DllClass::Impl
{
public:
	Impl();
	~Impl();

	int Test();
private:
	int value_;
};

DllClass::Impl::Impl()
	:value_(100)
{
}

DllClass::Impl::~Impl()
{
}

int DllClass::Impl::Test()
{
	return value_;
}


DllClass::DllClass()
	:impl_(new Impl)
{
}

DllClass::~DllClass()
{
	delete impl_;
}

int DllClass::Test()
{
	return impl_->Test();
}

}
