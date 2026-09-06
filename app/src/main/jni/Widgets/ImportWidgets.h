#include "Tab.h"
#include "Category.h"
#include "Switch.h"
#include "SeekBar.h"
#include "Images.h"

class Widget {

private:
    JNIEnv* env;
    Tab tab;
    Category category;
    Switch aSwitch;
    SeekBar seekBar;

public:
    Widget(JNIEnv* globEnv) {
        env = globEnv;
    }

    void Tab(const char* name) {
        tab.create(env, name);
    }

    void Category(const char* name) {
        category.create(env, name);
    }

    void Switch(const char* name, jint ID) {
        aSwitch.create(env, name, ID);
    }

    void SwitchWithCheckbox(const char* name, jint mainID, jint subID) {
        jclass CMenu = env->FindClass("com/terminalx999/Menu");
        jmethodID MSwitch = env->GetStaticMethodID(CMenu, "addSwitchWithCheckbox", "(Ljava/lang/String;II)V");
        env->CallStaticVoidMethod(CMenu, MSwitch, env->NewStringUTF(name), mainID, subID);
    }

    void SwitchWithSubCheck(const char* name, jint mainID, jint subID) {
        jclass CMenu = env->FindClass("com/terminalx999/Menu");
        jmethodID MSwitch = env->GetStaticMethodID(CMenu, "addSwitchWithSubCheck", "(Ljava/lang/String;II)V");
        env->CallStaticVoidMethod(CMenu, MSwitch, env->NewStringUTF(name), mainID, subID);
    }

    void SeekBar(const char* name, jint value, jint max, const char* type, jint ID) {
        seekBar.create(env, name, value, max, type, ID);
    }

    void Button(const char* label, const char* buttonText, jint ID) {
        jclass CMenu = env->FindClass("com/terminalx999/Menu");
        if (CMenu) {
            jmethodID MButton = env->GetStaticMethodID(CMenu, "addButton", "(Ljava/lang/String;Ljava/lang/String;I)V");
            if (MButton) {
                env->CallStaticVoidMethod(CMenu, MButton, env->NewStringUTF(label), env->NewStringUTF(buttonText), ID);
            }
        }
    }

};
