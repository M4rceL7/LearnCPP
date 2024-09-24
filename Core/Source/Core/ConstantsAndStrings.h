#pragma once
#include <string_view>
#include <xstring>

namespace ConstantsAndStrings
{
    void EnterTwoNames ();
    constexpr std::string getQuantityPhrase(int quantity);
    constexpr std::string getApplesPluralized(int amount);
}
