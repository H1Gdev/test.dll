#pragma once

#ifdef TESTDLL_EXPORTS
#define TESTDLL_API __declspec(dllexport)
#else
#define TESTDLL_API __declspec(dllimport)
#endif

namespace test {

// PImpl(Pointer to implementation)
class TESTDLL_API DllClass
{
public:
	DllClass();
	~DllClass();

	int Test();
private:
	class Impl;
	Impl* pimpl;
};

}
