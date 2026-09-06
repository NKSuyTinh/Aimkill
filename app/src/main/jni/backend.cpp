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



// Forward declaration to fix build error

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

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "TX999", __VA_ARGS__)

#define PORT 7777

#pragma once



struct FlyHack {

    int Fly = 0;

    float HaruX = 0.0f;

    int FlySpeed = 0;

    float HaruY = 0.0f;

    float HaruZ = 0.0f;

    Vector3 MountCam;

} flysaved;



struct {

    bool autoswitch = false;

    bool autoswitchsafe = false;

    bool teledifender = false;

    bool Aimkilltpv2 = false;

    bool ghoston = false;

    bool flyhack = false;

    bool flyhackop = false;

    bool mapateleport = false;

    bool Aimkillrotate = false;

    bool Aimkilltp = false;

    bool autofire = false;

    bool downplayer = false;

    bool downaimkill = false;

    bool spoofname = false;

    bool flyinit = false;

    bool godweapon = false;

    bool Aimkill = false;

    bool Aimkill360 = false;

    bool aimbotbody = false;

    bool ultraswitch = false;

    float aimbotFOV = 1000.0f;

    bool enableESP = false;

    bool nickfuck = true;

    bool speedrun = false;

    bool highjump = false;

    bool doublegun = false;

    bool speedHack = false;

    bool autojump = false;

    bool downkillv2 = false;

    bool flyexploit = false;

    bool ghostHack = false;

    bool resetguest = false;

    bool wallHack = false;

    bool medikitrun = false;

    bool autoteleport = false;

    bool telehack = false;

    bool aimbody = false;

    bool fastswitch = false;

    bool NoBulletTracking = false;

    bool PullEnemyV2Enabled = false;

    bool autorevive = false;

    bool autoexecute = false;

    bool smartmove = false;

    bool Aimkillsend = false;

    bool AimkillBrutal = false;

    bool AimkillBody = false;

    bool AimkillSendAutoSwitch = false;

    bool AimkillSendCoverPull = false;

    bool SafeAimkill = false;

    bool RealAimkill = false;

    bool RealAimkillV2 = false;

    bool TargetAll = false;

    bool fastfiremax = false;

    bool fastfireauto = false;

    bool noreloadfck = false;

    bool fastfuck = false;

    bool snapfly = false;

    bool autofireslow = false;

    bool noDelay = false;

    bool fucked = false;

    bool fireScaleHack = false;

    bool SafeSilentAim = false;

    bool targetLock = false;

    bool autoSwitchEnabled = false;

    int FlyUp = 0;

    float FlySpeed = 0.0f;

    bool ExampleFeature = false;

    float ExampleValue = 0.0f;

    bool hidedamage = false;

    bool burstFire = false;

    bool highfps = false;

    bool speedhackjoy = false;

    bool football = false;

    bool autoGlider = false;

    bool noDamage = false;

    bool ActivateAll = true;

    bool flyx40 = false;

    bool flyX80 = false;

    bool infinityFly = false;

    Vector3 originalPlayerScale;

} MasterBool;



void* lockedEnemy = nullptr;

char lockedEnemyName[128] = {0};

bool wasLockedEnemyDown = false;

static bool g_inAimkillSend = false;



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

};



struct Response {

    bool Success;

    int PlayerCount;

    PlayerData Players[maxplayerCount];

    int matchAlive;           // 1 = in match, 0 = not

    int remainingTimeSeconds; // 190..0 when in match, -1 when not

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





void ghoston();
void ghostoff();

void SetFootballState(void* player) {
    void* (*getter)(void*) = (void* (*)(void*))offset_PhysXData;
    if (!getter) return;
    void *physXData = getter(player);
    if (!physXData) return;
    *(int *)((uintptr_t)physXData + 0xc) = 8;
}

bool (*orig_TakeDamage)(void* pthis, void* avatar, void* local, void* WeaponData, const void* method) = nullptr;

bool hook_TakeDamage(void* pthis, void* avatar, void* local, void* WeaponData, const void* method) {
    if (MasterBool.ActivateAll && MasterBool.noDamage) {
        void* localPlayerc = Current_Local_Player();
        if (local == localPlayerc || pthis == localPlayerc) {  
            return false;
        }
    }
    if (orig_TakeDamage) {
        return orig_TakeDamage(pthis, avatar, local, WeaponData, method);
    }
    return false;
}

static bool g_TakeDamageHooked = false;

void InvisiblePlayer() {
    if (!MasterBool.ActivateAll || !MasterBool.noDamage) return;
    if (!InActiveMatch()) return;

    void *Local_Player = Current_Local_Player();
    if (Local_Player == nullptr) return;
    if (IsDieing(Local_Player)) return;
    if (GetHp(Local_Player) <= 0) return;

    uint32_t* stateponiter = (uint32_t*)((uint64_t)Local_Player + 0xC4C);
    if (!stateponiter) return;

    bool firingc = IsFiringPlayer(Local_Player);

    ghoston();
    if (firingc) {
        *stateponiter = 3;
    } else {
        *stateponiter = 1;
        SetFootballState(Local_Player);
    }
}

void AutoFootball() {
    // Reserved for auto-football logic — needs current game dump for correct offsets
}

void SpoofName() {

    auto player = Current_Local_Player();

    if (!player) return;

    monoString** namePtr = (monoString**)((uintptr_t)player + _NickName);

    static monoString* cachedSpoofName = nullptr;

    std::string base = "[b][FF0000]Onyx [ffffff]Aimkill[B][C]";



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



    if (!MasterBool.ActivateAll || !MasterBool.enableESP) return;



    void *CurrentLocalPlayer = Current_Local_Player();

    if (!CurrentLocalPlayer) return;

    InvisiblePlayer();



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

            if (Nick->toChars() != NULL) {

                if (MasterBool.targetLock && player == lockedEnemy) {

                    char lockName[128];

                    sprintf(lockName, "%s [LOCK]", Nick->toChars());

                    strcpy(data->name, lockName);

                } else {

                    strcpy(data->name, Nick->toChars());

                }

            }

        }

        SpoofName();

        response.PlayerCount++;

    }

}



// Called every 17ms (same smoothness ratio as the original 0.06f/10ms that worked perfectly).

// 0.1f/17ms = 0.006 m/ms = 6 m/s ascend — smooth, no jitter.

void FlyExploitSBG(void* localPlayer)

{

    if (!localPlayer) return;

    if (!(MasterBool.flyexploit && MasterBool.enableESP)) return;



    void *transform = Component_get_transform(localPlayer);

    if (!transform) return;



    Vector3 pos = Transform_INTERNAL_GetPosition(transform);

    pos.Y += 0.1f;   // same ratio as 0.06f/10ms — perfectly smooth

    Transform_set_position(transform, pos);

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

    static auto lastFireTick = std::chrono::steady_clock::now();

    static auto lastVisibleTime = std::chrono::steady_clock::now() - std::chrono::seconds(10);

    auto now = std::chrono::steady_clock::now();



    // Increased AllGun speed further as requested: 40ms -> 30ms

    // Winchester stays at 65ms

    int tickDelay = MasterBool.autofireslow ? 65 : 30;

    static bool noDelayAutoOffed = false;



    if (MasterBool.autofire || MasterBool.autofireslow) {

        auto now = std::chrono::steady_clock::now();



        // Target check (Visible or Pullable via Ghost Pull)

        void* target = (lockedEnemy != nullptr) ? lockedEnemy : cachedTarget;

        bool isTargetHitlable = false;



        if (target != nullptr) {

            void* local = Current_Local_Player();

            void* weapon = GetWeaponOnHand(local);



            if (isVisible_Aimbot(target)) {

                // If visible, still check range for realism/accuracy

                if (isEnemyInRangeWeapon(local, target, weapon)) {

                    isTargetHitlable = true;

                }

            } else if (MasterBool.NoBulletTracking || MasterBool.SafeSilentAim) {

                // If Silent Aim is on, check if we can pull them out of cover AND if they are in range

                if (isEnemyInRangeWeapon(local, target, weapon)) {

                    if (MasterBool.SafeSilentAim) {

                        if (SafeSilentPull(target, nullptr, false)) {

                            isTargetHitlable = true;

                        }

                    } else {

                        if (SilentGhostPullV2(target, nullptr, false)) {

                            isTargetHitlable = true;

                        }

                    }

                }

            }

        }



        if (isTargetHitlable) {

            lastVisibleTime = now;

        }



        // AUTO FIRE: Fire if visible or pullable

        if (isTargetHitlable) {

            InitializeFireTapper();

            TickFireTapper(false);



            // Enable Turbo Mode (Fast Fire) while persistent fire is active

            MasterBool.fastfiremax = true;



            // --- AUTO SPEED TIMER OFF DURING FIRE ---

            if (MasterBool.noDelay) {

                MasterBool.noDelay = false;

                noDelayAutoOffed = true;

            }



            // --- AUTO SWITCH FOR SMG (Only if Checkbox is enabled) ---

            if (MasterBool.autofire && MasterBool.autoSwitchEnabled) {

                void* local = Current_Local_Player();

                if (local) {

                    static int smgSwitchSlot = 1;

                    static int switchCounter = 0;



                    switchCounter++;

                    if (switchCounter >= 6) { // Balanced Speed: Switch every 6 ticks (~200ms)

                        switchCounter = 0;

                        smgSwitchSlot = (smgSwitchSlot == 1) ? 2 : 1;

                        SwapWeapon(local, smgSwitchSlot, 1);

                    }

                }

            }

        } else {

            // Restore Speed Timer when not firing

            if (noDelayAutoOffed) {

                MasterBool.noDelay = true;

                noDelayAutoOffed = false;

            }



            // Reset counter when not firing

            static int switchCounterReset = 0;

            if (fireTapState.isActive) StopFireTapper();

            if (fireTapState.isActive) StopFireTapper();

            if (!MasterBool.fastfireauto) MasterBool.fastfiremax = false;

        }

    } else {

        StopFireTapper();

        // Ensure Speed Timer is restored if hack is toggled off

        if (noDelayAutoOffed) {

            MasterBool.noDelay = true;

            noDelayAutoOffed = false;

        }

        // Ensure timer/sticky visibility is reset when hack is toggled off

        lastVisibleTime = std::chrono::steady_clock::now() - std::chrono::seconds(10);

    }

}



void BurstFireLoop() {

    if (MasterBool.burstFire && !MasterBool.autofire) {

        void* local = Current_Local_Player();

        // Removed IsFiringPlayer(local) per user request: "want it working whole time"

        if (local) {

            static auto lastFireTick = std::chrono::steady_clock::now();

            auto now = std::chrono::steady_clock::now();

            long long msSinceLast = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFireTick).count();

            

            // 300ms delay ensures a proper 3-tap burst cadence instead of rapid auto-fire

            if (msSinceLast >= 300) { 

                lastFireTick = now;

                InitializeFireTapper();

                TickFireTapper(true); // Sends 3 consecutive button down events

            }

        } else {

            StopFireTapper();

        }

    }

}



void AutoJumpLoop() {

    if (MasterBool.autojump) {

        InitializeJumpTapper();

        TickJumpTapper();

    }

    else

    {

        StopJumpTapper();

    }

}



MemoryPatch patchFunction;

bool ghostPatchInit = false;

void ghoston() {

    uintptr_t targetAddress = offset_GhostHack;

    unlockMemory(targetAddress);

    if (!ghostPatchInit) {

        patchFunction = MemoryPatch::createWithHex(targetAddress,"00 00 A0 E3 1E FF 2F E1");

        ghostPatchInit = true;

    }

    patchFunction.Modify();

}

void ghostoff() {

    if (patchFunction.isValid()) {

        patchFunction.Restore();

    }

}



Vector3 ghostStartPos = Vector3::Zero();

bool ghostWasEnabled = false;

void EnableGhostHack(){

    if(MasterBool.ghoston) {

        if (!ghostWasEnabled) {

            void *local = Current_Local_Player();

            if (local) {

                void *tfLocal = Component_get_transform(local);

                if (tfLocal) ghostStartPos = Transform_INTERNAL_GetPosition(tfLocal);

            }

            ghoston();

            ghostWasEnabled = true;

        }

    } else {

        if (ghostWasEnabled) {

            ghostoff();

            void *local = Current_Local_Player();

            if (local) {

                void *tfLocal = Component_get_transform(local);

                if (tfLocal) Transform_set_position(tfLocal, ghostStartPos);

            }

            ghostWasEnabled = false;

        }

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

// class ExternalSocketServer {

// private:

//     int server_fd;

//     int client_fd;

//     struct sockaddr_in address;

//     socklen_t addrlen;

//     bool isConnected;



// public:

//     ExternalSocketServer() : server_fd(-1), client_fd(-1), isConnected(false) {

//         addrlen = sizeof(address);

//     }



//     ~ExternalSocketServer() {

//         Disconnect();

//     }



//     void Disconnect() {

//         if (client_fd >= 0) {

//             close(client_fd);

//             client_fd = -1;

//         }

//         if (server_fd >= 0) {

//             close(server_fd);

//             server_fd = -1;

//         }

//         isConnected = false;

//     }



//     bool Create() {

//         server_fd = socket(AF_INET, SOCK_STREAM, 0);

//         if (server_fd < 0) {

//             LOGI("Socket creation failed");

//             return false;

//         }

//         return true;

//     }



//     bool Bind() {

//         memset(&address, 0, sizeof(address));

//         address.sin_family = AF_INET;

//         address.sin_addr.s_addr = inet_addr("127.0.0.1");

//         address.sin_port = htons(7777); // SECRET_PORT



//         int opt = 1;

//         setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));



//         if (::bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {

//             LOGI("Bind failed: %d", errno);

//             return false;

//         }

//         // LOGI("Control socket bound to port 21405");

//         return true;

//     }



//     bool Listen() {

//         if (listen(server_fd, 3) < 0) {

//             LOGI("Listen failed");

//             return false;

//         }

//         // LOGI("Control server listening...");

//         return true;

//     }



//     bool Accept() {

//         LOGI("Waiting for control connection...");

//         client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);

//         if (client_fd < 0) {

//             LOGI("Accept failed: %d", errno);

//             return false;

//         }



//         isConnected = true;

//         char clientIP[INET_ADDRSTRLEN];

//         inet_ntop(AF_INET, &(address.sin_addr), clientIP, INET_ADDRSTRLEN);

//         LOGI("Control connection accepted from %s", clientIP);

//         return true;

//     }



//     int receive(void* buffer, size_t length) {

//         if (!isConnected) return -1;

//         int received = read(client_fd, buffer, length);

//         if (received <= 0) {

//             LOGI("Control connection closed");

//             isConnected = false;

//         }

//         return received;

//     }



//     int send(const void* buffer, size_t length) {

//         if (!isConnected) return -1;

//         int sent = write(client_fd, buffer, length);

//         if (sent <= 0) {

//             LOGI("Send failed");

//             isConnected = false;

//         }

//         return sent;

//     }



//     bool IsConnected() const {

//         return isConnected;

//     }

// };



// // Global control server instance

// ExternalSocketServer controlServer;



// // Initialize control server

// int InitControlServer() {

//     if (!controlServer.Create()) return -1;

//     if (!controlServer.Bind()) return -1;

//     if (!controlServer.Listen()) return -1;

//     // LOGI("External control server initialized on port 21405");

//     return 0;

// }



// // External Socket Connection Thread Function

// void *ExternalControlServer(void *) {

//     if (InitControlServer() != 0) {

//         LOGI("Failed to init control server");

//         return nullptr;

//     }



//     while (true) {

//         if (controlServer.Accept()) {

//             LOGI("Control connection established");

//             char buffer[256];



//             // Send greeting

//             const char* greet = "READY";

//             controlServer.send((void*)greet, strlen(greet));



//             static bool isAuthorized = false;

//             while (true) {

//                 memset(buffer, 0, sizeof(buffer));

//                 int bytes = controlServer.receive(buffer, sizeof(buffer) - 1);

//                 if (bytes <= 0) break;



//                 buffer[bytes] = '\0';



//                 // --- SUPER HARD HANDSHAKE AUTHENTICATION ---

//                 static const char* SECRET_KEY = OBFUSCATE("TX999_SYSTEM_PROTECTED_LINK_#_999_@_SECURE_AUTH_888_!_X");



//                 if (!isAuthorized) {

//                     if (strcmp(buffer, SECRET_KEY) == 0) {

//                         isAuthorized = true;

//                         const char* authOk = "AUTH_OK";

//                         controlServer.send((void*)authOk, strlen(authOk));

//                         LOGI("External tool authorized successfully.");

//                         continue;

//                     } else {

//                         LOGI("Unauthorized access attempt. Disconnecting.");

//                         const char* authFail = "AUTH_FAIL";

//                         controlServer.send((void*)authFail, strlen(authFail));

//                         break; // Kick them out

//                     }

//                 }

//                 // --- END AUTHENTICATION ---



//                 LOGI("Received command: %s", buffer);



//                 // --- ACTUAL COMMANDS SYNC ---



//                 if (strcmp(buffer, "ENABLE_ALL_ON") == 0) {

//                     MasterBool.enableESP = true;

//                     LOGI("ENABLE_ALL Enabled");

//                 }

//                 else if (strcmp(buffer, "ENABLE_ALL_OFF") == 0) {

//                     MasterBool.enableESP = false;

//                     LOGI("ENABLE_ALL Disabled");

//                 }

//                 else if (strcmp(buffer, "SILENT_AIM_ON") == 0) {

//                     MasterBool.NoBulletTracking = true;

//                     LOGI("Silent Aim Enabled");

//                 }

//                 else if (strcmp(buffer, "SILENT_AIM_OFF") == 0) {

//                     MasterBool.NoBulletTracking = false;

//                     LOGI("Silent Aim Disabled");

//                 }

//                 else if (strcmp(buffer, "COVER_PULL_ON") == 0) {

//                     MasterBool.smartmove = true;

//                     LOGI("Cover Pull Enabled");

//                 }

//                 else if (strcmp(buffer, "COVER_PULL_OFF") == 0) {

//                     MasterBool.smartmove = false;

//                     LOGI("Cover Pull Disabled");

//                 }

//                 else if (strcmp(buffer, "AIMLOCK_ON") == 0) {

//                     MasterBool.teledifender = true;

//                     LOGI("Aimlock Enabled");

//                 }

//                 else if (strcmp(buffer, "AIMLOCK_OFF") == 0) {

//                     MasterBool.teledifender = false;

//                     LOGI("Aimlock Disabled");

//                 }

//                 else if (strcmp(buffer, "TARGET_LOCK_ON") == 0) {

//                     MasterBool.targetLock = true;

//                     LOGI("Target Lock Enabled");

//                 }

//                 else if (strcmp(buffer, "TARGET_LOCK_OFF") == 0) {

//                     MasterBool.targetLock = false;

//                     LOGI("Target Lock Disabled");

//                 }

//                 else if (strcmp(buffer, "AUTO_EXECUTE_ON") == 0) {

//                     MasterBool.autoexecute = true;

//                     LOGI("Auto Execute Enabled");

//                 }

//                 else if (strcmp(buffer, "AUTO_EXECUTE_OFF") == 0) {

//                     MasterBool.autoexecute = false;

//                     LOGI("Auto Execute Disabled");

//                 }

//                 else if (strcmp(buffer, "SNAPFLY_ON") == 0) {

//                     MasterBool.snapfly = true;

//                     LOGI("Snapfly Enabled");

//                 }

//                 else if (strcmp(buffer, "SNAPFLY_OFF") == 0) {

//                     MasterBool.snapfly = false;

//                     LOGI("Snapfly Disabled");

//                 }

//                 else if (strcmp(buffer, "AUTO_REVIVE_ON") == 0) {

//                     MasterBool.autorevive = true;

//                     LOGI("Auto Revive Enabled");

//                 }

//                 else if (strcmp(buffer, "AUTO_REVIVE_OFF") == 0) {

//                     MasterBool.autorevive = false;

//                     LOGI("Auto Revive Disabled");

//                 }

//                 else if (strcmp(buffer, "SPEED_TIMER_ON") == 0) {

//                     MasterBool.noDelay = true;

//                     LOGI("Speed Timer Enabled");

//                 }

//                 else if (strcmp(buffer, "SPEED_TIMER_OFF") == 0) {

//                     MasterBool.noDelay = false;

//                     LOGI("Speed Timer Disabled");

//                 }

//                 else if (strcmp(buffer, "AUTOFIRE_ALLGUN_ON") == 0) {

//                     MasterBool.autofire = true;

//                     MasterBool.noreloadfck = true;

//                     LOGI("Autofire Allgun Enabled");

//                 }

//                 else if (strcmp(buffer, "AUTOFIRE_ALLGUN_OFF") == 0) {

//                     MasterBool.autofire = false;

//                     MasterBool.noreloadfck = false;

//                     LOGI("Autofire Allgun Disabled");

//                 }

//                 else if (strcmp(buffer, "AUTOFIRE_WINCHESTER_ON") == 0) {

//                     MasterBool.autofireslow = true;

//                     MasterBool.fastfiremax = true;

//                     MasterBool.noreloadfck = true;

//                     LOGI("Autofire Winchester Enabled");

//                 }

//                 else if (strcmp(buffer, "AUTOFIRE_WINCHESTER_OFF") == 0) {

//                     MasterBool.autofireslow = false;

//                     MasterBool.fastfiremax = false;

//                     MasterBool.noreloadfck = false;

//                     LOGI("Autofire Winchester Disabled");

//                 }

//                 else if (strcmp(buffer, "FAST_FIRE_ON") == 0) {

//                     MasterBool.fireScaleHack = true;

//                     LOGI("Fast Fire Enabled");

//                 }

//                 else if (strcmp(buffer, "FAST_FIRE_OFF") == 0) {

//                     MasterBool.fireScaleHack = false;

//                     LOGI("Fast Fire Disabled");

//                 }

//                 else if (strcmp(buffer, "FLYHACK_ON") == 0) {

//                     MasterBool.flyhackop = true;

//                     LOGI("Flyhack Enabled");

//                 }

//                 else if (strcmp(buffer, "FLYHACK_OFF") == 0) {

//                     MasterBool.flyhackop = false;

//                     LOGI("Flyhack Disabled");

//                 }

//                 else if (strcmp(buffer, "MAP_TELEPORT_ON") == 0) {

//                     MasterBool.mapateleport = true;

//                     LOGI("Map Teleport Enabled");

//                 }

//                 else if (strcmp(buffer, "MAP_TELEPORT_OFF") == 0) {

//                     MasterBool.mapateleport = false;

//                     LOGI("Map Teleport Disabled");

//                 }

//                 else if (strcmp(buffer, "TELEPORT_ENEMY_ON") == 0) {

//                     MasterBool.autoteleport = true;

//                     LOGI("Teleport Enemy Enabled");

//                 }

//                 else if (strcmp(buffer, "TELEPORT_ENEMY_OFF") == 0) {

//                     MasterBool.autoteleport = false;

//                     LOGI("Teleport Enemy Disabled");

//                 }

//                 else if (strcmp(buffer, "RESET_GUEST_ON") == 0) {

//                     MasterBool.resetguest = true;

//                     LOGI("Reset Guest Triggered");

//                 }

//                 else if (strncmp(buffer, "SET_AIMFOV ", 11) == 0) {

//                     float fov = atof(buffer + 11);

//                     MasterBool.aimbotFOV = fov;

//                     LOGI("Aim FOV Set: %f", fov);

//                 }

//                 else if (strcmp(buffer, "SAFE_SILENT_AIM_ON") == 0) {

//                     MasterBool.SafeSilentAim = true;

//                     LOGI("Safe Silent Aim Enabled");

//                 }

//                 else if (strcmp(buffer, "SAFE_SILENT_AIM_OFF") == 0) {

//                     MasterBool.SafeSilentAim = false;

//                     LOGI("Safe Silent Aim Disabled");

//                 }



//                 else {

//                     LOGI("Unknown command: %s", buffer);

//                 }



//                 // --- END ACTUAL COMMANDS SYNC ---



//                 const char* resp = "OK";

//                 controlServer.send((void*)resp, strlen(resp));

//             }



//             LOGI("Control connection closed");

//                 isAuthorized = false; // Reset for next connection

//             controlServer.Disconnect();

//         }

//     }

//     return nullptr;

// }



void allfunction() {

    if (MasterBool.enableESP) {

        if (MasterBool.downaimkill) {

            MasterBool.downplayer = true;

            MasterBool.flyhack = true;



        } else {

            MasterBool.downplayer = false;

            MasterBool.flyhack = false;

        }

    }

}

void *CreateServer(void *) {

    if (InitServer() == 0) {

        while(true) {

            if (server.Accept()) {

                Request request{};

                while (server.receive((void*)&request) > 0) {

                    Response response{};

                    //allfunction();

                    AutoJumpLoop();

                    if (request.Mode == Mode::InitMode) {

                        response.Success = true;

                    } else if (request.Mode == Mode::EspMode) {

                        g_screenWidth = request.ScreenWidth;

                        g_screenHeight = request.ScreenHeight;

                        response.Success = true;

                        NewEspForUnity31(response);

                    } else if (request.Mode == 3) {

                        MasterBool.ActivateAll = request.boolean;
                        MasterBool.enableESP = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 5659) {

                        MasterBool.flyx40 = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 5002) {

                        MasterBool.flyX80 = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 5003) {

                        MasterBool.infinityFly = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 7002) {

                        MasterBool.ghoston = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 109) {

                        MasterBool.speedHack = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 565789) {

                        MasterBool.flyinit = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 5657) {

                        MasterBool.flyhackop = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 56578) {

                        MasterBool.mapateleport = request.boolean;

                        response.Success = true;

                    }

                    else if (request.Mode == 5657899) {

                        MasterBool.autoteleport = request.boolean;

                        response.Success = true;

                    }

                    else if (request.Mode == 889) {

                        MasterBool.NoBulletTracking = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 7001) {

                        MasterBool.autoGlider = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 100) {

                        MasterBool.Aimkill = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 1044) {

                        MasterBool.Aimkillsend = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 1051) {

                        MasterBool.AimkillBrutal = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 1052) {

                        MasterBool.AimkillBody = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 1047) {

                        MasterBool.AimkillSendAutoSwitch = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 1048) {

                        MasterBool.AimkillSendCoverPull = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 1049) {

                        MasterBool.SafeAimkill = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 5661) {

                        MasterBool.RealAimkill = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 5662) {

                        MasterBool.RealAimkillV2 = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 5001) {

                        MasterBool.snapfly = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 1043) {

                        MasterBool.FlySpeed = (float)request.value;

                        response.Success = true;

                    } else if (request.Mode == 1045) {

                        MasterBool.fucked = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 1046) {

                        MasterBool.fireScaleHack = request.boolean;

                        response.Success = true;

                    }

                    else if (request.Mode == 104) {

                        MasterBool.aimbotFOV = request.value;

                        response.Success = true;

                    } else if (request.Mode == 1055) {

                        MasterBool.Aimkill360 = request.boolean;

                        response.Success = true;

                    } else if(request.Mode == 108) {

                        MasterBool.aimbotbody = request.boolean;

                        response.Success = true;

                    }else if(request.Mode == 7865) {

                        MasterBool.autojump = request.boolean;

                        response.Success = true;

                    } else if(request.Mode == 40004) {

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

                    } else if(request.Mode == 21) {

                        MasterBool.aimbody = request.boolean;

                        response.Success = true;

                    } else if(request.Mode == 500) {

                        MasterBool.Aimkilltp = request.boolean;

                        response.Success = true;

                    } else if(request.Mode == 501) {

                        MasterBool.Aimkilltpv2 = request.boolean;

                        response.Success = true;

                    } else if(request.Mode == 502) {

                        MasterBool.Aimkillrotate = request.boolean;

                        response.Success = true;

                    } else if(request.Mode == 504) {

                        MasterBool.downaimkill = request.boolean;

                        response.Success = true;

                    } else if (request.Mode == 525) {

                        // Manual Target Lock by Pointer passed in playerPtr field

                        lockedEnemy = (void*)request.playerPtr;

                        if (lockedEnemy != nullptr) {

                            MasterBool.targetLock = true; // Force ON

                            monoString *Nick = *(monoString **) ((uint64_t) lockedEnemy + _OriginalName);

                            if (Nick && Nick->toChars() != NULL) {

                                strncpy(lockedEnemyName, Nick->toChars(), 127);

                            }

                            wasLockedEnemyDown = false;

                        } else {

                            MasterBool.targetLock = false;

                            lockedEnemyName[0] = '\0';

                        }

                        response.Success = true;

                    } else if(request.Mode == 505) {

                        MasterBool.autoswitch = request.boolean;

                        response.Success = true;

                    } else if(request.Mode == 508) {

                        MasterBool.autoswitchsafe = request.boolean;

                        response.Success = true;

                    } else if(request.Mode == 527) {

                        MasterBool.hidedamage = request.boolean;

                        response.Success = true;

                    } else if(request.Mode == 529) {

                        MasterBool.highfps = request.boolean;

                        response.Success = true;

                    } else if(request.Mode == 531) {

                        MasterBool.football = request.boolean;

                        response.Success = true;

                    } else if(request.Mode == 15) {

                        MasterBool.speedhackjoy = request.boolean;

                        response.Success = true;

                    } else if(request.Mode == 528) {

                        MasterBool.burstFire = request.boolean;

                        response.Success = true;

                    }

                    else if(request.Mode == 34834) {

                        MasterBool.teledifender = request.boolean;

                        response.Success = true;

                    }

                    else if(request.Mode == 23294) {

                        MasterBool.godweapon = request.boolean;

                        response.Success = true;

                    }

                    else if(request.Mode == 5001) {

                        MasterBool.snapfly = request.boolean;

                        response.Success = true;

                    }

                    else if(request.Mode == 7896) {

                        MasterBool.autorevive = request.boolean;

                        response.Success = true;

                    }

                    else if(request.Mode == 7898) {

                        MasterBool.autoexecute = request.boolean;

                        response.Success = true;

                    }

                    else if(request.Mode == 524) {

                        MasterBool.autoSwitchEnabled = request.boolean;

                        response.Success = true;

                    }



else if (request.Mode == 1080) {

                    MasterBool.flyexploit = request.boolean;

                    MasterBool.flyhackop = request.boolean;

                        if (request.boolean) MasterBool.flyhack = false;

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

                    else if (request.Mode == 517) {

                        MasterBool.noDelay = request.boolean;

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

                    else if (request.Mode == 521) {

                        MasterBool.autofireslow = request.boolean;

                        if (request.boolean) {

                            MasterBool.fastfiremax = true;

                            MasterBool.noreloadfck = true;

                        }

                        response.Success = true;

                    }

                    else if (request.Mode == 522) {

                        MasterBool.autojump = request.boolean;

                        response.Success = true;

                    }

                    else if (request.Mode == 523) {

                        MasterBool.targetLock = request.boolean;

                        if (request.boolean) {

                            // If turning ON and we don't have a remembered target, try to pick closest

                            if (lockedEnemy == nullptr && cachedTarget != nullptr) {

                                lockedEnemy = cachedTarget;

                                monoString *Nick = *(monoString **) ((uint64_t) lockedEnemy + _OriginalName);

                                if (Nick && Nick->toChars() != NULL) {

                                    strncpy(lockedEnemyName, Nick->toChars(), 127);

                                }

                                wasLockedEnemyDown = false;

                            }

                        } else {

                            // If turning OFF, we keep 'lockedEnemy' in memory but stop using it 

                            // because MasterBool.targetLock is now false.

                            // No action needed here to preserve memory.

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

        // teammate check

        if (!IsLocalTeammate(player)) continue;

        // knocked check

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

void RequestExecuteTargetV2(void *thiss, COW_GamePlay_IHAAMHPPLMG_o targetID)

{

    void *message = (void *)offset_RequestExecuteTar;

    if (message)

    {

        *(uint32_t*)((uint64_t)message + offset_exc_PJKBDOJLDNN) = CFFPIACECIG(targetID);

        *(int64_t*)((uint64_t)message + offset_exc_EGAMAMKBENE) = 1;

        GameFacade_Send(951, message, 2, 0);

    }

}



void AutoExecute() {

    void *LocalPlayer = Current_Local_Player();



    if(MasterBool.autoexecute){

        void *targetTeammate = GetKnockedEnemyNearby();

        if (LocalPlayer != nullptr && targetTeammate != nullptr) {

            COW_GamePlay_IHAAMHPPLMG_o tID = GetplayerID(targetTeammate);

            RequestExecuteTargetV2(LocalPlayer, tID);

        }

    }

}







// #define offset_EMAOKNCFCKE (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GPBDEDFKJNA"), OBFUSCATE("EMAOKNCFCKE"), 0)

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









void AllInOneDownKill(void *ClosestEnemy) {

    if (MasterBool.downplayer && ClosestEnemy != nullptr) {

        void *LocalPlayer = Current_Local_Player();

        Vector3 gotten = Transform_INTERNAL_GetPosition(Component_get_transform(LocalPlayer));

        Vector3 enemyPos = Transform_INTERNAL_GetPosition(Component_get_transform(ClosestEnemy));

        float realDistance = sqrt(pow(enemyPos.X - gotten.X, 2) +pow(enemyPos.Y - gotten.Y, 2) +pow(enemyPos.Z - gotten.Z, 2));

        if (realDistance < 150.0f) {

            enemyPos.Y -= 1.9f;

            Transform_set_position(Component_get_transform(ClosestEnemy), enemyPos);

        }

    }

}





void DownKillV2(void *clos) {

    static auto lastTick = std::chrono::steady_clock::now();

    auto now = std::chrono::steady_clock::now();

    long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTick).count();

    if (elapsed < 50) return;

    lastTick = now;



    void *localPlayer = Current_Local_Player();

    if (localPlayer == nullptr) return;

    std::vector<void *> enemies;

    bool enemiesFetched = false;

    if (MasterBool.downplayer) {

        if (clos != nullptr) {

            enemies.push_back(clos);

            enemiesFetched = true;

        }



        for (void *e: enemies) {

            if (!e) continue;

            void *eTf = Component_get_transform(e);

            if (!eTf) continue;

            Vector3 cur = Transform_INTERNAL_GetPosition(eTf);

            Vector3 target;

            target.X = cur.X;

            target.Z = cur.Z;

            target.Y = cur.Y - 2.8f;

            Transform_set_position(eTf, target);

        }

    }



    static bool isFlyLocked = false;

    static Vector3 flyLockPosition = Vector3::Zero();



    if (MasterBool.flyhack) {

        if (!enemiesFetched) {

            enemies.push_back(clos);

            enemiesFetched = true;

        }

        bool foundEnemy = !enemies.empty();



        if (foundEnemy) {

            void *tfLocal = Component_get_transform(localPlayer);

            if (!tfLocal) {

                isFlyLocked = false;

                return;

            }



            Vector3 localPos = Transform_INTERNAL_GetPosition(tfLocal);

            if (!isFlyLocked) {

                flyLockPosition = localPos;

                flyLockPosition.Y -= 2.5f;

                isFlyLocked = true;

            }



            localPos.Y = flyLockPosition.Y;

            Transform_set_position(tfLocal, localPos);

        } else {

            isFlyLocked = false;

        }

    } else {

        isFlyLocked = false;

    }

}



float TimerTakeDamageinit = 0.0f;

float TimerTakeDamageEnd  = 0.0f; // AGGRESSIVE: instant fire, no cooldown



// Pull enemy into line of sight inside aimkill — no player fire button needed

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
        set_position_Injected(tf, original);
}
}

// Shared damage instances (reused by AimKillV2 + AimKillSend + RealAimkill)
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
    if (MasterBool.Aimkilltpv2) {
        return;
    }
    if (!(MasterBool.Aimkill || MasterBool.Aimkill360)) {
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



// ======================================================================

// Safe Aimkill — fully separate; max 1-2 packets per burst, hard cap 3/enemy

// ======================================================================

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



// ======================================================================

// Aimkill Send — V2 pattern: GKHECDLGAJA→LCLHHHKFCFP(NULL)→Player_TakeDamage (no WeaponFire)

// ======================================================================

static bool (*original_WeaponFire)(void* weapon, COW_GamePlay_MADMMIICBNN_o *hitInfo) = nullptr;



static void FillHitInfoDirectly(COW_GamePlay_MADMMIICBNN_o *hitInfo, void *headCollider,

                                Vector3 enemyHeadPos, Vector3 localHeadPos, Vector3 direction,

                                float dist, int baseDamage) {

    if (!hitInfo || !headCollider) return;



    void* go = get_gameObject(headCollider);

    if (!go) return; // FIX: null guard — get_gameObject can return null after cover pull

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

static bool ResolveWeaponFireFn() {
    if (original_WeaponFire) return true;
    uintptr_t offset = offset_WeaponFire;
    if (!offset) offset = getRealOffset(0x66E999C);
    if (!offset) return false;
    original_WeaponFire = (bool (*)(void*, COW_GamePlay_MADMMIICBNN_o*))offset;
    return original_WeaponFire != nullptr;
}

static Vector3 GetBodyPosition(void* target) {
    if (!target) return Vector3::Zero();
    void* RootTF = TransformNode(*(void**)((uint64_t)target + _RootTF));
    if (!RootTF) return Vector3::Zero();
    Vector3 rootPos = Transform_INTERNAL_GetPosition(RootTF);
    void* HeadTF = TransformNode(*(void**)((uint64_t)target + _HeadTF));
    if (!HeadTF) return rootPos;
    Vector3 headPos = Transform_INTERNAL_GetPosition(HeadTF);
    Vector3 bodyPos;
    bodyPos.X = (headPos.X + rootPos.X) * 0.5f;
    bodyPos.Y = (headPos.Y * 0.65f + rootPos.Y * 0.35f);
    bodyPos.Z = (headPos.Z + rootPos.Z) * 0.5f;
    return bodyPos;
}

static void* GetBodyCollider(void* target, void* headCollider) {
    if (!target) return nullptr;
    if (headCollider) return headCollider;
    return get_HeadCollider(target);
}

void StartAimKillSend(void* ClosestEnemy) {
    if (!MasterBool.Aimkillsend && !MasterBool.AimkillBrutal && !MasterBool.AimkillBody) return;
    if (MasterBool.Aimkilltpv2) return;
    if (!InActiveMatch()) return;

    if (g_inAimkillSend) return;
    g_inAimkillSend = true;

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

    if (ClosestEnemy && !IsDieing(ClosestEnemy) && GetHp(ClosestEnemy) > 0 && !IsLocalTeammate(ClosestEnemy)) {
        targetsToProcess.push_back(ClosestEnemy);
    }

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

    void *playerattributes = *(void **) ((uint64_t) localPlayer + _playerAttributes);
    if (playerattributes != nullptr) {
        *(bool *) ((uintptr_t) playerattributes + offset_NoReload) = true;
    }

    int processedTargets = 0;
    for (auto target : targetsToProcess) {
        if (processedTargets >= 5) break;
        if (!target || target == localPlayer || IsDieing(target) || GetHp(target) <= 0 || IsLocalTeammate(target)) continue;

        void* enemyTf = nullptr;
        Vector3 originalPos = {0, 0, 0};
        bool wasPulled = AimkillMethodPull(target, &enemyTf, &originalPos);
        bool visible = isVisible_Aimbot(target);

        if (!visible && !wasPulled) {
            if (wasPulled && enemyTf && target) AimkillMethodRestore(target, enemyTf, originalPos);
            continue;
        }

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

        if (!wasPulled && !GKHECDLGAJA(localPlayer, hitObjectInfo)) {
            if (wasPulled && enemyTf && target) AimkillMethodRestore(target, enemyTf, originalPos);
            continue;
        }

        if (!IsFiringPlayer(localPlayer)) {
            StartFiring(localPlayer, weaponOnHand);
        }

        if (target && !IsDieing(target) && GetHp(target) > 0 && weaponOnHand && hitInfo) {
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

// ======================================================================
// REAL AIMKILL — SafeAimkill pattern: double GKHECDLGAJA + WeaponFire only
// ======================================================================

void StartRealAimkill(void* ClosestEnemy) {
    if (!MasterBool.RealAimkill) return;
    if (MasterBool.Aimkilltpv2) return;
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

    // SafeAimkill proven pattern: double GKHECDLGAJA + WeaponFire
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

    FillHitInfoDirectly(hitInfo, headColliderEnemy, hitPos, firePos, dir, dist, 999);
    GKHECDLGAJA(localPlayer, hitObjectInfo);

    if (ClosestEnemy && !IsDieing(ClosestEnemy) && GetHp(ClosestEnemy) > 0) {
        original_WeaponFire(weaponOnHand, hitInfo);
    }

    StopFire(localPlayer, weaponOnHand);
    Syns_SwapWeapon_Impl(localPlayer, weaponOnHand);
    AimkillMethodRestore(ClosestEnemy, enemyTf, originalPos);
}

// ======================================================================
// REAL AIMKILL V2 — Throttled packet-based kill method
// ======================================================================

static bool g_inAimkillV2 = false;
static std::vector<void*> g_aimkillV2EnemyList;
static int g_aimkillV2CurrentIndex = 0;
static bool g_aimkillV2Initialized = false;
bool g_isAimkillShot = false;
extern bool (*NoBUlletTractOriginal)(void* weapon, COW_GamePlay_MADMMIICBNN_o *hitInfo);
void FastFireMaxTimer();

void StartRealAimkillV2(void* ClosestEnemy) {
    if (!(MasterBool.RealAimkillV2 || MasterBool.TargetAll)) return;
    if (MasterBool.Aimkilltpv2) return;
    if (!InActiveMatch()) return;
    if (g_inAimkillV2) return;

    g_inAimkillV2 = true;

    void* local = Current_Local_Player();
    if (!local || IsDieing(local)) { g_inAimkillV2 = false; return; }

    void* weapon = GetWeaponOnHand(local);
    if (!weapon) { g_inAimkillV2 = false; return; }

    // Force No Reload (Packet Suppression Bypass)
    void* attrs = *(void**)((uintptr_t)local + _playerAttributes);
    if (attrs) *(bool*)((uintptr_t)attrs + offset_NoReload) = true;

    // Get current match instance
    if (!_GameFacade) { g_inAimkillV2 = false; return; }
    void* matchGame = *(void**)((uintptr_t)_GameFacade + _StaticClass);
    if (!matchGame) { g_inAimkillV2 = false; return; }
    void* classMatchGame = *(void**)((uintptr_t)matchGame + _MatchGame);
    if (!classMatchGame) { g_inAimkillV2 = false; return; }
    void* current_match = *(void**)((uintptr_t)classMatchGame + _Match);
    if (!current_match) { g_inAimkillV2 = false; return; }

    auto players = GetEntities(current_match);

    // ---- Build enemy list (once per batch/match tick) ----
    if (!g_aimkillV2Initialized || g_aimkillV2CurrentIndex >= (int)g_aimkillV2EnemyList.size()) {
        g_aimkillV2EnemyList.clear();
        for (void* enemy : players) {
            if (!enemy || enemy == local) continue;
            if (IsDieing(enemy) || GetHp(enemy) <= 0) continue;
            if (IsLocalTeammate(enemy)) continue;
            if (!isEnemyInRangeWeapon(local, enemy, weapon)) continue;
            g_aimkillV2EnemyList.push_back(enemy);
        }
        g_aimkillV2CurrentIndex = 0;
        g_aimkillV2Initialized = true;
    }

    if (g_aimkillV2EnemyList.empty()) {
        g_aimkillV2Initialized = false;
        g_inAimkillV2 = false;
        return;
    }

    // ---- Process ONLY ONE enemy per call (Smoothness & Stability) ----
    if (g_aimkillV2CurrentIndex < (int)g_aimkillV2EnemyList.size()) {
        void* enemy = g_aimkillV2EnemyList[g_aimkillV2CurrentIndex];
        g_aimkillV2CurrentIndex++;

        if (!enemy || IsDieing(enemy) || GetHp(enemy) <= 0) {
            g_inAimkillV2 = false;
            return;
        }

        // ---- Auto-Pull if Target is Hidden ----
        void* enemyTf = nullptr;
        Vector3 originalPos = {0, 0, 0};
        bool wasPulled = false;
        if (!isVisible_Aimbot(enemy)) {
            wasPulled = AimkillMethodPull(enemy, &enemyTf, &originalPos);
            if (!wasPulled) {
                g_inAimkillV2 = false;
                return;
            }
        }

        void* headCollider = get_HeadCollider(enemy);
        if (!headCollider) {
            if (wasPulled) AimkillMethodRestore(enemy, enemyTf, originalPos);
            g_inAimkillV2 = false;
            return;
        }

        void* hitObjectInfo = *(void**)((uintptr_t)local + _HitObjectInfoWp);
        if (!hitObjectInfo) {
            if (wasPulled) AimkillMethodRestore(enemy, enemyTf, originalPos);
            g_inAimkillV2 = false;
            return;
        }

        Vector3 localHead = GetHeadPosition(local);
        Vector3 hitPos = GetHeadPosition(enemy);
        float dx = hitPos.X - localHead.X;
        float dy = hitPos.Y - localHead.Y;
        float dz = hitPos.Z - localHead.Z;
        float dist = sqrtf(dx*dx + dy*dy + dz*dz);
        Vector3 direction = {0, 0, 0};
        if (dist > 0.0001f) {
            float inv = 1.0f / dist;
            direction.X = dx * inv;
            direction.Y = dy * inv;
            direction.Z = dz * inv;
        }

        // ---- Calculate realistic damage packet values ----
        int baseDamage = GetDamage(weapon);
        if (baseDamage <= 0) baseDamage = 30;
        int damageToSend = baseDamage * 2;
        if (damageToSend > 250) damageToSend = 250;

        COW_GamePlay_MADMMIICBNN_o* hitInfo = (COW_GamePlay_MADMMIICBNN_o*)hitObjectInfo;
        FillHitInfoDirectly(hitInfo, headCollider, hitPos, localHead, direction, dist, damageToSend);
        GKHECDLGAJA(local, hitObjectInfo);

        // ---- Resolve original WeaponFire Hook Fallback ----
        if (!NoBUlletTractOriginal) {
            NoBUlletTractOriginal = (bool (*)(void*, COW_GamePlay_MADMMIICBNN_o*))getRealOffset(0x66E999C);
        }
        if (!NoBUlletTractOriginal) {
            if (wasPulled) AimkillMethodRestore(enemy, enemyTf, originalPos);
            g_inAimkillV2 = false;
            return;
        }

        // ---- Temporarily remove fire rate delay for burst delivery ----
        bool oldFast = MasterBool.fastfiremax;
        bool oldFireScale = MasterBool.fireScaleHack;
        MasterBool.fastfiremax = true;
        MasterBool.fireScaleHack = true;
        FastFireMaxTimer();

        // ---- Enable damage hook override for one-shot ----
        g_isAimkillShot = true;

        // ---- EXECUTE FIRE PACKET ----
        StartFiring(local, weapon);
        NoBUlletTractOriginal(weapon, hitInfo);
        StopFire(local, weapon);

        // ---- Disable overrides ----
        g_isAimkillShot = false;

        // ---- Restore normal fire rates ----
        MasterBool.fastfiremax = oldFast;
        MasterBool.fireScaleHack = oldFireScale;
        FastFireMaxTimer();

        // ---- Resync Weapon State (Instant Packet Channel) ----
        Syns_SwapWeapon_Impl(local, weapon);

        // Restore enemy to original position (Server Anti-Cheat Sync)
        if (wasPulled) AimkillMethodRestore(enemy, enemyTf, originalPos);
    }

    // ---- Reset iteration state when batch is finished ----
    if (g_aimkillV2CurrentIndex >= (int)g_aimkillV2EnemyList.size()) {
        g_aimkillV2Initialized = false;
        g_aimkillV2EnemyList.clear();
        g_aimkillV2CurrentIndex = 0;
    }

    g_inAimkillV2 = false;
}

// ======================================================================

// Hit Fly — launches enemy upward on hit via ClientHitFlyToCenterTrigger.HitFly(Player)

// ======================================================================

static void (*HitFly_DirectMethod)(void*, void*) = nullptr;

void StartEnemyHitFly(void* enemyPlayer) {
    if (!enemyPlayer) return;
    if (IsDieing(enemyPlayer)) return;

    // Resolve ClientHitFlyToCenterTrigger.HitFly(Player player) once
    if (!HitFly_DirectMethod) {
        uintptr_t off = getRealOffset(0x169e074);
        if (off) HitFly_DirectMethod = (void (*)(void*, void*))off;
    }
    if (!HitFly_DirectMethod) return;

    // Method at 0x169e074 is ClientHitFlyToCenterTrigger.HitFly(Player).
    // Try localPlayer as this (shooter), enemyPlayer as the target.
    void* localPlayer = Current_Local_Player();
    if (!localPlayer) return;
    HitFly_DirectMethod(localPlayer, enemyPlayer);
}

// ======================================================================

// Safe Aimkill — same as Aimkill Send (WeaponFire) but 1-2 hits/burst, max 3/enemy

// ======================================================================

void StartSafeAimkill(void* enemy) {
    if (!MasterBool.SafeAimkill) return;
    if (MasterBool.Aimkilltpv2) {
        return;
    }
    if (!enemy) {
        return;
    }
    if (!IsPullTargetValid(enemy)) {
        return;
    }
    if (!InActiveMatch()) {

        return;
    }
    if (IsDieing(enemy)) {

        return;
    }
    if (GetHp(enemy) <= 0) {

        return;
    }
    if (!SafeAimkillCanSendPacket(enemy)) {

        return;
    }

    void *localPlayer = Current_Local_Player();
    if (!localPlayer) {
        return;
    }
    if (localPlayer == enemy) {
        return;
    }
    if (IsDieing(localPlayer)) {

        return;
    }

    void *weaponOnHand = GetWeaponOnHand(localPlayer);
    if (!weaponOnHand) {

        return;
    }
    if (!isEnemyInRangeWeapon(localPlayer, enemy, weaponOnHand)) {

        return;
    }

    static bool s_inSafeAimkill = false;
    if (s_inSafeAimkill) {

        return;
    }
    s_inSafeAimkill = true;

    void* enemyTf = nullptr;
    Vector3 originalPos = {0, 0, 0};
    bool wasPulled = AimkillMethodPull(enemy, &enemyTf, &originalPos);
    bool visible = isVisible_Aimbot(enemy);


    if (!visible && !wasPulled) {

        s_inSafeAimkill = false;
        return;
    }

    void *headColliderEnemy = get_HeadCollider(enemy);
    void *headColliderLocal = get_HeadCollider(localPlayer);
    if (!headColliderEnemy || !headColliderLocal) {
        AimkillMethodRestore(enemy, enemyTf, originalPos);
        s_inSafeAimkill = false;
        return;
    }

    void *hitObjectInfo = *(void **)((uintptr_t)localPlayer + _HitObjectInfoWp);
    if (!hitObjectInfo) {

        AimkillMethodRestore(enemy, enemyTf, originalPos);
        s_inSafeAimkill = false;
        return;
    }

    if (!original_WeaponFire) {
        uintptr_t offset = offset_WeaponFire;
        if (!offset) {
            offset = getRealOffset(0x66E999C);
        }
        original_WeaponFire = (bool (*)(void*, COW_GamePlay_MADMMIICBNN_o*))offset;
    }
    if (!original_WeaponFire) {

        AimkillMethodRestore(enemy, enemyTf, originalPos);
        s_inSafeAimkill = false;
        return;
    }

    int baseDamage = GetDamage(weaponOnHand);
    if (baseDamage <= 0) baseDamage = 99;

    Vector3 firePos = GetHeadPosition(localPlayer);
    Vector3 hitPos = GetHeadPosition(enemy);

    void *headGameObject = get_gameObject(headColliderEnemy);
    if (!headGameObject) {

        AimkillMethodRestore(enemy, enemyTf, originalPos);
        s_inSafeAimkill = false;
        return;
    }

    void *head = get_HeadCollider(enemy);
    if (!head) {
        AimkillMethodRestore(enemy, enemyTf, originalPos);
        s_inSafeAimkill = false;
        return;
    }

    *(void **)((uintptr_t)hitObjectInfo + Hit_GameObject) = headGameObject;
    *(void **)((uintptr_t)hitObjectInfo + Hit_HeadCollider) = headColliderEnemy;

    if (!GKHECDLGAJA(localPlayer, hitObjectInfo)) {
        AimkillMethodRestore(enemy, enemyTf, originalPos);
        s_inSafeAimkill = false;
        return;
    }

    if (!IsFiringPlayer(localPlayer)) {
        StartFiring(localPlayer, weaponOnHand);
    }

    float dx = hitPos.X - firePos.X;
    float dy = hitPos.Y - firePos.Y;
    float dz = hitPos.Z - firePos.Z;
    float dist = sqrtf(dx * dx + dy * dy + dz * dz);
    Vector3 direction = {0, 0, 0};
    if (dist > 0.0001f) {
        float inv = 1.0f / dist;
        direction.X = dx * inv;
        direction.Y = dy * inv;
        direction.Z = dz * inv;
    }

    COW_GamePlay_MADMMIICBNN_o *hitInfo = (COW_GamePlay_MADMMIICBNN_o *)hitObjectInfo;
    FillHitInfoDirectly(hitInfo, head, hitPos, firePos, direction, dist, baseDamage);
    GKHECDLGAJA(localPlayer, hitObjectInfo);

    bool fired = false;
    if (enemy && !IsDieing(enemy) && GetHp(enemy) > 0) {
        fired = original_WeaponFire(weaponOnHand, hitInfo);
    }

    if (fired) {
        SafeAimkillRecordPacketSent();
    } else {
    }

    StopFire(localPlayer, weaponOnHand);
    Syns_SwapWeapon_Impl(localPlayer, weaponOnHand);
    AimkillMethodRestore(enemy, enemyTf, originalPos);
    s_inSafeAimkill = false;
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



    if (MasterBool.autoswitch && MasterBool.enableESP)

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

    // Secondary fallback: check UIBigMapController m_SelectPoint (offset 0x12C)
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

    if (elapsed < 50) return; // 50ms — redundant with inline swap, keep light

    last = now;

    void *localPlayer = Current_Local_Player();

    if (localPlayer == nullptr) return;

    ForceAutoSwitchReliable(localPlayer);

}



void AimkillSendAutoSwitchLoop() {

    if (!MasterBool.Aimkillsend || !MasterBool.AimkillSendAutoSwitch || MasterBool.Aimkilltpv2) return;



    static auto lastSwitch = std::chrono::steady_clock::now();

    auto now = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastSwitch).count() < 50) return; // 50ms — inline swap in StartAimKillSend handles instant swap already

    lastSwitch = now;



    void *localPlayer = Current_Local_Player();

    if (!localPlayer || IsDieing(localPlayer)) return;



    void *weaponOnHand = GetWeaponOnHand(localPlayer);

    if (!weaponOnHand) return;



    static int lastSlot = 2;

    int newSlot = (lastSlot == 1) ? 2 : 1;

    SwapWeapon(localPlayer, newSlot, 1);

    lastSlot = newSlot;



    void *syncedWeapon = GetWeaponOnHand(localPlayer);

    if (syncedWeapon) Syns_SwapWeapon_Impl(localPlayer, syncedWeapon);

}

// ======================================================================
// Normal Auto Switch — human-like speed (250-400ms random delay)
// ======================================================================

void NormalAutoSwitchLoop() {
    if (!MasterBool.autoswitchsafe) return;
    if (MasterBool.Aimkilltpv2) return;

    static auto lastSwitch = std::chrono::steady_clock::now();
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)(get_realtimeSinceStartup() * 1000.0f));
        seeded = true;
    }

    auto now = std::chrono::steady_clock::now();
    long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastSwitch).count();

    long long minDelay = 250;
    long long maxDelay = 400;
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

    void *syncedWeapon = GetWeaponOnHand(localPlayer);
    if (syncedWeapon) Syns_SwapWeapon_Impl(localPlayer, syncedWeapon);
}

bool (*old_IsWeaponInAutoCharge)(void *instance);

bool IsWeaponInAutoCharge_Hook(void *instance) {

    if (MasterBool.autofire && instance != NULL && fireTapState.isActive) {

        return true;

    }

    return old_IsWeaponInAutoCharge(instance);

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



    // --- 1. MANUAL PRIORITY LOCK (Target List) ---

    // Rule: Always return locked enemy if alive, UNLESS we specifically want to skip them

    if (MasterBool.targetLock && lockedEnemy != nullptr && lockedEnemy != skipTarget) {

        if (!IsDieing(lockedEnemy) && GetHp(lockedEnemy) > 0) {

            persistentTarget = lockedEnemy;

            return lockedEnemy;

        }

    }



    // --- 2. PERSISTENT (STICKY) LOCK ---

    // Rule: Stay on current target if they are alive

    if (persistentTarget != nullptr) {

        if (!IsDieing(persistentTarget) && GetHp(persistentTarget) > 0) {

            // Check FOV bounds

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



    // --- 3. AUTO ACQUISITION (Find New Closest Visible) ---

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



    // --- SMART PRIORITY LOCK (360) ---

    if (MasterBool.targetLock && lockedEnemy != nullptr) {

        if (!IsDieing(lockedEnemy) && GetHp(lockedEnemy) > 0 && isVisible_Aimbot(lockedEnemy)) {

             return lockedEnemy; // Prioritize Locked Visible Target in 360 mode

        }

    }



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



void TeleDefender() {

    if (!MasterBool.teledifender)return;

    void *LocalPlayer = Current_Local_Player();

    if (!LocalPlayer) return;

    void *aimTarget = BestEnemyFind360();

    if (!aimTarget) return;

    Vector3 EnemyHeadPos = GetHeadPosition(aimTarget);

    Vector3 cam = CameraMain(LocalPlayer);

    float distance = Vector3::Distance(GetHeadPosition(LocalPlayer), EnemyHeadPos);

    Quaternion targetRotation = GetRotationToLocation(EnemyHeadPos, 0.0f, cam);

    if (!isEnemyInRangeWeapon(LocalPlayer, aimTarget, GetWeaponOnHand(LocalPlayer))) return;

    if (isVisible_Aimbot(aimTarget)) {

        set_aim(LocalPlayer, targetRotation);

    }

}





static monoString* get_NickName(void* player) {
    if (!player) return U3DStr("Enemy");
    monoString* n = nullptr;
    uintptr_t offOrig = _OriginalName;
    if (offOrig != 0) {
        n = *(monoString**)((uint64_t)player + offOrig);
    }
    if (!n) {
        uintptr_t offNick = _NickName;
        if (offNick != 0) {
            n = *(monoString**)((uint64_t)player + offNick);
        }
    }
    if (!n) {
        n = U3DStr("Enemy");
    }
    return n;
}

void RajaXModsCreditText() {  
    ShowCreditPopup(U3DStr("WonderLand Store | discord.gg/gavzAT99tR"));
}

void RajaxModsCreditText() {
    RajaXModsCreditText();
}

void RxmGetNickName(void* targetVivo)
{
    if ((MasterBool.enableESP || MasterBool.ActivateAll) && MasterBool.nickfuck)
    {
        void *LocalPlayer = Current_Local_Player();
        if (LocalPlayer != NULL) {
            void* targetEnemy = targetVivo;

            if (targetEnemy != nullptr)
            {
                if (MasterBool.nickfuck) {

                    void *ui = CurrentUIScene();
                    if (ui != NULL) {
                        Vector3 EnemyHeadPosition = GetHeadPosition(targetEnemy);
                        Vector3 LocalPlayerPos = CameraPosition(Current_Local_Player());

                        // Calculate distance
                        float distance = sqrtf(
                                (LocalPlayerPos.X - EnemyHeadPosition.X) * (LocalPlayerPos.X - EnemyHeadPosition.X) +
                                (LocalPlayerPos.Y - EnemyHeadPosition.Y) * (LocalPlayerPos.Y - EnemyHeadPosition.Y) +
                                (LocalPlayerPos.Z - EnemyHeadPosition.Z) * (LocalPlayerPos.Z - EnemyHeadPosition.Z)
                        );

                        monoString *nick = get_NickName(targetEnemy);
                        int enemyHp = GetHp(targetEnemy);
                        monoString *distances = U3DStrFormat(distance, enemyHp);
                        AddTeammateHud(ui, nick, distances);
                    }

                }

            }
        }
    }
    return;
}

void AESPName()
{
    ShowCenterUpTeammateTips(U3DStr("Copyright \xC2\xA9 WonderLand Store | Developed By onyxontop._"), 3.0f);
    RajaXModsCreditText();

    void *ClosestEnemys = GetEnemyInsideScreen();
    if (ClosestEnemys == nullptr && cachedTarget != nullptr) {
        ClosestEnemys = cachedTarget;
    }
    if (ClosestEnemys != nullptr) {
        RxmGetNickName(ClosestEnemys);
    }
}







void ApplyFlyMap(void* localPlayer) {

    if (!localPlayer) return;

    void *transform = Component_get_transform(localPlayer);

    if (!transform) return;



    // --- Priority 1: Teleport Map ---
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



    // --- Priority 2: Auto Teleport (Enemy) ---

    if (MasterBool.autoteleport) {

        void* closestTarget = BestEnemyFind360();

        if (closestTarget) {

            Vector3 gotten = Transform_INTERNAL_GetPosition(transform);

            Vector3 enemyPos = Transform_INTERNAL_GetPosition(Component_get_transform(closestTarget));

            float realDistance = sqrt(pow(enemyPos.X - gotten.X, 2) + pow(enemyPos.Y - gotten.Y, 2) + pow(enemyPos.Z - gotten.Z, 2));

            if (realDistance < 200.0f) {

                Vector3 coord;

                coord.X = enemyPos.X;

                coord.Y = enemyPos.Y;

                coord.Z = enemyPos.Z + 2.0f;

                Transform_set_position(transform, coord);

                return; // Skip other movement hacks this frame

            }

        }

    }



    // --- Priority 3: Flyhack ---

    if (MasterBool.flyhackop && !MasterBool.infinityFly) {

        Vector3 pos = Transform_INTERNAL_GetPosition(transform);

        pos.Y += 0.10f;

        Transform_set_position(transform, pos);

        return; // Skip FLY X40 if normal flyhack is active

    }

    // --- Priority 4: FLY X40 (3.96m altitude limit) ---

    static float groundY_x40 = 0.0f;
    static bool x40_initialized = false;
    const float heightLimit = 3.96f; // 13 feet in meters

    if (MasterBool.flyx40 && !MasterBool.infinityFly) {

        Vector3 pos = Transform_INTERNAL_GetPosition(transform);

        if (!x40_initialized) {
            groundY_x40 = pos.Y;
            x40_initialized = true;
        }

        float targetY = groundY_x40 + heightLimit;

        if (pos.Y < targetY) {
            pos.Y += 0.4f;
            if (pos.Y > targetY) {
                pos.Y = targetY;
            }
        } else {
            pos.Y = targetY;
        }

        Transform_set_position(transform, pos);

    } else {
        x40_initialized = false;
    }

}

void ApplyInfinityFly(void* localPlayer) {
    static bool flying = false;
    static float startGroundY = 0.0f;
    static float flyY = 0.0f;
    static const float riseSpeed = 0.40f;

    if (!localPlayer) {
        flying = false;
        return;
    }

    void *transform = Component_get_transform(localPlayer);
    if (!transform) {
        flying = false;
        return;
    }

    if (!MasterBool.infinityFly) {
        if (flying) {
            Vector3 pos = Transform_INTERNAL_GetPosition(transform);
            pos.Y = startGroundY;
            Transform_set_position(transform, pos);
            flying = false;
            startGroundY = 0.0f;
            flyY = 0.0f;
        }
        return;
    }

    Vector3 pos = Transform_INTERNAL_GetPosition(transform);
    if (!flying) {
        startGroundY = pos.Y;
        flyY = pos.Y;
        flying = true;
    }

    flyY += riseSpeed;
    pos.Y = flyY;
    Transform_set_position(transform, pos);
}



void ApplySnapFly(void* localPlayer) {

    // Skip Snap Fly if any teleport hack is active to prevent flickering

    if (MasterBool.mapateleport || MasterBool.autoteleport) return;



    static bool lastState = false;

    static std::chrono::steady_clock::time_point lastSnapTime;

    static bool isHoldingSnap = false;

    static float targetSnapX = 0.0f;

    static float targetSnapY = 0.0f;

    static float targetSnapZ = 0.0f;

    static std::chrono::steady_clock::time_point snapStartTime;



    static Vector3 lastPosBeforeSnap;

    static bool fakeFlyDetected = false;



    if (!MasterBool.snapfly) {

        lastState = false;

        isHoldingSnap = false;

        fakeFlyDetected = false;

        return;

    }



    void *transform = Component_get_transform(localPlayer);

    if (!transform) return;



    Vector3 pos = Transform_INTERNAL_GetPosition(transform);

    auto now = std::chrono::steady_clock::now();



    // --- Fake Fly Anti-Glitch Check ---

    if (isHoldingSnap) {

        auto elapsedHold = std::chrono::duration_cast<std::chrono::milliseconds>(now - snapStartTime).count();



        // After 300ms, if we are still near the ground height, it's a fake fly

        if (elapsedHold > 300 && elapsedHold < 400 && !fakeFlyDetected) {

            if (pos.Y < lastPosBeforeSnap.Y + 5.0f) {

                // FAKE FLY DETECTED: Auto-Resetting for retry

                isHoldingSnap = false;

                lastState = false;

                return;

            }

        }



        if (elapsedHold < 1200) {

            pos.X = targetSnapX;

            pos.Y = targetSnapY;

            pos.Z = targetSnapZ;

            Transform_set_position(transform, pos);

            return;

        } else {

            isHoldingSnap = false;

        }

    }



    // --- OP Stable Phase ---

    bool shouldSnap = false;

    if (!lastState) {

        shouldSnap = true;

        lastState = true;

        lastPosBeforeSnap = pos; // Save starting height

    }



    if (!shouldSnap) {

        targetSnapY -= 0.08f;

        pos.X = targetSnapX;

        pos.Y = targetSnapY;

        pos.Z = targetSnapZ;

        Transform_set_position(transform, pos);



        void* hitCollider = NULL;

        Vector3 groundCheck = pos;

        groundCheck.Y -= 1.8f;

        if (Physics_Raycast(pos, groundCheck, 12, &hitCollider)) {

            shouldSnap = true;

            lastPosBeforeSnap = pos;

        }

    }



    if (shouldSnap) {

        targetSnapX = pos.X;

        targetSnapY = pos.Y + 60.0f;

        targetSnapZ = pos.Z;



        // --- PHASE 1: THE BUMP (Break Grounding) ---

        // Move slightly up first to ensure server registers we are off-ground

        Vector3 bumpPos = pos;

        bumpPos.Y += 2.0f;

        Transform_set_position(transform, bumpPos);



        // --- PHASE 2: THE HAUL ---

        pos.X = targetSnapX;

        pos.Y = targetSnapY;

        pos.Z = targetSnapZ;

        Transform_set_position(transform, pos);



        isHoldingSnap = true;

        fakeFlyDetected = false;

        snapStartTime = now;

        lastSnapTime = now;

    }

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

                        noDelayPatch = false; // Reset others

                    }

                    return;

                }



                // Priority 2: Speed Timer (noDelay)

                if (MasterBool.noDelay) {

                    if (!noDelayPatch) {

                        *(float *) ((uintptr_t) timeService + _FixedDeltaTime) = 0.065f;

                        noDelayPatch = true;

                        SpeedTimerpatch = false; // Reset others

                    }

                    return;

                }



                // Reset to Normal if both OFF

                if (SpeedTimerpatch || noDelayPatch) {

                    *(float *) ((uintptr_t) timeService + _FixedDeltaTime) = 0.033f;

                    SpeedTimerpatch = false;

                    noDelayPatch = false;

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



// Catapult Fallbacks for FlyHack

static bool get_IsCatapultFalling(void* player) { return false; }

static void OnStopCatapultFalling(void* player) { }



// Simplified Vertical Teleport Fly (80 Units) - REAL FLY Version with Auto-Off





bool (*orig_IsVisible)(void *Player);

bool hook_IsVisible(void *Player) {

    return orig_IsVisible(Player);

}

void (*orig_UpdateBehavior)(void *Player);

void hook_UpdateBehavior(void *Player){

    orig_UpdateBehavior(Player);


    if (MasterBool.football) {
        if (Player == Current_Local_Player()) {
            AutoFootball();
        }
    }

    static bool lastAutoGliderState = false;

    if (MasterBool.autoGlider) {
        if (Player == Current_Local_Player()) {
            hilll_gliderbkc(Player);
            TriggerInfiniteGlide(Player);
            void* pTransform = Component_get_transform(Player);
            if (pTransform) {
                Vector3 currentPos = Transform_INTERNAL_GetPosition(pTransform);
                currentPos.Y += 0.8f;
                set_position_Injected(pTransform, currentPos);
            }
        }
        lastAutoGliderState = true;
    } else {
        if (lastAutoGliderState) {
            if (Player == Current_Local_Player()) {
                hilll_gliderbkc(Player);
            }
            lastAutoGliderState = false;
        }
    }

}



float (*orig_GetGravity)(void *Player);

float hook_GetGravity(void *Player){

    return orig_GetGravity(Player);

}



void (*orig_ShowDamage)(void* thiz, int damage, void* colliderT, void* p, int shieldDamage, int weaponID, float delay);
void hook_ShowDamage(void* thiz, int damage, void* colliderT, void* p, int shieldDamage, int weaponID, float delay) {
    if (MasterBool.hidedamage) {
        return;
    }
    orig_ShowDamage(thiz, damage, colliderT, p, shieldDamage, weaponID, delay);
}

bool (*orig_get_ShowDamageNum)(void* thiz);
bool hook_get_ShowDamageNum(void* thiz) {
    if (MasterBool.hidedamage) {
        return false;
    }
    return orig_get_ShowDamageNum(thiz);
}

bool (*orig_IsHighFPS120Open)();
bool hook_IsHighFPS120Open() {
    if (MasterBool.highfps) {
        return true;
    }
    return orig_IsHighFPS120Open();
}

bool (*orig_IsHighFPS144Open)();
bool hook_IsHighFPS144Open() {
    if (MasterBool.highfps) {
        return true;
    }
    return orig_IsHighFPS144Open();
}

bool (*orig_SpeedBypass)(void* instance);
bool hook_SpeedBypass(void* instance) {
    if (MasterBool.speedhackjoy) {
        return true;
    }
    return orig_SpeedBypass(instance);
}

bool (*orig_SpeedHack)(void* instance);
bool hook_SpeedHack(void* instance) {
    if (MasterBool.speedhackjoy) {
        return true;
    }
    return orig_SpeedHack(instance);
}



float(*FIRE_BACKUP)(void* thiz);

float FIRE_HOOK(void* thiz) {

    if (thiz != nullptr ) 
    {
        if (MasterBool.fastfuck){

            return 0.1f;
        }
    }
    return FIRE_BACKUP(thiz);
}



float(*SPEED_BACKUP)(void *thiz, int type);

float SPEED_HOOK(void* thiz, int type) {

    if (thiz != nullptr ) {

        if (MasterBool.fastfiremax) {

            return 0.35f;

        } else if (MasterBool.fastfireauto) {

            return 1.7f;

        }

    }

    return SPEED_BACKUP(thiz, type);

}



float(*FIRE_BACKUP_NEW)(void *thiz);

float FIRE_HOOK_NEW(void* thiz) {

    if (thiz != nullptr) {

        if (MasterBool.fireScaleHack && MasterBool.enableESP){

            return 0.1f;

        }

    }

    return FIRE_BACKUP_NEW(thiz);

}



std::chrono::steady_clock::time_point last_update_time = std::chrono::steady_clock::now();

static std::chrono::steady_clock::time_point last_update_time_exploit = std::chrono::steady_clock::now();

GCommon_AnimationRuntimeHandle_o *(*GetCurrentRunningHandler)(GCommon_AnimationSystemComponent_o *Instance,int32_t layerIndex);

GCommon_AnimationRuntimeHandle_o *_GetCurrentRunningHandler(GCommon_AnimationSystemComponent_o *Instance,int32_t layerIndex)

{

    if (Instance != nullptr && layerIndex == 0) {

        std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();

        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_update_time).count();

auto elapsed_time_exploit = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_update_time_exploit).count();





// 17ms tick + 0.1f step = same smoothness ratio as original 0.06f/10ms

        // (0.1/17 ≈ 0.006 m/ms = 6 m/s, small discrete steps = no visible jitter)

        if (elapsed_time_exploit > 17)

        {

            void *LocalPlayer = Current_Local_Player();

            if (LocalPlayer != nullptr) {

                FlyExploitSBG(LocalPlayer);

            }

            last_update_time_exploit = current_time;

        }



        if (!MasterBool.ActivateAll) return GetCurrentRunningHandler(Instance, layerIndex);

        if (elapsed_time > 35) {

            if (MasterBool.fastfireauto) {

                MasterBool.fastfiremax = MasterBool.autoswitch;

            }

            FastFireMaxTimer();



            cachedTarget360 = BestEnemyFind360();



            void *current_match = nullptr;

            void* StaticGameFacade = *(void**)((uint64_t)_GameFacade + _StaticClass);

            if (StaticGameFacade) {

                void *ClassMatchGame = *(void **) ((uint64_t) StaticGameFacade + _MatchGame);

                if (ClassMatchGame) {

                    current_match = *(void **) ((uint64_t) ClassMatchGame + _Match);

                }

            }



            // Maintenance and Persistence for Target Lock

            if (MasterBool.targetLock) {

                if (lockedEnemy != nullptr) {

                    bool isDown = (IsDieing(lockedEnemy) || GetHp(lockedEnemy) <= 0);

                    if (isDown) {

                        if (!wasLockedEnemyDown) {

                            ShowLowPopupMessage(U3DStr(OBFUSCATE("fucker knock")), 2.0f);

                            wasLockedEnemyDown = true;

                        }

                        lockedEnemy = nullptr; // Reset pointer but keep name for persistence

                    }

                } else if (lockedEnemyName[0] != '\0') {

                    // Try to re-lock by name (for next rounds)

                    auto players = GetEntities(current_match);

                    for (auto p : players) {

                        if (p && !IsLocalTeammate(p)) {

                            monoString *n = *(monoString **) ((uint64_t) p + _OriginalName);

                            if (n && n->toChars() != NULL && strcmp(n->toChars(), lockedEnemyName) == 0) {

                                if (!IsDieing(p) && GetHp(p) > 0) {

                                    lockedEnemy = p;

                                    wasLockedEnemyDown = false;

                                    break;

                                }

                            }

                        }

                    }

                }

            } else {

                lockedEnemyName[0] = '\0';

                lockedEnemy = nullptr;

            }



            // --- DYNAMIC SMART TRACKING SYSTEM ---

            void* prevTarget = cachedTarget;

            cachedTarget = nullptr; // Reset for dynamic search



            // Priority 1: Smart-Track the Locked Enemy

            if (MasterBool.targetLock && lockedEnemy != nullptr) {

                if (SmartEnemyMovementTracker(lockedEnemy, false)) {

                    cachedTarget = lockedEnemy;

                }

            }



            // Priority 2: Fallback to Best FOV Candidate if locked enemy is unpullable or no lock

            if (cachedTarget == nullptr) {

                void* bestFovCandidate = BestEnemyFind(lockedEnemy); // Skip locked enemy if they failed tracker

                if (bestFovCandidate != nullptr) {

                    if (SmartEnemyMovementTracker(bestFovCandidate, false)) {

                        cachedTarget = bestFovCandidate;

                    } else if (isVisible_Aimbot(bestFovCandidate)) {

                        // If tracker failed but they are naturally visible, take them anyway

                        cachedTarget = bestFovCandidate;

                    }

                }

            }



            // AutoFire Loop (Uses the synced tracker result)

            AutoFireLoop();

            BurstFireLoop();



            // PROACTIVE KILL (Safe Aimkill runs once in weapon block below)

            if (cachedTarget != nullptr && !MasterBool.SafeAimkill) {

                if (isVisible_Aimbot(cachedTarget) || MasterBool.smartmove || MasterBool.Aimkill || MasterBool.Aimkill360) {

                    StartAimKillV2(cachedTarget);

                }

            }

            AutoJumpLoop();

            EnableGhostHack();



            TeleDefender();

            AESPName();

            AutoRevive();

            FastSwitch();

            SuperFastAutoSwitchLoop1();

            AimkillSendAutoSwitchLoop();

            NormalAutoSwitchLoop();

            AutoExecute();



            void *LocalPlayer = Current_Local_Player();

            if (LocalPlayer != nullptr) {

                fastreload();



                ApplySnapFly(LocalPlayer);

                ApplyFlyMap(LocalPlayer);

                ApplyInfinityFly(LocalPlayer);

                void* weaponOnHand = GetWeaponOnHand(LocalPlayer);

                void *ClosestEnemyv2 = cachedTarget;

                void *ClosestEnemy360 = cachedTarget360;



                if (weaponOnHand != nullptr) {

                    if (MasterBool.SafeAimkill) {

                        void* safeEnemy = ClosestEnemyv2 ? ClosestEnemyv2 : ClosestEnemy360;

                        if (safeEnemy != nullptr && isEnemyInRangeWeapon(LocalPlayer, safeEnemy, weaponOnHand)) {

                            StartSafeAimkill(safeEnemy);

                        }

                    } else {

                        if (ClosestEnemyv2 != nullptr && (MasterBool.Aimkill || MasterBool.NoBulletTracking)) {

                            if (isEnemyInRangeWeapon(LocalPlayer, ClosestEnemyv2, weaponOnHand)) {

                                StartAimKillV2(ClosestEnemyv2);

                            }

                        }

                        if (ClosestEnemy360 != nullptr) {

                            if (isEnemyInRangeWeapon(LocalPlayer, ClosestEnemy360, weaponOnHand)) {

                                if (MasterBool.RealAimkillV2) {

                                    StartRealAimkillV2(ClosestEnemy360);

                                } else if (MasterBool.RealAimkill) {

                                    StartRealAimkill(ClosestEnemy360);

                                } else if (MasterBool.Aimkillsend) {

                                    StartAimKillSend(ClosestEnemy360);

                                } else if (MasterBool.Aimkill360) {

                                    StartAimKillV2(ClosestEnemy360);

                                }

                            }

                        }

                    }

                }



                void *ClosestEnemy = ClosestEnemyv2;

                if (ClosestEnemy != nullptr) {



                    if (MasterBool.Aimkilltp && ClosestEnemy != nullptr) {

                        Vector3 gotten = Transform_INTERNAL_GetPosition(Component_get_transform(LocalPlayer));

                        Vector3 enemyPos = Transform_INTERNAL_GetPosition(Component_get_transform(ClosestEnemy));

                        float realDistance = sqrt(pow(enemyPos.X - gotten.X, 2) +pow(enemyPos.Y - gotten.Y, 2) +pow(enemyPos.Z - gotten.Z, 2));

                        if (realDistance < 9.0f) {

                            Vector3 coord = gotten;

                            Transform_set_position(Component_get_transform(ClosestEnemy), coord);

                        }

                    }



                    if (MasterBool.Aimkilltpv2) {

                        //ghoston();

                        Vector3 gotten = Transform_INTERNAL_GetPosition(Component_get_transform(LocalPlayer));

                        Vector3 enemyPos = Transform_INTERNAL_GetPosition(Component_get_transform(ClosestEnemy));



                        float realDistance = sqrt(pow(enemyPos.X - gotten.X, 2) +pow(enemyPos.Y - gotten.Y, 2) +pow(enemyPos.Z - gotten.Z, 2));

                        if (realDistance < 200.0f) {

                            Vector3 coord;

                            coord.X = enemyPos.X;// ✅ Add 0.5f to X

                            coord.Y = enemyPos.Y;        // ✅ Keep Y same

                            coord.Z = enemyPos.Z + 1.5f; // ✅ Add 0.5f to Z

                            Transform_set_position(Component_get_transform(LocalPlayer), coord);

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

            }



            last_update_time = std::chrono::steady_clock::now();

        }

        return GetCurrentRunningHandler(Instance, layerIndex);



    }

    return GetCurrentRunningHandler(Instance,layerIndex);

}







// NoBulletTracking

bool (*NoBUlletTractOriginal)(void* weapon, COW_GamePlay_MADMMIICBNN_o *hitInfo);

bool NoBUlletTract(void* weapon, COW_GamePlay_MADMMIICBNN_o *hitInfo) {

    if (hitInfo == nullptr) {

        return NoBUlletTractOriginal ? NoBUlletTractOriginal(weapon, nullptr) : false;

    }



    if (MasterBool.enableESP && (MasterBool.NoBulletTracking || MasterBool.SafeSilentAim)) {

        void *LocalPlayer = Current_Local_Player();

        if (LocalPlayer != nullptr) {

            void *weaponOnHand = GetWeaponOnHand(LocalPlayer);

            if (weaponOnHand != nullptr) {

                void *ClosestEnemys = GetEnemyInsideScreen();

                if (ClosestEnemys != nullptr) {



                    void *enemyTF = Component_get_transform(ClosestEnemys);

                    Vector3 originalPos = {0.0f, 0.0f, 0.0f};

                    bool wasPulled = false;



                    if (enemyTF) {

                        originalPos = Transform_INTERNAL_GetPosition(enemyTF);

                    }



                    if ((MasterBool.smartmove || MasterBool.NoBulletTracking || MasterBool.SafeSilentAim) && !isVisible_Aimbot(ClosestEnemys)) {

                        if (MasterBool.SafeSilentAim) {

                            wasPulled = SafeSilentPull(ClosestEnemys, nullptr);

                        } else {

                            wasPulled = SilentGhostPullV2(ClosestEnemys, nullptr);

                        }

                    }



                    if(isVisible_Aimbot(ClosestEnemys)) {

                        void *HeadTF = TransformNode(*(void **) ((uint64_t) ClosestEnemys + _HeadTF));

                        if (HeadTF != nullptr) {

                            Vector3 EnemayHead = Transform_INTERNAL_GetPosition(HeadTF);

                            void *HeadTF2 = TransformNode(*(void **) ((uint64_t) LocalPlayer + _HeadTF));

                            if (HeadTF2 != nullptr) {

                                Vector3 LocalHead = Transform_INTERNAL_GetPosition(HeadTF2);



                                auto HeadCollider = get_HeadCollider(ClosestEnemys);

                                if (HeadCollider != nullptr) {

                                    void *headGameObj = get_gameObject(HeadCollider);

                                    if (headGameObj != nullptr) {

                                        *(void **) ((uint64_t) hitInfo + Hit_GameObject) = headGameObj;

                                        *(void **) ((uint64_t) hitInfo + Hit_HeadCollider) = HeadCollider;

                                        *(Vector3 *) ((uint64_t) hitInfo + Hit_HitLoc) = EnemayHead;

                                        *(Vector3 *) ((uint64_t) hitInfo + Hit_Normal) = EnemayHead;



                                        float v19 = EnemayHead.X - LocalHead.X;

                                        float dy = EnemayHead.Y - LocalHead.Y;

                                        float dz = EnemayHead.Z - LocalHead.Z;

                                        float v21 = sqrtf(v19 * v19 + dy * dy + dz * dz);

                                        Vector3 direction = {0, 0, 0};

                                        if (v21 > 0.001f) {

                                            direction.X = v19 / v21;

                                            direction.Y = dy / v21;

                                            direction.Z = dz / v21;

                                        }

                                        *(Vector3 *) ((uint64_t) hitInfo + Hit_RayDir) = direction;

                                        *(Vector3 *) ((uint64_t) hitInfo + Hit_StartPos) = LocalHead;

                                        *(Vector3 *) ((uint64_t) hitInfo + Hit_OrgStrtPos) = LocalHead;

                                        *(int *) ((uint64_t) hitInfo + Hit_Part) = 1;

                                        *(bool *) ((uint64_t) hitInfo + Hit_Ignore) = false;

                                    }

                                }

                            }

                        }

                    }



                    // CRITICAL: Call original function WHILE pulled

                    bool result = NoBUlletTractOriginal(weapon, hitInfo);



                    if (wasPulled && enemyTF) {

                        set_position_Injected(enemyTF, originalPos);

                    }



                    return result;

                }

            }

        }

    }

    return NoBUlletTractOriginal(weapon, hitInfo);

}





bool(*MedikitRun)(bool* instance);

bool _MedikitRun(bool* instance)  {

    return (MasterBool.medikitrun) ? false : MedikitRun(instance);

}

bool(*DoubleGun)(bool* instance);

bool _DoubleGun(bool* instance){

    return (MasterBool.doublegun) ? true : DoubleGun(instance);

}



bool (*ResetGuest)(bool* instance);

bool _ResetGuest(bool* instance) {

    return (MasterBool.resetguest) ? true : ResetGuest(instance);

}



typedef int (*CalcRealDamage_fn)(float, void*, void*, void*, void*, int, void*, void*, float, uint32_t);

static CalcRealDamage_fn orig_CalcRealDamage = nullptr;

static int hook_CalcRealDamage(float baseDamage, void* hitPart, void* damageInfo, void* damager, void* beDamager, int weaponDataID, void* damagerWeaponDynamicInfo, void* weapon, float overrideHeadshot, uint32_t flag) {

    int result = orig_CalcRealDamage(baseDamage, hitPart, damageInfo, damager, beDamager, weaponDataID, damagerWeaponDynamicInfo, weapon, overrideHeadshot, flag);

    if ((MasterBool.Aimkill || MasterBool.Aimkill360) && result > 0) {

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
    if (instance != nullptr && instance == localPlayer && MasterBool.enableESP) {
        if (MasterBool.speedrun) {
            return 9.0f;
        }
    }
    return old_GetCurrentDashSpeed(instance);
}



static bool (*O_get_isGrounded)(void* instance);

bool Hook_get_isGrounded(void* instance) {

    if (MasterBool.flyhackop || MasterBool.snapfly || MasterBool.FlyUp == 1) {

        return true;

    }

    return O_get_isGrounded(instance);

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

            DobbyHook((void*) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.PhysicsModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("CharacterController"),OBFUSCATE("get_isGrounded"),0),(void*)Hook_get_isGrounded,(void**)&O_get_isGrounded);



            //DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("ELMGJKHIIAA"), OBFUSCATE("EIHCOMDNIGJ"), 10), (void *)hook_CalcRealDamage, (void **)&orig_CalcRealDamage);

            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"),OBFUSCATE("IsWeaponInAutoCharge"), 0),(void *) IsWeaponInAutoCharge_Hook, (void **) &old_IsWeaponInAutoCharge);

            DobbyHook((void *) offset_SetStartDamage, (void *) NoBUlletTract,(void **) &NoBUlletTractOriginal);

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

            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player.FGAHFBDAKPI"), OBFUSCATE("DAKCCEIPDFI"), 0), (void *)hook_GetGravity, (void **) &orig_GetGravity);

            DobbyHook((void*)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_ShowDamageNum"), 0), (void*)hook_get_ShowDamageNum, (void**)&orig_get_ShowDamageNum);     
            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.HUD"), OBFUSCATE("UIHudNameController"), OBFUSCATE("ShowDamage"), 6), (void *)hook_ShowDamage, (void **) &orig_ShowDamage);
            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameSettingData"), OBFUSCATE("IsHighFPS120Open"), 0), (void *)hook_IsHighFPS120Open, (void **) &orig_IsHighFPS120Open);
            DobbyHook((void *) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameSettingData"), OBFUSCATE("IsHighFPS144Open"), 0), (void *)hook_IsHighFPS144Open, (void **) &orig_IsHighFPS144Open);
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

            const char* greet = "UNFAIR_CHEAT_AIMKILLv2_READY";

            controlServer.send((void*)greet, strlen(greet));



            while (true) {

                int bytes = controlServer.receive(buffer, sizeof(buffer) - 1);

                if (bytes <= 0) break;

                buffer[bytes] = '\0';

                LOGI("C# CMD: %s", buffer);



                // // ===== STATUS =====

                // if (strcmp(buffer, "GETSTATUS") == 0) {

                //     char statusMsg[512];

                //     snprintf(statusMsg, sizeof(statusMsg),

                //         "STATUS ESP=%d SILENTAIM=%d AIMKILL=%d AIMKILLTP=%d "

                //         "AIMKILLTPV2=%d AIMKILL360=%d AIMKILLROTATE=%d DOWNAIMKILL=%d "

                //         "RAPIDFIRE=%d FASTRELOAD=%d AIMBOTBODY=%d AIMBODY=%d "

                //         "SPEEDHACK=%d FLYHACK=%d WALLHACK=%d GHOST=%d FOV=%.1f",

                //         MasterBool.enableESP ? 1 : 0,

                //         MasterBool.SafeSilentAim ? 1 : 0,

                //         MasterBool.Aimkill ? 1 : 0,

                //         MasterBool.Aimkilltp ? 1 : 0,

                //         MasterBool.Aimkilltpv2 ? 1 : 0,

                //         MasterBool.Aimkill360 ? 1 : 0,

                //         MasterBool.Aimkillrotate ? 1 : 0,

                //         MasterBool.downaimkill ? 1 : 0,

                //         MasterBool.rapidFire ? 1 : 0,

                //         MasterBool.fastReload ? 1 : 0,

                //         MasterBool.aimbotbody ? 1 : 0,

                //         MasterBool.aimbody ? 1 : 0,

                //         MasterBool.speedHack ? 1 : 0,

                //         MasterBool.flyhackop ? 1 : 0,

                //         MasterBool.wallHack ? 1 : 0,

                //         MasterBool.ghoston ? 1 : 0,

                //         MasterBool.aimbotFOV

                //     );

                //     controlServer.send((void*)statusMsg, strlen(statusMsg));

                //     continue;

                // }



                if (strcmp(buffer, "ENABLE_ALL_ON") == 0) {

                    MasterBool.enableESP = true;

                    LOGI("ENABLE_ALL Enabled");

                }

                else if (strcmp(buffer, "ENABLE_ALL_OFF") == 0) {

                    MasterBool.enableESP = false;

                    LOGI("ENABLE_ALL Disabled");

                }

                else if (strcmp(buffer, "SILENT_AIM_ON") == 0) {

                    MasterBool.NoBulletTracking = true;

                    LOGI("Silent Aim Enabled");

                }

                else if (strcmp(buffer, "SILENT_AIM_OFF") == 0) {

                    MasterBool.NoBulletTracking = false;

                    LOGI("Silent Aim Disabled");

                }

                else if (strcmp(buffer, "COVER_PULL_ON") == 0) {

                    MasterBool.smartmove = true;

                    LOGI("Cover Pull Enabled");

                }

                else if (strcmp(buffer, "COVER_PULL_OFF") == 0) {

                    MasterBool.smartmove = false;

                    LOGI("Cover Pull Disabled");

                }

                else if (strcmp(buffer, "AIMLOCK_ON") == 0) {

                    MasterBool.teledifender = true;

                    LOGI("Aimlock Enabled");

                }

                else if (strcmp(buffer, "AIMLOCK_OFF") == 0) {

                    MasterBool.teledifender = false;

                    LOGI("Aimlock Disabled");

                }

                else if (strcmp(buffer, "TARGET_LOCK_ON") == 0) {

                    MasterBool.targetLock = true;

                    LOGI("Target Lock Enabled");

                }

                else if (strcmp(buffer, "TARGET_LOCK_OFF") == 0) {

                    MasterBool.targetLock = false;

                    LOGI("Target Lock Disabled");

                }

                else if (strcmp(buffer, "AUTO_EXECUTE_ON") == 0) {

                    MasterBool.autoexecute = true;

                    LOGI("Auto Execute Enabled");

                }

                else if (strcmp(buffer, "AUTO_EXECUTE_OFF") == 0) {

                    MasterBool.autoexecute = false;

                    LOGI("Auto Execute Disabled");

                }

                else if (strcmp(buffer, "SNAPFLY_ON") == 0) {

                    MasterBool.snapfly = true;

                    LOGI("Snapfly Enabled");

                }

                else if (strcmp(buffer, "SNAPFLY_OFF") == 0) {

                    MasterBool.snapfly = false;

                    LOGI("Snapfly Disabled");

                }

                else if (strcmp(buffer, "AUTO_REVIVE_ON") == 0) {

                    MasterBool.autorevive = true;

                    LOGI("Auto Revive Enabled");

                }

                else if (strcmp(buffer, "AUTO_REVIVE_OFF") == 0) {

                    MasterBool.autorevive = false;

                    LOGI("Auto Revive Disabled");

                }

                else if (strcmp(buffer, "SPEED_TIMER_ON") == 0) {

                    MasterBool.noDelay = true;

                    LOGI("Speed Timer Enabled");

                }

                else if (strcmp(buffer, "SPEED_TIMER_OFF") == 0) {

                    MasterBool.noDelay = false;

                    LOGI("Speed Timer Disabled");

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

                else if (strcmp(buffer, "AUTOFIRE_WINCHESTER_ON") == 0) {

                    MasterBool.autofireslow = true;

                    MasterBool.fastfiremax = true;

                    MasterBool.noreloadfck = true;

                    LOGI("Autofire Winchester Enabled");

                }

                else if (strcmp(buffer, "AUTOFIRE_WINCHESTER_OFF") == 0) {

                    MasterBool.autofireslow = false;

                    MasterBool.fastfiremax = false;

                    MasterBool.noreloadfck = false;

                    LOGI("Autofire Winchester Disabled");

                }

                else if (strcmp(buffer, "FAST_FIRE_ON") == 0) {

                    MasterBool.fireScaleHack = true;

                    LOGI("Fast Fire Enabled");

                }

                else if (strcmp(buffer, "FAST_FIRE_OFF") == 0) {

                    MasterBool.fireScaleHack = false;

                    LOGI("Fast Fire Disabled");

                }

                else if (strcmp(buffer, "FLYHACK_ON") == 0) {

                    MasterBool.flyhackop = true;

                    LOGI("Flyhack Enabled");

                }

                else if (strcmp(buffer, "FLYHACK_OFF") == 0) {

                    MasterBool.flyhackop = false;

                    LOGI("Flyhack Disabled");

                }

                else if (strcmp(buffer, "MAP_TELEPORT_ON") == 0) {

                    MasterBool.mapateleport = true;

                    LOGI("Map Teleport Enabled");

                }

                else if (strcmp(buffer, "MAP_TELEPORT_OFF") == 0) {

                    MasterBool.mapateleport = false;

                    LOGI("Map Teleport Disabled");

                }

                else if (strcmp(buffer, "TELEPORT_ENEMY_ON") == 0) {

                    MasterBool.autoteleport = true;

                    LOGI("Teleport Enemy Enabled");

                }

                else if (strcmp(buffer, "TELEPORT_ENEMY_OFF") == 0) {

                    MasterBool.autoteleport = false;

                    LOGI("Teleport Enemy Disabled");

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



// =====================================================================

// Constructor - starts all threads when lib loads

// =====================================================================

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