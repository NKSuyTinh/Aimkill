class SeekBar {

public:
    void create(JNIEnv* env, const char* name, jint value, jint max, const char* type, jint ID) {
        jclass CMenu = env->FindClass("com/terminalx999/Menu");
        jmethodID MSeekBar = env->GetStaticMethodID(CMenu, "addSeekBar", "(Ljava/lang/String;IILjava/lang/String;I)V");
        return env->CallStaticVoidMethod(CMenu, MSeekBar, env->NewStringUTF(name), value, max, env->NewStringUTF(type), ID);
    }

};
