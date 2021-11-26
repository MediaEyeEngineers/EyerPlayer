cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

${JAVA_HOME}/bin/javac -h ./ ${basepath}/EyerPlayerAndroid/eyerplayer/src/main/java/com/zzsin/eyerplayer/jni/EyerPlayerJNI.java -classpath ${ANDROID_SDK_HOME}/platforms/android-22/android.jar:${basepath}/EyerPlayerAndroid/eyerplayer/src/main/java/:.

mv ${basepath}/com_zzsin_eyerplayer_jni_EyerPlayerJNI.h ${basepath}/src/EyerAndroidInterface/com_zzsin_eyerplayer_jni_EyerPlayerJNI.h