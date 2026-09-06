class Category {

public:
    void create(JNIEnv* env, const char* name) {
        jclass CMenu = env->FindClass("com/terminalx999/Menu");
        jmethodID MCategory = env->GetStaticMethodID(CMenu, "addCategory", "(Ljava/lang/String;)V");
        return env->CallStaticVoidMethod(CMenu, MCategory, env->NewStringUTF(name));
    }

};
