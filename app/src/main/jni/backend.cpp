#include <list>
#include <vector>
#include <string.h>
#include <string>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <map>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <sys/mman.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "Tools/Includes/Logger.h"
#include "Tools/Includes/obfuscate.h"
#include "Tools/Includes/Utils.h"
#include "Tools/SOCKET/Server.h"
#include "Tools/KittyMemory/KittyInclude.hpp"
#include "Hack/Memory.h"

bool isInsideFOV(int x, int y, float customFOV = 0.0f);
std::vector<void*> GetEntities(void* currentGame);

#include "Hack/class.h"

#include <stdarg.h>
#include <time.h>

void write_aimkill_log(const char* format, ...) {
    FILE* fp = fopen("/storage/emulated/0/DCIM/aimkill_log.txt", "a");
    if (!fp) {
        fp = fopen("/sdcard/DCIM/aimkill_log.txt", "a");
    }
    if (fp) {
        time_t rawtime;
        struct tm * timeinfo;
        char timebuf[80];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        if (timeinfo) {
            strftime(timebuf, sizeof(timebuf), "[%Y-%m-%d %H:%M:%S] ", timeinfo);
            fprintf(fp, "%s", timebuf);
        }
        va_list args;
        va_start(args, format);
        vfprintf(fp, format, args);
        va_end(args);
        fprintf(fp, "\n");
        fclose(fp);
    }
}

void log_enemy_info(const char* prefix, void* enemy) {
    if (!enemy) {
        return;
    }
    bool isDead = IsDieing(enemy);
    float hp = GetHp(enemy);
    bool valid = IsPullTargetValid(enemy);
    bool visible = isVisible_Aimbot(enemy);
}

#include "Tools/Includes/Macros.h"

#include "dobby.h"

#include "Tools/Canvas/Color.hpp"

#include <AutoUpdate/Il2Cppp.h>

#include "Unity/Unity.h"

#define targetLibName OBFUSCATE("libil2cpp.so")

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "Onyx", __VA_ARGS__)

#define PORT 7777

#pragma once

struct {
    bool ActivateAll = false;
    bool autoswitch = false;
    bool autoswitchsafe = false;

    bool ghoston = false;

    bool mapateleport = false;
    bool Aimkillrotate = false;

    bool autofire = false;
    bool downplayer = false;
    bool downaimkill = false;
    bool spoofname = false;

    bool Aimkill = false;

    bool ultraswitch = false;
    float aimbotFOV = 1000.0f;
    bool enableESP = false;
    bool speedrun = false;

    bool doublegun = false;
    bool speedHack = false;

    bool downkillv2 = false;

    bool ghostHack = false;
    bool resetguest = false;
    bool wallHack = false;
    bool medikitrun = false;

    bool telehack = false;

    bool fastswitch = false;

    bool PullEnemyV2Enabled = false;
    bool autorevive = false;

    bool smartmove = false;
    bool Aimkillsend = false;
    bool AimkillBrutal = false;
    bool AimkillBody = false;
    bool Aimkilltpv2 = false;

    bool AimkillSendCoverPull = false;

    bool RealAimkill = false;
    bool RealAimkillV2 = false;
    bool TargetAll = false;
    bool fastfiremax = false;
    bool fastfireauto = false;
    bool noreloadfck = false;
    bool fastfuck = false;

    bool fucked = false;

    bool SafeSilentAim = false;

    bool autoSwitchEnabled = false;

    float FlySpeed = 0.0f;
    bool ExampleFeature = false;
    float ExampleValue = 0.0f;

    bool burstFire = false;

    bool speedhackjoy = false;
    bool football = false;
    bool autoGlider = false;
    bool DiveKill = false;
    bool downplayerV2 = false;
    Vector3 originalPlayerScale;
} MasterBool;

char lockedEnemyName[128] = {0};

static bool SpeedTimerpatch = false;
int g_screenWidth, g_screenHeight;
ElfScanner g_il2cppELF;

enum Mode {
    InitMode = 1,
    HackMode = 2,
    StopMode = 98,
    EspMode = 99,
};

struct Request {
    int Mode;
    bool boolean;
    int value;
    int ScreenWidth;
    int ScreenHeight;
    uint64_t playerPtr;
};

#define maxplayerCount 60

struct PlayerData {
    Vector3 headPosition;
    Vector3 bottomPlayerPosition;
    float health;
    char name[2000];
    bool isDieing;
    bool isBot;
    bool isInVehicle;
    float distance;
    uint64_t playerPtr;
    char weaponName[64];
};

struct Response {
    bool Success;
    int PlayerCount;
    PlayerData Players[maxplayerCount];
    int matchAlive;
    int remainingTimeSeconds;

};

uintptr_t getLibBase(const char* libName) {
    uintptr_t base = 0;
    FILE* fp = fopen("/proc/self/maps", "rt");
    if (!fp) return 0;
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, libName)) {
            base = strtoul(line, NULL, 16);
            break;
        }

    }

    fclose(fp);
    return base;
}

void* BestEnemyFind(void* skipTarget = nullptr);
void* BestEnemyFind360();
static bool InActiveMatch();

std::string getPackageName() {
    char pkg[256] = {0};
    FILE *fp = fopen("/proc/self/cmdline", "r");
    if (fp) {
        fgets(pkg, sizeof(pkg), fp);
        fclose(fp);
    }

    return std::string(pkg);
}

SocketServer server;

int InitServer() {
    if (!server.Create()) return -1;
    if (!server.Bind()) return -1;
    if (!server.Listen()) return -1;
    return 0;
}

#define _GameFacade (uintptr_t) Il2CppGetClassType(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"))

#define _MatchGame (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentMatchGame"))

#define _Match (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("MatchGame"), OBFUSCATE("m_Match"))

#define _MatchState (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("EMKJHAJNPDH"), OBFUSCATE("MAOHIOEAMEA"))

#define _DicPlayer (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("EMKJHAJNPDH"), OBFUSCATE("NGFEHJMADOJ"))

#define _HeadTF (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("PEMOFNFCLFB"))

#define _RootTF (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("KNFKIDHJCCO"))

#define _OriginalName (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("OriginalNickName"))

#define _HitObjectInfoWp (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("AKFLHNOIHED"))

#define _NickName (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("MOKGDCJLJFI"))

#define _FastSwitch (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("KDNABNMDIPA"))

#define _UiScene (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("BaseGame"), OBFUSCATE("m_UIScene"))

#define _UiMapCtrl (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("m_BigMapCtrl"))

#define _MapContectCtrl (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIMapBaseController"), OBFUSCATE("m_MapContentCtrl"))

#define _LocalMarkCtrl (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIMapContentController"), OBFUSCATE("m_LocalMapMarkController"))

#define _LocalMarkPos (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudPlayerMarkController"), OBFUSCATE("m_pos"))

#define _PhysxData (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IFGAOAHPNOC"))

#define _playerAttributes (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("KDJHNBAECLM"))

#define offset_NoReload (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerAttributes"), OBFUSCATE("ShootNoReload"))

#define _GameTimer (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("BaseGame"), OBFUSCATE("m_SimulationTimer"))

#define _FixedDeltaTime (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("TimeService"), OBFUSCATE("m_FixedDeltaTime"))

#define Manual_Zone_Req (uintptr_t) Il2CppGetClassType(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("C2S_RUDP_Manual_Zone_EnterOrExit_Req"))

#define _LocalMarkCtrl (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIMapContentController"), OBFUSCATE("m_LocalMapMarkController"))

#define _LocalMarkPos (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudPlayerMarkController"), OBFUSCATE("m_pos"))

#define Sync_PlayerId (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JDIHDLDIMCK"), OBFUSCATE("BHGGAEEHJCO"))

#define Sync_DGLCOGJJFMI (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JDIHDLDIMCK"), OBFUSCATE("DBPPPOBFJNP"))

#define Item_UniqueId (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("LGMNCCAPNHJ"), OBFUSCATE("DEGODFCOKGC"))

#define Hit_GameObject (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GMPGMPFNMFP"), OBFUSCATE("HLIJMDODPIM"))

#define Hit_HeadCollider (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GMPGMPFNMFP"), OBFUSCATE("OCEBCHENIOK"))

#define Hit_Ignore (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GMPGMPFNMFP"), OBFUSCATE("DEDOKPCAHAC"))

#define Hit_SpecialHitType (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GMPGMPFNMFP"), OBFUSCATE("LNOIFBAFGOK"))

#define Hit_HitLoc (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GMPGMPFNMFP"), OBFUSCATE("MBGBCLNJOMK"))

#define Hit_Normal (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GMPGMPFNMFP"), OBFUSCATE("DGFLGBEOGPG"))

#define Hit_RayDir (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GMPGMPFNMFP"), OBFUSCATE("IKDEGKIICJP"))

#define Hit_StartPos (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GMPGMPFNMFP"), OBFUSCATE("LMAEGPEAECO"))

#define Hit_OrgStrtPos (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GMPGMPFNMFP"), OBFUSCATE("KPEICEMCHIF"))

#define Hit_Part (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GMPGMPFNMFP"), OBFUSCATE("FLCLOHCBJEI"))

#define Dmg_BaseDamage (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GLLLEDKLLDA"), OBFUSCATE("FOMIHMJCEHC"))

#define Dmg_ColliderType (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GLLLEDKLLDA"), OBFUSCATE("DNFNNJMHNEK"))

#define Dmg_PlayerID (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GLLLEDKLLDA"), OBFUSCATE("NIMANCBDPFK"))

#define Dmg_WeaponOnHand (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GLLLEDKLLDA"), OBFUSCATE("FDAEPHMIEPC"))

#define Dmg_FirePos (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GLLLEDKLLDA"), OBFUSCATE("EPCMOGEBEKM"))

#define Dmg_HitPos (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GLLLEDKLLDA"), OBFUSCATE("ILJBHKIFOEP"))

#define Dmg_WeaponDataId (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GLLLEDKLLDA"), OBFUSCATE("EJJFPFENMBP"))

#define offset_GhostHack (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PNCPKGJGBPP"), OBFUSCATE("EAIKJCCNGMJ"), 1)

#define offset_LCLHHHKFCFP (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FDAEPHMIEPC"), OBFUSCATE("LKHKGOFALIB"),4)

#define offset_Player_TakeDamage (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("TakeDamage"),9)

#define offset_SetStartDamage (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FDAEPHMIEPC"), OBFUSCATE("KOODEKEKFEK"),1)

#define offset_WeaponFire (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FDAEPHMIEPC"), OBFUSCATE("KOODEKEKFEK"),1)

#define offset_DamageS2C (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PhyXShield"), OBFUSCATE("OEEFOBLNIFG"),0)

#define offset_HighJump (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("KANJBNIANHC"), OBFUSCATE("GOEODCJNMPF"),1)

#define offset_RequestExecuteTar (uintptr_t) Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("OIKCHKMBEIK"))

#define offset_RequestRescureTar (uintptr_t) Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("COBFBHFCIPD"))

#define offset_DamageInfo (uintptr_t) Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GLLLEDKLLDA"))

#define offset_WeaponDynamicInfo (uintptr_t) Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("LOAEBBHPMEK"))

#define offset_PJKBDOJLDNN (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("COBFBHFCIPD"), OBFUSCATE("BAFEIAKDCEK"))

#define offset_GMOHIILGMGM (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("COBFBHFCIPD"), OBFUSCATE("OFAAFCOMJGJ"))

#define offset_exc_PJKBDOJLDNN (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("OIKCHKMBEIK"), OBFUSCATE("BAFEIAKDCEK"))

#define offset_exc_EGAMAMKBENE (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("OIKCHKMBEIK"), OBFUSCATE("OODOGCHKOMC"))

#define offset_EMAOKNCFCKE (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FDAEPHMIEPC"), OBFUSCATE("LHJFIFDCGAL"), 0)

// #define _GameFacade (uintptr_t) Il2CppGetClassType(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"))

// #define _MatchGame (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentMatchGame"))

// #define _Match (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("MatchGame"), OBFUSCATE("m_Match"))

// #define _MatchState (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("NFJPHMKKEBF"), OBFUSCATE("ILGECLEFCCO"))

// #define _DicPlayer (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("NFJPHMKKEBF"), OBFUSCATE("HOOCHDLKOOG"))

// #define _HeadTF (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("OLCJOGDHJJJ"))

// #define _RootTF (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("MPJBGDJJJMJ"))

// #define _OriginalName (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("OriginalNickName"))

// #define _HitObjectInfoWp (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GEGFCFDGGGP"))

// #define _NickName (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("OIAJCBLDHKP"))

// #define _FastSwitch (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("MNDBDFDOLNL"))

// #define _UiScene (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("BaseGame"), OBFUSCATE("m_UIScene"))

// #define _UiMapCtrl (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("m_BigMapCtrl"))

// #define _MapContectCtrl (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIMapBaseController"), OBFUSCATE("m_MapContentCtrl"))

// #define _LocalMarkCtrl (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIMapContentController"), OBFUSCATE("m_LocalMapMarkController"))

// #define _LocalMarkPos (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudPlayerMarkController"), OBFUSCATE("m_pos"))

// #define _PhysxData (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IBHJOIGFAEH"))

// #define _playerAttributes (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("JKPFFNEMJIF"))

// #define offset_NoReload (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerAttributes"), OBFUSCATE("ShootNoReload"))

// #define _GameTimer (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("BaseGame"), OBFUSCATE("m_SimulationTimer"))

// #define _FixedDeltaTime (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("TimeService"), OBFUSCATE("m_FixedDeltaTime"))

// #define Manual_Zone_Req (uintptr_t) Il2CppGetClassType(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("C2S_RUDP_Manual_Zone_EnterOrExit_Req"))

struct message_C2S_RUDP_Manual_Zone_EnterOrExit_Req_Fields {
    void *klass;
    void *monitor;
    bool UDPClientMessageBase_m_GetFromPool;
    uint64_t UserID;
    uint32_t PlayerID;
    uint32_t ZoneID;
    bool EnterOrExit;
};

// #define _LocalMarkCtrl (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIMapContentController"), OBFUSCATE("m_LocalMapMarkController"))

// #define _LocalMarkPos (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudPlayerMarkController"), OBFUSCATE("m_pos"))

// #define Sync_PlayerId (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JLMEBGKMNIL"), OBFUSCATE("IHAAMHPPLMG"))

// #define Sync_DGLCOGJJFMI (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JLMEBGKMNIL"), OBFUSCATE("DGLCOGJJFMI"))

// #define Item_UniqueId (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("KOGBJLFDJHC"), OBFUSCATE("JDPDFBINIJE"))

// #define Hit_GameObject (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("MADMMIICBNN"), OBFUSCATE("JMKMBNIBFNA"))

// #define Hit_HeadCollider (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("MADMMIICBNN"), OBFUSCATE("GHACJPMCEDK"))

// #define Hit_Ignore (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("MADMMIICBNN"), OBFUSCATE("AAABMPKNDBH"))

// #define Hit_SpecialHitType (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("MADMMIICBNN"), OBFUSCATE("ACAKHEABPEJ"))

// #define Hit_HitLoc (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("MADMMIICBNN"), OBFUSCATE("GAMMEIDKJHK"))

// #define Hit_Normal (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("MADMMIICBNN"), OBFUSCATE("JNLGFLFLBHO"))

// #define Hit_RayDir (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("MADMMIICBNN"), OBFUSCATE("NHKKHPLFMNG"))

// #define Hit_StartPos (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("MADMMIICBNN"), OBFUSCATE("BOGOIAMJFDN"))

// #define Hit_OrgStrtPos (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("MADMMIICBNN"), OBFUSCATE("BEMPDPJNILA"))

// #define Hit_Part (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("MADMMIICBNN"), OBFUSCATE("OJKBBAOPPIN"))

// #define Dmg_BaseDamage (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("ELMGJKHIIAA"), OBFUSCATE("DBLBLKADCNP"))

// #define Dmg_ColliderType (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("ELMGJKHIIAA"), OBFUSCATE("KENBMOOEHBG"))

// #define Dmg_PlayerID (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("ELMGJKHIIAA"), OBFUSCATE("DHGCIEKPBFA"))

// #define Dmg_WeaponOnHand (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("ELMGJKHIIAA"), OBFUSCATE("GPBDEDFKJNA"))

// #define Dmg_FirePos (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("ELMGJKHIIAA"), OBFUSCATE("CNEICNJFGLM"))

// #define Dmg_HitPos (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("ELMGJKHIIAA"), OBFUSCATE("HECJHKEDFEB"))

// #define Dmg_WeaponDataId (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("ELMGJKHIIAA"), OBFUSCATE("PIAMIOFEBKF"))

#define offset_GBFootballTryHitFlyPlayer (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GBFootballTryHitFlyPlayer"), 1)
#define offset_GBFootballTryHitIceWall (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GBFootballTryHitIceWall"), 1)

// #define offset_GhostHack (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("EGKODKEJIAD"), OBFUSCATE("BNFAGNBHHIF"), 1)

// #define offset_LCLHHHKFCFP (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GPBDEDFKJNA"), OBFUSCATE("LCLHHHKFCFP"),4)

// #define offset_Player_TakeDamage (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("TakeDamage"),9)

// #define offset_SetStartDamage (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GPBDEDFKJNA"), OBFUSCATE("BLAGCMCGEJG"),1)

// #define offset_WeaponFire (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GPBDEDFKJNA"), OBFUSCATE("BLAGCMCGEJG"),1)

// #define offset_DamageS2C (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PhyXShield"), OBFUSCATE("PNGAJBCPDNJ"),0)

// #define offset_HighJump (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("LLOABGDLMGK"), OBFUSCATE("IBJEJADAJMN"),1)

// #define offset_RequestExecuteTar (uintptr_t) Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("CEEAGMKELFD"))

// #define offset_RequestRescureTar (uintptr_t) Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("EMOBCDJEOLN"))

// #define offset_DamageInfo (uintptr_t) Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("ELMGJKHIIAA"))

// #define offset_WeaponDynamicInfo (uintptr_t) Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("MKFEKBKJCKE"))

void SetFootballState(void* player) {
    void* (*getter)(void*) = (void* (*)(void*))offset_PhysXData;
    if (!getter) return;
    void *physXData = getter(player);
    if (!physXData) return;
    *(int *)((uintptr_t)physXData + 0xc) = 8;
}

void InvisiblePlayer() {
    if (!InActiveMatch()) return;
    auto player = Current_Local_Player();
    if (!player) return;
    if (IsDieing(player)) return;
    if (GetHp(player) <= 0) return;

}

void SpoofName() {
    auto player = Current_Local_Player();
    if (!player) return;
    monoString** namePtr = (monoString**)((uintptr_t)player + _NickName);
    static monoString* cachedSpoofName = nullptr;
    std::string base = "[b][FF0000]Onyx [ffffff]VIP[B][C]";

    if (!cachedSpoofName) {
        cachedSpoofName = reinterpret_cast<monoString*>(Il2CppString::Create(base.c_str()));
    }

    if (cachedSpoofName && *namePtr != cachedSpoofName) {
        *namePtr = cachedSpoofName;
    }

}

std::vector<void*> GetEntities(void* currentGame) {
    std::vector<void *> entityList;
    if (!currentGame) return entityList;
    uintptr_t entityDictionary = *(uintptr_t *) ((uintptr_t) currentGame + _DicPlayer);
    if (!entityDictionary) return entityList;
    bool newLayout = false;

    uintptr_t entries = *(uintptr_t *) (entityDictionary + 0xC);
    int count = *(int *) (entityDictionary + 0x10);
    if (entries && count > 0 && count < 10000)

        newLayout = true;

    if (newLayout) {
        for (int i = 0; i < count; i++) {
            void *entity = *(void **) (entries + (i * 0x28) + 0x30);
            if (!entity) continue;

            entityList.push_back(entity);
        }

    } else {
        auto *MonoPlayer = *(System_Collections_Generic_Dictionary_IHAAMHPPLMG__Player__o * *)((uint64_t) currentGame + _DicPlayer);
        if (MonoPlayer != nullptr) {
            COW_GamePlay_Player_array *players = MonoPlayer->valueSlots;
            if (players != nullptr) {
                int Counts = players->max_length;
                if (Counts > 0 && Counts < 500) {
                    for (int i = 0; i < Counts; ++i) {
                        entityList.push_back(players->m_Items[i]);
                    }

                }

            }

        }

    }

    return entityList;
}

#include <algorithm>
#include "Hack/Namegun.h"

void NewEspForUnity31(Response &response) {
    Namegun::Init();
    response.matchAlive = 0;
    response.remainingTimeSeconds = -1;
    static time_t s_matchTimerStart = 0;

    const int MATCH_TIMER_SECONDS = 185; // 3 min 5 sec

    void *MatchGame = *(void **) ((uint64_t) _GameFacade + _StaticClass);
    if (!MatchGame) return;

    void *ClassMatchGame = *(void **) ((uint64_t) MatchGame + _MatchGame);
    if (!ClassMatchGame) return;

    void *current_match = *(void **) ((uint64_t) ClassMatchGame + _Match);
    if (!current_match) return;

    auto matchStatus = *(uint32_t *) ((uint64_t) current_match + _MatchState);

    if (matchStatus == 1) {
        if (s_matchTimerStart == 0)

            s_matchTimerStart = time(nullptr);
        int rem = MATCH_TIMER_SECONDS - (int)(time(nullptr) - s_matchTimerStart);
        if (rem < 0) rem = 0;
        response.matchAlive = 1;
        response.remainingTimeSeconds = rem;

    } else {
        s_matchTimerStart = 0;
        return;
    }

    void *CurrentLocalPlayer = Current_Local_Player();
    if (!CurrentLocalPlayer) return;

    auto players = GetEntities(current_match);
    for (auto player: players) {
        if (!player) continue;

        if (player == CurrentLocalPlayer) continue;

        if (IsLocalTeammate(player)) continue;

        int hp = GetHp(player);
        if (hp <= 0) continue;

        void *HeadTF = TransformNode(*(void **) ((uintptr_t) player + _HeadTF));
        void *RootTF = TransformNode(*(void **) ((uintptr_t) player + _RootTF));
        void *LocalHeadTF = TransformNode(*(void **) ((uintptr_t) CurrentLocalPlayer + _HeadTF));

        if (!HeadTF || !RootTF || !LocalHeadTF) continue;

        Vector3 headPos = Transform_INTERNAL_GetPosition(HeadTF);
        Vector3 rootPos = Transform_INTERNAL_GetPosition(RootTF);
        Vector3 localHeadPos = Transform_INTERNAL_GetPosition(LocalHeadTF);

        Vector3 screenHead = WorldToScreenPoint(headPos);
        Vector3 screenRoot = WorldToScreenPoint(rootPos);

        bool isDieing = IsDieing(player);
        float distance = Vector3::Distance(localHeadPos, headPos);
        monoString *Nick = *(monoString **) ((uint64_t) player + _OriginalName);

        if (response.PlayerCount >= maxplayerCount) break;
        PlayerData *data = &response.Players[response.PlayerCount];

        if (data) {
            data->headPosition = screenHead;
            data->bottomPlayerPosition = screenRoot;
            data->distance = distance;
            data->isDieing = isDieing;
            data->health = hp;
            data->playerPtr = (uint64_t)player;
            if (Nick && Nick->getLength() > 0 && Nick->getLength() < 128) {
                const char* nickChars = Nick->toChars();
                if (nickChars) {
                    snprintf(data->name, sizeof(data->name), "%s", nickChars);
                } else {
                    data->name[0] = '\0';
                }
            } else {
                data->name[0] = '\0';
            }
            data->weaponName[0] = '\0';
            void *enemyWeapon = GetWeaponOnHand(player);
            if (enemyWeapon != nullptr) {
                int gunId = GetWeaponID(enemyWeapon);
                std::string gName = Namegun::GetGunName((short)gunId);
                if (!gName.empty()) {
                    strncpy(data->weaponName, gName.c_str(), sizeof(data->weaponName) - 1);
                    data->weaponName[sizeof(data->weaponName) - 1] = '\0';
                }
            }
        }

        SpoofName();
        response.PlayerCount++;
    }

}

void FlyExploitSBG(void* localPlayer) {}

void unlockMemory(uintptr_t address) {
    uintptr_t pageStart = address & ~(getpagesize() - 1);
    mprotect((void*)pageStart, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC);
}

static float GetRandomTapInterval1() {
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)(get_realtimeSinceStartup() * 1000));
        seeded = true;
    }

    float baseInterval = 0.053f;
    float randomOffset = ((rand() % 17) - 8) / 1000.0f;
    float interval = baseInterval + randomOffset;
    if (interval < 0.045f) interval = 0.045f;
    if (interval > 0.061f) interval = 0.061f;
    return interval;
}

struct JumpTapperState {
    void* auxJumpController;
    float lastTapTime;
    bool isButtonDown;
    float tapInterval;
    bool isActive;

    JumpTapperState() {
        auxJumpController = nullptr;
        lastTapTime = 0.0f;
        isButtonDown = false;
        tapInterval = 0.05f;
        isActive = false;
    }

};

static JumpTapperState jumpTapState;

static void InitializeJumpTapper() {
    if (jumpTapState.isActive) return;

    jumpTapState.auxJumpController = GetJumpsex();
    if (!jumpTapState.auxJumpController) return;

    jumpTapState.lastTapTime = get_realtimeSinceStartup();
    jumpTapState.isButtonDown = false;
    jumpTapState.tapInterval = GetRandomTapInterval1();
    jumpTapState.isActive = true;
}

static void TickJumpTapper() {
    if (!jumpTapState.isActive) return;

    if (!jumpTapState.auxJumpController) {
        jumpTapState.auxJumpController = GetJumpsex();
        if (!jumpTapState.auxJumpController) return;
    }

    float currentTime = get_realtimeSinceStartup();
    float elapsed = currentTime - jumpTapState.lastTapTime;
    if (elapsed >= jumpTapState.tapInterval) {
        if (jumpTapState.isButtonDown) {
            JumpButton_OnBtnUp(jumpTapState.auxJumpController);
            jumpTapState.isButtonDown = false;
            jumpTapState.tapInterval = GetRandomTapInterval1();

        } else {
            JumpButton_OnBtnDown(jumpTapState.auxJumpController);
            jumpTapState.isButtonDown = true;
            jumpTapState.tapInterval = 0.005f;
        }

        jumpTapState.lastTapTime = currentTime;
    }

}

static void StopJumpTapper() {
    if (!jumpTapState.isActive)

        return;

    if (jumpTapState.auxJumpController) {
        JumpButton_OnBtnUp(jumpTapState.auxJumpController);
    }

    jumpTapState.isButtonDown = false;
    jumpTapState.isActive = false;
    jumpTapState.tapInterval = 0.05f;
    jumpTapState.lastTapTime = get_realtimeSinceStartup();
    jumpTapState.auxJumpController = nullptr;
}

struct FireTapperState {
    void* auxFireController;
    float lastTapTime;
    bool isButtonDown;
    float tapInterval;
    bool isActive;

    FireTapperState() {
        auxFireController = nullptr;
        lastTapTime = 0.0f;
        isButtonDown = false;
        tapInterval = 0.05f;
        isActive = false;
    }

};

static FireTapperState fireTapState;

static void InitializeFireTapper() {
    if (fireTapState.isActive) return;
    fireTapState.auxFireController = GetAuxFireController();
    if (!fireTapState.auxFireController) return;
    fireTapState.lastTapTime = get_realtimeSinceStartup();
    fireTapState.isButtonDown = false;
    fireTapState.tapInterval = 0.0f;
    fireTapState.isActive = true;
}

static void TickFireTapper(bool isBurst = false) {
    if (!fireTapState.isActive) return;
    if (!fireTapState.auxFireController) {
        fireTapState.auxFireController = GetAuxFireController();
        if (!fireTapState.auxFireController) return;
    }

    int burstCount = isBurst ? 3 : 1;
    for (int i = 0; i < burstCount; i++) {
        FireButton_OnBtnDown(fireTapState.auxFireController);
        JumpButton_OnBtnUp(fireTapState.auxFireController);
    }

    fireTapState.lastTapTime = get_realtimeSinceStartup();
}

static void StopFireTapper() {
    if (!fireTapState.isActive)

        return;

    if (fireTapState.auxFireController) {
        JumpButton_OnBtnUp(fireTapState.auxFireController);
    }

    fireTapState.isButtonDown = false;
    fireTapState.isActive = false;
    fireTapState.tapInterval = 0.05f;
    fireTapState.lastTapTime = get_realtimeSinceStartup();
    fireTapState.auxFireController = nullptr;
}

void* cachedTarget = nullptr;
void* cachedTarget360 = nullptr;

void AutoFireLoop() {
    if (!MasterBool.autofire) {
        if (fireTapState.isActive) StopFireTapper();
        return;
    }
    void* target = cachedTarget;
    if (!target) {
        if (fireTapState.isActive) StopFireTapper();
        return;
    }
    void* local = Current_Local_Player();
    void* weapon = GetWeaponOnHand(local);
    if (isVisible_Aimbot(target) && isEnemyInRangeWeapon(local, target, weapon)) {
        InitializeFireTapper();
        TickFireTapper(false);
        MasterBool.fastfiremax = true;
    } else {
        if (fireTapState.isActive) StopFireTapper();
        if (!MasterBool.fastfireauto) MasterBool.fastfiremax = false;
    }
}

void FlyInitializer() {
    void *enemyRoot = *(void **) ((uintptr_t) Current_Local_Player() + _PhysxData);
    void *enemyRootv = *(void **) ((uintptr_t) enemyRoot + 0xC);
    int32_t pos = *(int32_t * )((uintptr_t) enemyRootv + 0x8);
    if (pos != 1) {
        *(int32_t * )((uintptr_t) enemyRootv + 0x8) = 1;
    }

}

void FlyInitializerV() {
    void *enemyRoot = *(void **) ((uintptr_t) Current_Local_Player() + _PhysxData);
    void *enemyRootv = *(void **) ((uintptr_t) enemyRoot + 0xC);
    int32_t pos = *(int32_t * )((uintptr_t) enemyRootv + 0x8);
    if (pos == 1) {
        *(int32_t * )((uintptr_t) enemyRootv + 0x8) = 0;
    }

}

void *CreateServer(void *) {
    if (InitServer() == 0) {
        while(true) {
            if (server.Accept()) {
                Request request{};
                while (server.receive((void*)&request) > 0) {
                    Response response{};
                    if (request.Mode == Mode::InitMode) {
                        response.Success = true;

                    } else if (request.Mode == Mode::EspMode) {
                        g_screenWidth = request.ScreenWidth;
                        g_screenHeight = request.ScreenHeight;
                        response.Success = true;
                        if (MasterBool.ActivateAll) {
                            NewEspForUnity31(response);
                        } else {
                            response.PlayerCount = 0;
                        }

                    } else if (request.Mode == 3) {
                        MasterBool.enableESP = request.boolean;
                        response.Success = true;

                    } else if (request.Mode == 109) {
                        MasterBool.speedHack = request.boolean;
                        response.Success = true;
                    }

                     else if (request.Mode == 7001) {
                        MasterBool.autoGlider = request.boolean;
                        response.Success = true;

                    } else if (request.Mode == 100) {
                        MasterBool.Aimkill = request.boolean;
                        response.Success = true;

                    }  else if (request.Mode == 1048) {
                        MasterBool.AimkillSendCoverPull = request.boolean;
                        response.Success = true;

                    }   else if (request.Mode == 5662) {
                        MasterBool.RealAimkillV2 = request.boolean;
                        response.Success = true;

                    }   else if (request.Mode == 5663) {
                        MasterBool.Aimkillsend = request.boolean;
                        response.Success = true;

                    }   else if (request.Mode == 9999) {
                        MasterBool.ActivateAll = request.boolean;
                        if (!MasterBool.ActivateAll) {
                            MasterBool.RealAimkillV2 = false;
                            MasterBool.Aimkillsend = false;
                            MasterBool.Aimkill = false;
                            MasterBool.RealAimkill = false;
                            MasterBool.TargetAll = false;
                            MasterBool.enableESP = false;
                            MasterBool.autofire = false;
                            MasterBool.autoSwitchEnabled = false;
                            MasterBool.autoswitchsafe = false;
                            MasterBool.autoswitch = false;
                            MasterBool.speedrun = false;
                            MasterBool.speedHack = false;
                            MasterBool.speedhackjoy = false;
                            MasterBool.autoGlider = false;
                            MasterBool.autorevive = false;
                            MasterBool.fastfuck = false;
                            MasterBool.noreloadfck = false;
                            MasterBool.fastfiremax = false;
                            MasterBool.fastfireauto = false;
                            MasterBool.DiveKill = false;
                            MasterBool.downplayerV2 = false;
                            MasterBool.downaimkill = false;
                            MasterBool.telehack = false;
                            MasterBool.Aimkillrotate = false;
                            MasterBool.AimkillSendCoverPull = false;
                            MasterBool.mapateleport = false;
                            MasterBool.resetguest = false;
                            SpeedTimerpatch = false;
                        }
                        response.Success = true;

                    }  else if (request.Mode == 1043) {
                        MasterBool.FlySpeed = (float)request.value;
                        response.Success = true;
                    }

                    else if (request.Mode == 104) {
                        MasterBool.aimbotFOV = request.value;
                        response.Success = true;

                    }  else if(request.Mode == 40004) {
                        MasterBool.fastswitch = request.boolean;
                        response.Success = true;

                    } else if(request.Mode == 12) {
                        MasterBool.resetguest = request.boolean;
                        response.Success = true;

                    } else if(request.Mode == 13) {
                        MasterBool.medikitrun = request.boolean;
                        response.Success = true;

                    } else if(request.Mode == 56) {
                        MasterBool.spoofname = request.boolean;
                        response.Success = true;

                    } else if(request.Mode == 166) {
                        MasterBool.wallHack = request.boolean;
                        response.Success = true;

                    } else if(request.Mode == 19) {
                        MasterBool.telehack = request.boolean;
                        response.Success = true;

                    }    else if(request.Mode == 502) {
                        MasterBool.Aimkillrotate = request.boolean;
                        response.Success = true;

                    } else if(request.Mode == 504) {
                        MasterBool.downplayerV2 = request.boolean;
                        MasterBool.downaimkill = request.boolean;
                        response.Success = true;

                    } else if(request.Mode == 5660) {
                        MasterBool.DiveKill = request.boolean;
                        response.Success = true;

                    }  else if(request.Mode == 505) {
                        MasterBool.autoswitch = request.boolean;
                        response.Success = true;

                    } else if(request.Mode == 508) {
                        MasterBool.autoswitchsafe = request.boolean;
                        response.Success = true;

                    }   else if(request.Mode == 531) {
                        MasterBool.football = request.boolean;
                        response.Success = true;

                    } else if(request.Mode == 15) {
                        MasterBool.speedhackjoy = request.boolean;
                        response.Success = true;

                    } else if(request.Mode == 528) {
                        MasterBool.burstFire = request.boolean;
                        response.Success = true;
                    }

                    else if(request.Mode == 7896) {
                        MasterBool.autorevive = request.boolean;
                        response.Success = true;
                    }

                    else if(request.Mode == 524) {
                        MasterBool.autoSwitchEnabled = request.boolean;
                        response.Success = true;
                    }

                    else if(request.Mode == 7001) {
                        MasterBool.autofire = request.boolean;
                        response.Success = true;
                    }

                    else if (request.Mode == 509) {
                        MasterBool.smartmove = request.boolean;
                        response.Success = true;
                    }

                    else if(request.Mode == 149) {
                        MasterBool.ghoston = request.boolean;
                        response.Success = true;
                    }

                    else if(request.Mode == 515)

                    {
                        MasterBool.fastfiremax = request.boolean;
                        response.Success = true;
                    }

                    else if(request.Mode == 516)

                    {
                        MasterBool.fastfireauto = request.boolean;
                        response.Success = true;
                    }

                    else if (request.Mode == 518) {
                        MasterBool.fastfuck = request.boolean;
                        response.Success = true;
                    }

                    else if (request.Mode == 507) {
                        MasterBool.speedrun = request.boolean;
                        response.Success = true;
                    }

                    else if (request.Mode == 519) {
                        MasterBool.noreloadfck = request.boolean;
                        response.Success = true;
                    }

                    else if (request.Mode == 520) {
                        MasterBool.autofire = request.boolean;
                        if (request.boolean) {
                            MasterBool.noreloadfck = true;
                        }

                        response.Success = true;
                    }

                    server.send((void*)& response, sizeof(response));
                }

            }

        }

    }

    return NULL;
}

Vector3 cSubtract(Vector3 src, Vector3 dst) {
    Vector3 diff;
    diff.X = src.X - dst.X; diff.Y = src.Y - dst.Y; diff.Z = src.Z - dst.Z;
    return diff;
}

float cMagnitude(Vector3 vec) {
    return sqrtf(vec.X*vec.X + vec.Y*vec.Y + vec.Z*vec.Z);
}

float Vector3Distance(const Vector3& a, const Vector3& b) {
    float dx = a.X - b.X; float dy = a.Y - b.Y; float dz = a.Z - b.Z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}

void* GetEnemyInsideScreen()

{
    void* closestEnemy = nullptr;
    float closestDistSq = FLT_MAX;

    if (!_GameFacade) return nullptr;

    void* MatchGame = *(void**)((uint64_t)_GameFacade + _StaticClass);
    if (!MatchGame) return nullptr;

    void* ClassMatchGame = *(void**)((uint64_t)MatchGame + _MatchGame);
    if (!ClassMatchGame) return nullptr;

    void* current_match = *(void**)((uint64_t)ClassMatchGame + _Match);
    if (!current_match) return nullptr;

    if (*(uint32_t*)((uint64_t)current_match + _MatchState) != 1)

        return nullptr;

    void* LocalPlayer = Current_Local_Player();
    if (!LocalPlayer) return nullptr;

    Vector3 screenCenter(

            (float)(g_screenWidth * 0.5f),
            (float)(g_screenHeight * 0.5f),

            0.0f

    );

    auto players = GetEntities(current_match);
    for (auto player: players) {
        void* enemy = player;

        if (!enemy || enemy == LocalPlayer) continue;

        if (IsDieing(enemy)) continue;
        if (IsLocalTeammate(enemy)) continue;
        if (GetHp(enemy) <= 0) continue;

        void* headTF = TransformNode(*(void**)((uint64_t)enemy + _HeadTF));
        if (!headTF) continue;

        Vector3 worldPos = Transform_INTERNAL_GetPosition(headTF);
        Vector3 screenPos = WorldToScreenPoint(worldPos);

        // enemy camera ke aage hona chahiye

        if (screenPos.Z <= 0.01f) continue;

        // screen bounds check

        if (screenPos.X < 0 || screenPos.X > g_screenWidth) continue;
        if (screenPos.Y < 0 || screenPos.Y > g_screenHeight) continue;

        float dx = screenPos.X - screenCenter.X;
        float dy = screenPos.Y - screenCenter.Y;

        float distSq = dx * dx + dy * dy;

        if (distSq < closestDistSq)

        {
            closestDistSq = distSq;
            closestEnemy = enemy;
        }

    }

    return closestEnemy;
}

void *GetKnockedEnemyNearby()

{
    float closestDist = 999999.0f;
    void* targetTeammate = nullptr;

    if (!_GameFacade) return nullptr;

    void* MatchGame = *(void**)((uintptr_t)_GameFacade + _StaticClass);
    if (!MatchGame) return nullptr;

    void* ClassMatchGame = *(void**)((uintptr_t)MatchGame + _MatchGame);
    if (!ClassMatchGame) return nullptr;

    void* current_match = *(void**)((uintptr_t)ClassMatchGame + _Match);
    if (!current_match) return nullptr;

    void* LocalPlayer = Current_Local_Player();
    if (!LocalPlayer) return nullptr;

    Vector3 localPos = Transform_INTERNAL_GetPosition(TransformNode(*(void**)((uintptr_t)LocalPlayer + _HeadTF)));

    auto players = GetEntities(current_match);
    for (auto playerSS: players) {
        void* player = playerSS;

        if (!player || player == LocalPlayer) continue;
        if (IsLocalTeammate(player)) continue;
        if (!IsDieing(player)) continue;
        if (GetHp(player) <= 0) continue;

        void* TargetHead = TransformNode(*(void**)((uintptr_t)player + _HeadTF));
        if (!TargetHead) continue;

        Vector3 targetPos = Transform_INTERNAL_GetPosition(TargetHead);

        float dx = targetPos.X - localPos.X;
        float dy = targetPos.Y - localPos.Y;
        float dz = targetPos.Z - localPos.Z;
        float actualDistance = sqrtf(dx*dx + dy*dy + dz*dz);
        if (actualDistance < 5.0f && actualDistance < closestDist)

        {
            closestDist = actualDistance;
            targetTeammate = player;
        }

    }

    return targetTeammate;
}

void* GetKnockedTeammateNearby()

{
    float closestDist = 1000000.0f;
    void* targetTeammate = nullptr;

    if (!_GameFacade) return nullptr;

    void* MatchGame = *(void**)((uintptr_t)_GameFacade + _StaticClass);
    if (!MatchGame) return nullptr;

    void* ClassMatchGame = *(void**)((uintptr_t)MatchGame + _MatchGame);
    if (!ClassMatchGame) return nullptr;

    void* current_match = *(void**)((uintptr_t)ClassMatchGame + _Match);
    if (!current_match) return nullptr;

    void* LocalPlayer = Current_Local_Player();
    if (!LocalPlayer) return nullptr;

    void* LocalHead = TransformNode(*(void**)((uintptr_t)LocalPlayer + _HeadTF));
    if (!LocalHead) return nullptr;

    Vector3 localPos = Transform_INTERNAL_GetPosition(LocalHead);

    auto players = GetEntities(current_match);
    for (auto playerSS: players) {
        void* player = playerSS;
        if (!player) continue;
        if (player == LocalPlayer) continue;
        if (!IsLocalTeammate(player)) continue;
        if (!IsDieing(player)) continue;
        void* head = TransformNode(*(void**)((uintptr_t)player + _HeadTF));
        if (!head) continue;
        Vector3 targetPos = Transform_INTERNAL_GetPosition(head);
        float dx = targetPos.X - localPos.X;
        float dy = targetPos.Y - localPos.Y;
        float dz = targetPos.Z - localPos.Z;
        float dist = sqrtf(dx*dx + dy*dy + dz*dz);
        if (dist < 10.0f && dist < closestDist)

        {
            closestDist = dist;
            targetTeammate = player;
        }

    }

    return targetTeammate;
}

struct DamageInfo2_o {
    void *klass;
    void *monitor;
    int32_t BaseDamage;
    int32_t HitColliderType;
    monoString* HitColliderName;
    bool isBackArea;
    COW_GamePlay_IHAAMHPPLMG_o Damager;
    void* Weapon;
    int32_t WeaponDataID;
    Vector3 FirePos;
    Vector3 HitPos;
    Vector3 HitNormal;
    uint8_t SpecialHitType;
    bool ForceNoHeadShot;
    int32_t ExtraInfo;
    monoDictionary<uint8_t*, void **> *SpecialHitDic;
};

struct WeaponDynamicInfo2_o {
    void *klass;
    void *monitor;
    float BiteArmor;
    int32_t ContinuousFireDamage;
    int32_t DynamicChangeDamage;
    float DynamicDamageRatioBody;
    float DynamicDamageRatioHead;
    float DynamicDamageRatioLimb;
    float BoostDamage;
    float ShieldDamageRatioWeapon;
    float ShieldDamageRatioBody;
    float ShieldDamageRatioHead;
    float ShieldDamageRatioLimb;
};

monoList<float *> *LCLHHHKFCFP(void *Weapon, void *CAGCICACKCF, void *HFBDJJDICLN, bool LDGHPOPPPNL, DamageInfo2_o *DamageInfo)

{
    return ((monoList<float *> * (*)(void*, void*, void*, bool, DamageInfo2_o*))offset_LCLHHHKFCFP)(Weapon, CAGCICACKCF, HFBDJJDICLN, LDGHPOPPPNL, DamageInfo);
}

int32_t Player_TakeDamage(void *Player, int32_t p_damage, COW_GamePlay_IHAAMHPPLMG_o PlayerID, DamageInfo2_o *DamageInfo, int32_t WeaponDataID, Vector3 FirePos, Vector3 TargetPos, monoList<float *> *CheckParams, void *p_idk1, int32_t p_idk2)

{
    return ((int32_t (*)(void *, int32_t, COW_GamePlay_IHAAMHPPLMG_o, DamageInfo2_o *, int32_t, Vector3, Vector3, monoList<float *> *, void *, uint32_t))offset_Player_TakeDamage)(Player, p_damage, PlayerID, DamageInfo, WeaponDataID, FirePos, TargetPos, CheckParams, p_idk1, p_idk2);
}

// #define offset_PJKBDOJLDNN (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("EMOBCDJEOLN"), OBFUSCATE("PJKBDOJLDNN"))

// #define offset_GMOHIILGMGM (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("EMOBCDJEOLN"), OBFUSCATE("GMOHIILGMGM"))

void RequestRescureTargetV2(COW_GamePlay_IHAAMHPPLMG_o player)

{
    void *LocalPlayer = Current_Local_Player();
    void *message = (void *)offset_RequestRescureTar;
    if (message) {
        *(uint32_t*)((uint64_t)message + offset_PJKBDOJLDNN) = CFFPIACECIG(player);
        *(int64_t*)((uint64_t)message + offset_GMOHIILGMGM) = 1;
        GameFacade_Send(142, message, 2, 0);
    }

}

void AutoRevive() {
    void *LocalPlayer = Current_Local_Player();
    if(MasterBool.autorevive){
        void *targetTeammate = GetKnockedTeammateNearby();
        if (LocalPlayer != nullptr && targetTeammate != nullptr) {
            RequestRescureTargetV2(GetplayerID(targetTeammate));
        }

    }

}

// #define offset_exc_PJKBDOJLDNN (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("CEEAGMKELFD"), OBFUSCATE("PJKBDOJLDNN"))

// #define offset_exc_EGAMAMKBENE (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("CEEAGMKELFD"), OBFUSCATE("EGAMAMKBENE"))

void RequestExecuteTargetV2(void *thiss, COW_GamePlay_IHAAMHPPLMG_o targetID) {}

void (*RefreshAllParams)(void *player) = (void (*)(void *))offset_EMAOKNCFCKE;

bool DownEnemySnap(void *enemy)

{
    if (!enemy) return false;

    void *enemyTransform = Component_get_transform(enemy);
    if (!enemyTransform) return false;

    Vector3 enemyRoot = Transform_INTERNAL_GetPosition(enemyTransform);

    void *HeadTF = TransformNode(*(void **)((uint64_t)enemy + _HeadTF));
    if (!HeadTF) return false;

    Vector3 enemyHead = Transform_INTERNAL_GetPosition(HeadTF);

    Vector3 headOffset;
    headOffset.X = enemyHead.X - enemyRoot.X;
    headOffset.Y = enemyHead.Y - enemyRoot.Y;
    headOffset.Z = enemyHead.Z - enemyRoot.Z;

    void *LocalPlayer = Current_Local_Player();
    if (!LocalPlayer) return false;

    void *LPHeadTF = TransformNode(*(void **)((uint64_t)LocalPlayer + _HeadTF));
    if (!LPHeadTF) return false;

    Vector3 localHead = Transform_INTERNAL_GetPosition(LPHeadTF);

    float offsets[] = { -1.4f, -1.6f, -1.8f, -2.0f, -3.0f, -3.75f };
    for (int i = 0; i < 4; i++)

    {
        Vector3 newRoot = enemyRoot;
        newRoot.Y += offsets[i];

        Vector3 expectedHead;
        expectedHead.X = newRoot.X + headOffset.X;
        expectedHead.Y = newRoot.Y + headOffset.Y;
        expectedHead.Z = newRoot.Z + headOffset.Z;

        void *hitObj = NULL;

        if (!Physics_Raycast(localHead, expectedHead, 12, &hitObj))

        {
            Transform_set_position(enemyTransform, newRoot);
            return true;
        }

    }

    return false;
}


float TimerTakeDamageinit = 0.0f;

float TimerTakeDamageEnd  = 0.0f; // AGGRESSIVE: instant fire, no cooldown

// Pull enemy into line of sight inside aimkill â€” no player fire button needed

static bool AimkillMethodPull(void* enemy, void** outTf, Vector3* outOriginal) {
    if (!enemy) {
        return false;
    }
    if (!IsPullTargetValid(enemy)) {
        return false;
    }
    if (isVisible_Aimbot(enemy)) {
        return false;
    }
    void* tf = Component_get_transform(enemy);
    if (!tf) {
        return false;
    }
    *outTf = tf;
    *outOriginal = Transform_INTERNAL_GetPosition(tf);
    bool result = false;
    if (MasterBool.SafeSilentAim) {
        result = SafeSilentPull(enemy, nullptr, true);
    } else {
        result = SilentGhostPullV2(enemy, nullptr, true);
    }
    return result;
}

static void AimkillMethodRestore(void* enemy, void* tf, const Vector3& original) {
    if (enemy && tf && IsPullTargetValid(enemy)) {
        Transform_set_position(tf, original);
    }
}

static DamageInfo2_o* g_dmg99 = nullptr;
static WeaponDynamicInfo2_o* g_dyn99 = nullptr;

static void EnsureDamageInstances() {
    if (!g_dmg99) {
        g_dmg99 = (DamageInfo2_o*)Il2CppCreateClassInstance(
                OBFUSCATE("Assembly-CSharp.dll"),
                OBFUSCATE("COW.GamePlay"),
                OBFUSCATE("GLLLEDKLLDA")
        );
        if (g_dmg99) {
            memset((void*)((uintptr_t)g_dmg99 + sizeof(void*) * 2), 0, sizeof(DamageInfo2_o) - sizeof(void*) * 2);
        }
    }
    if (!g_dyn99) {
        g_dyn99 = (WeaponDynamicInfo2_o*)Il2CppCreateClassInstance(
                OBFUSCATE("Assembly-CSharp.dll"),
                OBFUSCATE("COW.GamePlay"),
                OBFUSCATE("LOAEBBHPMEK")
        );
        if (g_dyn99) {
            memset((void*)((uintptr_t)g_dyn99 + sizeof(void*) * 2), 0, sizeof(WeaponDynamicInfo2_o) - sizeof(void*) * 2);
            g_dyn99->DynamicDamageRatioBody  = 1.0f;
            g_dyn99->DynamicDamageRatioHead  = 1.0f;
            g_dyn99->DynamicDamageRatioLimb  = 1.0f;
            g_dyn99->ShieldDamageRatioWeapon = 1.0f;
            g_dyn99->ShieldDamageRatioBody   = 1.0f;
            g_dyn99->ShieldDamageRatioHead   = 1.0f;
            g_dyn99->ShieldDamageRatioLimb   = 1.0f;
        }
    }
}

void StartAimKillV2(void* enemy)
{
    if (!MasterBool.Aimkill) {
        return;
    }
    if (!enemy) {
        return;
    }

    void* local = Current_Local_Player();
    if (!local) {
        return;
    }
    if (local == enemy) {
        return;
    }
    if (IsDieing(local)) {
        return;
    }
    if (IsDieing(enemy)) {
        return;
    }

    void* hitInfo = *(void**)((uintptr_t)local + _HitObjectInfoWp);
    if (!hitInfo) {
        return;
    }

    void* headCollider = get_HeadCollider(enemy);
    if (!headCollider) {
        return;
    }
    void* headGO = get_gameObject(headCollider);
    if (!headGO) {
        return;
    }

    Vector3 localHead = GetHeadPosition(local);
    Vector3 enemyHead = GetHeadPosition(enemy);
    float dx = enemyHead.X - localHead.X;
    float dy = enemyHead.Y - localHead.Y;
    float dz = enemyHead.Z - localHead.Z;
    float len = sqrtf(dx*dx + dy*dy + dz*dz);
    Vector3 dir = {0,0,0};
    if (len > 0.0001f) {
        float inv = 1.0f / len;
        dir.X = dx * inv; dir.Y = dy * inv; dir.Z = dz * inv;
    }

    *(void**)((uintptr_t)hitInfo + Hit_GameObject)   = headGO;
    *(void**)((uintptr_t)hitInfo + Hit_HeadCollider) = headCollider;
    *(Vector3*)((uintptr_t)hitInfo + Hit_HitLoc)     = enemyHead;
    *(Vector3*)((uintptr_t)hitInfo + Hit_Normal)     = dir;
    *(Vector3*)((uintptr_t)hitInfo + Hit_RayDir)     = dir;
    *(Vector3*)((uintptr_t)hitInfo + Hit_StartPos)   = localHead;
    *(Vector3*)((uintptr_t)hitInfo + Hit_OrgStrtPos) = localHead;
    *(int*)((uintptr_t)hitInfo + Hit_Part)           = 1;
    *(bool*)((uintptr_t)hitInfo + Hit_Ignore)        = false;
    void* weapon = GetWeaponOnHand(local);
    if (!weapon) {
        return;
    }
    if (!isEnemyInRangeWeapon(local, enemy, weapon)) {
        return;
    }

    void* enemyTf = nullptr;
    Vector3 originalPos = {0, 0, 0};
    bool wasPulled = AimkillMethodPull(enemy, &enemyTf, &originalPos);
    bool visible = isVisible_Aimbot(enemy);
    if (!visible && !wasPulled) {
        return;
    }

    if (!IsFiringPlayer(local))
    {
        isfiringss(local, weapon);
        StartFiring(local, weapon);
        StartWholeFiring(local, weapon);
    }

    static bool hasStartedDamage = false;
    if (!hasStartedDamage) {
        SetStartDamage(weapon, hitInfo);
        hasStartedDamage = true;
    }

    int baseDamage = GetDamage(weapon);
    int weaponID   = GetWeaponID(weapon);
    EnsureDamageInstances();
    auto playerID = GetplayerID(local);
    g_dmg99->Damager = playerID;
    g_dmg99->HitColliderType = 1;
    g_dmg99->BaseDamage = baseDamage;
    g_dmg99->Weapon = weapon;
    g_dmg99->FirePos = localHead;
    g_dmg99->HitPos  = enemyHead;
    g_dmg99->WeaponDataID = GetWeaponDataId(weapon);
    LCLHHHKFCFP(weapon, GKHECDLGAJA(local, hitInfo), headCollider, false, (DamageInfo2_o*)NULL);
    void* rawParams = *(void**)((uintptr_t)weapon + 0x590);
    if (!rawParams) {
        return;
    }
    monoList<float*>* params = (monoList<float*>*)rawParams;
    if (!params) {
        return;
    }

    float now = get_time();
    if (now >= TimerTakeDamageinit)
    {
        TimerTakeDamageinit = now + TimerTakeDamageEnd;
        Player_TakeDamage(enemy, baseDamage, playerID, g_dmg99, weaponID,
                          localHead, enemyHead, params, g_dyn99, 0);
        AimkillMethodRestore(enemy, enemyTf, originalPos);
        StopFire(local, weapon);
        hasStartedDamage = false;
    Syns_SwapWeapon_Impl(local, weapon);
}
}

struct message_C2S_RUDP_TakeDamage_Req_o2 {
    void *klass;
    void *monitor;
    bool UDPClientMessageBase_m_GetFromPool;
    uint32_t ALFINFGBOBE;
    uint16_t ECDBFHHNPMI;
    uint16_t EKCONDDBKFO;
    uint32_t BJBPPEBIPFA;
    uint32_t LIIGLCNGOHG;
    int32_t PIAMIOFEBKF;
    uint32_t HCMIEJEBKAL;
    uint8_t ODCJPCEJHPK;
    uint32_t CEDJCPLOLNE;
    message_DEACEIFBHJK_o* CNEICNJFGLM;
    message_DEACEIFBHJK_o* PGDEDHFOMCN;
    monoList<float*> * AALHLOAJLEE;
    uint32_t HOBOHHJNDNH;
    float AILHIPMKJKJ;
    uint64_t LHGGPCFJNOO;
    int8_t ACAKHEABPEJ;
    bool MJIHLDJNHLF;
    bool MBGCAHPACOH;
    System_Collections_Generic_List_byte__o * FIKOAMIDEHL;
    float IOGIIEFAALP;
    bool HDEJLJKNLCI;
};

static bool InActiveMatch() {
    if (!_GameFacade) return false;

    void *matchGame = *(void **)((uintptr_t)_GameFacade + _StaticClass);
    if (!matchGame) return false;

    void *classMatchGame = *(void **)((uintptr_t)matchGame + _MatchGame);
    if (!classMatchGame) return false;

    void *current_match = *(void **)((uintptr_t)classMatchGame + _Match);
    if (!current_match) return false;

    return *(uint32_t *)((uintptr_t)current_match + _MatchState) == 1;
}

static bool (*original_WeaponFire)(void* weapon, COW_GamePlay_MADMMIICBNN_o *hitInfo) = nullptr;

static void FillHitInfoDirectly(COW_GamePlay_MADMMIICBNN_o *hitInfo, void *headCollider,
                                Vector3 enemyHeadPos, Vector3 localHeadPos, Vector3 direction,

                                float dist, int baseDamage) {
    if (!hitInfo || !headCollider) return;

    void* go = get_gameObject(headCollider);
    if (!go) return; // FIX: null guard â€” get_gameObject can return null after cover pull

    *(void**)((uintptr_t)hitInfo + Hit_GameObject) = go;
    *(void**)((uintptr_t)hitInfo + Hit_HeadCollider) = headCollider;
    *(Vector3*)((uintptr_t)hitInfo + Hit_HitLoc) = enemyHeadPos;
    *(Vector3*)((uintptr_t)hitInfo + Hit_Normal) = direction;
    *(Vector3*)((uintptr_t)hitInfo + Hit_RayDir) = direction;
    *(Vector3*)((uintptr_t)hitInfo + Hit_StartPos) = localHeadPos;
    *(Vector3*)((uintptr_t)hitInfo + Hit_OrgStrtPos) = localHeadPos;
    *(int*)((uintptr_t)hitInfo + Hit_Part) = 1;
    *(bool*)((uintptr_t)hitInfo + Hit_Ignore) = false;
    hitInfo->FFDIOGPKCKF = dist;
    hitInfo->IHNCAADOAAE = baseDamage;
}

void StartEnemyHitFly(void* enemyPlayer);

static inline bool ResolveWeaponFireFn() {
    if (!original_WeaponFire) {
        uintptr_t offset = offset_WeaponFire;
        if (!offset) offset = getRealOffset(0x66E999C);
        original_WeaponFire = (bool (*)(void*, COW_GamePlay_MADMMIICBNN_o*))offset;
    }
    return original_WeaponFire != nullptr;
}

void StartRealAimkill(void* ClosestEnemy) {
    if (!MasterBool.RealAimkill) return;
    if (!ClosestEnemy) return;
    if (IsDieing(ClosestEnemy)) return;
    if (GetHp(ClosestEnemy) <= 0) return;
    if (!InActiveMatch()) return;
    static void* s_lastTarget = nullptr;
    static float s_lastTime = 0;
    float now = get_time();
    if (ClosestEnemy == s_lastTarget && now - s_lastTime < 0.12f) return;
    s_lastTarget = ClosestEnemy;
    s_lastTime = now;
    void *localPlayer = Current_Local_Player();
    if (!localPlayer) return;
    if (localPlayer == ClosestEnemy) return;
    if (IsDieing(localPlayer)) return;
    void *weaponOnHand = GetWeaponOnHand(localPlayer);
    if (!weaponOnHand) return;
    void *enemyTf = nullptr;
    Vector3 originalPos = {0, 0, 0};
    bool wasPulled = AimkillMethodPull(ClosestEnemy, &enemyTf, &originalPos);
    if (!wasPulled && !isVisible_Aimbot(ClosestEnemy)) {
        AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
        return;
    }

    void *headColliderEnemy = get_HeadCollider(ClosestEnemy);
    if (!headColliderEnemy) {
        AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
        return;
    }

    if (!original_WeaponFire) {
        uintptr_t off = offset_WeaponFire;
        if (!off) off = getRealOffset(0x66E999C);
        original_WeaponFire = (bool (*)(void*, COW_GamePlay_MADMMIICBNN_o*))off;
    }
    if (!original_WeaponFire) {
        AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
        return;
    }

    void *hitObjectInfo = *(void **)((uintptr_t)localPlayer + _HitObjectInfoWp);
    if (!hitObjectInfo) {
        AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
        return;
    }

    Vector3 firePos = GetHeadPosition(localPlayer);
    Vector3 hitPos = GetHeadPosition(ClosestEnemy);
    float dx = hitPos.X - firePos.X, dy = hitPos.Y - firePos.Y, dz = hitPos.Z - firePos.Z;
    float dist = sqrtf(dx*dx + dy*dy + dz*dz);
    Vector3 dir = {0,0,0};
    if (dist > 0.0001f) { float inv = 1.0f/dist; dir.X = dx*inv; dir.Y = dy*inv; dir.Z = dz*inv; }

    void *headGameObject = get_gameObject(headColliderEnemy);
    if (!headGameObject) {
        AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
        return;
    }

    *(void **)((uintptr_t)hitObjectInfo + Hit_GameObject)   = headGameObject;
    *(void **)((uintptr_t)hitObjectInfo + Hit_HeadCollider) = headColliderEnemy;
    if (!GKHECDLGAJA(localPlayer, hitObjectInfo)) {
        AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
        return;
    }

    if (!IsFiringPlayer(localPlayer)) {
        StartFiring(localPlayer, weaponOnHand);
    }

    COW_GamePlay_MADMMIICBNN_o *hitInfo = (COW_GamePlay_MADMMIICBNN_o *)hitObjectInfo;
    if (!hitInfo) {
        AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
        return;
    }

    int realDmg = GetDamage(weaponOnHand);
    if (realDmg <= 0) realDmg = 40;
    if (realDmg > 200) realDmg = 200;
    FillHitInfoDirectly(hitInfo, headColliderEnemy, hitPos, firePos, dir, dist, realDmg);
    GKHECDLGAJA(localPlayer, hitObjectInfo);
    if (ClosestEnemy && !IsDieing(ClosestEnemy) && GetHp(ClosestEnemy) > 0) {
        original_WeaponFire(weaponOnHand, hitInfo);
    }

    StopFire(localPlayer, weaponOnHand);
    Syns_SwapWeapon_Impl(localPlayer, weaponOnHand);
    AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
}

static bool g_inAimkillV2 = false;
static std::vector<void*> g_aimkillV2EnemyList;
static int g_aimkillV2CurrentIndex = 0;
static bool g_aimkillV2Initialized = false;
bool g_isAimkillShot = false;
extern bool (*NoBUlletTractOriginal)(void* weapon, COW_GamePlay_MADMMIICBNN_o *hitInfo);
void FastFireMaxTimer();

void StartRealAimkillV2(void* ClosestEnemy) {
    if (!(MasterBool.RealAimkillV2 || MasterBool.TargetAll)) return;
    if (!InActiveMatch()) return;
    if (g_inAimkillV2) return;
    g_inAimkillV2 = true;

    // Shot cooldown / delay calibration (1.5x reduction in firing rate: eliminates lag, smooth 0-lag shots)
    static float s_last360FireTime = 0.0f;
    float now = get_time();
    if (now - s_last360FireTime < 0.10f) {
        g_inAimkillV2 = false;
        return;
    }

    void* local = Current_Local_Player();
    if (!local || IsDieing(local) || GetHp(local) <= 0) {
        g_inAimkillV2 = false;
        return;
    }

    void* weapon = GetWeaponOnHand(local);
    if (!weapon) {
        g_inAimkillV2 = false;
        return;
    }

    void* attrs = *(void**)((uintptr_t)local + _playerAttributes);
    if (attrs) *(bool*)((uintptr_t)attrs + offset_NoReload) = true;

    void* target = nullptr;
    if (ClosestEnemy && !IsDieing(ClosestEnemy) && GetHp(ClosestEnemy) > 0 && !IsLocalTeammate(ClosestEnemy)) {
        target = ClosestEnemy;
    } else if (MasterBool.TargetAll) {
        void* current_match = Current_Match();
        if (current_match) {
            auto players = GetEntities(current_match);
            Vector3 localHead = GetHeadPosition(local);
            float bestDistSq = 999999.0f;
            for (void* p : players) {
                if (!p || p == local || IsDieing(p) || GetHp(p) <= 0 || IsLocalTeammate(p)) continue;
                if (!isEnemyInRangeWeapon(local, p, weapon)) continue;
                Vector3 ePos = GetHeadPosition(p);
                float dx = ePos.X - localHead.X, dy = ePos.Y - localHead.Y, dz = ePos.Z - localHead.Z;
                float dSq = dx * dx + dy * dy + dz * dz;
                if (dSq < bestDistSq) {
                    bestDistSq = dSq;
                    target = p;
                }
            }
        }
    }

    if (!target) {
        g_inAimkillV2 = false;
        return;
    }

    void* hitObjectInfo = *(void**)((uintptr_t)local + _HitObjectInfoWp);
    if (!hitObjectInfo) {
        g_inAimkillV2 = false;
        return;
    }

    COW_GamePlay_MADMMIICBNN_o* hitInfo = (COW_GamePlay_MADMMIICBNN_o*)hitObjectInfo;

    void* enemyTf = nullptr;
    Vector3 originalPos = {0, 0, 0};
    bool wasPulled = false;
    if (!isVisible_Aimbot(target)) {
        wasPulled = AimkillMethodPull(target, &enemyTf, &originalPos);
        if (!wasPulled) {
            g_inAimkillV2 = false;
            return;
        }
    }

    void* headCollider = get_HeadCollider(target);
    if (!headCollider) {
        if (wasPulled && enemyTf && target) AimkillMethodRestore(target, enemyTf, originalPos);
        g_inAimkillV2 = false;
        return;
    }

    void* headGO = get_gameObject(headCollider);
    if (!headGO) {
        if (wasPulled && enemyTf && target) AimkillMethodRestore(target, enemyTf, originalPos);
        g_inAimkillV2 = false;
        return;
    }

    Vector3 curFirePos = GetHeadPosition(local);
    Vector3 hitPos = GetHeadPosition(target);
    float dx = hitPos.X - curFirePos.X;
    float dy = hitPos.Y - curFirePos.Y;
    float dz = hitPos.Z - curFirePos.Z;
    float dist = sqrtf(dx * dx + dy * dy + dz * dz);
    Vector3 direction = {0, 0, 0};
    if (dist > 0.0001f) {
        float inv = 1.0f / dist;
        direction.X = dx * inv;
        direction.Y = dy * inv;
        direction.Z = dz * inv;
    } else {
        direction.Z = 1.0f;
        dist = 1.0f;
    }

    if (wasPulled) {
        dist = 1.5f;
    }

    int baseDmg = GetDamage(weapon);
    if (baseDmg <= 0) baseDmg = 50;
    if (baseDmg > 200) baseDmg = 200;

    FillHitInfoDirectly(hitInfo, headCollider, hitPos, curFirePos, direction, dist, baseDmg);

    if (!wasPulled) {
        GKHECDLGAJA(local, hitObjectInfo);
    }

    if (!IsFiringPlayer(local)) {
        StartFiring(local, weapon);
    }

    GKHECDLGAJA(local, hitObjectInfo);

    if (NoBUlletTractOriginal) {
        NoBUlletTractOriginal(weapon, hitInfo);
    }
    if (ResolveWeaponFireFn() && original_WeaponFire) {
        original_WeaponFire(weapon, hitInfo);
    }

    if (wasPulled && enemyTf && target) {
        AimkillMethodRestore(target, enemyTf, originalPos);
    }

    StopFire(local, weapon);
    s_last360FireTime = now;
    g_inAimkillV2 = false;
}

static bool g_inAimkillSend = false;

Vector3 GetBodyPosition(void* player) {
    if (!player) return Vector3::Zero();
    if (_RootTF != 0 && _RootTF != (uintptr_t)-1) {
        void *RootTF = TransformNode(*(void **) ((uintptr_t) player + _RootTF));
        if (RootTF) {
            Vector3 rootPos = Transform_INTERNAL_GetPosition(RootTF);
            Vector3 headPos = GetHeadPosition(player);
            if (headPos.X != 0.0f || headPos.Y != 0.0f || headPos.Z != 0.0f) {
                return Vector3((headPos.X + rootPos.X) * 0.5f, (headPos.Y + rootPos.Y) * 0.5f, (headPos.Z + rootPos.Z) * 0.5f);
            }
            rootPos.Y += 0.9f;
            return rootPos;
        }
    }
    Vector3 head = GetHeadPosition(player);
    head.Y -= 0.6f;
    return head;
}

void* GetBodyCollider(void* player, void* headCollider) {
    if (!player) return headCollider;
    return headCollider;
}

void StartAimKillSend(void* ClosestEnemy) {
    if (!MasterBool.Aimkillsend && !MasterBool.AimkillBrutal && !MasterBool.AimkillBody) return;
    if (MasterBool.Aimkilltpv2) return;
    if (!InActiveMatch()) return;

    if (g_inAimkillSend) return;
    g_inAimkillSend = true;

    // Smooth burst cooldown to ensure 0 lag when performing squad swipe
    static float s_lastAimkillSendTime = 0.0f;
    float now = get_time();
    if (now - s_lastAimkillSendTime < 0.12f) {
        g_inAimkillSend = false;
        return;
    }
    s_lastAimkillSendTime = now;

    void *localPlayer = Current_Local_Player();
    if (!localPlayer || IsDieing(localPlayer)) { g_inAimkillSend = false; return; }

    void *weaponOnHand = GetWeaponOnHand(localPlayer);
    if (!weaponOnHand) { g_inAimkillSend = false; return; }

    void* current_match = Current_Match();
    if (!current_match) { g_inAimkillSend = false; return; }

    auto players = GetEntities(current_match);
    if (players.empty()) { g_inAimkillSend = false; return; }

    Vector3 firePos = GetHeadPosition(localPlayer);

    if (!ResolveWeaponFireFn()) { g_inAimkillSend = false; return; }

    void *hitObjectInfo = *(void **)((uintptr_t)localPlayer + _HitObjectInfoWp);
    if (!hitObjectInfo) { g_inAimkillSend = false; return; }

    COW_GamePlay_MADMMIICBNN_o *hitInfo = (COW_GamePlay_MADMMIICBNN_o *)hitObjectInfo;
    if (!hitInfo) { g_inAimkillSend = false; return; }

    std::vector<void*> targetsToProcess;

    // Prioritize explicit target parameter if valid (e.g. single enemy or locked target)
    if (ClosestEnemy && !IsDieing(ClosestEnemy) && GetHp(ClosestEnemy) > 0 && !IsLocalTeammate(ClosestEnemy)) {
        targetsToProcess.push_back(ClosestEnemy);
    }

    // Build target queue sorted by 3D distance squared (100x faster than WorldToScreenPoint, ZERO CPU lag)
    std::vector<std::pair<float, void*>> fastCandidates;
    for (auto p : players) {
        if (!p || p == localPlayer || p == ClosestEnemy || IsDieing(p) || GetHp(p) <= 0 || IsLocalTeammate(p)) continue;

        void *HeadTF = TransformNode(*(void **) ((uint64_t) p + _HeadTF));
        if (!HeadTF) continue;

        Vector3 headPos = Transform_INTERNAL_GetPosition(HeadTF);
        float dx = headPos.X - firePos.X;
        float dy = headPos.Y - firePos.Y;
        float dz = headPos.Z - firePos.Z;
        float distSq = dx * dx + dy * dy + dz * dz;

        fastCandidates.push_back({distSq, p});
    }

    if (!fastCandidates.empty()) {
        std::sort(fastCandidates.begin(), fastCandidates.end(),
                  [](const std::pair<float, void*>& a, const std::pair<float, void*>& b) {
                      return a.first < b.first;
                  });

        for (auto& item : fastCandidates) {
            targetsToProcess.push_back(item.second);
        }
    }

    if (targetsToProcess.empty()) { g_inAimkillSend = false; return; }

    // Force No Reload attribute so weapon ammo never drops and AWM bolt-action animation lock is bypassed
    void *playerattributes = *(void **) ((uint64_t) localPlayer + _playerAttributes);
    if (playerattributes != nullptr) {
        *(bool *) ((uintptr_t) playerattributes + offset_NoReload) = true;
    }

    int processedTargets = 0;
    for (auto target : targetsToProcess) {
        if (processedTargets >= 5) break; // Multi-target squad swipe: hit up to 5 targets in 1 tick
        if (!target || target == localPlayer || IsDieing(target) || GetHp(target) <= 0 || IsLocalTeammate(target)) continue;

        void* enemyTf = nullptr;
        Vector3 originalPos = {0, 0, 0};
        bool wasPulled = AimkillMethodPull(target, &enemyTf, &originalPos);
        bool visible = isVisible_Aimbot(target);

        if (!visible && !wasPulled) {
            if (wasPulled && enemyTf && target) AimkillMethodRestore(target, enemyTf, originalPos);
            continue;
        }

        // Calculate post-pull active positions for 100% valid server hit registration
        Vector3 curFirePos = GetHeadPosition(localPlayer);
        Vector3 hitPos = MasterBool.AimkillBody ? GetBodyPosition(target) : GetHeadPosition(target);

        float dx = hitPos.X - curFirePos.X;
        float dy = hitPos.Y - curFirePos.Y;
        float dz = hitPos.Z - curFirePos.Z;
        float dist = sqrtf(dx * dx + dy * dy + dz * dz);
        Vector3 direction = {0, 0, 0};
        if (dist > 0.0001f) {
            float inv = 1.0f / dist;
            direction.X = dx * inv;
            direction.Y = dy * inv;
            direction.Z = dz * inv;
        } else {
            direction.Z = 1.0f;
            dist = 1.0f;
        }

        // Bypasses weapon distance limits on short-range guns (Shotguns/Pistols) when target is pulled
        if (wasPulled) {
            dist = 1.5f;
        }

        void* headCollider = get_HeadCollider(target);
        if (!headCollider) {
            if (wasPulled && enemyTf && target) AimkillMethodRestore(target, enemyTf, originalPos);
            continue;
        }
        void* targetCollider = MasterBool.AimkillBody ? GetBodyCollider(target, headCollider) : headCollider;
        if (!targetCollider) {
            if (wasPulled && enemyTf && target) AimkillMethodRestore(target, enemyTf, originalPos);
            continue;
        }
        void *headGameObject = get_gameObject(targetCollider);
        if (!headGameObject) {
            if (wasPulled && enemyTf && target) AimkillMethodRestore(target, enemyTf, originalPos);
            continue;
        }

        // Calculate exact lethal damage for ALL weapon types (ARs, SMGs, Shotguns, Snipers, Pistols)
        int baseDmg = GetDamage(weaponOnHand);
        if (baseDmg <= 0 || baseDmg < 100) {
            baseDmg = MasterBool.AimkillBody ? 180 : 350; // Universal lethal damage calibration
        }

        FillHitInfoDirectly(hitInfo, targetCollider, hitPos, curFirePos, direction, dist, baseDmg);

        // Raycast line of sight check — bypass if target was pulled through cover to prevent fake damage
        if (!wasPulled && !GKHECDLGAJA(localPlayer, hitObjectInfo)) {
            if (wasPulled && enemyTf && target) AimkillMethodRestore(target, enemyTf, originalPos);
            continue;
        }

        if (!IsFiringPlayer(localPlayer)) {
            StartFiring(localPlayer, weaponOnHand);
        }

        if (target && !IsDieing(target) && GetHp(target) > 0 && weaponOnHand && hitInfo) {
            // Dual-channel hit packet dispatch for ZERO fake damage on ALL weapon types
            if (NoBUlletTractOriginal) {
                NoBUlletTractOriginal(weaponOnHand, hitInfo);
            }
            if (ResolveWeaponFireFn() && original_WeaponFire) {
                original_WeaponFire(weaponOnHand, hitInfo);
            }
        }

        if (wasPulled && enemyTf && target) {
            AimkillMethodRestore(target, enemyTf, originalPos);
        }

        processedTargets++;
    }

    g_inAimkillSend = false;
}

static void (*HitFly_DirectMethod)(void*, void*) = nullptr;

void StartEnemyHitFly(void* enemyPlayer) {
    if (!enemyPlayer) return;
    if (IsDieing(enemyPlayer)) return;

    if (!HitFly_DirectMethod) {
        uintptr_t off = getRealOffset(0x169e074);
        if (off) HitFly_DirectMethod = (void (*)(void*, void*))off;
    }
    if (!HitFly_DirectMethod) return;
    void* localPlayer = Current_Local_Player();
    if (!localPlayer) return;
    HitFly_DirectMethod(localPlayer, enemyPlayer);
}

void Telekillkk(void* targetVivo)

{
    if (MasterBool.telehack)

    {
        void *LocalPlayer = Current_Local_Player();
        if (LocalPlayer != NULL) {
            void *weaponOnHand = GetWeaponOnHand(LocalPlayer);
            if (weaponOnHand != nullptr)

            {
                void* targetEnemy = targetVivo;
                if (targetEnemy != nullptr)

                {
                    if (MasterBool.telehack && targetEnemy != nullptr && LocalPlayer != nullptr) {
                        void* enemyRoot = TransformNode(*(void**)((uintptr_t)targetEnemy + _RootTF));
                        if (!enemyRoot) return;
                        Vector3 EnemyPos = Transform_INTERNAL_GetPosition(enemyRoot);

                        void* playerRoot = TransformNode(*(void**)((uintptr_t)LocalPlayer + _RootTF));
                        if (!playerRoot) return;
                        Vector3 LocalPos = Transform_INTERNAL_GetPosition(playerRoot);

                        float distance = Vector3Distance(EnemyPos, LocalPos);
                        if (distance <= 20.0f) {
                            Transform_set_position(Component_get_transform(targetEnemy),LocalPos);
                        }

                    }

                }

            }

        }

    }

    return;
}

void ForceAutoSwitchReliable(void* LocalPlayer) {

    if (MasterBool.autoswitch)

    {
        static int lastSlot = 2;
        void* weaponOnHand = GetWeaponOnHand(LocalPlayer);
        if (!weaponOnHand) return;
        int newSlot = (lastSlot == 1) ? 2 : 1;
        SwapWeapon(LocalPlayer, newSlot, 1);
        lastSlot = newSlot;
    }

}

bool fastSwitchPatched = false;

void FastSwitch() {
    if (Current_Local_Player() != nullptr && MasterBool.fastswitch) {
        float *fASTSWITCH = (float *)((uint64_t)Current_Local_Player() +  _FastSwitch);
        if(fASTSWITCH != nullptr){
            *fASTSWITCH = 0.0f;
        }

    }

}

static uintptr_t off_UiScene = 0;
static uintptr_t off_UiMapCtrl = 0;
static uintptr_t off_MapContentCtrl = 0;
static uintptr_t off_LocalMarkCtrl = 0;
static uintptr_t off_LocalMarkPos = 0;

static void InitMapOffsets() {
    if (off_UiScene == 0) {
        size_t res = Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("BaseGame"), OBFUSCATE("m_UIScene"));
        off_UiScene = (res != (size_t)-1 && res != 0) ? res : 0x8;
    }
    if (off_UiMapCtrl == 0) {
        size_t res = Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("m_BigMapCtrl"));
        off_UiMapCtrl = (res != (size_t)-1 && res != 0) ? res : 0x104;
    }
    if (off_MapContentCtrl == 0) {
        size_t res = Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIMapBaseController"), OBFUSCATE("m_MapContentCtrl"));
        off_MapContentCtrl = (res != (size_t)-1 && res != 0) ? res : 0x54;
    }
    if (off_LocalMarkCtrl == 0) {
        size_t res = Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIMapContentController"), OBFUSCATE("m_LocalMapMarkController"));
        off_LocalMarkCtrl = (res != (size_t)-1 && res != 0) ? res : 0x90;
    }
    if (off_LocalMarkPos == 0) {
        size_t res = Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudPlayerMarkController"), OBFUSCATE("m_pos"));
        off_LocalMarkPos = (res != (size_t)-1 && res != 0) ? res : 0x58;
    }
}

Vector3 MarkedLoc()
{
    InitMapOffsets();
    if (!_GameFacade) return Vector3::Zero();
    uintptr_t staticGameFacadePtr = (uintptr_t)_GameFacade + _StaticClass;
    if (staticGameFacadePtr < 0x10000) return Vector3::Zero();
    void* StaticGameFacade = *(void**)staticGameFacadePtr;
    if (!StaticGameFacade || (uintptr_t)StaticGameFacade < 0x10000) return Vector3::Zero();
    uintptr_t currentGamePtr = (uintptr_t)StaticGameFacade + _MatchGame;
    if (currentGamePtr < 0x10000) return Vector3::Zero();
    void* CurrentGame = *(void**)currentGamePtr;
    if (!CurrentGame || (uintptr_t)CurrentGame < 0x10000) return Vector3::Zero();
    uintptr_t gameScenePtr = (uintptr_t)CurrentGame + off_UiScene;
    if (gameScenePtr < 0x10000) return Vector3::Zero();
    void* GameScene = *(void**)gameScenePtr;
    if (!GameScene || (uintptr_t)GameScene < 0x10000) return Vector3::Zero();
    uintptr_t bigMapRootPtr = (uintptr_t)GameScene + off_UiMapCtrl;
    if (bigMapRootPtr < 0x10000) return Vector3::Zero();
    void* BigMapRoot = *(void**)bigMapRootPtr;
    if (!BigMapRoot || (uintptr_t)BigMapRoot < 0x10000) return Vector3::Zero();

    Vector3 selectPoint = *(Vector3*)((uintptr_t)BigMapRoot + 0x12C);
    if (selectPoint.X != 0.0f || selectPoint.Z != 0.0f) {
        return selectPoint;
    }

    uintptr_t mapContentPtr = (uintptr_t)BigMapRoot + off_MapContentCtrl;
    if (mapContentPtr < 0x10000) return Vector3::Zero();
    void* MapContent = *(void**)mapContentPtr;
    if (!MapContent || (uintptr_t)MapContent < 0x10000) return Vector3::Zero();
    uintptr_t localMapMarkPtr = (uintptr_t)MapContent + off_LocalMarkCtrl;
    if (localMapMarkPtr < 0x10000) return Vector3::Zero();
    void* LocalMapMark = *(void**)localMapMarkPtr;
    if (!LocalMapMark || (uintptr_t)LocalMapMark < 0x10000) return Vector3::Zero();
    uintptr_t markPosPtr = (uintptr_t)LocalMapMark + off_LocalMarkPos;
    if (markPosPtr < 0x10000) return Vector3::Zero();
    Vector3 MarkPos = *(Vector3*)markPosPtr;
    return MarkPos;
}

#include <thread>

#include <chrono>

void SuperFastAutoSwitchLoop1() {
    static auto last = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
    if (elapsed < 50) return;
    last = now;
    void *localPlayer = Current_Local_Player();
    if (localPlayer == nullptr) return;
    ForceAutoSwitchReliable(localPlayer);
}

void NormalAutoSwitchLoop() {
    if (!MasterBool.autoswitchsafe) return;
    if (g_inAimkillV2) return;

    static auto lastSwitch = std::chrono::steady_clock::now();
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)(get_realtimeSinceStartup() * 1000.0f));
        seeded = true;
    }

    auto now = std::chrono::steady_clock::now();
    long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastSwitch).count();
    long long minDelay = 70;
    long long maxDelay = 120;
    long long humanDelay = minDelay + (rand() % (int)(maxDelay - minDelay + 1));
    if (elapsed < humanDelay) return;
    lastSwitch = now;
    void *localPlayer = Current_Local_Player();
    if (!localPlayer || IsDieing(localPlayer)) return;
    void *weaponOnHand = GetWeaponOnHand(localPlayer);
    if (!weaponOnHand) return;
    static int lastSlot = 2;
    int newSlot = (lastSlot == 1) ? 2 : 1;
    SwapWeapon(localPlayer, newSlot, 1);
    lastSlot = newSlot;
}

bool isInsideFOV(int x, int y, float customFOV) {
    float circle_x = (float)g_screenWidth / 2.0f;
    float circle_y = (float)g_screenHeight / 2.0f;
    float rad = (customFOV > 0) ? customFOV : MasterBool.aimbotFOV;
    return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
}

void* BestEnemyFind(void* skipTarget)

{
    static void* persistentTarget = nullptr;

    void* StaticGameFacade = *(void**)((uint64_t)_GameFacade + _StaticClass);
    if (!StaticGameFacade) return nullptr;
    void *ClassMatchGame = *(void **) ((uint64_t) StaticGameFacade + _MatchGame);
    if (ClassMatchGame == nullptr) return nullptr;
    void *current_match = *(void **) ((uint64_t) ClassMatchGame + _Match);
    if (current_match == nullptr) return nullptr;
    auto matchStatus = *(uint32_t *) ((uint64_t) current_match + _MatchState);
    if (matchStatus != 1) {
        persistentTarget = nullptr;
        return nullptr;
    }

    void *CurrentLocalPlayer = Current_Local_Player();
    if (CurrentLocalPlayer == nullptr) {
        persistentTarget = nullptr;
        return nullptr;
    }

    if (persistentTarget != nullptr) {
        if (!IsDieing(persistentTarget) && GetHp(persistentTarget) > 0) {
            void *HeadTF = TransformNode(*(void **) ((uint64_t) persistentTarget + _HeadTF));
            if (HeadTF != nullptr) {
                Vector3 screenHead = WorldToScreenPoint(Transform_INTERNAL_GetPosition(HeadTF));
                if (screenHead.Z > 0.01f && isInsideFOV((int)screenHead.X, (int)screenHead.Y)) {
                    return persistentTarget;
                }

            }

        }

        persistentTarget = nullptr;
    }

    static std::vector<std::pair<float, void*>> s_adiFovList;
    s_adiFovList.clear();
    Vector3 v2Middle = Vector3((float)(g_screenWidth / 2), (float)(g_screenHeight / 2));

    auto players = GetEntities(current_match);
    for (auto player: players) {
        if (player == nullptr || player == CurrentLocalPlayer) continue;
        if (IsDieing(player) || GetHp(player) <= 0 || IsLocalTeammate(player)) continue;

        void *HeadTF = TransformNode(*(void **) ((uint64_t) player + _HeadTF));
        if (HeadTF == nullptr) continue;

        Vector3 WorldToScreenHead = WorldToScreenPoint(Transform_INTERNAL_GetPosition(HeadTF));
        if (WorldToScreenHead.Z < 0.01f) continue;
        if (!isInsideFOV((int)WorldToScreenHead.X, (int)WorldToScreenHead.Y)) continue;

        float dist = (float)Vector3Distance(v2Middle, Vector3(WorldToScreenHead.X, WorldToScreenHead.Y));
        s_adiFovList.push_back(std::make_pair(dist, player));
    }

    if (!s_adiFovList.empty()) {
        std::sort(s_adiFovList.begin(), s_adiFovList.end(), [](const std::pair<float, void*>& a, const std::pair<float, void*>& b) { return a.first < b.first; });
        persistentTarget = s_adiFovList[0].second;
        return persistentTarget;
    }

    return nullptr;
}

void* BestEnemyFind360()

{
    static std::vector<std::pair<float, void*>> enemyList;
    static size_t index = 0;
    enemyList.clear();
    void* StaticGameFacade = *(void**)((uint64_t)_GameFacade + _StaticClass);
    if (!StaticGameFacade) return nullptr;
    void *ClassMatchGame = *(void **)((uint64_t)StaticGameFacade + _MatchGame);
    if (!ClassMatchGame) return nullptr;
    void *current_match = *(void **)((uint64_t)ClassMatchGame + _Match);
    if (!current_match) return nullptr;
    auto matchStatus = *(uint32_t*)((uint64_t)current_match + _MatchState);
    if (matchStatus != 1) return nullptr;
    void *LocalPlayer = Current_Local_Player();
    if (!LocalPlayer) return nullptr;
    void *LocalTF = Component_get_transform(LocalPlayer);
    if (!LocalTF) return nullptr;
    Vector3 LocalPos = Transform_INTERNAL_GetPosition(LocalTF);

    auto players = GetEntities(current_match);
    for (auto player: players) {
        void* enemy = player;
        if (!enemy || enemy == LocalPlayer)continue;
        if (IsDieing(enemy))continue;
        if (IsLocalTeammate(enemy)) continue;
        if (GetHp(enemy) <= 0)continue;
        void *HeadTF = TransformNode(*(void**)((uint64_t)enemy + _HeadTF));
        if (!HeadTF) continue;
        Vector3 enemyPos = Transform_INTERNAL_GetPosition(HeadTF);
        float distance = Vector3Distance(LocalPos, enemyPos);
        enemyList.push_back(std::make_pair(distance, enemy));
    }

    if (enemyList.empty()) return nullptr;
    std::sort(enemyList.begin(), enemyList.end(),[](const std::pair<float, void*>& a, const std::pair<float, void*>& b){return a.first < b.first;});
    size_t idx = index % enemyList.size();
    void* result = enemyList[idx].second;
    index++;
    return result;
}

#include <math.h>

Quaternion Quaternion_Euler(float x, float y, float z)

{
    float radX = x * (M_PI / 180.0f);
    float radY = y * (M_PI / 180.0f);
    float radZ = z * (M_PI / 180.0f);

    float cx = cos(radX * 0.5f);
    float sx = sin(radX * 0.5f);
    float cy = cos(radY * 0.5f);
    float sy = sin(radY * 0.5f);
    float cz = cos(radZ * 0.5f);
    float sz = sin(radZ * 0.5f);

    Quaternion q;

    q.W = cx * cy * cz + sx * sy * sz;
    q.X = sx * cy * cz - cx * sy * sz;
    q.Y = cx * sy * cz + sx * cy * sz;
    q.Z = cx * cy * sz - sx * sy * cz;

    return q;
}

static bool supermanActive = false;
static Vector3 lastPos = Vector3(0,0,0);

void SupermanJump(void* player)

{
    if (!player) return;
    void* tf = Component_get_transform(player);
    if (!tf) return;
    bool jumpReq = GetPhysicalCCT(player);
    bool falling = IsPlayerFalling(player);
    Vector3 pos = Transform_INTERNAL_GetPosition(tf);
    Vector3 move = pos - lastPos;
    float yaw;
    float pitch = 25.0f;
    Vector3 currentEuler = Quaternion::ToEuler(Transform_get_rotation(tf));
    if (move.Z > 0.01f)

    {
        yaw = atan2(move.X, move.Z) * 57.29578f;
        Vector3 forward = Transform_get_forward(tf);
        float dot = forward.X * move.X + forward.Z * move.Z;
        if (dot < 0) pitch = -25.0f;
    }

    else

    {
        yaw = currentEuler.Y;
    }

    if (falling && (jumpReq || !supermanActive))

    {
        Quaternion rot = Quaternion_Euler(pitch, yaw, 0.0f);
        Transform_set_rotation(tf, rot);
        supermanActive = true;
    }

    if (!falling && supermanActive)

    {
        Quaternion rot = Quaternion_Euler(0.0f, yaw, 0.0f);
        Transform_set_rotation(tf, rot);
        supermanActive = false;
    }

    lastPos = pos;
}

namespace DownPlayer {
    bool active = false;
    Vector3 originalPos = {0, 0, 0};
    bool firstTime = true;

    void Update() {
        if (!MasterBool.DiveKill && !active) return;
        if (_HeadTF == 0 || _HeadTF == (uintptr_t)-1) return;
        if (_RootTF == 0 || _RootTF == (uintptr_t)-1) return;

        void* lp = Current_Local_Player();
        if (!lp) {
            active = false;
            return;
        }
        void* headBone = *(void**)((uintptr_t)lp + _HeadTF);
        if (!headBone) return;

        void* t = *(void**)((uintptr_t)headBone + 0x8);
        if (!t) return;

        void* o = *(void**)((uintptr_t)t + 0x8);
        if (!o) return;

        void* matrix = *(void**)((uintptr_t)o + 0x20);
        if (!matrix) return;

        Vector3 current = *(Vector3*)((uintptr_t)matrix + 0x60);

        if (MasterBool.DiveKill) {

            if (!active || firstTime) {
                originalPos = current;
                active = true;
                firstTime = false;
            }

            Vector3 underground = current;
            underground.Y -= 3.0f;

            void* pesBone = *(void**)((uintptr_t)lp + _RootTF);
            if (!pesBone) return;

            void* pesT = *(void**)((uintptr_t)pesBone + 0x8);
            if (!pesT) return;

            void* pesO = *(void**)((uintptr_t)pesT + 0x8);
            if (!pesO) return;

            void* pesMatrix = *(void**)((uintptr_t)pesO + 0x20);
            if (!pesMatrix) return;

            *(Vector3*)((uintptr_t)pesMatrix + 0x60) = underground;
            *(Vector3*)((uintptr_t)matrix + 0x60) = underground;

        } else {

            if (active) {
                void* pesBone = *(void**)((uintptr_t)lp + _RootTF);
                if (pesBone) {
                    void* pesT = *(void**)((uintptr_t)pesBone + 0x8);
                    if (pesT) {
                        void* pesO = *(void**)((uintptr_t)pesT + 0x8);
                        if (pesO) {
                            void* pesMatrix = *(void**)((uintptr_t)pesO + 0x20);
                            if (pesMatrix) {
                                *(Vector3*)((uintptr_t)pesMatrix + 0x60) = originalPos;
                            }
                        }
                    }
                }
                *(Vector3*)((uintptr_t)matrix + 0x60) = originalPos;
                active = false;
                firstTime = true;
            }
        }
    }
}

namespace DownEnemy {
    bool active = false;
    Vector3 originalPos = {0, 0, 0};
    void* lastEnemy = nullptr;

    void ResetEnemy(void* enemy) {
        if (!enemy) return;

        void* headBone = *(void**)((uintptr_t)enemy + _HeadTF);
        if (!headBone) return;

        void* t = *(void**)((uintptr_t)headBone + 0x8);
        if (!t) return;

        void* o = *(void**)((uintptr_t)t + 0x8);
        if (!o) return;

        void* matrix = *(void**)((uintptr_t)o + 0x20);
        if (!matrix) return;

        void* pesBone = *(void**)((uintptr_t)enemy + _RootTF);
        if (pesBone) {
            void* pesT = *(void**)((uintptr_t)pesBone + 0x8);
            if (pesT) {
                void* pesO = *(void**)((uintptr_t)pesT + 0x8);
                if (pesO) {
                    void* pesMatrix = *(void**)((uintptr_t)pesO + 0x20);
                    if (pesMatrix) {
                        *(Vector3*)((uintptr_t)pesMatrix + 0x60) = originalPos;
                    }
                }
            }
        }

        *(Vector3*)((uintptr_t)matrix + 0x60) = originalPos;
    }

    void Update() {
        if (!MasterBool.downplayerV2 && !active) return;
        if (_HeadTF == 0 || _HeadTF == (uintptr_t)-1) return;
        if (_RootTF == 0 || _RootTF == (uintptr_t)-1) return;

        if (!MasterBool.downplayerV2) {
            if (active && lastEnemy) {
                ResetEnemy(lastEnemy);
                active = false;
                lastEnemy = nullptr;
            }
            return;
        }

        void* targetEnemy = cachedTarget ? cachedTarget : BestEnemyFind(nullptr);
        if (!targetEnemy) {
            targetEnemy = cachedTarget360 ? cachedTarget360 : BestEnemyFind360();
        }

        if (!targetEnemy) {
            if (active && lastEnemy) {
                ResetEnemy(lastEnemy);
                active = false;
                lastEnemy = nullptr;
            }
            return;
        }

        if (lastEnemy && lastEnemy != targetEnemy) {
            ResetEnemy(lastEnemy);
            active = false;
        }

        lastEnemy = targetEnemy;

        void* headBone = *(void**)((uintptr_t)targetEnemy + _HeadTF);
        if (!headBone) return;

        void* t = *(void**)((uintptr_t)headBone + 0x8);
        if (!t) return;

        void* o = *(void**)((uintptr_t)t + 0x8);
        if (!o) return;

        void* matrix = *(void**)((uintptr_t)o + 0x20);
        if (!matrix) return;

        Vector3 current = *(Vector3*)((uintptr_t)matrix + 0x60);

        if (!active) {
            originalPos = current;
            active = true;
        }

        Vector3 underground = current;
        underground.Y -= 3.0f;

        void* pesBone = *(void**)((uintptr_t)targetEnemy + _RootTF);
        if (!pesBone) return;

        void* pesT = *(void**)((uintptr_t)pesBone + 0x8);
        if (!pesT) return;

        void* pesO = *(void**)((uintptr_t)pesT + 0x8);
        if (!pesO) return;

        void* pesMatrix = *(void**)((uintptr_t)pesO + 0x20);
        if (!pesMatrix) return;

        *(Vector3*)((uintptr_t)pesMatrix + 0x60) = underground;
        *(Vector3*)((uintptr_t)matrix + 0x60) = underground;
    }
}


void AESPName()

{
    static int lastEnemyCount = -1;
    static monoString* globalName = nullptr;

    int currentEnemyCount = 0;
    void* StaticGameFacade = *(void**)((uint64_t)_GameFacade + _StaticClass);
    if (StaticGameFacade) {
        void *ClassMatchGame = *(void **) ((uint64_t) StaticGameFacade + _MatchGame);
        if (ClassMatchGame) {
            void *current_match = *(void **) ((uint64_t) ClassMatchGame + _Match);
            if (current_match) {
                auto players = GetEntities(current_match);
                void *LocalPlayer = Current_Local_Player();
                for (auto player: players) {
                    if (player && player != LocalPlayer && !IsLocalTeammate(player) && GetHp(player) > 0) {
                        currentEnemyCount++;
                    }

                }

            }

        }

    }

    if (currentEnemyCount != lastEnemyCount || globalName == nullptr) {
        lastEnemyCount = currentEnemyCount;
        std::string gameName = (getPackageName() == "com.dts.freefiremax") ? "Free Fire Max" : "Free Fire";
        char buffer[256];
        sprintf(buffer, " Onyx - %s [ %d ] ", gameName.c_str(), currentEnemyCount);
        globalName = (monoString*)Il2CppString::Create(buffer);
    }

    if (globalName != nullptr)

    {
        // ShowCenterUpTeammateTips(globalName, 0.2f);

    }

}

void ApplyFlyMap(void* localPlayer) {
    if (!localPlayer) return;
    void *transform = Component_get_transform(localPlayer);
    if (!transform) return;

    static bool isTeleportingMap = false;
    static Vector3 targetMapPos = Vector3::Zero();
    static std::chrono::steady_clock::time_point mapTeleportStart;
    typedef void* (*_Player_get_CharacterController)(void* player);
    typedef void (*_Behaviour_set_enabled)(void* behaviour, bool enabled);
    static _Player_get_CharacterController Player_get_CharacterController = nullptr;
    static _Behaviour_set_enabled Behaviour_set_enabled = nullptr;
    if (!Player_get_CharacterController) {
        Player_get_CharacterController = (_Player_get_CharacterController) Il2CppGetMethodOffset(
            OBFUSCATE("Assembly-CSharp.dll"),
            OBFUSCATE("COW.GamePlay"),
            OBFUSCATE("Player"),
            OBFUSCATE("get_CharacterController"),
            0
        );
    }
    if (!Behaviour_set_enabled) {
        Behaviour_set_enabled = (_Behaviour_set_enabled) Il2CppGetMethodOffset(
            OBFUSCATE("UnityEngine.CoreModule.dll"),
            OBFUSCATE("UnityEngine"),
            OBFUSCATE("Behaviour"),
            OBFUSCATE("set_enabled"),
            1
        );
    }

    auto nowTime = std::chrono::steady_clock::now();
    if (MasterBool.mapateleport) {
        if (!isTeleportingMap) {
            Vector3 mLoc = MarkedLoc();
            if (mLoc.X != 0.0f || mLoc.Z != 0.0f) {
                Vector3 currentPos = Transform_INTERNAL_GetPosition(transform);
                if (mLoc.Y <= 0.0f) {
                    mLoc.Y = (currentPos.Y > 0.0f) ? currentPos.Y : 50.0f;
                } else {
                    mLoc.Y += 1.5f; // Elevation to land cleanly on top of terrain
                }
                targetMapPos = mLoc;
                isTeleportingMap = true;
                mapTeleportStart = nowTime;
            } else {
                MasterBool.mapateleport = false;
            }
        }
    }

    if (isTeleportingMap) {
        auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - mapTeleportStart).count();
        void* cc = nullptr;
        if (Player_get_CharacterController && localPlayer) {
            cc = Player_get_CharacterController(localPlayer);
        }

        // Temporarily disable CharacterController to flush cached ground position
        if (cc && Behaviour_set_enabled) {
            Behaviour_set_enabled(cc, false);
        }

        // 1. Move main player transform
        Transform_set_position(transform, targetMapPos);

        // 2. Move RootTF transform (Root bone)
        if (_RootTF != 0) {
            uintptr_t rawRoot = *(uintptr_t*)((uintptr_t)localPlayer + _RootTF);
            if (rawRoot > 0x10000) {
                void* playerRoot = TransformNode((void*)rawRoot);
                if (playerRoot) {
                    Transform_set_position(playerRoot, targetMapPos);
                }
            }
        }

        // Re-enable CharacterController to lock new position in physics engine
        if (cc && Behaviour_set_enabled) {
            Behaviour_set_enabled(cc, true);
        }

        if (elapsedMs < 1000 && MasterBool.mapateleport) {
            return;
        } else {
            // Final position flush to guarantee no revert when turning OFF switch
            Transform_set_position(transform, targetMapPos);
            if (_RootTF != 0) {
                uintptr_t rawRoot = *(uintptr_t*)((uintptr_t)localPlayer + _RootTF);
                if (rawRoot > 0x10000) {
                    void* playerRoot = TransformNode((void*)rawRoot);
                    if (playerRoot) Transform_set_position(playerRoot, targetMapPos);
                }
            }
            isTeleportingMap = false;
            MasterBool.mapateleport = false;
        }
    }

// Auto Teleport Enemy removed

// Flyhack removed

}

void FastFireMaxTimer() {
    if (_GameFacade) {
        void *StaticGameFacade = *(void **) ((uint64_t) _GameFacade + _StaticClass);
        if (StaticGameFacade != nullptr) {
            void *currentGame = *(void **) ((uint64_t) StaticGameFacade + _MatchGame);
            if (currentGame != nullptr) {
                void *timeService = *(void **) ((uintptr_t) currentGame + _GameTimer);
                if (!timeService) return;

                // Priority 1: Fast Fire Max (Rage)

                if (MasterBool.fastfiremax) {
                    if (!SpeedTimerpatch) {
                        *(float *) ((uintptr_t) timeService + _FixedDeltaTime) = 0.20f;
                        SpeedTimerpatch = true;

                    }

                    return;
                }

// Speed Timer removed

                // Reset to Normal if both OFF

                if (SpeedTimerpatch) {
                    *(float *) ((uintptr_t) timeService + _FixedDeltaTime) = 0.033f;
                    SpeedTimerpatch = false;

                }

            }

        }

    }

}

void fastreload()

{
    void *LocalPlayer = Current_Local_Player();
    if (LocalPlayer != nullptr) {
        void *playerattributes = *(void **) ((uint64_t) LocalPlayer + _playerAttributes);
        if (playerattributes != nullptr) {
            if (MasterBool.noreloadfck) {
                *(bool *) ((uintptr_t) playerattributes + offset_NoReload) = true;

            } else {
                *(bool *) ((uintptr_t) playerattributes + offset_NoReload) = false;
            }

        }

    }

}

static bool get_IsCatapultFalling(void* player) { return false; }

static void OnStopCatapultFalling(void* player) { }

bool (*orig_IsVisible)(void *Player);

bool hook_IsVisible(void *Player) {
    return orig_IsVisible(Player);
}

void (*orig_UpdateBehavior)(void *Player, float a, float b) = nullptr;
void hook_UpdateBehavior(void *Player, float a, float b) {
    if (orig_UpdateBehavior) orig_UpdateBehavior(Player, a, b);
    if (!MasterBool.ActivateAll) return;

    if (!Player) return;
    void *localPlayer = Current_Local_Player();
    if (Player == localPlayer && localPlayer != nullptr) {
        if (MasterBool.autoGlider) {
            hilll_gliderbkc(Player);
            TriggerInfiniteGlide(Player);
        }

        DownPlayer::Update();
        DownEnemy::Update();
    }
}

bool (*orig_SpeedBypass)(void* instance);
bool hook_SpeedBypass(void* instance) {
    if (MasterBool.ActivateAll && MasterBool.speedhackjoy) {
        return true;
    }
    return orig_SpeedBypass(instance);
}

bool (*orig_SpeedHack)(void* instance);
bool hook_SpeedHack(void* instance) {
    if (MasterBool.ActivateAll && MasterBool.speedhackjoy) {
        return true;
    }
    return orig_SpeedHack(instance);
}

float(*FIRE_BACKUP)(void* thiz);

float FIRE_HOOK(void* thiz) {
    if (thiz != nullptr )
    {
        if (MasterBool.ActivateAll && MasterBool.fastfuck){
            return 0.1f;
        }
    }
    return FIRE_BACKUP(thiz);
}

float(*SPEED_BACKUP)(void *thiz, int type);

float SPEED_HOOK(void* thiz, int type) {
    if (thiz != nullptr && MasterBool.ActivateAll) {
        if (MasterBool.fastfiremax) {
            return 0.35f;

        } else if (MasterBool.fastfireauto) {
            return 1.7f;
        }

    }

    return SPEED_BACKUP(thiz, type);
}

float(*FIRE_BACKUP_NEW)(void *thiz);
float FIRE_HOOK_NEW(void* thiz) { return FIRE_BACKUP_NEW(thiz); }

#define offset_ShowCreditPopup (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowCreditBehaviorPopupMessage"), 1)

static void ShowCreditPopup(monoString *message) {
    if (!message) return;
    static uintptr_t s_offCredit = 0;
    if (s_offCredit == 0) {
        s_offCredit = (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowCreditBehaviorPopupMessage"), 1);
        if (s_offCredit == 0) {
            s_offCredit = (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowCreditBeahviorPopupMessage"), 1);
        }
    }
    if (s_offCredit == 0) return;
    void (*_Show)(void *, monoString *) = (void (*)(void *, monoString *))(s_offCredit);
    void *ui = CurrentInGameUIScene();
    if (ui) _Show(ui, message);
}

void RajaXModsCreditText() {  
    ShowCreditPopup(U3DStr("Onyx Aimkill | discord.gg/hBGz2wy67T"));
}

static monoString *get_NickName(void* player) {
    if (!player) return nullptr;
    if (_OriginalName != 0 && _OriginalName != (uintptr_t)-1) {
        monoString* name = *(monoString**)((uintptr_t)player + _OriginalName);
        if (name) return name;
    }
    if (_NickName != 0 && _NickName != (uintptr_t)-1) {
        monoString* name = *(monoString**)((uintptr_t)player + _NickName);
        if (name) return name;
    }
    return nullptr;
}

static void AddTeammateHud(void *ui, monoString *nick, monoString *grup) {
    if (!ui || !nick || !grup) return;
    if (m_addTeamHud == 0) return;
    void (*_AddTeammateHud)(void *, monoString *, monoString *) = (void (*)(void *, monoString *, monoString *))m_addTeamHud;
    _AddTeammateHud(ui, nick, grup);
}

void RxmGetNickName(void* targetVivo) {
    if (!MasterBool.ActivateAll) return;
    void *LocalPlayer = Current_Local_Player();
    if (LocalPlayer != nullptr) {
        void* targetEnemy = targetVivo;
        if (targetEnemy != nullptr && !IsDieing(targetEnemy) && GetHp(targetEnemy) > 0) {
            void *ui = CurrentInGameUIScene();
            if (ui != nullptr) {
                Vector3 EnemyHeadPosition = GetHeadPosition(targetEnemy);
                Vector3 LocalPlayerPos = CameraPosition(LocalPlayer);

                float distance = sqrtf(
                    (LocalPlayerPos.X - EnemyHeadPosition.X) * (LocalPlayerPos.X - EnemyHeadPosition.X) +
                    (LocalPlayerPos.Y - EnemyHeadPosition.Y) * (LocalPlayerPos.Y - EnemyHeadPosition.Y) +
                    (LocalPlayerPos.Z - EnemyHeadPosition.Z) * (LocalPlayerPos.Z - EnemyHeadPosition.Z)
                );

                monoString *nick = get_NickName(targetEnemy);
                if (!nick) {
                    nick = (monoString*)U3DStr("Enemy");
                }
                int enemyHp = GetHp(targetEnemy);
                monoString *distances = U3DStrFormat(distance, enemyHp);
                AddTeammateHud(ui, nick, distances);
            }
        }
    }
}

std::chrono::steady_clock::time_point last_update_time = std::chrono::steady_clock::now();
static std::chrono::steady_clock::time_point last_update_time_exploit = std::chrono::steady_clock::now();
GCommon_AnimationRuntimeHandle_o *(*GetCurrentRunningHandler)(GCommon_AnimationSystemComponent_o *Instance,int32_t layerIndex);

GCommon_AnimationRuntimeHandle_o *_GetCurrentRunningHandler(GCommon_AnimationSystemComponent_o *Instance,int32_t layerIndex)

{
    if (!MasterBool.ActivateAll) {
        return GetCurrentRunningHandler(Instance, layerIndex);
    }
    if (Instance != nullptr && layerIndex == 0) {
        std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_update_time).count();
auto elapsed_time_exploit = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_update_time_exploit).count();
        if (elapsed_time_exploit > 17)

        {
            void *LocalPlayer = Current_Local_Player();
            if (LocalPlayer != nullptr) {
                FlyExploitSBG(LocalPlayer);
            }

            last_update_time_exploit = current_time;
        }

        if (elapsed_time > 55) {
            if (MasterBool.fastfireauto) {
                MasterBool.fastfiremax = MasterBool.autoswitch;
            }

            FastFireMaxTimer();

            if (MasterBool.RealAimkillV2 || MasterBool.RealAimkill || MasterBool.Aimkillsend) {
                cachedTarget360 = BestEnemyFind360();
            } else {
                cachedTarget360 = nullptr;
            }

            void *current_match = nullptr;
            void* StaticGameFacade = *(void**)((uint64_t)_GameFacade + _StaticClass);
            if (StaticGameFacade) {
                void *ClassMatchGame = *(void **) ((uint64_t) StaticGameFacade + _MatchGame);
                if (ClassMatchGame) {
                    current_match = *(void **) ((uint64_t) ClassMatchGame + _Match);
                }

            }
            void* prevTarget = cachedTarget;
            cachedTarget = nullptr;
            if (cachedTarget == nullptr) {

                void* bestFovCandidate = BestEnemyFind(nullptr); // Skip locked enemy if they failed tracker

                if (bestFovCandidate != nullptr) {
                    if (SmartEnemyMovementTracker(bestFovCandidate, false)) {
                        cachedTarget = bestFovCandidate;

                    } else if (isVisible_Aimbot(bestFovCandidate)) {
                        cachedTarget = bestFovCandidate;
                    }

                }

            }
            AutoFireLoop();
            if (cachedTarget != nullptr) {
                if (isVisible_Aimbot(cachedTarget) || MasterBool.smartmove || MasterBool.Aimkill) {
                    StartAimKillV2(cachedTarget);
                }

            }

            AESPName();
            AutoRevive();
            FastSwitch();
            SuperFastAutoSwitchLoop1();
            NormalAutoSwitchLoop();
            DownPlayer::Update();
            DownEnemy::Update();

            void *LocalPlayer = Current_Local_Player();
            if (LocalPlayer != nullptr) {
                fastreload();
                ApplyFlyMap(LocalPlayer);
                void* weaponOnHand = GetWeaponOnHand(LocalPlayer);
                void *ClosestEnemyv2 = cachedTarget;
                void *ClosestEnemy360 = cachedTarget360;

                if (weaponOnHand != nullptr) {
                    if (true) {
                        if (ClosestEnemyv2 != nullptr && MasterBool.Aimkill) {
                            if (isEnemyInRangeWeapon(LocalPlayer, ClosestEnemyv2, weaponOnHand)) {
                                StartAimKillV2(ClosestEnemyv2);
                            }

                        }

                        if (MasterBool.Aimkillsend || MasterBool.AimkillBrutal || MasterBool.AimkillBody) {
                            StartAimKillSend(ClosestEnemy360);
                        }
                        if (MasterBool.RealAimkillV2 && ClosestEnemy360 != nullptr) {
                            if (isEnemyInRangeWeapon(LocalPlayer, ClosestEnemy360, weaponOnHand)) {
                                StartRealAimkillV2(ClosestEnemy360);
                            }
                        } else if (MasterBool.RealAimkill && ClosestEnemy360 != nullptr) {
                            if (isEnemyInRangeWeapon(LocalPlayer, ClosestEnemy360, weaponOnHand)) {
                                StartRealAimkill(ClosestEnemy360);
                            }
                        }

                    }

                }

                void *ClosestEnemy = ClosestEnemy360 ? ClosestEnemy360 : ClosestEnemyv2;

                // Credit text and Teammate tips (default ON when ActivateAll is enabled)
                if (MasterBool.ActivateAll) {
                    static float s_lastCreditShowTime = 0.0f;
                    float curTime = get_time();
                    if (curTime - s_lastCreditShowTime >= 2.0f) {
                        s_lastCreditShowTime = curTime;
                        ShowCenterUpTeammateTips(U3DStr("Copyright © WonderLand Store | Developed By onyxontop._"), 3.0f);
                        RajaXModsCreditText();
                    }

                    if (ClosestEnemy != nullptr) {
                        RxmGetNickName(ClosestEnemy);
                    }
                }

                if (MasterBool.Aimkillrotate && ClosestEnemy != nullptr) {
                    auto enemyTransform = Component_get_transform(ClosestEnemy);
                    static float spinAngle = 0.0f;
                    spinAngle += 15.0f;
                    if (spinAngle >= 360.0f) spinAngle = 0.0f;
                    Vector3 centerPos = Transform_INTERNAL_GetPosition(enemyTransform);
                    float radius = 5.0f;
                    Vector3 newPos;
                    newPos.X = centerPos.X + radius * cosf(spinAngle * 3.14159f / 180.0f);
                    newPos.Z = centerPos.Z + radius * sinf(spinAngle * 3.14159f / 180.0f);
                    newPos.Y = centerPos.Y;
                    Transform_set_position(enemyTransform, newPos);
                }
            }
            last_update_time = std::chrono::steady_clock::now();
        }

        return GetCurrentRunningHandler(Instance, layerIndex);

    }

    return GetCurrentRunningHandler(Instance,layerIndex);
}

bool (*NoBUlletTractOriginal)(void* weapon, COW_GamePlay_MADMMIICBNN_o *hitInfo);

bool(*MedikitRun)(bool* instance);

bool _MedikitRun(bool* instance)  {
    return (MasterBool.ActivateAll && MasterBool.medikitrun) ? false : MedikitRun(instance);
}

bool(*DoubleGun)(bool* instance);

bool _DoubleGun(bool* instance){
    return (MasterBool.doublegun) ? true : DoubleGun(instance);
}

bool (*ResetGuest)(bool* instance);

bool _ResetGuest(bool* instance) {
    return (MasterBool.ActivateAll && MasterBool.resetguest) ? true : ResetGuest(instance);
}

typedef int (*CalcRealDamage_fn)(float, void*, void*, void*, void*, int, void*, void*, float, uint32_t);
static CalcRealDamage_fn orig_CalcRealDamage = nullptr;

static int hook_CalcRealDamage(float baseDamage, void* hitPart, void* damageInfo, void* damager, void* beDamager, int weaponDataID, void* damagerWeaponDynamicInfo, void* weapon, float overrideHeadshot, uint32_t flag) {
    int result = orig_CalcRealDamage(baseDamage, hitPart, damageInfo, damager, beDamager, weaponDataID, damagerWeaponDynamicInfo, weapon, overrideHeadshot, flag);
    if (MasterBool.Aimkill && result > 0) {
        int enemyHp = GetHp(beDamager);
        int weaponDamage = (int)baseDamage;
        if (enemyHp > 0 && enemyHp >= 30 && enemyHp <= 100 && weaponDamage > 0 && weaponDamage < 200 && weaponDamage >= enemyHp) {
            int killDamage = ((enemyHp + 9) / 10) * 10;
            if (killDamage < 10)  killDamage = 10;
            if (killDamage > 200) killDamage = 244;
            result = killDamage;

        } else {
            if (result > 200) {
                result = 244;
            }

            else{
                result = 244;
            }

        }

    }

    return result;
}

float (*old_GetCurrentDashSpeed)(void *instance);
float hook_GetCurrentDashSpeed(void *instance) {
    void* localPlayer = Current_Local_Player();
    if (instance != nullptr && instance == localPlayer && MasterBool.speedrun) {
        return 9.0f;
    }
    return old_GetCurrentDashSpeed(instance);
}

void DumpDamagePacket(message_C2S_RUDP_TakeDamage_Req_o2* p) {
    if (!p) return;

    LOGI("==== Damage Packet Dump Start ====");

    LOGI("ALFINFGBOBE: %u", p->ALFINFGBOBE);
    LOGI("ECDBFHHNPMI: %u", p->ECDBFHHNPMI);
    LOGI("EKCONDDBKFO: %u", p->EKCONDDBKFO);
    LOGI("BJBPPEBIPFA: %u", p->BJBPPEBIPFA);
    LOGI("LIIGLCNGOHG: %u", p->LIIGLCNGOHG);
    LOGI("PIAMIOFEBKF: %d", p->PIAMIOFEBKF);
    LOGI("HCMIEJEBKAL: %u", p->HCMIEJEBKAL);
    LOGI("ODCJPCEJHPK: %u", p->ODCJPCEJHPK);
    LOGI("CEDJCPLOLNE: %u", p->CEDJCPLOLNE);

    LOGI("HOBOHHJNDNH: %u", p->HOBOHHJNDNH);
    LOGI("AILHIPMKJKJ: %f", p->AILHIPMKJKJ);
    LOGI("LHGGPCFJNOO: %llu", p->LHGGPCFJNOO);
    LOGI("ACAKHEABPEJ: %d", p->ACAKHEABPEJ);

    LOGI("MJIHLDJNHLF: %d", p->MJIHLDJNHLF);
    LOGI("MBGCAHPACOH: %d", p->MBGCAHPACOH);
    LOGI("IOGIIEFAALP: %f", p->IOGIIEFAALP);
    LOGI("HDEJLJKNLCI: %d", p->HDEJLJKNLCI);

    LOGI("CNEICNJFGLM: %p", p->CNEICNJFGLM);
    LOGI("PGDEDHFOMCN: %p", p->PGDEDHFOMCN);
    LOGI("AALHLOAJLEE (List<float*>): %p", p->AALHLOAJLEE);
    LOGI("FIKOAMIDEHL (List<byte>): %p", p->FIKOAMIDEHL);

    LOGI("==== Damage Packet Dump End ====");
}

void DumpManual_Zone_EnterOrExitPacket(message_C2S_RUDP_Manual_Zone_EnterOrExit_Req_Fields* p) {
    if (!p) return;

    LOGI("==== Manual_Zone_EnterOrExit Packet Dump Start ====");
    LOGI("UserID: %llu", (unsigned long long)p->UserID);
    LOGI("PlayerID: %u", p->PlayerID);
    LOGI("ZoneID: %u", p->ZoneID);
    LOGI("EnterOrExit: %s", p->EnterOrExit ? "ENTER" : "EXIT");
    LOGI("==== Manual_Zone_EnterOrExit Packet Dump End ====");
}

bool (*old_GameFacade_Send)(uint32_t messageID, void *msg, uint8_t sendOption, bool cacheMsgAnyWay) = nullptr;

bool hook_GameFacade_Send(uint32_t messageID, void *msg, uint8_t sendOption, bool cacheMsgAnyWay) {
    LOGI("GameFacade_Send: ID = %u", messageID);
    if (messageID == 106 && msg != nullptr) {
        auto* damagePacket = (message_C2S_RUDP_TakeDamage_Req_o2 *)msg;
        DumpDamagePacket(damagePacket);
    }

    if (messageID == 322 && msg != nullptr) {
        auto* Manual_Zone_EnterOrExit = (message_C2S_RUDP_Manual_Zone_EnterOrExit_Req_Fields *)msg;
        DumpManual_Zone_EnterOrExitPacket(Manual_Zone_EnterOrExit);
    }

    return old_GameFacade_Send(messageID, msg, sendOption, cacheMsgAnyWay);
}

void *pthreadcreate(void *arg) {
    while (true) {
        if (getLibBase(targetLibName) != 0) {
            Il2CppAttach();
            //DobbyHook((void*)getRealOffset(0x4315F54), (void*)New_FFAnti, (void**)&Old_FFAnti);

            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("COW"), OBFUSCATE("GameConfig"),OBFUSCATE("get_ResetGuest"), 0),(void *) _ResetGuest, (void **) &ResetGuest);
            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("GCommon"),OBFUSCATE("AnimationSystemComponent"),OBFUSCATE("GetCurrentRunningHandler"), 1),(void *) _GetCurrentRunningHandler, (void **) &GetCurrentRunningHandler);
            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"),OBFUSCATE("IsMoving"), 0),(void *) _MedikitRun, (void **) &MedikitRun);
            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetCurrentDashSpeed"), 0),(void *)hook_GetCurrentDashSpeed,(void **)&old_GetCurrentDashSpeed);
            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerAttributes"), OBFUSCATE("get_FireIntervalScale"), 0), (void *) FIRE_HOOK, (void **) &FIRE_BACKUP);
            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerAttributes"), OBFUSCATE("GetMultiplyFireIntervalScaleByWeaponType"), 1), (void *) FIRE_HOOK_NEW, (void **) &FIRE_BACKUP_NEW);
            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerAttributes"), OBFUSCATE("GetSpeedScaleBySpeedType"), 1), (void *) SPEED_HOOK, (void **) &SPEED_BACKUP);
            //DobbyHook((void *) offset_GameFacade_Send, (void *) hook_GameFacade_Send, (void **) &old_GameFacade_Send);
            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("UpdateBehavior"), 2), (void *)hook_UpdateBehavior, (void **) &orig_UpdateBehavior);
            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsVisible"), 0), (void *)hook_IsVisible, (void **) &orig_IsVisible);
            // Hooks removed: Gravity, ShowDamageNum, ShowDamage, HighFPS120, HighFPS144
            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("KANJBNIANHC"), OBFUSCATE("MBOHNCMOJDE"), 1), (void *)hook_SpeedBypass, (void **) &orig_SpeedBypass);
            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsFoldWingGliding"), 0), (void *)hook_SpeedHack, (void **) &orig_SpeedHack);

            pthread_exit(0);
        }

        return NULL;
    }

}

// =====================================================================

// ExternalSocketServer - TCP control channel for C# exe

// Listens on port 21405 for simple text commands

// =====================================================================

#include <arpa/inet.h>

#define CONTROL_PORT 21405

class ExternalSocketServer {

private:

    int server_fd;
    int client_fd;
    struct sockaddr_in address;
    socklen_t addrlen;
    bool isConnected;

public:

    ExternalSocketServer() : server_fd(-1), client_fd(-1), isConnected(false) {
        addrlen = sizeof(address);
    }

    ~ExternalSocketServer() { Disconnect(); }

    void Disconnect() {
        if (client_fd >= 0) { close(client_fd); client_fd = -1; }

        if (server_fd >= 0) { close(server_fd); server_fd = -1; }

        isConnected = false;
    }

    bool Create() {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) { LOGI("Control socket creation failed"); return false; }

        return true;
    }

    bool Bind() {
        memset(&address, 0, sizeof(address));
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(CONTROL_PORT);
        int opt = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        if (::bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
            LOGI("Control bind failed: %d", errno);
            return false;
        }

        LOGI("Control socket bound to port %d", CONTROL_PORT);
        return true;
    }

    bool Listen() {
        if (listen(server_fd, 3) < 0) { LOGI("Control listen failed"); return false; }

        LOGI("Listening for C# connections...");
        return true;
    }

    bool Accept() {
        LOGI("Waiting for C# connection...");
        client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (client_fd < 0) { LOGI("Control accept failed: %d", errno); return false; }

        isConnected = true;
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(address.sin_addr), clientIP, INET_ADDRSTRLEN);
        LOGI("C# connected from %s", clientIP);
        return true;
    }

    int receive(void* buffer, size_t length) {
        if (!isConnected) return -1;
        int received = read(client_fd, buffer, length);
        if (received <= 0) { LOGI("Control connection closed"); isConnected = false; }

        return received;
    }

    int send(const void* buffer, size_t length) {
        if (!isConnected) return -1;
        int sent = write(client_fd, buffer, length);
        if (sent <= 0) { LOGI("Control send failed"); isConnected = false; }

        return sent;
    }

    bool IsConnected() const { return isConnected; }

};

ExternalSocketServer controlServer;

int InitExternalServer() {
    if (!controlServer.Create()) return -1;
    if (!controlServer.Bind()) return -1;
    if (!controlServer.Listen()) return -1;
    LOGI("C# control server ready on port %d", CONTROL_PORT);
    return 0;
}

// =====================================================================

// ExternalControlServer thread - text commands from C# exe

// =====================================================================

void* ExternalControlServer(void*) {
    if (InitExternalServer() != 0) {
        LOGI("Failed to init C# control server");
        return nullptr;
    }

    while (true) {
        if (controlServer.Accept()) {
            char buffer[256];

            // Send greeting

            const char* greet = "ONYX_READY";
            controlServer.send((void*)greet, strlen(greet));

            while (true) {
                int bytes = controlServer.receive(buffer, sizeof(buffer) - 1);
                if (bytes <= 0) break;
                buffer[bytes] = '\0';
                LOGI("C# CMD: %s", buffer);

                if (strcmp(buffer, "ENABLE_ALL_ON") == 0) {
                    MasterBool.enableESP = true;
                    LOGI("ENABLE_ALL Enabled");
                }

                else if (strcmp(buffer, "ENABLE_ALL_OFF") == 0) {
                    MasterBool.enableESP = false;
                    LOGI("ENABLE_ALL Disabled");
                }

                else if (strcmp(buffer, "COVER_PULL_ON") == 0) {
                    MasterBool.smartmove = true;
                    LOGI("Cover Pull Enabled");
                }

                else if (strcmp(buffer, "COVER_PULL_OFF") == 0) {
                    MasterBool.smartmove = false;
                    LOGI("Cover Pull Disabled");
                }

                else if (strcmp(buffer, "AUTO_REVIVE_ON") == 0) {
                    MasterBool.autorevive = true;
                    LOGI("Auto Revive Enabled");
                }

                else if (strcmp(buffer, "AUTO_REVIVE_OFF") == 0) {
                    MasterBool.autorevive = false;
                    LOGI("Auto Revive Disabled");
                }

                else if (strcmp(buffer, "AUTOFIRE_ALLGUN_ON") == 0) {
                    MasterBool.autofire = true;
                    MasterBool.noreloadfck = true;
                    LOGI("Autofire Allgun Enabled");
                }

                else if (strcmp(buffer, "AUTOFIRE_ALLGUN_OFF") == 0) {
                    MasterBool.autofire = false;
                    MasterBool.noreloadfck = false;
                    LOGI("Autofire Allgun Disabled");
                }

                else if (strcmp(buffer, "MAP_TELEPORT_ON") == 0) {
                    MasterBool.mapateleport = true;
                    LOGI("Map Teleport Enabled");
                }

                else if (strcmp(buffer, "MAP_TELEPORT_OFF") == 0) {
                    MasterBool.mapateleport = false;
                    LOGI("Map Teleport Disabled");
                }

                else if (strcmp(buffer, "RESET_GUEST_ON") == 0) {
                    MasterBool.resetguest = true;
                    LOGI("Reset Guest Triggered");
                }

                else if (strncmp(buffer, "SET_AIMFOV ", 11) == 0) {
                    float fov = atof(buffer + 11);
                    MasterBool.aimbotFOV = fov;
                    LOGI("Aim FOV Set: %f", fov);
                }

                else if (strcmp(buffer, "SAFE_SILENT_AIM_ON") == 0) {
                    MasterBool.SafeSilentAim = true;
                    LOGI("Safe Silent Aim Enabled");
                }

                else if (strcmp(buffer, "SAFE_SILENT_AIM_OFF") == 0) {
                    MasterBool.SafeSilentAim = false;
                    LOGI("Safe Silent Aim Disabled");
                }

                else {
                    LOGI("Unknown command: %s", buffer);
                }

                // Send ACK

                const char* ack = "OK";
                controlServer.send((void*)ack, strlen(ack));
            }

            LOGI("C# control disconnected");
            controlServer.Disconnect();
        }

    }

    return nullptr;
}
#ifndef STANDALONE_LIB

__attribute__((constructor))

void initializer() {

    pthread_t ptid12;
    pthread_create(&ptid12, nullptr, pthreadcreate, nullptr);

    pthread_t ptid1;
    pthread_create(&ptid1, nullptr, CreateServer, nullptr);

    // Start C# control server thread

    pthread_t ptid_control;
    pthread_create(&ptid_control, nullptr, ExternalControlServer, nullptr);
}

#endif
