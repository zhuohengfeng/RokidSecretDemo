#include <jni.h>
#include <string>

extern void getRokidSecret(const char *sn, const char *seed, char *secretStr);

extern "C"
JNIEXPORT jstring JNICALL
Java_com_rokid_rokidsecretdemo_MainActivity_getRokidSecret(JNIEnv *env, jobject instance,
                                                           jstring sn_, jstring seed_) {
    const char *sn = env->GetStringUTFChars(sn_, 0);
    const char *seed = env->GetStringUTFChars(seed_, 0);

    //LOGD("Rokid =====>>snContent %s",sn); //601091847330038
    //LOGD("Rokid =====>>seedContent %s",seed); //NZUNwyiLdxv0Ut2ItrHwVfLCAlu7zM

    char secretStr[64] = {0};
    getRokidSecret(sn , seed, secretStr);
    //LOGD("Rokid =====>>seedContent %s",secretStr); //260EB4D4583B5BBA91DEF14150109A39
    return (*env).NewStringUTF(secretStr);
}