# Rokid设备生成SecretID Demo

## 背景
Rokid设备进行账号绑定，或语音鉴权等操作时都需要生产一个secret id进行网络鉴权。
本demo演示了如何配置编译Rokid鉴权so，并调用其API，传入sn+seed参数, 来获取SecretId的流程。

## 编译

### 1. 添加so文件
把rokid鉴权so 【libstupid.so】 放在 src/main/cpp/armeabi-v7a目录下

### 2. gradle配置（app/build.gradle）
        externalNativeBuild {
            cmake {
                cppFlags ""
            }
            ndk {
                abiFilters "armeabi-v7a" //只支持armeabi-v7a
            }
        }
        sourceSets {
            main {
                jniLibs.srcDirs = ['src/main/cpp']
            }
        }

### 3. CMAKE配置(src/main/cpp/CMakeList.txt)
        add_library( stupid
                SHARED
                IMPORTED)
        set_target_properties( stupid
                PROPERTIES IMPORTED_LOCATION
                ${CMAKE_SOURCE_DIR}/armeabi-v7a/libstupid.so)
        .....
        target_link_libraries( # Specifies the target library.
                native-lib
                stupid

                # Links the target library to the log library
                # included in the NDK.
                ${log-lib})

### 4. 修改JNI文件native-lib.cpp
```java
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
```
完成以上配置后就完成JNI的配置和编译。

## 调用
在JAVA代码中调用native接口：
```java
public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.sample_text);

        // e.g. 输入设备的sn号和seed
        String sn = "601091847330038";
        String seed = "NZUNwyiLdxv0Ut2ItrHwVfLCAlu7zM";
        String secret = getRokidSecret(sn, seed);
        tv.setText("sn: " + sn +
                "\nseed: " + seed +
                "\nseed: "+secret); //"正确的值为: 260EB4D4583B5BBA91DEF14150109A39";
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String getRokidSecret(String sn, String seed);
}
```
