cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

cd ${basepath}/EyerPlayerCore

if [ -d ./build ];then 
    rm -rf build
fi

if [ -d ./install ];then 
    rm -rf install
fi

mkdir build

cd build

cmake ../ \
-DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake \
-DANDROID_ABI=armeabi-v7a \
-DANDROID_NATIVE_API_LEVEL=21

make
make install

cp ${basepath}/EyerPlayerCore/install/lib/libEyerPlayerJNI.so ${basepath}/EyerPlayerAndroid/eyerplayer_lib/src/main/jniLibs/armeabi-v7a/libEyerPlayerJNI.so

cd ${basepath}/EyerPlayerAndroid/eyerplayer_lib/src/main/jniLibs/armeabi-v7a/
ls -lh