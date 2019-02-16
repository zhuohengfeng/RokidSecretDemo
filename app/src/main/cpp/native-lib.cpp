#include <jni.h>
#include <string>

extern void getRokidSecret(const char *sn, const char *seed, char *secretStr);

extern "C"
JNIEXPORT jstring JNICALL
Java_com_rokid_rokidsecretdemo_MainActivity_getRokidSecret(JNIEnv *env, jobject instance,
                                                           jstring sn_, jstring seed_) {
    const char *sn = env->GetStringUTFChars(sn_, 0);
    const char *seed = env->GetStringUTFChars(seed_, 0);

    char secretStr[64] = {0};
    getRokidSecret(sn , seed, secretStr);
    return (*env).NewStringUTF(secretStr);
}