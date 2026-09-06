#pragma once

//
// Created by Reflex on 09/22/2025.
//
#pragma once

#include <stdio.h>
#include <string>
#include <inttypes.h>
#include <codecvt>
#include <locale>
#include <dlfcn.h>

#ifndef IL2CPP_H
#define IL2CPP_H

typedef void(*Il2CppMethodPointer)();

struct MethodInfo;

struct VirtualInvokeDataV
{
    Il2CppMethodPointer methodPtr;
    const MethodInfo* method;
};

struct Il2CppTypeV
{
    void* data;
    unsigned int bits;
};

struct Il2CppClass;


union Il2CppRGCTXData
{
    void* rgctxDataDummy;
    const MethodInfo* method;
    const Il2CppTypeV* type;
    Il2CppClass* klass;
};

struct Il2CppClass_1V
{
    void* image;
    void* gc_desc;
    const char* name;
    const char* namespaze;
    Il2CppTypeV* byval_arg;
    Il2CppTypeV* this_arg;
    Il2CppClass* element_class;
    Il2CppClass* castClass;
    Il2CppClass* declaringType;
    Il2CppClass* parent;
    void *generic_class;
    void* typeDefinition;
    void* interopData;
    void* fields;
    void* events;
    void* properties;
    void* methods;
    Il2CppClass** nestedTypes;
    Il2CppClass** implementedInterfaces;
    void* interfaceOffsets;
};

struct Il2CppClass_2V
{
    Il2CppClass** typeHierarchy;
    uint32_t cctor_started;
    uint32_t cctor_finished;
    uint64_t cctor_thread;
    int32_t genericContainerIndex;
    int32_t customAttributeIndex;
    uint32_t instance_size;
    uint32_t actualSize;
    uint32_t element_size;
    int32_t native_size;
    uint32_t static_fields_size;
    uint32_t thread_static_fields_size;
    int32_t thread_static_fields_offset;
    uint32_t flags;
    uint32_t token;
    uint16_t method_count;
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count;
    uint16_t interfaces_count;
    uint16_t interface_offsets_count;
    uint8_t typeHierarchyDepth;
    uint8_t genericRecursionDepth;
    uint8_t rank;
    uint8_t minimumAlignment;
    uint8_t packingSize;
    uint8_t bitflags1;
    uint8_t bitflags2;
};

struct Il2CppClassV
{
    Il2CppClass_1V _1;
    void* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2V _2;
    VirtualInvokeDataV vtable[255];
};

struct MethodInfo
{
    Il2CppMethodPointer methodPointer;
    void* invoker_method;
    const char* name;
    Il2CppClass *declaring_type;
    const Il2CppTypeV *return_type;
    const void* parameters;
    union
    {
        const Il2CppRGCTXData* rgctx_data;
        const void* methodDefinition;
    };
    union
    {
        const void* genericMethod;
        const void* genericContainer;
    };
    int32_t customAttributeIndex;
    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint8_t parameters_count;
    uint8_t bitflags;
};

struct FieldInfo
{
public:
    const char* name;
    const Il2CppTypeV* type;
    Il2CppClassV *parent;
    int32_t offset;
    uint32_t token;
};


template<typename T> struct Il2CppArray {
    Il2CppClass *klass;
    void *monitor;
    void *bounds;
    int max_length;
    T m_Items[65535];

    int getLength() {
        return max_length;
    }

    T *getPointer() {
        return (T *)m_Items;
    }

    T &operator[](int i) {
        return m_Items[i];
    }

    T &operator[](int i) const {
        return m_Items[i];
    }
};

template<typename T>
using Array = Il2CppArray<T>;

struct Il2CppString {
    Il2CppClass *klass;
    void *monitor;
    int32_t length;
    uint16_t start_char;

    const char *CString();

    const wchar_t *WCString();

    static Il2CppString *Create(const char *s);
    static Il2CppString *Create(const wchar_t *s, int len);

    int getLength() {
        return length;
    }
};

typedef Il2CppString String;

template<typename T> struct Il2CppList {
    Il2CppClass *klass;
    void *unk1;
    Il2CppArray<T> *items;
    int size;
    int version;

    T *getItems() {
        return items->getPointer();
    }

    int getSize() {
        return size;
    }

    int getVersion() {
        return version;
    }

    T &operator[](int i) {
        return items->m_Items[i];
    }

    T &operator[](int i) const {
        return items->m_Items[i];
    }
};

template<typename T>
using List = Il2CppList<T>;


void Il2CppAttach(const char *name="libil2cpp.so");
void *Il2CppGetImageByName(const char *image);
void *Il2CppGetClassType(const char *image, const char *namespaze, const char *clazz);
void *Il2CppCreateClassInstance(const char *image, const char *namespaze, const char *clazz);
void* Il2CppCreateArray(const char *image, const char *namespaze, const char *clazz, size_t length);
void Il2CppGetStaticFieldValue(const char *image, const char *namespaze, const char *clazz, const char *name, void *output);
void Il2CppSetStaticFieldValue(const char *image, const char *namespaze, const char *clazz, const char *name, void* value);
void *Il2CppGetMethodOffset(const char *image, const char *namespaze, const char *clazz, const char *name, int argsCount = 0);
void *Il2CppGetMethodOffset(const char *image, const char *namespaze, const char *clazz, const char *name, char** args, int argsCount);
size_t Il2CppGetFieldOffset(const char *image, const char *namespaze, const char *clazz, const char *name);
size_t Il2CppGetStaticFieldOffset(const char *image, const char *namespaze, const char *clazz, const char *name);
bool Il2CppIsAssembliesLoaded();
extern uintptr_t _StaticClass;
#endif

