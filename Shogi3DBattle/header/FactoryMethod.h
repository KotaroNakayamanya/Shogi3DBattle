#pragma once

#include<memory>

class FactoryMethod
{
public:
    // T2ファクトリーから返されるユニークポインタをT1にダウンキャストして返す
    template<typename T1, typename T2>
    static std::unique_ptr<T1> GetDownCastUniquePtr(T2* factory);
};




// T2ファクトリーから返されるユニークポインタをT1にダウンキャストして返す
template<typename T1, typename T2>
static std::unique_ptr<T1> FactoryMethod::GetDownCastUniquePtr(T2* factory)
{
    // ポインタを取得
    auto tempUniquePtr = factory->CreateUniquePtr();
    auto tempPtr = tempUniquePtr.get();

    // ユニークポインタの管理を外し、ダウンキャストして新しいユニークポインタに返す
	tempUniquePtr.release();
    auto downCastPtr = static_cast<T1*>(tempPtr);
    std::unique_ptr<T1> uniquePtr(downCastPtr);

    return uniquePtr;
}