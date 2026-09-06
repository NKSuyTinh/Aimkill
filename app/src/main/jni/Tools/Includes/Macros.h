#ifndef ANDROID_MOD_MENU_MACROS_H
#define ANDROID_MOD_MENU_MACROS_H

// thanks to shmoo and joeyjurjens for the usefull stuff under this comment.

#if defined(__aarch64__) //Compile for arm64 lib only
#include <And64InlineHook/And64InlineHook.hpp>

#define HOOK(offset, ptr, orig) A64HookFunction((void *)getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE(offset))), (void *)ptr, (void **)&orig)
#define HOOK_LIB(lib, offset, ptr, orig) A64HookFunction((void *)getAbsoluteAddress(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset))), (void *)ptr, (void **)&orig)

#define HOOK_NO_ORIG(offset, ptr) A64HookFunction((void *)getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE(offset))), (void *)ptr, NULL)
#define HOOK_LIB_NO_ORIG(lib, offset, ptr) A64HookFunction((void *)getAbsoluteAddress(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset))), (void *)ptr, NULL)

#define HOOKSYM(sym, ptr, org) A64HookFunction(dlsym(dlopen(targetLibName, 4), OBFUSCATE(sym)), (void *)ptr, (void **)&org)
#define HOOKSYM_LIB(lib, sym, ptr, org) A64HookFunction(dlsym(dlopen(OBFUSCATE(lib), 4), OBFUSCATE(sym)), (void *)ptr, (void **)&org)

#define HOOKSYM_NO_ORIG(sym, ptr) A64HookFunction(dlsym(dlopen(targetLibName, 4), OBFUSCATE(sym)), (void *)ptr, NULL)
#define HOOKSYM_LIB_NO_ORIG(lib, sym, ptr) A64HookFunction(dlsym(dlopen(OBFUSCATE(lib), 4), OBFUSCATE(sym)), (void *)ptr, NULL)

#else //Compile for armv7 lib only. Do not worry about greyed out highlighting code, it still works

#include "Tools/Substrate/SubstrateHook.h"
#include "Tools/Substrate/CydiaSubstrate.h"

#define HOOK(offset, ptr, orig) MSHookFunction((void *)getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE(offset))), (void *)ptr, (void **)&orig)
//#define HOOK_LIB(lib, offset, ptr, orig) MSHookFunction((void *)getAbsoluteAddress2(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset))), (void *)ptr, (void **)&orig)

#define HOOK_NO_ORIG(offset, ptr) MSHookFunction((void *)getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE(offset))), (void *)ptr, NULL)
#define HOOK_LIB_NO_ORIG(lib, offset, ptr) MSHookFunction((void *)getAbsoluteAddress(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset))), (void *)ptr, NULL)

#define HOOKSYM(sym, ptr, org) MSHookFunction(dlsym(dlopen(targetLibName, 4), OBFUSCATE(sym)), (void *)ptr, (void **)&org)
#define HOOKSYM_LIB(lib, sym, ptr, org) MSHookFunction(dlsym(dlopen(OBFUSCATE(lib), 4), OBFUSCATE(sym)), (void *)ptr, (void **)&org)

#define HOOKSYM_NO_ORIG(sym, ptr)  MSHookFunction(dlsym(dlopen(targetLibName, 4), OBFUSCATE(sym)), (void *)ptr, NULL)
#define HOOKSYM_LIB_NO_ORIG(lib, sym, ptr)  MSHookFunction(dlsym(dlopen(OBFUSCATE(lib), 4), OBFUSCATE(sym)), (void *)ptr, NULL)

#endif
//

#endif //ANDROID_MOD_MENU_MACROS_H

