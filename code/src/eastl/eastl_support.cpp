// code/dao_eastl_support.cpp
#include <cstdlib>
#include <cstdio>
#include <new>

namespace eastl {
    void AssertionFailure(const char* msg)
    {
        std::fprintf(stderr, "[EASTL] Assertion Failed: %s\n", msg ? msg : "(null)");
        std::abort();
    }
} // namespace eastl

// 使用 malloc 做为 EASTL 的 debug-new 后端，避免调用全局 operator new 导致任何歧义。
// EASTL 仅期望这些符号存在并返回有效内存指针。

void* operator new(std::size_t size,
                   const char*, int, unsigned,
                   const char*, int) noexcept(false)
{
    void* p = std::malloc(size);
    if (!p) throw std::bad_alloc();
    return p;
}

void* operator new[](std::size_t size,
                     const char*, int, unsigned,
                     const char*, int) noexcept(false)
{
    void* p = std::malloc(size);
    if (!p) throw std::bad_alloc();
    return p;
}

void* operator new(std::size_t size, std::size_t, std::size_t,
                   const char*, int, unsigned,
                   const char*, int) noexcept(false)
{
    void* p = std::malloc(size);
    if (!p) throw std::bad_alloc();
    return p;
}

void* operator new[](std::size_t size, std::size_t, std::size_t,
                     const char*, int, unsigned,
                     const char*, int) noexcept(false)
{
    void* p = std::malloc(size);
    if (!p) throw std::bad_alloc();
    return p;
}

// 为了完备（如果 EASTL 或其它组件 free 这些内存，确保使用 free）
// 注意：不要覆盖全局 delete/delete[]，这里不提供 delete 重载。
// 如果需要也可以补充 delete 的对应签名并调用 std::free。
