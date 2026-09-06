#ifndef UTILS_H
#define UTILS_H

typedef unsigned long DWORD;

DWORD libBase = 0;

const char* libName = OBFUSCATE("libil2cpp.so");

DWORD get_libBase(const char* libName);
DWORD get_libBase(const char* libName)
{
    FILE *fp;
    DWORD addr = 0;
    char filename[32], buffer[1024];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", getpid());
    fp = fopen(filename, "rt");
    if (fp != NULL) {
        while (fgets(buffer, sizeof(buffer), fp))
        {
            if (strstr(buffer, libName))
            {
                addr = (uintptr_t) strtoul(buffer, NULL, 16);
                break;
            }
        }
        fclose(fp);
    }
    return addr;
}

uintptr_t basePtr = 0;
uintptr_t get_lib_start(const char* lib) {
    uintptr_t basePtr = 0;
    char line[1024];
    char filename[0xFF] = {0};
    sprintf(filename, "/proc/self/maps");
    FILE* fp = fopen(filename, "re");
    if(fp) {
        while(fgets(line, sizeof line, fp)) {
            if(strstr(line, lib)) {
                basePtr = std::stoul(line, NULL, 16);
                return basePtr;
            }
        }
    }
    return basePtr;
}

void* getAddress(const char* lib, uintptr_t relativeAddr2, bool recheck2 = false)
{
    while(basePtr == 0)
    {
        basePtr = get_lib_start(lib);

    }
    if(recheck2)
        basePtr = get_lib_start(lib);
    return (void*)(basePtr + relativeAddr2);
}
bool libLoaded = false;
bool isLibraryLoaded(const char *libraryName) {
    char line[512] = {0};
    FILE *fp = fopen("/proc/self/maps", "rt");
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            std::string a = line;
            if (strstr(line, libraryName)) {
                libLoaded = true;
                return true;
            }
        }
        fclose(fp);
    }
    return false;
}
DWORD getRealOffset(DWORD address);
DWORD getRealOffset(DWORD address) {
    if (libBase == 0) {
        libBase = get_libBase(libName);
    }
    return (libBase + address);
}

uintptr_t getLibraryBase(const char *libName) {
    uintptr_t retAddr = 0;

    char fileName[255];
    memset(fileName, 0, sizeof(fileName));

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    snprintf(fileName, sizeof(fileName), "/proc/%d/maps", getpid());
    FILE *fp = fopen(fileName, "rt");
    if (fp != NULL) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strstr(buffer, libName) != NULL) {
                retAddr = (uintptr_t) strtoul(buffer, NULL, 16);
                break;
            }
        }
        fclose(fp);
    }
    return retAddr;
}

uintptr_t getLibraryBase2(const char *libName) {
    uintptr_t retAddr = 0;

    char fileName[255];
    memset(fileName, 0, sizeof(fileName));

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    snprintf(fileName, sizeof(fileName), "/proc/%d/maps", getpid());
    FILE *fp = fopen(fileName, "rt");
    if (fp != NULL) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strstr(buffer, libName) != NULL) {
                retAddr = (uintptr_t) strtoul(buffer, NULL, 16);
                break;
            }
        }
        fclose(fp);
    }
    return retAddr;
}
uintptr_t location;
uintptr_t getRealOffsetAnogs(uintptr_t offset)
{
    if (location <= 0)
    {
        location = getLibraryBase2(OBFUSCATE("libanogs.so"));
    }

    return location + offset;
}


uintptr_t getLibraryBase23(const char *libName) {
    uintptr_t retAddr = 0;

    char fileName[255];
    memset(fileName, 0, sizeof(fileName));

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    snprintf(fileName, sizeof(fileName), "/proc/%d/maps", getpid());
    FILE *fp = fopen(fileName, "rt");
    if (fp != NULL) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strstr(buffer, libName) != NULL) {
                retAddr = (uintptr_t) strtoul(buffer, NULL, 16);
                break;
            }
        }
        fclose(fp);
    }
    return retAddr;
}
uintptr_t locationanort33;
uintptr_t getRealOffsetlibc(uintptr_t offset)
{
    if (locationanort33 <= 0)
    {
        locationanort33 = getLibraryBase23(OBFUSCATE("libGGP.so"));
    }

    return locationanort33 + offset;
}


#endif
