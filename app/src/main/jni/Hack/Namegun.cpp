#include "Namegun.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

std::vector<Namegun::GunInfo> Namegun::GunData;

void Namegun::Init() {
    if (!GunData.empty()) return;

    GunData.resize(25000);

    // SPECIALS
    GunData[6016] = { "CALL AIRDROP", "", true };
    GunData[10006] = { u8"TRUCK DROP", "", true };
    GunData[-15524 + 25000] = { "HEALING MINI DRONE", "", true };
    GunData[-15521 + 25000] = { "HEALING MINI DRONE (1 USE)", "", true };
    GunData[21001] = { "HEALING PISTOL", "\ue066", true };
    GunData[21002] = { "M590", "\ue084", true };

    // BOTS
    GunData[0] = { "AK47", "\ue074" };

    // ASSAULT RIFLES
    GunData[2] = { "M4A1", "\ue075" };
    GunData[80] = { "M4A1-I", "\ue075", false, true };
    GunData[81] = { "M4A1-II", "\ue075", false, true };
    GunData[82] = { "M4A1-III", "\ue075", false, true };
    GunData[6] = { "AK47", "\ue074" };
    GunData[11] = { "M14", "\ue079" };
    GunData[63] = { "M14-I", "\ue079", false, true };
    GunData[126] = { "M14-II", "\ue079", false, true };
    GunData[127] = { "M14-III", "\ue079", false, true };
    GunData[12] = { "SCAR", "\ue078" };
    GunData[178] = { "SCAR-I", "\ue078", false, true };
    GunData[179] = { "SCAR-II", "\ue078", false, true };
    GunData[180] = { "SCAR-III", "\ue078", false, true };
    GunData[14] = { "GROZA", "\ue07b" };
    GunData[70] = { "GROZA-X", "\ue07b", false, true };
    GunData[24] = { "FAMAS", "\ue07a" };
    GunData[67] = { "FAMAS-I", "\ue07a", false, true };
    GunData[130] = { "FAMAS-II", "\ue07a", false, true };
    GunData[131] = { "FAMAS-III", "\ue07a", false, true };
    GunData[28] = { "XM8", "\ue077" };
    GunData[33] = { "AN94", "\ue07d" };
    GunData[39] = { "PLASMA", "\ue07c" };
    GunData[46] = { "AUG", "\ue076" };
    GunData[193] = { "AUG-I", "\ue076", false, true };
    GunData[194] = { "AUG-II", "\ue076", false, true };
    GunData[195] = { "AUG-III", "\ue076", false, true };
    GunData[47] = { "PARAFAL", "\ue07f" };
    GunData[57] = { "SHOOTER", "\ue07e" };
    GunData[73] = { "G36-ASSAULT", "\ue087" };
    GunData[74] = { "G36-RANGE", "\ue087" };

    // MARKSMAN RIFLES
    GunData[18] = { "SKS", "\ue071" };
    GunData[26] = { "SVD", "\ue070" };
    GunData[72] = { "SVD-Y", "\ue070", false, true };
    GunData[48] = { "WOODPECKER", "\ue073" };
    GunData[89] = { "AC80", "\ue072" };

    // MACHINE GUNS
    GunData[19] = { "M249", "\ue06f" };
    GunData[71] = { "M249-X", "\ue06f", false, true };
    GunData[30] = { "M60", "\ue06e" };
    GunData[61] = { "M60-I", "\ue06e", false, true };
    GunData[122] = { "M60-II", "\ue06e", false, true };
    GunData[123] = { "M60-III", "\ue06e", false, true };
    GunData[54] = { "KORD", "" };

    // SMGS
    GunData[7] = { "UMP", "\ue063" };
    GunData[8] = { "MP5", "\ue061" };
    GunData[60] = { "MP5-I", "\ue061", false, true };
    GunData[120] = { "MP5-II", "\ue061", false, true };
    GunData[121] = { "MP5-III", "\ue061", false, true };
    GunData[13] = { "VSS", "\ue065" };
    GunData[62] = { "VSS-I", "\ue065", false, true };
    GunData[124] = { "VSS-II", "\ue065", false, true };
    GunData[125] = { "VSS-III", "\ue065", false, true };
    GunData[15] = { "MP40", "\ue064" };
    GunData[32] = { "P90", "\ue069" };
    GunData[35] = { "CG15", "\ue067" };
    GunData[43] = { "THOMPSON", "\ue06b" };
    GunData[49] = { "VECTOR", "\ue06a" };
    GunData[69] = { "DOUBLE VECTOR", "\ue088" };
    GunData[88] = { "MAC10", "\ue06d" };
    GunData[228] = { "MAC10-I", "\ue06d", false, true };
    GunData[229] = { "MAC10-II", "\ue06d", false, true };
    GunData[230] = { "MAC10-III", "\ue06d", false, true };
    GunData[150] = { u8"BIZON", "\uE06C" };

    // SHOTGUNS
    GunData[5] = { "M1014", "\ue059" };
    GunData[184] = { "M1014-I", "\ue059", false, true };
    GunData[185] = { "M1014-II", "\ue059", false, true };
    GunData[186] = { "M1014-III", "\ue059", false, true };
    GunData[29] = { "SPAS12", "\ue05a" };
    GunData[41] = { "M1887", "\ue05d" };
    GunData[119] = { "M1887-X", "\ue05d", false, true };
    GunData[50] = { "MAG-7", "\ue05b" };
    GunData[86] = { "EXTRA LOAD", "\ue05F" };
    GunData[181] = { "TROGON-SHOTGUN", "\ue05e" };
    GunData[182] = { "TROGON-GRENADE", "\ue05e" };

    // SNIPER RIFLES
    GunData[4] = { "AWM", "\ue04f" };
    GunData[65] = { "AWM-Y", "\ue04f", false, true };
    GunData[21] = { "KAR98K", "\ue050", false, true };
    GunData[64] = { "KAR98K-I", "\ue050", false, true };
    GunData[128] = { "KAR98K-II", "\ue050", false, true };
    GunData[129] = { "KAR98K-III", "\ue050", false, true };
    GunData[45] = { "M82B", "\ue053" };
    GunData[75] = { "M24", "\ue054" };
    GunData[78] = { "HEALING FP", "" };
    GunData[197] = { "VSK94", "\ue056" };

    // PISTOLS
    GunData[3] = { "USP", "\ue04e" };
    GunData[56] = { "USP-2", "\ue060", false, true };
    GunData[9] = { (const char*)u8"DESERT EAGLE", "\ue051" };
    GunData[10] = { "G18", "\ue052" };
    GunData[20] = { "M1873", "\ue057" };
    GunData[25] = { "M500", "\ue058" };
    GunData[55] = { "M1917", "\ue05c" };
    GunData[58] = { "MINI UZI", "\ue062" };
    GunData[93] = { "HEALING PISTOL", "\ue066" };

    // MELEE WEAPONS
    GunData[16] = { "PAN", "\ue04a" };
    GunData[17] = { "MACHETE", "\ue04b" };
    GunData[27] = { u8"BAT", "\ue04c" };
    GunData[34] = { "KATANA", "\ue04d" };
    GunData[51] = { "SCYTHE", "\ue04d" };
    GunData[53] = { "FF KNIFE", "\ue085" };

    // FIST
    GunData[1] = { "FIST", "\ue005" };

    // GRENADES
    GunData[601] = { "GRENADE", "\ue080" };
    GunData[603] = { u8"SMOKE GRENADE", "\uE086" };
    GunData[1201] = { "GLOO WALL", "\ue080" };
    GunData[1204] = { "GLOO WALL", "\ue080" };
    GunData[602] = { "FLASHBANG", "\ue082" };
    GunData[608] = { "ICE BOMB", "\ue083" };

    // OTHERS
    GunData[23] = { "M79", "" };
    GunData[36] = { "RGS-50", "" };
    GunData[196] = { "FGL-24", "" };

    // MISC
    GunData[100] = { u8"FLAMETHROWER", "\ue068" };
    GunData[99] = { "SHIELD GUN", "" };
    GunData[617] = { "WALL BREAKER", "" };
    GunData[1401] = { "LAND MINES", "" };
    GunData[1006] = { "MINI DRONE", "" };
    GunData[1015] = { "SUPPLY CRATE", "" };
}

std::string Namegun::GetGunName(short gunId) {
    int adjustedId = gunId < 0 ? gunId + 25000 : gunId;

    if (adjustedId >= 0 && adjustedId < GunData.size() &&
        (!GunData[adjustedId].name.empty() || GunData[adjustedId].isSpecial)) {
        return GunData[adjustedId].name;
    }

    return "ID: " + std::to_string(gunId);
}

std::string Namegun::GetGunIcon(short gunId) {
    int adjustedId = gunId < 0 ? gunId + 25000 : gunId;

    if (adjustedId >= 0 && adjustedId < GunData.size()) {
        if (!GunData[adjustedId].icon.empty()) {
            if (GunData[adjustedId].hasLevels) {
                std::string baseName = GetBaseName(GunData[adjustedId].name);
                std::string suffix = GunData[adjustedId].name.substr(baseName.length());
                return GunData[adjustedId].icon + suffix;
            }
            return GunData[adjustedId].icon;
        }
        return GunData[adjustedId].name;
    }
    return "";
}

std::string Namegun::GetBaseName(const std::string& fullName) {
    size_t dashPos = fullName.find_last_of('-');
    if (dashPos != std::string::npos) {
        std::string suffix = fullName.substr(dashPos + 1);
        if (suffix == "I" || suffix == "II" || suffix == "III" ||
            suffix == "X" || suffix == "Y" || suffix == "2") {
            return fullName.substr(0, dashPos);
        }
    }
    return fullName;
}

bool Namegun::HasIcon(short gunId) {
    int adjustedId = gunId < 0 ? gunId + 25000 : gunId;
    return (adjustedId >= 0 && adjustedId < GunData.size() &&
        !GunData[adjustedId].icon.empty());
}
