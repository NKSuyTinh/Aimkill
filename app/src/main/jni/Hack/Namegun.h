#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class Namegun {
public:
    struct GunInfo {
        std::string name;
        std::string icon;
        bool isSpecial = false;
        bool hasLevels = false;
    };

    static void Init();
    static std::string GetGunName(short gunId);
    static std::string GetGunIcon(short gunId);
    static std::string GetBaseName(const std::string& fullName);
    static bool HasIcon(short gunId);

private:
    static std::vector<GunInfo> GunData;
};
