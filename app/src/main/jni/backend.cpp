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
#include <cstdlib>
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

    bool SafeAimkill = false;
    bool SafeSilentAim = false;
    bool enableFunctions = false;
    bool flyhack = false;
    bool flyexploit = false;
    bool noDelay = false;

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
    bool downKillMaxVip = false;
    bool RajaXModsFireAimkill = false;
    Vector3 originalPlayerScale;
} MasterBool;

char lockedEnemyName[128] = {0};

static bool SpeedTimerpatch = false;
static bool noDelayPatch = false;
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

void FootBallNew() {}

bool (*orig_CanTakeDamage)(void* _this, void* attacker, void* victim, void* weaponData, const void* method) = nullptr;
bool hook_CanTakeDamage(void* _this, void* attacker, void* victim, void* weaponData, const void* method) {
    if (orig_CanTakeDamage) {
        return orig_CanTakeDamage(_this, attacker, victim, weaponData, method);
    }
    return true;
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

void FlyExploitSBG(void* localPlayer)
{
    if (!localPlayer) return;
    if (!MasterBool.enableFunctions || !MasterBool.flyexploit) return;
    if (!InActiveMatch()) return;

    void *transform = Component_get_transform(localPlayer);
    if (!transform) return;

    Vector3 pos = Transform_INTERNAL_GetPosition(transform);
    pos.Y += 1.0f; // Bay không giới hạn +1.0 mỗi tick (giống noclip)
    Transform_set_position(transform, pos);

    hilll_gliderbkc(localPlayer);
    TriggerInfiniteGlide(localPlayer);
}

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
                        NewEspForUnity31(response);

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

                    }   else if (request.Mode == 5664) {
                        MasterBool.SafeAimkill = request.boolean;
                        MasterBool.RajaXModsFireAimkill = request.boolean;
                        response.Success = true;

                    }   else if (request.Mode == 504) {
                        MasterBool.downKillMaxVip = request.boolean;
                        response.Success = true;

                    }   else if (request.Mode == 9001) {
                        MasterBool.enableFunctions = request.boolean;
                        response.Success = true;

                    }   else if (request.Mode == 5665) {
                        MasterBool.flyexploit = request.boolean;
                        response.Success = true;

                    }   else if (request.Mode == 5666) {
                        // Invisible removed
                        response.Success = true;

                    }   else if (request.Mode == 5667) {
                        MasterBool.noDelay = request.boolean;
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

                    } else if(request.Mode == 504 || request.Mode == 5658 || request.Mode == 5660) {
                        // Down Kill removed
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

bool DownEnemySnap(void *enemy) { return false; }


float TimerTakeDamageinit = 0.0f;

float TimerTakeDamageEnd  = 0.0f; // AGGRESSIVE: instant fire, no cooldown

// Pull enemy into line of sight inside aimkill â€” no player fire button needed

static bool AimkillMethodPull(void* enemy, void** outTf, Vector3* outOriginal) {
    if (!enemy) {
        return false;
    }
    if (!MasterBool.AimkillSendCoverPull) {
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

static const int kSafeMaxPacketsPerEnemy = 15;
static const int kSafeBurstPacketMax = 8;
static const long long kSafeMinPacketGapMs = 20;    // 0.02s — much faster burst
static const long long kSafeMaxPacketGapMs = 80;    // 0.08s — tighter gap
static const long long kSafeBurstResetMs = 2000;

struct SafeAimkillTracker {
    void* trackedEnemy = nullptr;
    int packetsToEnemy = 0;
    int burstPackets = 0;
    long long nextRequiredGapMs = 200;
    std::chrono::steady_clock::time_point lastPacketAt{};
    std::chrono::steady_clock::time_point burstWindowStart{};
};

static SafeAimkillTracker g_safeAimkill;

static long long SafeAimkillNextGapMs() {
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)(get_realtimeSinceStartup() * 1000.0f));
        seeded = true;
    }
    long long span = kSafeMaxPacketGapMs - kSafeMinPacketGapMs;
    if (span < 0) span = 0;
    return kSafeMinPacketGapMs + (rand() % (int)(span + 1));
}

static void SafeAimkillResetBurstWindow(std::chrono::steady_clock::time_point now) {
    g_safeAimkill.burstPackets = 0;
    g_safeAimkill.burstWindowStart = now;
}

static bool SafeAimkillCanSendPacket(void* enemy) {
    if (!enemy) {
        return false;
    }

    auto now = std::chrono::steady_clock::now();

    if (g_safeAimkill.trackedEnemy != enemy) {
        g_safeAimkill.trackedEnemy = enemy;
        g_safeAimkill.packetsToEnemy = 0;
    }

    if (IsDieing(enemy) || GetHp(enemy) <= 0) {
        g_safeAimkill.trackedEnemy = nullptr;
        g_safeAimkill.packetsToEnemy = 0;
        return false;
    }

    if (g_safeAimkill.packetsToEnemy >= kSafeMaxPacketsPerEnemy) {
        return false;
    }

    if (g_safeAimkill.burstWindowStart.time_since_epoch().count() == 0) {
        SafeAimkillResetBurstWindow(now);
    } else {
        long long burstAge = std::chrono::duration_cast<std::chrono::milliseconds>(
                now - g_safeAimkill.burstWindowStart).count();
        if (burstAge >= kSafeBurstResetMs) {
            SafeAimkillResetBurstWindow(now);
        }
    }

    if (g_safeAimkill.burstPackets >= kSafeBurstPacketMax) {
        return false;
    }

    if (g_safeAimkill.lastPacketAt.time_since_epoch().count() != 0) {
        long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                now - g_safeAimkill.lastPacketAt).count();
        if (elapsed < g_safeAimkill.nextRequiredGapMs) {
            return false;
        }
    }

    return true;
}

static void SafeAimkillRecordPacketSent() {
    auto now = std::chrono::steady_clock::now();
    if (g_safeAimkill.burstWindowStart.time_since_epoch().count() == 0) {
        SafeAimkillResetBurstWindow(now);
    }
    g_safeAimkill.packetsToEnemy++;
    g_safeAimkill.burstPackets++;
    g_safeAimkill.lastPacketAt = now;
    g_safeAimkill.nextRequiredGapMs = SafeAimkillNextGapMs();
}

void StartRealAimkill(void* ClosestEnemy) {
    if (!MasterBool.RealAimkill) return;
    if (!ClosestEnemy) return;
    if (IsDieing(ClosestEnemy)) return;
    if (GetHp(ClosestEnemy) <= 0) return;
    if (!InActiveMatch()) return;

    if (MasterBool.SafeAimkill && !SafeAimkillCanSendPacket(ClosestEnemy)) {
        return;
    }
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
        if (MasterBool.SafeAimkill) {
            SafeAimkillRecordPacketSent();
        }
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

    if (MasterBool.SafeAimkill && !SafeAimkillCanSendPacket(target)) {
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

    if (MasterBool.SafeAimkill) {
        SafeAimkillRecordPacketSent();
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

    // Ultra-smooth zero-overhead cadence (75ms = ~13 shots/s, lightning fast lethality, 0 FPS drops)
    static auto s_lastAimkillSendTime = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    long long elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - s_lastAimkillSendTime).count();
    if (elapsedMs < 75) {
        g_inAimkillSend = false;
        return;
    }
    s_lastAimkillSendTime = now;

    void *localPlayer = Current_Local_Player();
    if (!localPlayer || IsDieing(localPlayer) || GetHp(localPlayer) <= 0) { g_inAimkillSend = false; return; }

    void *weaponOnHand = GetWeaponOnHand(localPlayer);
    if (!weaponOnHand) { g_inAimkillSend = false; return; }

    void* current_match = Current_Match();
    if (!current_match) { g_inAimkillSend = false; return; }

    if (!ResolveWeaponFireFn() || !original_WeaponFire) { g_inAimkillSend = false; return; }

    void *hitObjectInfo = *(void **)((uintptr_t)localPlayer + _HitObjectInfoWp);
    if (!hitObjectInfo) { g_inAimkillSend = false; return; }

    COW_GamePlay_MADMMIICBNN_o *hitInfo = (COW_GamePlay_MADMMIICBNN_o *)hitObjectInfo;
    if (!hitInfo) { g_inAimkillSend = false; return; }

    // Fast candidate gathering: limit to at most 2 closest valid enemies within combat range (180m)
    std::vector<void*> targetsToProcess;

    if (ClosestEnemy && !IsDieing(ClosestEnemy) && GetHp(ClosestEnemy) > 0 && !IsLocalTeammate(ClosestEnemy)) {
        targetsToProcess.push_back(ClosestEnemy);
    }

    if (targetsToProcess.size() < 2) {
        auto players = GetEntities(current_match);
        Vector3 firePos = GetHeadPosition(localPlayer);

        void* secondBest = nullptr;
        float secondBestDistSq = 180.0f * 180.0f; // Ignore enemies further than 180m!

        for (auto p : players) {
            if (!p || p == localPlayer || p == ClosestEnemy || IsDieing(p) || GetHp(p) <= 0 || IsLocalTeammate(p)) continue;

            void *HeadTF = TransformNode(*(void **) ((uint64_t) p + _HeadTF));
            if (!HeadTF) continue;

            Vector3 headPos = Transform_INTERNAL_GetPosition(HeadTF);
            float dx = headPos.X - firePos.X;
            float dy = headPos.Y - firePos.Y;
            float dz = headPos.Z - firePos.Z;
            float distSq = dx * dx + dy * dy + dz * dz;

            if (distSq < secondBestDistSq) {
                secondBestDistSq = distSq;
                secondBest = p;
            }
        }

        if (secondBest) {
            targetsToProcess.push_back(secondBest);
        }
    }

    if (targetsToProcess.empty()) { g_inAimkillSend = false; return; }

    // Bypass reload lock so ammo does not drop and AWM/Sniper animation lock is skipped
    void *playerattributes = *(void **) ((uint64_t) localPlayer + _playerAttributes);
    if (playerattributes != nullptr) {
        *(bool *) ((uintptr_t) playerattributes + offset_NoReload) = true;
    }

    int processedTargets = 0;
    int candidatesTested = 0;

    for (auto target : targetsToProcess) {
        if (processedTargets >= 2) break; // Multi-target squad swipe: hit up to 2 targets in 1 tick
        if (++candidatesTested > 2) break; // Never test more than 2 candidates (guarantees 0 lag)
        if (!target || target == localPlayer || IsDieing(target) || GetHp(target) <= 0 || IsLocalTeammate(target)) continue;

        if (MasterBool.SafeAimkill && !SafeAimkillCanSendPacket(target)) {
            continue;
        }

        void* enemyTf = nullptr;
        Vector3 originalPos = {0, 0, 0};
        bool wasPulled = false;
        bool visible = isVisible_Aimbot(target);

        // For 100% REAL damage without wall obstruction or distance falloff:
        // Pull target to point-blank (1.5m) during hit calculation and restore immediately
        wasPulled = AimkillMethodPull(target, &enemyTf, &originalPos);
        if (wasPulled) {
            dist = 1.5f;
        }

        Vector3 curFirePos = GetHeadPosition(localPlayer);
        Vector3 hitPos = MasterBool.AimkillBody ? GetBodyPosition(target) : GetHeadPosition(target);

        float dx = hitPos.X - curFirePos.X;
        float dy = hitPos.Y - curFirePos.Y;
        float dz = hitPos.Z - curFirePos.Z;
        float distReal = sqrtf(dx * dx + dy * dy + dz * dz);
        Vector3 direction = {0, 0, 0};
        if (distReal > 0.0001f) {
            float inv = 1.0f / distReal;
            direction.X = dx * inv;
            direction.Y = dy * inv;
            direction.Z = dz * inv;
        } else {
            direction.Z = 1.0f;
        }

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

        int baseDmg = GetDamage(weaponOnHand);
        if (baseDmg <= 0 || baseDmg < 100) {
            baseDmg = MasterBool.AimkillBody ? 180 : 350;
        }

        FillHitInfoDirectly(hitInfo, targetCollider, hitPos, curFirePos, direction, dist, baseDmg);

        GKHECDLGAJA(localPlayer, hitObjectInfo);

        if (!IsFiringPlayer(localPlayer)) {
            StartFiring(localPlayer, weaponOnHand);
        }

        GKHECDLGAJA(localPlayer, hitObjectInfo);

        if (target && !IsDieing(target) && GetHp(target) > 0 && weaponOnHand && hitInfo) {
            if (NoBUlletTractOriginal) {
                NoBUlletTractOriginal(weaponOnHand, hitInfo);
            }
            if (ResolveWeaponFireFn() && original_WeaponFire) {
                original_WeaponFire(weaponOnHand, hitInfo);
            }
            if (MasterBool.SafeAimkill) {
                SafeAimkillRecordPacketSent();
            }
        }

        if (wasPulled && enemyTf && target) {
            AimkillMethodRestore(target, enemyTf, originalPos);
        }

        StopFire(localPlayer, weaponOnHand);

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
    void* bestEnemy = nullptr;
    float minDistance = 180.0f; // Target closest active threat within 180m

    for (auto player: players) {
        if (!player || player == LocalPlayer) continue;
        if (IsDieing(player) || IsLocalTeammate(player) || GetHp(player) <= 0) continue;
        void *HeadTF = TransformNode(*(void**)((uint64_t)player + _HeadTF));
        if (!HeadTF) continue;
        Vector3 enemyPos = Transform_INTERNAL_GetPosition(HeadTF);
        float distance = Vector3Distance(LocalPos, enemyPos);
        if (distance < minDistance) {
            minDistance = distance;
            bestEnemy = player;
        }
    }

    return bestEnemy;
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
    void Update() {}
}

namespace DownEnemy {
    void Update() {}
}

// ======================================================================
//  DOWN KILL MAX VIP
//  - Local:   -2.5m (lock, save/restore 0-delay khi OFF)
//  - Enemies: -2.8m (tất cả enemy, lọc teammate/chết/knocked)
//  - Smooth LERP (không giật / cực mượt) — Lerp 22%
//  - OFF: restore NGAY LẬP TỨC (0 delay), clear state bộ nhớ
// ======================================================================
static const float kDownVip_EnemyY    = -2.8f;
static const float kDownVip_LocalY    = -2.5f;
static const float kDownVip_LerpDown  =  0.22f;

struct DKV_EnemyState { void* ptr; Vector3 save; Vector3 cur; bool alive; };
struct DKV_LocalState { bool prev;    Vector3 save; Vector3 cur; };

static std::map<void*, DKV_EnemyState> g_dkvEnemies;
static DKV_LocalState                   g_dkvLocal = { false, Vector3::Zero(), Vector3::Zero() };

static inline float   dkv_clamp01(float v)               { return v<0?0: v>1?1:v; }
static inline Vector3 dkv_lerp(const Vector3& a, const Vector3& b, float t) {
    t = dkv_clamp01(t);
    return Vector3(a.X+(b.X-a.X)*t, a.Y+(b.Y-a.Y)*t, a.Z+(b.Z-a.Z)*t);
}

void DownKillMaxVip(void* closestHint = nullptr)
{
    if (!InActiveMatch()) {
        g_dkvEnemies.clear();
        g_dkvLocal = {false, Vector3::Zero(), Vector3::Zero()};
        return;
    }

    const bool on = MasterBool.enableFunctions && MasterBool.downKillMaxVip;

    if (!on && !g_dkvLocal.prev && g_dkvEnemies.empty()) return;

    void* local = Current_Local_Player(); if (!local) return;
    void* ltf   = Component_get_transform(local); if (!ltf) return;

    // ===== LOCAL =====
    {
        Vector3 L = Transform_INTERNAL_GetPosition(ltf);
        if (on && !g_dkvLocal.prev) { g_dkvLocal.save = L; g_dkvLocal.cur = L; }
        if (!on &&  g_dkvLocal.prev) {
            Transform_set_position(ltf, g_dkvLocal.save);
            g_dkvLocal = {false, Vector3::Zero(), Vector3::Zero()};
        } else if (on) {
            Vector3 tgt = Vector3(L.X, g_dkvLocal.save.Y + kDownVip_LocalY, L.Z);
            g_dkvLocal.cur = dkv_lerp(g_dkvLocal.cur, tgt, kDownVip_LerpDown);
            g_dkvLocal.cur.X = L.X;
            g_dkvLocal.cur.Z = L.Z;
            Transform_set_position(ltf, g_dkvLocal.cur);
            g_dkvLocal.prev = true;
        } else {
            g_dkvLocal.prev = false;
        }
    }

    // ===== ALL ENEMIES =====
    {
        void* match = Current_Match();
        if (!match) return;

        std::vector<void*> arr = GetEntities(match);
        if (arr.empty() && closestHint) {
            arr.push_back(closestHint);
        }

        if (on) {
            for (auto& kv : g_dkvEnemies) kv.second.alive = false;

            for (void* e : arr) {
                if (!e || e == local)                         continue;
                if (IsDieing(e) || GetHp(e) <= 0)             continue;
                if (IsLocalTeammate(e))                       continue;
                void* tf = Component_get_transform(e);        if (!tf) continue;
                Vector3 P  = Transform_INTERNAL_GetPosition(tf);

                auto it = g_dkvEnemies.find(e);
                if (it == g_dkvEnemies.end()) {
                    DKV_EnemyState s{e, P, P, true};
                    g_dkvEnemies[e] = s;
                    it = g_dkvEnemies.find(e);
                } else it->second.alive = true;
                DKV_EnemyState& st = it->second;

                if (st.save.X==0 && st.save.Y==0 && st.save.Z==0) { st.save=P; st.cur=P; }
                Vector3 tgt = Vector3(st.save.X, st.save.Y + kDownVip_EnemyY, st.save.Z);

                float dxz = (P.X-st.save.X)*(P.X-st.save.X) + (P.Z-st.save.Z)*(P.Z-st.save.Z);
                if (dxz > 0.09f) {
                    st.save.X = P.X; st.save.Z = P.Z;
                    st.cur .X = P.X; st.cur .Z = P.Z;
                    tgt.X = P.X;      tgt.Z = P.Z;
                }
                st.cur = dkv_lerp(st.cur, tgt, kDownVip_LerpDown);
                Transform_set_position(tf, st.cur);
            }

            // Clean up enemies that died or left
            for (auto it = g_dkvEnemies.begin(); it != g_dkvEnemies.end(); ) {
                if (!it->second.alive) {
                    it = g_dkvEnemies.erase(it);
                } else {
                    ++it;
                }
            }
        } else {
            // Restore when turned OFF: only restore if entity is still present in current arr
            if (!g_dkvEnemies.empty()) {
                for (auto& kv : g_dkvEnemies) {
                    DKV_EnemyState& s = kv.second;
                    bool exists = false;
                    for (void* a : arr) {
                        if (a == s.ptr) { exists = true; break; }
                    }
                    if (exists && (s.save.X!=0 || s.save.Y!=0 || s.save.Z!=0)) {
                        void* tf = Component_get_transform(s.ptr);
                        if (tf) Transform_set_position(tf, s.save);
                    }
                }
                g_dkvEnemies.clear();
            }
        }
    }
}

// ======================================================================
//  RajaXMods Safe Aimkill Integration
// ======================================================================
namespace RajaXMods {
    inline uintptr_t Il2CppGetMethodOffset(const char* a, const char* b, const char* c, const char* d, int e) {
        return (uintptr_t)::Il2CppGetMethodOffset(a, b, c, d, e);
    }
    inline uintptr_t Il2CppGetFieldOffset(const char* a, const char* b, const char* c, const char* d) {
        return (uintptr_t)::Il2CppGetFieldOffset(a, b, c, d);
    }
    inline void* Il2CppCreateClassInstance(const char* a, const char* b, const char* c) {
        return ::Il2CppCreateClassInstance(a, b, c);
    }
}

static inline uintptr_t getRealOffsetSafe(uintptr_t addr) {
    if (addr > 0x10000000) return addr;
    return (uintptr_t)getRealOffset((DWORD)addr);
}
#define getRealOffset getRealOffsetSafe

static struct pAddress_s {
    inline uintptr_t GameFacade_Send() {
        return (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("Send"), 4);
    }
    inline uintptr_t ExecuteFireWeapon() {
        return (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("NLCOIOLCGLM"), OBFUSCATE("LADPODDMGFI"), 0);
    }
    inline uintptr_t StartFiring() {
        return (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("StartFiring"), 1);
    }
    inline uintptr_t StartWholeBodyFiring() {
        return (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("StartWholeBodyFiring"), 1);
    }
    inline uintptr_t StopFire() {
        return (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("StopFire"), 1);
    }
    inline uintptr_t HeadTF() {
        uintptr_t off = (uintptr_t)Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("PEMOFNFCLFB"));
        return off ? off : _HeadTF;
    }
    uintptr_t AcessClass = _StaticClass;
} pAddress;

#define uniqueid (uintptr_t) RajaXMods::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("LGMNCCAPNHJ"), OBFUSCATE("DEGODFCOKGC"))
#define GetUniqueID(WeaponHand) (*(uint32_t*)((uint64_t)WeaponHand + (uniqueid ? uniqueid : 0x18)))

#define offset_SyncSwapWeapon (uintptr_t) RajaXMods::Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JDIHDLDIMCK"))
#define offset_BHGGAEEHJCO_s (uintptr_t) RajaXMods::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JDIHDLDIMCK"), OBFUSCATE("BHGGAEEHJCO"))
#define offset_DGLCOGJJFMI_s (uintptr_t) RajaXMods::Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JDIHDLDIMCK"), OBFUSCATE("DBPPPOBFJNP"))

static void Syns_SwapWeapon(void *LocalPlayer, void *WeaponOnHand) {
    if (LocalPlayer == nullptr || WeaponOnHand == nullptr) return;
    void *RUDP_CHANGE_INVENTORY_ON_HAND = (void*)offset_SyncSwapWeapon;
    if (RUDP_CHANGE_INVENTORY_ON_HAND) {
        *(uint32_t * )((uint64_t) RUDP_CHANGE_INVENTORY_ON_HAND + offset_BHGGAEEHJCO_s) = CFFPIACECIG(GetplayerID(LocalPlayer));
        *(uint32_t * )((uint64_t) RUDP_CHANGE_INVENTORY_ON_HAND + offset_DGLCOGJJFMI_s) = GetUniqueID(WeaponOnHand);
        GameFacade_Send(108, RUDP_CHANGE_INVENTORY_ON_HAND, 2, 0);
    }
}

static int ExecuteFireWeapon(void* weaponComp)
{
    if (!weaponComp) return 0;

    int (*_FireFunc)(void*) = (int (*)(void*))getRealOffset(pAddress.ExecuteFireWeapon());
    if (_FireFunc) return _FireFunc(weaponComp);
    return 0;
}

#define gamefacadeclass (void*)_GameFacade

void RajaXModsFireAimkill(void* TargetEntity) {
    if (!MasterBool.enableFunctions) return;
    if (!MasterBool.RajaXModsFireAimkill && !MasterBool.SafeAimkill) return;
    if (!TargetEntity) return;

    void *LocalPlayer = Current_Local_Player();
    if (!LocalPlayer || LocalPlayer == TargetEntity) return;
    if (IsDieing(LocalPlayer)) return;

    void *GameFacade = gamefacadeclass;
    if (GameFacade != nullptr) {
        void *MatchGame = *(void **) ((uint64_t) GameFacade + pAddress.AcessClass);
        if (MatchGame != nullptr) {
            void *currentGame = *(void **) ((uint64_t) MatchGame + _MatchGame);
            if (!currentGame) currentGame = *(void **) ((uint64_t) MatchGame);
            if (currentGame != nullptr) {

                void *CurrentWeapon = GetWeaponOnHand(LocalPlayer);
                if (!CurrentWeapon) return;

                Syns_SwapWeapon(LocalPlayer , CurrentWeapon);

                void *WeaponComponent = *(void **) ((uint64_t) CurrentWeapon + 0x58);
                if (!WeaponComponent) return;

                void *WeaponState = *(void **) ((uint64_t) CurrentWeapon + 0x60);
                if (!WeaponState) return;

                auto startFiringFn = (void (*)(void *, void *)) (void *) getRealOffset(pAddress.StartFiring());
                if (startFiringFn) startFiringFn(LocalPlayer, CurrentWeapon);

                auto startWholeBodyFn = (void (*)(void *, void *)) (void *) getRealOffset(pAddress.StartWholeBodyFiring());
                if (startWholeBodyFn) startWholeBodyFn(LocalPlayer, CurrentWeapon);

                ExecuteFireWeapon(WeaponComponent);

                auto stopFireFn = (void (*)(void *, void *)) (void *) getRealOffset(pAddress.StopFire());
                if (stopFireFn) stopFireFn(LocalPlayer, CurrentWeapon);
            }
        }
    }
}

static inline void* RajaGetTarget() {
    if (cachedTarget && !IsDieing(cachedTarget) && GetHp(cachedTarget) > 0) return cachedTarget;
    if (cachedTarget360 && !IsDieing(cachedTarget360) && GetHp(cachedTarget360) > 0) return cachedTarget360;
    return BestEnemyFind(nullptr);
}

int (*Rxm_BulletTrack)(void *, void* HitObjectInfo) = nullptr;

int Rxm_NoBullet(void *ist, void* HitObjectInfo){

    if (MasterBool.enableFunctions && (MasterBool.RajaXModsFireAimkill || MasterBool.SafeAimkill)) {
        auto *closestEnemy = RajaGetTarget();
        if (closestEnemy != NULL && HitObjectInfo != NULL) {

            void* local_player = Current_Local_Player();
            if (local_player != NULL) {
                void *weaponOnHand = GetWeaponOnHand(local_player);
                if (weaponOnHand != nullptr) {
                    if (isVisible_Aimbot(closestEnemy) || true) {

                        void *HeadTF = TransformNode(
                                *(void **)((uint64_t)closestEnemy + pAddress.HeadTF()));
                        Vector3 enemyHeadPosition = HeadTF ? Transform_INTERNAL_GetPosition(HeadTF) : GetHeadPosition(closestEnemy);

                        void *HeadTF1 = TransformNode(
                                *(void **)((uint64_t)local_player + pAddress.HeadTF()));
                        Vector3 PlayerLocation = HeadTF1 ? Transform_INTERNAL_GetPosition(HeadTF1) : GetHeadPosition(local_player);

                        void* headCol = get_HeadCollider(closestEnemy);
                        if (headCol) {
                            *(void **)((uint64_t)HitObjectInfo + 0xC) = get_gameObject(headCol);
                            *(void **)((uint64_t)HitObjectInfo + 0x10) = headCol;
                            *(Vector3 *)((uint64_t)HitObjectInfo + 0x14) = enemyHeadPosition;
                            *(Vector3 *)((uint64_t)HitObjectInfo + 0x20) = enemyHeadPosition;
                            *(Vector3 *)((uint64_t)HitObjectInfo + 0x2C) = Vector3::Normalized(enemyHeadPosition - PlayerLocation);
                            *(Vector3 *)((uint64_t)HitObjectInfo + 0x38) = PlayerLocation;
                            *(Vector3 *)((uint64_t)HitObjectInfo + 0x5C) = PlayerLocation;
                            *(int *)((uint64_t)HitObjectInfo + 0x68) = 0;
                            *(bool *)((uint64_t)HitObjectInfo + 0x58) = false;
                        }
                    }
                }
            }
        }
    }

    if (Rxm_BulletTrack) {
        return Rxm_BulletTrack(ist, HitObjectInfo);
    }
    return 0;
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

// ======================================================================
//  FastFireMaxTimer()
//  - 2 mode trong 1 hàm, dùng chung logic (vì đều patch _FixedDeltaTime)
//  - Priority 1: Fast Fire Max (fastfiremax)   → Δ = 0.20  (bắn cực nhanh, 3x tick bắn/giây)
//  - Priority 2: Speed Timer / No Delay (noDelay) → Δ = 0.065 (1.5x simulation, 50% nhanh hơn thường)
//  - Off cả 2: restore về 0.033 (30 tick/giây, giá trị game gốc)
//  - Flag SpeedTimerpatch / noDelayPatch để CHỈ PATCH KHI CẦN THAY ĐỔI  (tránh crash)
// ======================================================================
void FastFireMaxTimer() {
    if (!MasterBool.fastfiremax && !MasterBool.noDelay && !SpeedTimerpatch && !noDelayPatch) return;
    if (!InActiveMatch()) return;

    if (!_GameFacade) return;
    void *StaticGameFacade = *(void **) ((uint64_t) _GameFacade + _StaticClass);
    if (!StaticGameFacade) return;

    void *currentGame = *(void **) ((uint64_t) StaticGameFacade + _MatchGame);
    if (!currentGame) return;

    static uintptr_t s_offSimulationTimer = 0;
    static uintptr_t s_offFixedDeltaTime = 0;
    static bool s_checkedTimer = false;
    if (!s_checkedTimer) {
        s_offSimulationTimer = (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("MatchGame"), OBFUSCATE("m_SimulationTimer"));
        if (s_offSimulationTimer == 0) {
            s_offSimulationTimer = (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("COWGameBase"), OBFUSCATE("m_SimulationTimer"));
        }
        s_offFixedDeltaTime = (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("TimeService"), OBFUSCATE("m_FixedDeltaTime"));
        s_checkedTimer = true;
    }

    if (s_offSimulationTimer == 0 || s_offFixedDeltaTime == 0) return;

    void *timeService = *(void **) ((uintptr_t) currentGame + s_offSimulationTimer);
    if (!timeService) return;

    // ===== Priority 1: Fast Fire Max (Rage mode) =====
    if (MasterBool.fastfiremax) {
        if (!SpeedTimerpatch) {
            *(float *) ((uintptr_t) timeService + s_offFixedDeltaTime) = 0.20f;
            SpeedTimerpatch = true;
            noDelayPatch    = false;
        }
        return;
    }

    // ===== Priority 2: SPEED TIMER (No Delay) =====
    if (MasterBool.noDelay) {
        if (!noDelayPatch) {
            *(float *) ((uintptr_t) timeService + s_offFixedDeltaTime) = 0.065f;
            noDelayPatch     = true;
            SpeedTimerpatch  = false;
        }
        return;
    }

    // ===== Khôi phục mặc định khi tắt cả 2 =====
    if (SpeedTimerpatch || noDelayPatch) {
        *(float *) ((uintptr_t) timeService + s_offFixedDeltaTime) = 0.033f;
        SpeedTimerpatch = false;
        noDelayPatch    = false;
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
    return orig_IsVisible ? orig_IsVisible(Player) : true;
}

void (*orig_UpdateBehavior)(void *Player, float a, float b) = nullptr;
void hook_UpdateBehavior(void *Player, float a, float b) {
    if (orig_UpdateBehavior) orig_UpdateBehavior(Player, a, b);

    if (!Player) return;
    if (!InActiveMatch()) return;

    void *localPlayer = Current_Local_Player();
    if (Player == localPlayer && localPlayer != nullptr) {
        if (!MasterBool.enableFunctions) {
            if (g_dkvLocal.prev || !g_dkvEnemies.empty()) {
                DownKillMaxVip();
            }
            return;
        }

        if (MasterBool.autoGlider) {
            hilll_gliderbkc(Player);
            TriggerInfiniteGlide(Player);
        }

        if (MasterBool.flyexploit) {
            FlyExploitSBG(localPlayer);
        }

        if (MasterBool.downKillMaxVip || g_dkvLocal.prev || !g_dkvEnemies.empty()) {
            DownKillMaxVip();
        }
    }
}

bool (*orig_SpeedBypass)(void* instance);
bool hook_SpeedBypass(void* instance) {
    if (MasterBool.enableFunctions && MasterBool.speedhackjoy) {
        return true;
    }
    return orig_SpeedBypass(instance);
}

bool (*orig_SpeedHack)(void* instance);
bool hook_SpeedHack(void* instance) {
    if (MasterBool.enableFunctions && MasterBool.speedhackjoy) {
        return true;
    }
    return orig_SpeedHack(instance);
}

float(*FIRE_BACKUP)(void* thiz);

float FIRE_HOOK(void* thiz) {
    if (thiz != nullptr && MasterBool.enableFunctions)
    {
        if (MasterBool.fastfuck){
            return 0.1f;
        }
    }
    return FIRE_BACKUP(thiz);
}

float(*SPEED_BACKUP)(void *thiz, int type);

float SPEED_HOOK(void* thiz, int type) {
    if (thiz != nullptr && MasterBool.enableFunctions) {
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

static void ShowCreditPopup(monoString *message) {}

void RajaXModsCreditText() {}

static monoString *get_NickName(void* player) { return nullptr; }

static void AddTeammateHud(void *ui, monoString *nick, monoString *grup) {}

void RxmGetNickName(void* targetVivo) {}

std::chrono::steady_clock::time_point last_update_time = std::chrono::steady_clock::now();
GCommon_AnimationRuntimeHandle_o *(*GetCurrentRunningHandler)(GCommon_AnimationSystemComponent_o *Instance,int32_t layerIndex);

GCommon_AnimationRuntimeHandle_o *_GetCurrentRunningHandler(GCommon_AnimationSystemComponent_o *Instance,int32_t layerIndex)

{
    if (Instance != nullptr && layerIndex == 0) {
        if (!MasterBool.enableFunctions) {
            return GetCurrentRunningHandler(Instance, layerIndex);
        }
        std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_update_time).count();
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
    return (MasterBool.enableFunctions && MasterBool.medikitrun) ? false : MedikitRun(instance);
}

bool(*DoubleGun)(bool* instance);

bool _DoubleGun(bool* instance){
    return (MasterBool.enableFunctions && MasterBool.doublegun) ? true : DoubleGun(instance);
}

bool (*ResetGuest)(bool* instance);

bool _ResetGuest(bool* instance) {
    return (MasterBool.enableFunctions && MasterBool.resetguest) ? true : ResetGuest(instance);
}

typedef int (*CalcRealDamage_fn)(float, void*, void*, void*, void*, int, void*, void*, float, uint32_t);
static CalcRealDamage_fn orig_CalcRealDamage = nullptr;

static int hook_CalcRealDamage(float baseDamage, void* hitPart, void* damageInfo, void* damager, void* beDamager, int weaponDataID, void* damagerWeaponDynamicInfo, void* weapon, float overrideHeadshot, uint32_t flag) {
    int result = orig_CalcRealDamage(baseDamage, hitPart, damageInfo, damager, beDamager, weaponDataID, damagerWeaponDynamicInfo, weapon, overrideHeadshot, flag);
    if (MasterBool.enableFunctions && (MasterBool.Aimkill || MasterBool.Aimkillsend || MasterBool.RealAimkillV2 || MasterBool.RealAimkill || MasterBool.SafeAimkill || MasterBool.RajaXModsFireAimkill) && result > 0) {
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
    if (MasterBool.enableFunctions && instance != nullptr && instance == localPlayer && MasterBool.speedrun) {
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

static void SafeHook(void *target, void *replace, void **backup) {
    if (target != nullptr && target != (void*)-1) {
        DobbyHook(target, replace, backup);
    }
}

void *pthreadcreate(void *arg) {
    while (true) {
        if (getLibBase(targetLibName) != 0) {
            Il2CppAttach();

            SafeHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("COW"), OBFUSCATE("GameConfig"),OBFUSCATE("get_ResetGuest"), 0),(void *) _ResetGuest, (void **) &ResetGuest);
            SafeHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("GCommon"),OBFUSCATE("AnimationSystemComponent"),OBFUSCATE("GetCurrentRunningHandler"), 1),(void *) _GetCurrentRunningHandler, (void **) &GetCurrentRunningHandler);
            SafeHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"),OBFUSCATE("IsMoving"), 0),(void *) _MedikitRun, (void **) &MedikitRun);
            SafeHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetCurrentDashSpeed"), 0),(void *)hook_GetCurrentDashSpeed,(void **)&old_GetCurrentDashSpeed);
            SafeHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerAttributes"), OBFUSCATE("get_FireIntervalScale"), 0), (void *) FIRE_HOOK, (void **) &FIRE_BACKUP);
            SafeHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerAttributes"), OBFUSCATE("GetMultiplyFireIntervalScaleByWeaponType"), 1), (void *) FIRE_HOOK_NEW, (void **) &FIRE_BACKUP_NEW);
            SafeHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerAttributes"), OBFUSCATE("GetSpeedScaleBySpeedType"), 1), (void *) SPEED_HOOK, (void **) &SPEED_BACKUP);
            SafeHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("UpdateBehavior"), 2), (void *)hook_UpdateBehavior, (void **) &orig_UpdateBehavior);
            SafeHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsVisible"), 0), (void *)hook_IsVisible, (void **) &orig_IsVisible);
            SafeHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("KANJBNIANHC"), OBFUSCATE("MBOHNCMOJDE"), 1), (void *)hook_SpeedBypass, (void **) &orig_SpeedBypass);
            SafeHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsFoldWingGliding"), 0), (void *)hook_SpeedHack, (void **) &orig_SpeedHack);

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
