#include "pch.h"
#include <iostream>

//#define TEST_C_PLUS_PLUS_ELEVEN_MOVE
//#define TEST_C_PLUS_PLUS_ELEVEN_SMART_POINTER
#define TEST_C_PLUS_PLUS_ELEVEN_AUTO
//#define TEST_C_PLUS_PLUS_ELEVEN_VECTOR
//#define TEST_C_PLUS_PLUS_ELEVEN_ITERATION
//#define TEST_C_PLUS_PLUS_ELEVEN_ENUM_CLASS
//#define TEST_C_PLUS_PLUS_ELEVEN_DEFAULT_DELETE
//#define TEST_C_PLUS_PLUS_ELEVEN_IN_CLASS_INITIALIZER
//#define TEST_C_PLUS_PLUS_ELEVEN_CONSTANT_EXPRESSION
//#define TEST_C_PLUS_PLUS_ELEVEN_LAMBDA

#ifdef TEST_C_PLUS_PLUS_ELEVEN_MOVE
#include <string>
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_SMART_POINTER
#include <memory>
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_VECTOR
#include <vector>
#include <algorithm>
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_ITERATION
#include <algorithm>
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_LAMBDA
#include <functional>
#endif

#ifdef TEST_C_PLUS_PLUS_ELEVEN_AUTO
auto test0(int a, int b)
{
    return a + b + 0xffffffff;
}
auto test1(int a, int b) -> decltype(a + b)
{
    return a + b + 0xffffffff;
}
#endif

#ifdef TEST_C_PLUS_PLUS_ELEVEN_CONSTANT_EXPRESSION
constexpr
static int square(int x)
{
    return x * x;
}
static int square2(int x)
{
    return x * x;
}
#endif

#ifdef TEST_C_PLUS_PLUS_ELEVEN_ENUM_CLASS
#if 1
enum class Alphabet
#else
enum struct Alphabet
#endif
{
    A,
    B,
    C,
    D,
};

// default type is int.
enum class Color : char
{
    Red,
    Green,
    Blue,
#if 0
    // warning.
    Black = 300,
#endif
};

enum class ETest1
{
    // empty.
};

enum class ETest2
{
    ZERO = 0,
    ONE,
    TWO,
    THREE,
    END,
};
enum class ETest21
{
    FOUR = static_cast<ETest21>(ETest2::END),
    FIVE,
    SIX,
};
#endif

#ifdef TEST_C_PLUS_PLUS_ELEVEN_DEFAULT_DELETE
class Inner
{
public:
    Inner() { std::cout << "Inner" << std::endl; }
    ~Inner() { std::cout << "~Inner" << std::endl; }
};
#endif

#ifdef TEST_C_PLUS_PLUS_ELEVEN_LAMBDA
using func = int(*)(int, int);
#endif

class Test
{
public:
#ifdef TEST_C_PLUS_PLUS_ELEVEN_MOVE
#if 1
    Test()
        : value(nullptr)
    {
        std::cout << "Test::Test()" << std::endl;
}
    ~Test()
    {
        std::cout << "Test::~Test()" << std::endl;
        delete value;
    }
    // copy
    Test(const Test& other)
    {
        std::cout << "Test::Test(const Test&)" << std::endl;
        if (other.value)
            value = new int(*other.value);

    }
    Test& operator=(const Test& other)
    {
        std::cout << "Test& Test::operator=(const Test&)" << std::endl;
        if (this == &other)
            return *this;

        if (other.value)
            delete value;
        value = new int(*other.value);

        return *this;
    }
    // move
    Test(Test&& other)
        : value(other.value)
    {
        std::cout << "Test::Test(Test&&)" << std::endl;
        other.value = nullptr;
    }
    Test& operator=(Test&& other)
    {
        std::cout << "Test& Test::operator=(Test&&)" << std::endl;
        if (this == &other)
            return *this;

        delete value;
        value = other.value;
        other.value = nullptr;

        return *this;
    }
#elif 1
    Test() = default;
    ~Test() = default;
    // copy
    Test(const Test&) = default;
    Test& operator=(const Test&) = default;
    // move
    Test(Test&&) = default;
    Test& operator=(Test&&) = default;
#else
    Test() = delete;
    ~Test() = delete;
    // copy
    Test(const Test&) = delete;
    Test& operator=(const Test&) = delete;
    // move
    Test(Test&&) = delete;
    Test& operator=(Test&&) = delete;
#endif
public:
    int* value;
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_SMART_POINTER
    Test() { std::cout << "Test::Test()" << std::endl; }
    ~Test() { std::cout << "Test::~Test()" << std::endl; }
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_AUTO
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_VECTOR
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_ITERATION
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_ENUM_CLASS
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_DEFAULT_DELETE
#if 1
    // specified.
    Test() = default;
    ~Test() = default;
#endif

    const Inner& ref() const { return inner_; }
    const Inner* const& ptr() const { return pinner_; }
    const int& value() const { return value_; }
private:
    Inner inner_;
    Inner* pinner_;
    int value_;
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_IN_CLASS_INITIALIZER
    // in-class initializer
    int i0 = 100;
    std::string s0 = "test s0.";
    std::string s1{ "test s1." };

    static const int ci0 = 100;
    static const auto ca0 = 200;
#if 0
    // error
    static const std::string cs0 = "test c.";
    static constexpr std::string cs1 = "test c.";
#endif
    const std::string cs2 = "test c.";
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_CONSTANT_EXPRESSION
    static constexpr int c1 = square(100);
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_LAMBDA
#endif
};

#ifdef TEST_C_PLUS_PLUS_ELEVEN_MOVE
// Move sample class
class Sample
{
public:
#if 1
    Sample(Sample&& s)
        : name_(std::move(s.name_))
    {
    }
#else
    Sample(Sample&& s)
    {
        // call move operator.
        *this = std::move(s);
    }
#endif
    Sample(std::string&& name)
        : name_(std::move(name))
    {
    }
    Sample& operator=(Sample&& d)
    {
        name_ = std::move(d.name_);
        return *this;
    }
    Sample& operator=(std::string&& name)
    {
        name_ = std::move(name);
        return *this;
    }

    Sample()
        :name_("default.")
    {
    }
    const std::string& GetName() const
    {
        return name_;
    }
private:
    // std::string has move.
    std::string name_;
};
#endif

void test_cpp_eleven()
{
#ifdef TEST_C_PLUS_PLUS_ELEVEN_MOVE
    std::cout << "[Start]move" << std::endl;
    {
        std::cout << "Test A" << std::endl;
        {
            Test a;
            a.value = new int(100);

            // lvalue reference
            Test& lvalue = a;
            // rvalue reference
#if 1
            Test&& rvalue = std::move(a);
#else
        // equivalence
            Test&& rvalue = static_cast<Test&&>(a);
#endif
            // But 'rvalue' variable is lvalue...

            Test l0(lvalue);	// call copy constructor
            Test r0(rvalue);	// call copy constructor

            Test r1 = rvalue;	// call copy constructor

            Test r2(std::move(rvalue));	// call move constructor
        }

        std::cout << "Test B" << std::endl;
        {
            Test a;
            a.value = new int(100);

            // copy constructor
            Test b0(a);
            Test b1;
            // copy operator
            b1 = a;
        }

        std::cout << "Test C" << std::endl;
        {
            Test t0, t1;

            // move constructor
            Test c0(std::move(t0));
            Test c1;
            // move operator
            c1 = std::move(t1);
        }

        std::cout << "Test D" << std::endl;
        {
            std::string s1 = "test1";

            Sample sa1(std::move(s1));
            Sample sa2(std::move(sa1));
            Sample sa3;
            sa3 = std::move(sa2);
            Sample sa4;
            sa4 = std::move(sa3);

            std::cout << sa4.GetName() << std::endl;
        }
    }
    std::cout << "[End]" << std::endl;
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_SMART_POINTER
    std::cout << "[Start]smart pointer" << std::endl;
    {
        // auto_ptr (deprecated)
        // unique_ptr
        // shared_ptr
        // weak_ptr

        {
            int* v = new int(100);

            std::unique_ptr<int> a0;
            std::unique_ptr<int> a1(v);

            std::cout << std::boolalpha << "null check is " << (a0.get() != nullptr) << std::endl;
            std::cout << std::boolalpha << "null check is " << (a0.operator bool()) << std::endl;
            std::cout << std::boolalpha << "null check is " << (a1.get() != nullptr) << std::endl;
            std::cout << std::boolalpha << "null check is " << (a1.operator bool()) << std::endl;

            // Pointer
            const int* p = a1.get();
            // Reference
            const int& r = *a1;
        }
        {
            // new[] and delete[]
            std::initializer_list<std::uint8_t> initialize_list = { 0x50, 0x4e, 0x47 };
            std::unique_ptr<std::uint8_t[]> a2(new std::uint8_t[initialize_list.size()]);
            std::copy(initialize_list.begin(), initialize_list.end(), a2.get());
            std::cout << a2[2] << std::endl;
        }
        {
            auto up = std::unique_ptr<Test>();
            for (auto i = 0; i < 4; ++i)
            {
                std::cout << "reset (" << i << ")." << std::endl;
                up.reset(new Test);
            }
            std::cout << "End of reset test." << std::endl;
        }
        {
            auto p = new Test;
            {
                auto up = std::unique_ptr<Test>(p);
                up.release();
                std::cout << "release" << std::endl;
            }
            std::cout << "delete" << std::endl;
            delete p;
        }
    }
    std::cout << "[End]" << std::endl;
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_AUTO
    std::cout << "[Start]auto" << std::endl;
    {
        // * : omissible
        // & : not omissible

        auto i0 = 2;                                        // int
        const auto ci0 = 100;                               // const int

        auto l0 = 100L;                                     // long
        auto ll0 = 100LL;                                   // long long
        auto i1 = 2U;                                       // unsigned int
        auto l1 = 100UL;                                    // unsigned long
        auto ll1 = 100ULL;                                  // unsigned long long
        auto f0 = 1.8F;                                     // float
        auto d0 = 1.8;                                      // double
        auto ld0 = 100.0L;                                  // long double
        auto b0 = true;                                     // bool

        auto* pi0 = &i0;                                    // int*
        auto  pi1 = &i0;                                    // int*
        auto  pi2 = new int(3);                             // int*
        auto  pi3 = new int[2]{ 8, 9 };                     // int*

        auto** ppi0 = &pi0;                                 // int**
        auto   ppi1 = &pi0;                                 // int**

        auto&  r0 = i0;                                     // int&
        auto&  r1 = ci0;                                    // const int&
        const auto& r2 = i0;                                // const int&
        auto*& r3 = pi0;                                    // int*&
        auto&  r4 = pi0;                                    // int*&

        auto s0 = "c string";                               // const char*
        auto s1 = std::string("string");                    // std::string

        auto z0 = { 1, 2, 3 };                              // std::initializer_list<int>
        auto z1 = { 1u, 2u, 3u };                           // std::initializer_list<unsigned int>
        auto z2 = std::initializer_list<short>{ 1, 2, 3 };  // std::initializer_list<short>
        auto z3 = { 1.0, 2.0, 3.0, };                       // std::initializer_list<double>

        auto fu0 = [] {};                                   // void f()

        auto fc0 = test0(5, 10);                            // unsigned int
        auto fc1 = test1(5, 10);                            // int

        // error
#if 0
        auto test[] = { 1, 2, 3 };
#endif

        delete pi2;
        delete[] pi3;

    }
    std::cout << "[End]" << std::endl;
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_VECTOR
    std::cout << "[Start]vector" << std::endl;
    {
        // std::vector -> dynamic size
        // std::array  -> fixed size
        // std::list

        std::vector<std::uint8_t> v0 = { 0, 1, 2, 3 };
        std::for_each(v0.begin(), v0.end(), [](std::uint8_t x) { std::cout << (std::uint32_t)x << std::endl; });

        std::uint8_t d1[] = { 0, 1, 2, 3, 4 };
        std::size_t size1 = sizeof(d1);
        std::vector<std::uint8_t> v1(std::begin(d1), std::end(d1));
        d1[3] = 100;    // have no effect on v1.
        std::for_each(v1.begin(), v1.end(), [](std::uint8_t x) { std::cout << (std::uint32_t)x << std::endl; });

        std::size_t size2 = 6;
        std::uint8_t* d2 = new std::uint8_t[size2]{ 0, 1, 2, 3, 4, 5 };
        size2 *= sizeof(std::uint8_t);
        std::vector<std::uint8_t> v2(d2, d2 + size2);
        d2[3] = 200;    // have no effect on v2.
        std::for_each(v2.begin(), v2.end(), [](std::uint8_t x) { std::cout << (std::uint32_t)x << std::endl; });

        std::vector<std::uint8_t> v3(v0);
        v0[1] = 255;    // have no effect on v3.
        std::for_each(v3.begin(), v3.end(), [](std::uint8_t x) { std::cout << (std::uint32_t)x << std::endl; });

        delete[] d2;
    }
    std::cout << "[End]" << std::endl;
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_ITERATION
    std::cout << "[Start]Iteration" << std::endl;
    {
        // <algorithm> and <numeric>

        std::uint8_t a[] = { 1, 2, 3 };
        // Array
        std::for_each(std::begin(a), std::end(a), [](std::uint8_t x) { std::cout << (std::uint32_t)x << std::endl; });
    }
    std::cout << "[End]" << std::endl;
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_ENUM_CLASS
    std::cout << "[Start]enum class" << std::endl;
    {
        Alphabet e0 = Alphabet::A;
        ETest1 e1 = static_cast<ETest1>(10);

#if 0
        // operator << is not defined.
        std::cout << "Alphabet::A=" << e0 << std::endl;
#else
        std::cout << "Alphabet::A=" << static_cast<int>(e0) << std::endl;
#endif

        auto e2 = Alphabet::B;
        if (e2 == Alphabet::A)
            std::cout << "Alphabet::A" << std::endl;
        else if (e2 > Alphabet::D)
            std::cout << "unknown." << std::endl;

        auto e3 = Alphabet::B;
        auto e3_1 = e3;
#if 0
        // is not defined.
        auto e3_2 = e3 + e3;
        auto e3_1++;
        e3 += Alphabet::D;
#endif
    }
    std::cout << "[End]" << std::endl;
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_DEFAULT_DELETE
    std::cout << "[Start]default and delete" << std::endl;
    {
        {
            Test test;
            std::cout << &(test.ref()) << std::endl;
            std::cout << test.ptr() << std::endl;
            std::cout << test.value() << std::endl;
        }
    }
    std::cout << "[End]" << std::endl;
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_IN_CLASS_INITIALIZER
    std::cout << "[Start]in-class initializer" << std::endl;
    {
    }
    std::cout << "[End]" << std::endl;
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_CONSTANT_EXPRESSION
    std::cout << "[Start]constexpr" << std::endl;
    {
        // compile
        {
            constexpr auto a = square(100);

            const int b0 = 200;
            constexpr auto b1 = square(b0);

            constexpr auto c0 = 100;
            const auto c1 = 200;
        }
        // not compile
        {
            int v = 200;

#if 0
            // error
            constexpr auto a = square(v);
            constexpr auto d1 = square2(v);
#endif

            auto c1 = square(v);
            const auto c2 = square(v);
        }
    }
    std::cout << "[End]" << std::endl;
#endif
#ifdef TEST_C_PLUS_PLUS_ELEVEN_LAMBDA
    std::cout << "[Start]lambda" << std::endl;
    {
#if 1
        auto plus = [](int a, int b) { return a + b; };
#else
        struct F
        {
            auto operator ()(int a, int b) const -> decltype(a + b)
            {
                return a + b;
            }
        };
        auto plus = F();
#endif
        std::cout << "plus(3, 4)=" << plus(3, 4) << std::endl;

        // set to function pointer.
        func f0 = plus;
        std::cout << "f0(100, 23)=" << f0(100, 23) << std::endl;

        auto shortest = [] {};
        shortest();

        auto cap = 100;
        auto c_ref = [&]() { cap += 100; };
        auto c_copy = [=]() { auto c = cap; };

        std::cout << "cap=" << cap << std::endl;
        c_ref();
        std::cout << "cap=" << cap << std::endl;
        c_copy();
        std::cout << "cap=" << cap << std::endl;

        std::function<int(short, short, short, short)> f = [](short a, short b, short c, short d) -> int { return a * b * c * d; };
        std::cout << f(5, 10, 4, 2) << std::endl;
    }
    std::cout << "[End]" << std::endl;
#endif
}
