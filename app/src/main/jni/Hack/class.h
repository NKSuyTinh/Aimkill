#ifndef ANDROID_MOD_MENU_HOOK_H
#define ANDROID_MOD_MENU_HOOK_H
#include <AutoUpdate/Il2Cppp.h>
#include "Hack/il2cpp.h"














#define offset_getdamage (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FDAEPHMIEPC"), OBFUSCATE("BAPINEFALEM"), 0)


#define offset_WeaponOnHand (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetWeaponOnHand"), 0)

#define SwapWeaponnn (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("SwapWeapon"), 2)


#define offset_CurrentGameSimulationTimer \
Il2CppGetMethodOffset("Assembly-CSharp.dll","COW","GameFacade","CurrentGameSimulationTimer",0)


#define offset_swapweaopon (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("SwapWeapon"), 3)


#define offset_GameFacade_Send (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("Send"), 4)


#define offset_GKHECDLGAJA (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("KNBEPECEJEP"), 1)


#define offset_Transform_INTERNAL_GetPosition (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position_Injected"), 1)

#define offset_Component_GetTransform (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)


#define offset_HeadTF2 (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetHeadTF"), 0)


#define offset_get_main (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_main"), 0)

#define offset_WorldToScreenPoint (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("WorldToScreenPoint"), 1)


#define offset_get_forward (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_forward"), 0)


#define offset_GetHp (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_CurHP"), 0)

#define offset_FireIntervalScale (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerAttributes"), OBFUSCATE("set_FireIntervalScale"), 1)

#define offset_Attribute (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("KDJHNBAECLM"))

#define offset_NoReload (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerAttributes"), OBFUSCATE("ShootNoReload"))


#define offset_LAEMLAPIAFD (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FDAEPHMIEPC"), OBFUSCATE("DJMMOHAJFPB"))
#define offset_POBGKMDJMDC (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("AGACNOCEEFP"), OBFUSCATE("FPANKJIJBIH"))

#define uniqueid (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("LGMNCCAPNHJ"), OBFUSCATE("DEGODFCOKGC"))
#define GetUniqueID(WeaponHand) *(uint32_t*)((uint64_t)WeaponHand + uniqueid)


#define get_LHGGPDLOPAH (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("KANJBNIANHC"),OBFUSCATE("COGCJKJPPHI"),1)

#define offset_set_aim (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("ADHOBODJNED"), 1)


#define offset_set_rotation (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("set_rotation"), 1)

#define offset_get_rotation (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_rotation"), 0)

#define offset_get_forward (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_forward"), 0)

#define offset_set_localScale (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("set_localScale"), 1)

#define offset_get_IsSighting (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsSighting"), 0)

#define offset_get_IsFiringFromPRI (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsFiringFromPRI"), 0)


#define offset_Transform_SetPosition (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("set_position"), 1)

#define offset_SetResolution (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("SetResolution"), 4)

#define offset_get_isVisible (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsVisible"), 0)


#define offset_IsLocalTeammate (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsLocalTeammate"), 1)


#define offset_TransformNode (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("TransformNode"), OBFUSCATE("get_transform"), 0)

#define offset_Curent_Match (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentMatch"), 0)

#define offset_Current_Local_Player (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentLocalPlayer"), 0)

#define offset_get_isVisibleMoita (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsStreamerVisible"), 0)

#define offset_get_IsDieing (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsDieing"), 0)

#define offset_itemid (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("LGMNCCAPNHJ"), OBFUSCATE("LJIPAJAMCKK"), 0)



#define offset_PhysXData (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_MyPhsXData"), 0)


#define offset_get_HeadCollider (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_HeadCollider"), 0)

#define offset_get_gameObject (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_gameObject"), 0)


#define offset_Physics_Raycast (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("HPFKOGPDBBE"), OBFUSCATE("KPEIJLDPGEJ"), 4)

#define offset_HeadTF (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("PEMOFNFCLFB"))


#define offset_CurrentGameSimulationTimer (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentGameSimulationTimer"),0)


#define u3str (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("mscorlib.dll"), OBFUSCATE("System"), OBFUSCATE("String"), OBFUSCATE("CreateString"), 1)


#define m_currentUi Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentInGameUIScene"), 0)


#define ShowDynamicupMessage (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowDynamicPopupMessage"), 2)


#define offset_ShowLowPopupMessage (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowLowPopupMessage"), 2)


#define offset_ShowPopupNoAnim (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowPopupMessageNoAnim"), 2)


#define offset_ShowTeammateTips (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowCenterUpTeammateTips"), 2)


#define offset_JumpBtnCtrl (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("m_JumpBtnCtrl"))


#define offset_AuxfireCtrl (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("m_AuxfireCtrl"))


#define offset_BaseCtrl_OnBtnUp (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudButtonBaseController"), OBFUSCATE("OnBtnUp"), 0)


#define offset_FireButton_OnBtnDown (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudFireController"), OBFUSCATE("OnBtnDown"), 0)


#define offset_BaseCtrl_OnBtnDown (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudJumpController"), OBFUSCATE("OnBtnDown"), 0)

#define offset_get_realtimeSinceStartup  (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Time"),OBFUSCATE("get_realtimeSinceStartup"),0)


#define offset_GetRange (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FDAEPHMIEPC"), OBFUSCATE("CGFPKFGGLIE"),0)


#define m_addTeamHud Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowAssistantText"), 2)

#define _MainCameraTransform (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("MainCameraTransform"))


#define offset_PlayerID (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_PlayerID"),0)


#define offset_CFFPIACECIG (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("BHGGAEEHJCO"), OBFUSCATE("LMCLIKOCCJM"),1)


#define offset_SyncSwapWeapon (uintptr_t) Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JDIHDLDIMCK"))
#define offset_IHAAMHPPLMG_s (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JDIHDLDIMCK"), OBFUSCATE("BHGGAEEHJCO"))
#define offset_DGLCOGJJFMI_s (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JDIHDLDIMCK"), OBFUSCATE("DBPPPOBFJNP"))

 
#define SetStartDamageV (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FDAEPHMIEPC"),OBFUSCATE("KOODEKEKFEK"),1)


#define GetTypeWeaponV  (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FDAEPHMIEPC"),OBFUSCATE("GELOIHCDLGC"),0)


#define get_timeV  (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Time"),OBFUSCATE("get_time"),0)


#define StartWholeBodyFiringV  (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"),OBFUSCATE("StartWholeBodyFiring"),1)

#define offset_get_IsFiringFromPRI (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsFiringFromPRI"), 0)

#define offset_StartFiring (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("StartFiring"),1)


#define offset_PlayerNetwork_StopFire (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("StopFire"), 1)


#define offset_UGCRequestJump (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("UGCRequestJump"))

#define offset_GetPhysXState (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetPhysXState"), 0)
















#define offset_SetOrgModelVisible (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("SetOrgModelVisible"), 1)

static void SetOrgModelVisible(void* player, bool visible) {
    if (!player) return;
    void (*_SetOrgModelVisible)(void*, bool) = (void (*)(void*, bool))offset_SetOrgModelVisible;
    if (_SetOrgModelVisible) _SetOrgModelVisible(player, visible);
}

//#define offset_getdamage (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GPBDEDFKJNA"), OBFUSCATE("MEMAEFCDOFL"), 0)
static int GetDamage(void *pthis)
{
    return ((int (*)(void *))offset_getdamage)(pthis);
}

//#define offset_WeaponOnHand (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetWeaponOnHand"), 0)
static void *GetWeaponOnHand(void *local) {
    void *(*GetWeaponOnHand)(void *local) = (void *(*)(void *))offset_WeaponOnHand;
    return GetWeaponOnHand(local);
}
//#define SwapWeaponnn (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("SwapWeapon"), 2)

static void SwapWeaponn(void* player, int POFFNNMOOBM, bool GDKLMFLNNGM) {
    void (*_SwapWeaponn)(void* player, int POFFNNMOOBM, bool GDKLMFLNNGM) = (void (*)(void *, int, bool))(SwapWeaponnn);
    _SwapWeaponn(player, POFFNNMOOBM, GDKLMFLNNGM);
}

#include "Hack/Memory.h"


//#define offset_CurrentGameSimulationTimer \
Il2CppGetMethodOffset("Assembly-CSharp.dll","COW","GameFacade","CurrentGameSimulationTimer",0)

static void* GetTimeService()
{
    typedef void* (*fn)(const MethodInfo*);
    auto func = (fn)offset_CurrentGameSimulationTimer;
    return func ? func(nullptr) : nullptr;
}

uint32_t GetCurrentTick()
{
    void* timeService = GetTimeService();
    if (!timeService)
        return 0;
    return *(uint32_t*)((uintptr_t)timeService + 0x18);
}

typedef void* (*uint32_ToString_t)(uint32_t* instance);

typedef void* (*NPLKBIKNMLH_t)(void* listPtr, void* stringPtr);

void* GCommon_Checker_SendToServer(uint32_t myValue) {
    uint32_ToString_t ToString = (uint32_ToString_t)getRealOffset(0x8A64560);
    NPLKBIKNMLH_t EncryptFunc = (NPLKBIKNMLH_t)getRealOffset(0x6ACA1F4);
    typedef void* (*il2cpp_new_object_t)(uintptr_t klass);
    auto il2cpp_new_object = (il2cpp_new_object_t)getRealOffset(0x430D95C);
    // Search RVA for: System.Collections.Generic.List<byte>..ctor()
    typedef void (*List_ctor_t)(void* instance);
    auto List_ctor = (List_ctor_t)getRealOffset(0x821E9B0);
    void* monoString = ToString(&myValue);
    uintptr_t listKlassPtr = *(uintptr_t*)(getRealOffset(0x991B294) + 0x0);
    if (listKlassPtr && il2cpp_new_object) {
        void* myByteList = il2cpp_new_object(listKlassPtr);
        if (myByteList != nullptr) {
            if (List_ctor) List_ctor(myByteList);
            if (monoString != nullptr) {
                return EncryptFunc(myByteList, monoString);
            }
        }
    }
    return nullptr;
}

//#define offset_swapweaopon (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("SwapWeapon"), 3)
void SwapWeapon(void *Pthis,int32_t FANMJANBFIL,bool GDKLMFLNNGM)
{
    return ((void (*)(void *,int,bool,void*))offset_swapweaopon)(Pthis,FANMJANBFIL,GDKLMFLNNGM,nullptr);
}

//#define offset_GameFacade_Send (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("Send"), 4)
bool GameFacade_Send(uint32_t messageID,void *msg,uint8_t sendOption,bool cacheMsgAnyWay)
{
    return ((bool (*)(uint32_t,void *,uint8_t,bool))offset_GameFacade_Send)(messageID,msg,sendOption,cacheMsgAnyWay);
}

//#define offset_GKHECDLGAJA (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GKHECDLGAJA"), 1)
void *GKHECDLGAJA(void *pthis, void* a1)
{
    return ((void* (*)(void *,void *))offset_GKHECDLGAJA)(pthis,a1);
}

//#define offset_Transform_INTERNAL_GetPosition (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position_Injected"), 1)
static Vector3 Transform_INTERNAL_GetPosition(void *player)
{
    Vector3 out = Vector3::Zero();
    void (*_Transform_INTERNAL_GetPosition)(void *transform, Vector3 * out) = (void (*)(void *, Vector3 *))offset_Transform_INTERNAL_GetPosition;
    _Transform_INTERNAL_GetPosition(player, &out);
    return out;
}

//#define offset_Component_GetTransform (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)
static void *Component_get_transform(void *player)
{
    void *(*_Component_GetTransform)(void *nullo) = (void *(*)(void *))offset_Component_GetTransform;
    return _Component_GetTransform(player);
}

//#define offset_HeadTF2 (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetHeadTF"), 0)
static void *GetHeadTF(void* player) {
    void *(*_GetHeadTF)(void *_this) = (void *(*)(void *))offset_HeadTF2;
    return _GetHeadTF(player);
}

Vector3 GetHeadPosition(void* player) {
    if (!player) return Vector3::Zero();
    void* head = GetHeadTF(player);
    if (!head) return Vector3::Zero();
    void* tf = Component_get_transform(head);
    if (!tf) return Vector3::Zero();
    return Transform_INTERNAL_GetPosition(tf);
}

//#define offset_get_main (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_main"), 0)
static void *get_main() {
    void *(*nget_main)(void *Instance) = (void *(*)(void *))offset_get_main;
    return nget_main(nullptr);
}

//#define offset_WorldToScreenPoint (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("WorldToScreenPoint"), 1)
Vector3 WorldToScreenPoint(Vector3 pos) {
    auto main = get_main();
    if (main) {
        auto Camera_WorldToScreenPoint = (Vector3 (*)(void *, Vector3))offset_WorldToScreenPoint;
        return Camera_WorldToScreenPoint(main, pos);
    }
    return {0, 0, 0};
}

//#define offset_get_forward (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_forward"), 0)
static Vector3 GetForward(void *player) {
    Vector3 (*NGetForward)(void *players) = (Vector3 (*)(void *))offset_get_forward;
    return NGetForward(player);
}

//#define offset_GetHp (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_CurHP"), 0)
static int GetHp(void *instance) {
    return ((int (*)(void *)) offset_GetHp)(instance);
}

//#define offset_FireIntervalScale (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerAttributes"), OBFUSCATE("set_FireIntervalScale"), 1)
//#define offset_Attribute (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("JKPFFNEMJIF"))
//#define offset_NoReload (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerAttributes"), OBFUSCATE("ShootNoReload"))
static void set_FireIntervalScale(void *player, float VALUE) {
    void *attru = *(void **) ((uint64_t) player + offset_Attribute);
//    *(bool *) ((uint64_t) attru + offset_NoReload) = true;
//    *(bool *) ((uint64_t) attru + 0xd8) = true;
    void (*_set_FireIntervalScale)(void *attru, float VALUE) = (void (*)(void *, float))offset_FireIntervalScale;
    _set_FireIntervalScale(attru, VALUE);
}

//#define offset_LAEMLAPIAFD (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GPBDEDFKJNA"), OBFUSCATE("LAEMLAPIAFD"))
//#define offset_POBGKMDJMDC (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("OOIPMACFIFL"), OBFUSCATE("POBGKMDJMDC"))
uintptr_t GetWeaponDataId(void *WeaponOnHand) {
    return *(int*)((uintptr_t)*(void**)((uintptr_t)WeaponOnHand + offset_LAEMLAPIAFD) + offset_POBGKMDJMDC);
}

//#define uniqueid (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("KOGBJLFDJHC"), OBFUSCATE("JDPDFBINIJE"))
//#define GetUniqueID(WeaponHand) *(uint32_t*)((uint64_t)WeaponHand + uniqueid)

//static uint32_t GetUniqueID(uintptr_t WeaponHand) {
//if (WeaponHand == 0) return 0;
//return *(uint32_t*)(WeaponHand + uniqueid);
//}

//#define get_LHGGPDLOPAH (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("LLOABGDLMGK"),OBFUSCATE("LHGGPDLOPAH"),1)
message_DEACEIFBHJK_o *LHGGPDLOPAH(Vector3 JOGHOHLEJFL) {
    return ((message_DEACEIFBHJK_o * (*)(Vector3))get_LHGGPDLOPAH)(JOGHOHLEJFL);
}

//#define offset_set_aim (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("JPNJCAONHME"), 1)
static void set_aim(void *player, Quaternion look) {
    void (*_set_aim)(void *player, Quaternion look) = (void (*)(void *, Quaternion))offset_set_aim;
    _set_aim(player, look);
}

//#define offset_set_rotation (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("set_rotation"), 1)
static void Transform_set_rotation(void *player, Quaternion look) {
    void (*_Transform_set_rotation)(void *player, Quaternion look) = (void (*)(void *, Quaternion))offset_set_rotation;
    _Transform_set_rotation(player, look);
}

//#define offset_get_rotation (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_rotation"), 0)
static Quaternion Transform_get_rotation(void *transform) {

    if (!transform) return {0, 0, 0, 1};
    Quaternion (*_Transform_get_rotation)(void *tf) = (Quaternion (*)(void *)) offset_get_rotation;
    return _Transform_get_rotation(transform);
}

//#define offset_get_forward (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_forward"), 0)
static Vector3 Transform_get_forward(void *transform) {
    if (!transform) return {0, 0, 0};
    Vector3 (*_Transform_get_forward)(void *tf) = (Vector3 (*)(void *)) offset_get_forward;
    return _Transform_get_forward(transform);
}

//#define offset_get_IsSighting (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsSighting"), 0)
static bool get_IsSighting(void *player) {
    bool (*_get_IsSighting)(void *players) = (bool (*)(void *))offset_get_IsSighting;
    return _get_IsSighting(player);
}
//#define offset_get_IsFiringFromPRI (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsFiringFromPRI"), 0)
static bool IsFiringPlayer(void *player) {
    bool (*_IsFiringPlayer)(void *players) = (bool (*)(void *))offset_get_IsFiringFromPRI;
    return _IsFiringPlayer(player);
}

//#define offset_Transform_SetPosition (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("set_position"), 1)
static void Transform_set_position(void *player, Vector3 inn)
{
    if (!player) return;
    void (*_Transform_SetPosition)(void *transform, Vector3 in) = (void (*)(void *, Vector3))offset_Transform_SetPosition;
    if (!_Transform_SetPosition) return;
    _Transform_SetPosition(player, inn);
}

static void Transform_set_localScale(void *transform, Vector3 scale)
{
    if (!transform) return;
    void (*_Transform_set_localScale)(void *, Vector3) = (void (*)(void *, Vector3))offset_set_localScale;
    if (!_Transform_set_localScale) return;
    _Transform_set_localScale(transform, scale);
}

//#define offset_SetResolution (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("SetResolution"), 4)
static void SetResolution(int32_t width, int32_t height, int32_t fullscreenMode, int32_t preferredRefreshRate)
{
    void (*_SetResolution)(int32_t width, int32_t height, int32_t fullscreenMode, int32_t preferredRefreshRate) = (void (*)(int32_t,int32_t,int32_t,int32_t))offset_SetResolution;
    return _SetResolution(width,height,fullscreenMode,preferredRefreshRate);
}

//#define offset_get_isVisible (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsVisible"), 0)
static bool get_isVisible(void *player) {
    bool (*Nget_isVisible)(void *players) = (bool (*)(void *))offset_get_isVisible;
    return Nget_isVisible(player);
}

//#define offset_IsLocalTeammate (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsLocalTeammate"), 1)
static bool IsLocalTeammate(void *instance) {
    return ((bool (*)(void *)) offset_IsLocalTeammate)(instance);
}

static Vector3 CameraPosition(void *player)
{
    return Transform_INTERNAL_GetPosition(Component_get_transform(get_main()));
}

//#define offset_TransformNode (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("TransformNode"), OBFUSCATE("get_transform"), 0)
void* TransformNode(void *_this)
{
    return ((void* (*)(void *))offset_TransformNode)(_this);
}

//#define offset_Curent_Match (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentMatch"), 0)
static void* Current_Match() {
    using MatchFn = void*(*)(void*);
    return ((MatchFn)offset_Curent_Match)(nullptr);
}

//#define offset_Current_Local_Player (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentLocalPlayer"), 0)
static void *Current_Local_Player() {
    void *(*_Local_Player)(void *players) = (void *(*)(void *))offset_Current_Local_Player;
    return _Local_Player(NULL);
}

//#define offset_get_isVisibleMoita (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsStreamerVisible"), 0)
static bool IsStreamerVisible(void *player) {
    bool (*_IsStreamerVisible)(void *players) = (bool (*)(void *))offset_get_isVisibleMoita;
    return _IsStreamerVisible(player);
}
//#define offset_get_IsDieing (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsDieing"), 0)
static bool IsDieing(void *player) {
    if (!player) return false;
    bool (*_IsDieing)(void *players) = (bool (*)(void *))offset_get_IsDieing;
    return _IsDieing ? _IsDieing(player) : false;
}

//#define offset_itemid (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("KOGBJLFDJHC"), OBFUSCATE("IDOGDPOPGAI"), 0)
static int GetWeaponID(void* enemy) {
    int (*GetWeapon)(void *player) = (int(*)(void *))offset_itemid;
    return GetWeapon(enemy);
}

typedef int(*TakeDamageFn)(void*,int,void*,void*,int,Vector3,Vector3,void*,void*,uint32_t,MethodInfo*);
TakeDamageFn GetTakeDamageFn(void* player, MethodInfo** outMethod)
{
    if (!player) return nullptr;
    Il2CppClass* klass = *(Il2CppClass**)player;
    if (!klass) return nullptr;
    VirtualInvokeData vid = klass->vtable[171];
    if (!vid.methodPtr) return nullptr;
    if (outMethod)*outMethod = (MethodInfo*)vid.method;
    return (TakeDamageFn)vid.methodPtr;
}
int Call_TakeDamage(void* player,int damage,void* attacker,void* damageInfo,int weaponID,Vector3 firePos,Vector3 hitPos,void* params,void* extra,uint32_t flags)
{
    if (!player) return 0;
    MethodInfo* method = nullptr;
    TakeDamageFn fn = GetTakeDamageFn(player, &method);
    if (!fn) return 0;
    return fn(player,damage,attacker,damageInfo,weaponID,firePos,hitPos,params,extra,flags,method);
}


//#define offset_PhysXData (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_MyPhsXData"), 0)
static void *get_MyPhsXData(void *player) {
    void *(*_get_MyPhsXData)(void *players) = (void *(*)(void *))offset_PhysXData;
    return _get_MyPhsXData(player);
}

//#define offset_get_HeadCollider (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_HeadCollider"), 0)
void *get_HeadCollider(void *pthis)
{
    return ((void* (*)(void *))offset_get_HeadCollider)(pthis);
}
//#define offset_get_gameObject (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_gameObject"), 0)
void *get_gameObject(void *Pthis)
{
    return ((void* (*)(void *))offset_get_gameObject)(Pthis);
}

//#define offset_Physics_Raycast (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("JEAGCMACNNC"), OBFUSCATE("JJCJBPLPGOO"), 4)
static bool Physics_Raycast(Vector3 camLocation, Vector3 headLocation, unsigned int LayerID, void* collider) {
    bool (*_Physics_Raycast)(Vector3 camLocation, Vector3 headLocation, unsigned int LayerID, void* collider) = (bool(*)(Vector3, Vector3, unsigned int, void*))offset_Physics_Raycast;
    return _Physics_Raycast(camLocation, headLocation, LayerID, collider);
}

//#define offset_HeadTF (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("OLCJOGDHJJJ"))

static inline bool IsPullTargetValid(void *enemy) {
    if (!enemy) return false;
    if (*(void **)((uintptr_t) enemy) == nullptr) return false;
    if (GetHp(enemy) <= 0) return false;
    if (IsDieing(enemy)) return false;
    void *headNode = *(void **) ((uintptr_t) enemy + offset_HeadTF);
    if (!headNode) return false;
    if (!TransformNode(headNode)) return false;
    if (!Component_get_transform(enemy)) return false;
    return true;
}

static inline void *GetPlayerHeadTransform(void *player) {
    if (!player) return nullptr;
    void *headNode = *(void **) ((uintptr_t) player + offset_HeadTF);
    if (!headNode) return nullptr;
    return TransformNode(headNode);
}

bool isVisible_Aimbot(void * player)
{
    if (!IsPullTargetValid(player)) return false;

    void *hitObj = NULL;
    void *HeadTF = GetPlayerHeadTransform(player);
    if (!HeadTF) return false;

    void *local = Current_Local_Player();
    if (!local) return false;

    Vector3 EnemyHeadPosition = Transform_INTERNAL_GetPosition(HeadTF);
    Vector3 LocalPlayerPos = CameraPosition(local);
    return !Physics_Raycast(LocalPlayerPos, EnemyHeadPosition, 12, &hitObj);
}

//#define offset_CurrentGameSimulationTimer (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentGameSimulationTimer"),0)
void* CurrentGameSimulationTimer()
{
    return ((void* (*)(void *))(offset_CurrentGameSimulationTimer))(NULL);
}

//#define u3str (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("mscorlib.dll"), OBFUSCATE("System"), OBFUSCATE("String"), OBFUSCATE("CreateString"), 1)
static monoString *U3DStr(const char *str) {
    monoString *(*String_CreateString)(void *_this, const char *str) = (monoString * (*)(void *, const char *))(u3str);
    return String_CreateString(NULL, str);
}

//#define m_currentUi Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentInGameUIScene"), 0)
static void* CurrentInGameUIScene() {
    using fnCurrentUIScene = void* (*)();
    auto _CurrentUIScene = reinterpret_cast<fnCurrentUIScene>(m_currentUi);
    return _CurrentUIScene();
}


//#define ShowDynamicupMessage (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowDynamicPopupMessage"), 2)
static void ShowDynamicPopupMessage(monoString *nick) {
    void (*_ShowDynamicPopupMessage)(void *players, monoString * nicks, float duration) = (void (*)(void *, monoString *, float))(ShowDynamicupMessage);
    void *ui = CurrentInGameUIScene();
    if (ui != NULL) {
        _ShowDynamicPopupMessage(ui, nick, 0.1f);
    }
}

//#define offset_ShowLowPopupMessage (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowLowPopupMessage"), 2)
static void ShowLowPopupMessage(monoString *message, float duration = 3.0f) {
    if (offset_ShowLowPopupMessage == 0) return;
    void (*_ShowLowPopupMessage)(void *_this, monoString *msg, float dur) =
    (void (*)(void *, monoString *, float))(offset_ShowLowPopupMessage);
    void *ui = CurrentInGameUIScene();
    if (ui != nullptr) {
        _ShowLowPopupMessage(ui, message, duration);
    }
}

//#define offset_ShowPopupNoAnim (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowPopupMessageNoAnim"), 2)
static void ShowPopupMessageNoAnim(monoString *message, float duration = 2.0f) {
    if (offset_ShowPopupNoAnim == 0) return;
    void (*_Show)(void *, monoString *, float) = (void (*)(void *, monoString *, float))(offset_ShowPopupNoAnim);
    void *ui = CurrentInGameUIScene();
    if (ui) _Show(ui, message, duration);
}

//#define offset_ShowTeammateTips (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowCenterUpTeammateTips"), 2)
static void ShowCenterUpTeammateTips(monoString *message, float duration = 3.0f) {
    if (offset_ShowTeammateTips == 0) return;
    void (*_Show)(void *, monoString *, float) = (void (*)(void *, monoString *, float))(offset_ShowTeammateTips);
    void *ui = CurrentInGameUIScene();
    if (ui != nullptr) {
        _Show(ui, message, duration);
    }
}

//#define offset_JumpBtnCtrl (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("m_JumpBtnCtrl"))
static void* GetJumpsex() {
    void* uiScene = CurrentInGameUIScene();
    if (!uiScene) return nullptr;
    void* auxCtrl = *(void**)((uintptr_t)uiScene + offset_JumpBtnCtrl);
    return auxCtrl;
}

//#define offset_AuxfireCtrl (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("m_AuxfireCtrl"))
static void* GetAuxFireController() {
    void* uiScene = CurrentInGameUIScene();
    if (!uiScene) return nullptr;
    void* auxCtrl = *(void**)((uintptr_t)uiScene + offset_AuxfireCtrl);
    return auxCtrl;
}

//#define offset_BaseCtrl_OnBtnUp (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudButtonBaseController"), OBFUSCATE("OnBtnUp"), 0)
static void JumpButton_OnBtnUp(void* controller) {
    if (!controller) return;

    ((void (*)(void*))offset_BaseCtrl_OnBtnUp)(controller);
}

//#define offset_FireButton_OnBtnDown (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudFireController"), OBFUSCATE("OnBtnDown"), 0)
static void FireButton_OnBtnDown(void* controller) {
    if (!controller) return;
    ((void (*)(void*))offset_FireButton_OnBtnDown)(controller);
}

//#define offset_BaseCtrl_OnBtnDown (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudJumpController"), OBFUSCATE("OnBtnDown"), 0)
static void JumpButton_OnBtnDown(void* controller) {
    if (!controller) return;
    ((void (*)(void*))offset_BaseCtrl_OnBtnDown)(controller);
}

//#define offset_get_realtimeSinceStartup  (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Time"),OBFUSCATE("get_realtimeSinceStartup"),0)
float get_realtimeSinceStartup() {
    if (offset_get_realtimeSinceStartup){
        float (*func)();
        func = (float (*)())(offset_get_realtimeSinceStartup);
        return func();
    } return 0;
}

//#define offset_GetRange (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GPBDEDFKJNA"), OBFUSCATE("JDGGIFMKIKF"),0)
static float get_Range(void *pthis)
{
    return ((float (*)(void *))offset_GetRange)(pthis);
}
bool isEnemyInRangeWeapon(void *player, void *enemy, void* weapon)
{
    if (player != nullptr && enemy != nullptr && weapon != nullptr)
    {
        void *HeadTF = TransformNode(*(void **) ((uint64_t) enemy + offset_HeadTF));
        void *HeadTF2 = TransformNode(*(void **) ((uint64_t) player + offset_HeadTF));
        Vector3 EnemyHeadPosition = Transform_INTERNAL_GetPosition(HeadTF);
        Vector3 PlayerHeadPosition = Transform_INTERNAL_GetPosition(HeadTF2);
        float distance = Vector3::Distance(PlayerHeadPosition, EnemyHeadPosition);
        float range = get_Range(weapon);

        if (distance <= range) {
            return true;
        }
    }
    return false;
}


//#define m_addTeamHud Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIInGameScene"), OBFUSCATE("ShowAssistantText"), 2)
static void ShowAssistantText(void* uiInstance, monoString* playerName, monoString* line) {
    using fnShowAssistantText = void(*)(void*, monoString*, monoString*);
    auto _ShowAssistantText = reinterpret_cast<fnShowAssistantText>(m_addTeamHud);

    if (uiInstance != nullptr) {
        _ShowAssistantText(uiInstance, playerName, line);
    }
}

static monoString *U3DStrFormat(float distance, float vida) {
    char buffer[128] = {0};
    sprintf(buffer, "[PHX CORP] distance: %.2fm", distance);
    return U3DStr(buffer);
}

//#define _MainCameraTransform (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("MainCameraTransform"))

Vector3 CameraMain(void* player) {
    return Transform_INTERNAL_GetPosition(*(void**) ((uint64_t) player + _MainCameraTransform));
}
bool SmartEnemyMovementTracker(void *enemy, bool apply = true) {
    if (!IsPullTargetValid(enemy)) return false;

    if (isVisible_Aimbot(enemy)) return true;

    void *enemyTransform = Component_get_transform(enemy);
    if (!enemyTransform) return false;

    void *HeadTF = GetPlayerHeadTransform(enemy);
    if (!HeadTF) return false;

    void *local = Current_Local_Player();
    if (!local) return false;

    Vector3 LocalPlayerPos = CameraPosition(local);
    Vector3 OriginalRootPos = Transform_INTERNAL_GetPosition(enemyTransform);
    Vector3 EnemyHeadPos = Transform_INTERNAL_GetPosition(HeadTF);
    void *hitObj = NULL;

    // --- MAX BRUTAL PULL (24 Directions, Dual-Height, 12m Range) ---

    // 1. DENSE HORIZONTAL & MICRO-VERTICAL SCAN
    static const float ultraRadii[] = {1.5f, 2.7f, 3.9f, 5.0f, 7.0f, 9.5f, 12.0f};
    static const float ultraDirs[][2] = {
        {1.000f, 0.000f}, {0.966f, 0.259f}, {0.866f, 0.500f}, {0.707f, 0.707f},
        {0.500f, 0.866f}, {0.259f, 0.966f}, {0.000f, 1.000f}, {-0.259f, 0.966f},
        {-0.500f, 0.866f}, {-0.707f, 0.707f}, {-0.866f, 0.500f}, {-0.966f, 0.259f},
        {-1.000f, 0.000f}, {-0.966f, -0.259f}, {-0.866f, -0.500f}, {-0.707f, -0.707f},
        {-0.500f, -0.866f}, {-0.259f, -0.966f}, {0.000f, -1.000f}, {0.259f, -0.966f},
        {0.500f, -0.866f}, {0.707f, -0.707f}, {0.866f, -0.500f}, {0.966f, -0.259f}
    };
    static const float microY[] = {0.0f, 0.25f};

    for (float r : ultraRadii) {
        for (int i = 0; i < 24; i++) {
            float dx = ultraDirs[i][0] * r;
            float dz = ultraDirs[i][1] * r;
            
            for (float dy : microY) {
                Vector3 testHead = EnemyHeadPos;
                testHead.X += dx;
                testHead.Y += dy;
                testHead.Z += dz;

                if (!Physics_Raycast(LocalPlayerPos, testHead, 12, &hitObj)) {
                    if (apply) {
                        if (!IsPullTargetValid(enemy)) return false;
                        void *tf = Component_get_transform(enemy);
                        if (!tf) return false;
                        Vector3 finalRoot = OriginalRootPos;
                        finalRoot.X += dx;
                        finalRoot.Y += dy;
                        finalRoot.Z += dz;
                        Transform_set_position(tf, finalRoot);
                    }
                    return true;
                }
            }
        }
    }

    // 2. EMERGENCY VERTICAL FALLBACK (Last Resort)
    float emergencyY = 0.30f;
    Vector3 testHeadUp = EnemyHeadPos; testHeadUp.Y += emergencyY;
    if (!Physics_Raycast(LocalPlayerPos, testHeadUp, 12, &hitObj)) {
        if (apply) {
            if (!IsPullTargetValid(enemy)) return false;
            void *tf = Component_get_transform(enemy);
            if (!tf) return false;
            Vector3 finalRoot = OriginalRootPos;
            finalRoot.Y += emergencyY;
            Transform_set_position(tf, finalRoot);
        }
        return true;
    }



    return false;
}



bool SilentGhostPull(void *enemy, float *outBestXZRadius, bool apply = true) {
    if (!enemy) return false;

    if (isVisible_Aimbot(enemy)) {
        if (outBestXZRadius) *outBestXZRadius = 0.0f;
        return true;
    }

    void *enemyTransform = Component_get_transform(enemy);
    if (!enemyTransform) return false;
    Vector3 EnemyRootPos = Transform_INTERNAL_GetPosition(enemyTransform);

    void *HeadTF = TransformNode(*(void **) ((uint64_t) enemy + offset_HeadTF));
    if (!HeadTF) return false;
    Vector3 EnemyHeadPos = Transform_INTERNAL_GetPosition(HeadTF);

    Vector3 headOffset;
    headOffset.X = EnemyHeadPos.X - EnemyRootPos.X;
    headOffset.Y = EnemyHeadPos.Y - EnemyRootPos.Y;
    headOffset.Z = EnemyHeadPos.Z - EnemyRootPos.Z;

    void *LocalPlayer = Current_Local_Player();
    if (!LocalPlayer) return false;

    void *LPHeadTF = TransformNode(*(void **) ((uint64_t) LocalPlayer + offset_HeadTF));
    if (!LPHeadTF) return false;
    Vector3 lpHead = Transform_INTERNAL_GetPosition(LPHeadTF);

    Vector3 LocalPlayerPos = lpHead;

    struct Candidate {
        bool valid;
        Vector3 rootPos;
        float dx, dy, dz;
    };

    auto isBetter = [](const Candidate &a, const Candidate &b) -> bool {
        if (!b.valid) return true;

        bool aForward = (a.dz > 0.0f);
        bool bForward = (b.dz > 0.0f);
        if (aForward != bForward) return aForward && !bForward;

        float aAbsZ = fabsf(a.dz);
        float bAbsZ = fabsf(b.dz);
        if (aForward && bForward) {
            if (aAbsZ != bAbsZ) return aAbsZ < bAbsZ;
        } else {
            if (aAbsZ != bAbsZ) return aAbsZ < bAbsZ;
        }

        float aAbsX = fabsf(a.dx);
        float bAbsX = fabsf(b.dx);
        if (aAbsX != bAbsX) return aAbsX < bAbsX;

        float aAbsY = fabsf(a.dy);
        float bAbsY = fabsf(b.dy);
        if (aAbsY != bAbsY) return aAbsY < bAbsY;

        return false;
    };

    const float xPoints[] = {
            -2.5f, -1.0f, 1.0f, 2.5f
    };
    const int xCount = 4;

    const float zPoints[] = {
        -1.5f,
            1.5f
    };
    const int zCount = 2;

    const float yPoints[] = {
            0.0f
    };
    const int yCount = 1;

    auto checkPointVisible = [&](float dx, float dy, float dz, Candidate &best) -> bool {
        Vector3 testRootPos = EnemyRootPos;
        testRootPos.X += dx;
        testRootPos.Y += dy;
        testRootPos.Z += dz;

        Vector3 expectedHeadPos;
        expectedHeadPos.X = testRootPos.X + headOffset.X;
        expectedHeadPos.Y = testRootPos.Y + headOffset.Y;
        expectedHeadPos.Z = testRootPos.Z + headOffset.Z;

        void *hitObj = NULL;
        bool hasObstacle = Physics_Raycast(LocalPlayerPos, expectedHeadPos, 12, &hitObj);
        bool visible = !hasObstacle;
        if (!visible) return false;

        Candidate cand;
        cand.valid = true;
        cand.rootPos = testRootPos;
        cand.dx = dx;
        cand.dy = dy;
        cand.dz = dz;

        if (isBetter(cand, best)) {
            best = cand;
        }
        return true;
    };

    Candidate best = {false};

    for (int zi = 0; zi < zCount; ++zi) {
        if (checkPointVisible(0.0f, 0.0f, zPoints[zi], best)) {
        }
    }
    if (best.valid) {
        float radius = sqrtf(best.dx * best.dx + best.dz * best.dz);
        if (outBestXZRadius) *outBestXZRadius = radius;
        if (apply) Transform_set_position(enemyTransform, best.rootPos);
        return true;
    }

    for (int xi = 0; xi < xCount; ++xi) {
        checkPointVisible(xPoints[xi], 0.0f, 0.0f, best);
    }
    if (best.valid) {
        float radius = sqrtf(best.dx * best.dx + best.dz * best.dz);
        if (outBestXZRadius) *outBestXZRadius = radius;
        if (apply) Transform_set_position(enemyTransform, best.rootPos);
        return true;
    }

    for (int yi = 0; yi < yCount; ++yi) {
        checkPointVisible(0.0f, yPoints[yi], 0.0f, best);
    }
    if (best.valid) {
        float radius = sqrtf(best.dx * best.dx + best.dz * best.dz);
        if (outBestXZRadius) *outBestXZRadius = radius;
        if (apply) Transform_set_position(enemyTransform, best.rootPos);
        return true;
    }

    best.valid = false;
    for (int zi = 0; zi < zCount; ++zi) {
        for (int xi = 0; xi < xCount; ++xi) {
            for (int yi = 0; yi < yCount; ++yi) {
                checkPointVisible(xPoints[xi], yPoints[yi], zPoints[zi], best);
            }
        }
    }

    if (best.valid) {
        float radius = sqrtf(best.dx * best.dx + best.dz * best.dz);
        if (outBestXZRadius) *outBestXZRadius = radius;
        if (apply) Transform_set_position(enemyTransform, best.rootPos);
        return true;
    }

    const int yDownCount = 41;
    for (int yi = 0; yi < yDownCount; ++yi) {
        float dy = -1.40f - 0.01f * (float) yi;
        Vector3 testRootPos = EnemyRootPos;
        testRootPos.X += 0.0f;
        testRootPos.Y += dy;
        testRootPos.Z += 0.0f;

        Vector3 expectedHeadPos;
        expectedHeadPos.X = testRootPos.X + headOffset.X;
        expectedHeadPos.Y = testRootPos.Y + headOffset.Y;
        expectedHeadPos.Z = testRootPos.Z + headOffset.Z;

        void *hitObj = NULL;
        bool hasObstacle = Physics_Raycast(LocalPlayerPos, expectedHeadPos, 12, &hitObj);
        if (hasObstacle) continue;

        if (outBestXZRadius) *outBestXZRadius = 0.0f;
        if (apply) Transform_set_position(enemyTransform, testRootPos);
        return true;
    }

    return false;
}


//#define offset_PlayerID (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_PlayerID"),0)

COW_GamePlay_IHAAMHPPLMG_o GetplayerID(void *_this)
{
    return ((COW_GamePlay_IHAAMHPPLMG_o (*)(void *))offset_PlayerID)(_this);
}

//#define offset_CFFPIACECIG (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("IHAAMHPPLMG"), OBFUSCATE("CFFPIACECIG"),1)
uint32_t CFFPIACECIG(COW_GamePlay_IHAAMHPPLMG_o IDNEFEOPGIF)
{
    return ((uint32_t (*)(COW_GamePlay_IHAAMHPPLMG_o))offset_CFFPIACECIG)(IDNEFEOPGIF);
}


//#define offset_SyncSwapWeapon (uintptr_t) Il2CppCreateClassInstance(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JLMEBGKMNIL"))
//#define offset_IHAAMHPPLMG_s (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JLMEBGKMNIL"), OBFUSCATE("IHAAMHPPLMG"))
//#define offset_DGLCOGJJFMI_s (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("JLMEBGKMNIL"), OBFUSCATE("DGLCOGJJFMI"))
static void Syns_SwapWeapon_Impl(void *LocalPlayer, void *WeaponOnHand) {
    if (WeaponOnHand == nullptr) return;
    void *RUDP_CHANGE_INVENTORY_ON_HAND = (void*)offset_SyncSwapWeapon;
    if (RUDP_CHANGE_INVENTORY_ON_HAND) {
        *(uint32_t * )((uint64_t) RUDP_CHANGE_INVENTORY_ON_HAND + offset_IHAAMHPPLMG_s) = CFFPIACECIG(GetplayerID(LocalPlayer));
        *(uint32_t * )((uint64_t) RUDP_CHANGE_INVENTORY_ON_HAND + offset_DGLCOGJJFMI_s) = GetUniqueID(WeaponOnHand);
        GameFacade_Send(108, RUDP_CHANGE_INVENTORY_ON_HAND, 2, 0);
    }
}

//#define SetStartDamageV (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GPBDEDFKJNA"),OBFUSCATE("BLAGCMCGEJG"),1)
void SetStartDamage(void * Player, void * ObjectPoolCallbackBase) {
    if (Player){ uintptr_t (*func)(void *,void *);
        func = (uintptr_t (*)(void *,void *))(SetStartDamageV);
        func(Player,ObjectPoolCallbackBase);
    }
}

//#define GetTypeWeaponV  (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("GPBDEDFKJNA"),OBFUSCATE("GJCHEHNJIAD"),0)
int GetTypeWeapon(void * Player) {
    if (Player){
        int (*func)(void *);
        func = (int (*)(void *))(GetTypeWeaponV);
        return func(Player);
    } return 0;
}

//#define get_timeV  (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Time"),OBFUSCATE("get_time"),0)
float get_time() {
    if (get_timeV){
        float (*func)();
        func = (float (*)())(get_timeV);
        return func();
    } return 0;
}

//#define StartWholeBodyFiringV  (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"),OBFUSCATE("StartWholeBodyFiring"),1)
static void StartWholeFiring(void* player, void* weapon) {
    if (!player || !weapon) return;
    auto fn = reinterpret_cast<void(*)(void*, void*)>(StartWholeBodyFiringV);
    fn(player, weapon);
}
//#define offset_get_IsFiringFromPRI (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsFiringFromPRI"), 0)
static bool isfiringss(void *player, void *weapon = nullptr) {
    bool (*_IsFiringPlayer)(void *players) = (bool (*)(void *))offset_get_IsFiringFromPRI;
    return _IsFiringPlayer(player);
}
//#define offset_StartFiring (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("StartFiring"),1)
static void StartFiring(void* player, void* weapon) {
    if (!player || !weapon) return;
    auto fn = reinterpret_cast<void(*)(void*, void*)>(offset_StartFiring);
    fn(player, weapon);
}

static void SyncStartFiring(void* player, int weapon) {
    if (!player || !weapon) return;
    auto fn = reinterpret_cast<void(*)(void*, int)>(getRealOffset(0x61E9DA8));
    fn(player, weapon);
}

//#define offset_PlayerNetwork_StopFire (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("StopFire"), 1)
static void StopFire(void* player, void* weapon) {
    if (!player || !weapon) return;
    auto fn = reinterpret_cast<void(*)(void*, void*)>(offset_PlayerNetwork_StopFire);
    fn(player, weapon);
}


//#define offset_UGCRequestJump (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("UGCRequestJump"))
bool GetPhysicalCCT(void* player)
{
    if (!player) return false;

    return *(bool *)((uint64_t)player + offset_UGCRequestJump);
}

//#define offset_GetPhysXState (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetPhysXState"), 0)
bool IsPlayerFalling(void* player)
{
    if (!player) return false;

    int state = ((int(*)(void*))offset_GetPhysXState)(player);
    return (state == 1);
}

bool SilentGhostPullV2(void *enemy, float *outBestXZRadius, bool apply = true)
{
    if (!IsPullTargetValid(enemy)) return false;

    if (isVisible_Aimbot(enemy)) {
        if (outBestXZRadius) *outBestXZRadius = 0.0f;
        return true;
    }

    void *enemyTF = Component_get_transform(enemy);
    if (!enemyTF) return false;

    Vector3 enemyRoot = Transform_INTERNAL_GetPosition(enemyTF);

    void *headTF = GetPlayerHeadTransform(enemy);
    if (!headTF) return false;

    Vector3 enemyHead = Transform_INTERNAL_GetPosition(headTF);

    Vector3 headOffset = {
            enemyHead.X - enemyRoot.X,
            enemyHead.Y - enemyRoot.Y,
            enemyHead.Z - enemyRoot.Z
    };

    void *lp = Current_Local_Player();
    if (!lp) return false;

    void *lpHeadTF = GetPlayerHeadTransform(lp);
    if (!lpHeadTF) return false;

    Vector3 lpHead = Transform_INTERNAL_GetPosition(lpHeadTF);

    auto testPull = [&](float dx,float dy,float dz)->bool
    {
        if (!IsPullTargetValid(enemy)) return false;

        Vector3 newRoot = enemyRoot;
        newRoot.X += dx;
        newRoot.Y += dy;
        newRoot.Z += dz;

        Vector3 newHead = {
                newRoot.X + headOffset.X,
                newRoot.Y + headOffset.Y,
                newRoot.Z + headOffset.Z
        };

        void* hitObj = nullptr;

        if (Physics_Raycast(lpHead,newHead,12,&hitObj))
            return false;

        if (outBestXZRadius)
            *outBestXZRadius = sqrtf(dx*dx + dz*dz);

        if (apply) {
            void *tf = Component_get_transform(enemy);
            if (!tf) return false;
            Transform_set_position(tf, newRoot);
        }
        return true;
    };

    /* ---------- Forward priority ---------- */

    static const float zForward[] = {1.5f,3.0f,4.5f,-1.5f,-3.0f,-4.5f};
    for (float z : zForward)
        if (testPull(0,0,z)) return true;

    /* ---------- Side offsets ---------- */

    static const float xSide[] = {-2.0f,-0.8f,0.8f,2.0f,-3.2f,3.2f};
    for (float x : xSide)
        if (testPull(x,0,0)) return true;

    /* ---------- Small grid search ---------- */

    for (float z : zForward)
    {
        for (float x : xSide)
        {
            if (testPull(x,0,z))
                return true;
        }
    }

    /* ---------- Drop below cover ---------- */

    for (int i=0;i<30;i++)
    {
        float dy = -1.4f - 0.015f*i;
        if (testPull(0,dy,0))
            return true;
    }

    return false;
}

bool SafeSilentPull(void *enemy, float *outBestXZRadius, bool apply = true)
{
    if (!IsPullTargetValid(enemy)) return false;

    if (isVisible_Aimbot(enemy)) {
        if (outBestXZRadius) *outBestXZRadius = 0.0f;
        return true;
    }

    void *enemyTF = Component_get_transform(enemy);
    if (!enemyTF) return false;

    Vector3 enemyRoot = Transform_INTERNAL_GetPosition(enemyTF);

    void *headTF = GetPlayerHeadTransform(enemy);
    if (!headTF) return false;

    Vector3 enemyHead = Transform_INTERNAL_GetPosition(headTF);

    Vector3 headOffset = {
            enemyHead.X - enemyRoot.X,
            enemyHead.Y - enemyRoot.Y,
            enemyHead.Z - enemyRoot.Z
    };

    void *lp = Current_Local_Player();
    if (!lp) return false;

    void *lpHeadTF = GetPlayerHeadTransform(lp);
    if (!lpHeadTF) return false;

    Vector3 lpHead = Transform_INTERNAL_GetPosition(lpHeadTF);

    auto testPull = [&](float dx,float dy,float dz)->bool
    {
        if (!IsPullTargetValid(enemy)) return false;

        Vector3 newRoot = enemyRoot;
        newRoot.X += dx;
        newRoot.Y += dy;
        newRoot.Z += dz;

        Vector3 newHead = {
                newRoot.X + headOffset.X,
                newRoot.Y + headOffset.Y,
                newRoot.Z + headOffset.Z
        };

        void* hitObj = nullptr;

        if (Physics_Raycast(lpHead,newHead,12,&hitObj))
            return false;

        if (outBestXZRadius)
            *outBestXZRadius = sqrtf(dx*dx + dz*dz);

        if (apply) {
            void *tf = Component_get_transform(enemy);
            if (!tf) return false;
            Transform_set_position(tf, newRoot);
        }
        return true;
    };

    // ultra tight limits to completely prevent game back/kick issues!
    static const float zForward[] = {0.8f, 1.2f, -0.8f, -1.2f};
    for (float z : zForward)
        if (testPull(0,0,z)) return true;

    static const float xSide[] = {-0.5f, -0.8f, 0.5f, 0.8f};
    for (float x : xSide)
        if (testPull(x,0,0)) return true;

    for (float z : zForward) {
        for (float x : xSide) {
            if (testPull(x,0,z)) return true;
        }
    }

    return false;
}


static void set_position_Injected(void* transform, Vector3 position)
{
    if (!transform) return;
    static void (*_set_position_Injected)(void*, Vector3*) = nullptr;
    if (!_set_position_Injected)
    {
        _set_position_Injected = (void (*)(void*, Vector3*)) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"),OBFUSCATE("UnityEngine"),OBFUSCATE("Transform"),OBFUSCATE("set_position_Injected"),1);
    }
    if (!_set_position_Injected) return;
    _set_position_Injected(transform, &position);
}

#define Offset_StartSAPJumpBeforeGlid (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("StartSAPJumpBeforeGlid"), 0)
#define Offset_StartInSAPFlyJumping Offset_StartSAPJumpBeforeGlid
#define Offset_Startgliderbkc (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("StartSAPGlid"), 0)

static void hilll_gliderbkc(void* localPlayer) {
    if (!localPlayer || localPlayer != Current_Local_Player()) return;
    typedef void (*gliderbkc_t)(void*);
    uintptr_t fnOffset = Offset_Startgliderbkc;
    if (!fnOffset) return;

    gliderbkc_t gliderbkc = nullptr;
    if (fnOffset < 0x10000000) {
        gliderbkc = (gliderbkc_t)getRealOffset(fnOffset);
    } else {
        gliderbkc = (gliderbkc_t)fnOffset;
    }

    if (gliderbkc) {
        gliderbkc(localPlayer);
    }
}

static void TriggerInfiniteGlide(void* localPlayer) {
    if (!localPlayer || localPlayer != Current_Local_Player()) return;
    typedef void (*StartSAPJumpBeforeGlid_t)(void*);
    uintptr_t fnOffset = Offset_StartSAPJumpBeforeGlid;
    if (!fnOffset) return;

    StartSAPJumpBeforeGlid_t StartSAPJumpBeforeGlid = nullptr;
    if (fnOffset < 0x10000000) {
        StartSAPJumpBeforeGlid = (StartSAPJumpBeforeGlid_t)getRealOffset(fnOffset);
    } else {
        StartSAPJumpBeforeGlid = (StartSAPJumpBeforeGlid_t)fnOffset;
    }

    if (StartSAPJumpBeforeGlid) {
        StartSAPJumpBeforeGlid(localPlayer);
    }
}

#endif


