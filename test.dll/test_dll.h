#pragma once

#include <memory>

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

	DllClass(const DllClass&) = delete;
	DllClass& operator=(const DllClass&) = delete;

	int Test();
private:
	class Impl;
	std::unique_ptr<Impl> impl_;
};

}
