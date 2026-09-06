class Switch {

public:
    void create(JNIEnv* env, const char* name, jint ID) {
        jclass CMenu = env->FindClass("com/terminalx999/Menu");
        jmethodID MSwitch = env->GetStaticMethodID(CMenu, "addSwitch", "(Ljava/lang/String;I)V");
        return env->CallStaticVoidMethod(CMenu, MSwitch, env->NewStringUTF(name), ID);
    }

};
