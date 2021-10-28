cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ./Eyer3rdpart ];then 
    rm -rf Eyer3rdpart
fi

git clone https://gitee.com/redknot/Eyer3rdpart

files=$(ls $NDK/toolchains/llvm/prebuilt/)
HOST_TAG=$""
for filename in $files
do
    echo $filename
    HOST_TAG=$filename
done

# HOST_TAG=linux-x86_64
# HOST_TAG=darwin-x86_64
# HOST_TAG=windows-x86_64

echo "HOST_TAG:"$HOST_TAG

export ANDROID_NDK_HOME=$NDK
export TOOLCHAIN=$NDK/toolchains/llvm/prebuilt/$HOST_TAG

# Only choose one of these, depending on your device...
# export TARGET=aarch64-linux-android
export TARGET=armv7a-linux-androideabi
# export TARGET=i686-linux-android
# export TARGET=x86_64-linux-android


# Set this to your minSdkVersion.
export API=18

export CC=$TOOLCHAIN/bin/$TARGET$API-clang
export CXX=$TOOLCHAIN/bin/$TARGET$API-clang++

# export AR=$TOOLCHAIN/bin/$TARGET-ar
export AR=$TOOLCHAIN/bin/arm-linux-androideabi-ar
export AS=$TOOLCHAIN/bin/arm-linux-androideabi-as
export LD=$TOOLCHAIN/bin/arm-linux-androideabi-ld
export RANLIB=$TOOLCHAIN/bin/arm-linux-androideabi-ranlib
export STRIP=$TOOLCHAIN/bin/arm-linux-androideabi-strip



export COMMON_FF_CFG_FLAGS=
. ${basepath}/tools/configs/module.sh

# echo $COMMON_FF_CFG_FLAGS

:<<!

cd ${basepath}/Eyer3rdpart/ffmpeg_3.2.14/
./configure \
--enable-static \
--disable-shared \
--disable-ffmpeg \
--disable-ffplay \
--disable-ffprobe \
--disable-ffserver \
--disable-avdevice \
--disable-doc \
--disable-symver \
--prefix=./ffmpeg_install \
--enable-libx264 \
--enable-gpl \
--enable-pic \
--disable-neon \
--extra-cflags=-I${basepath}/Eyer3rdpart/x264/x264_install/include/ \
--extra-ldflags=-L${basepath}/Eyer3rdpart/x264/x264_install/lib/ \
--enable-cross-compile \
--target-os=android \
--arch=arm \
--nm=$TOOLCHAIN/bin/arm-linux-androideabi-nm \
--cc=$TOOLCHAIN/bin/$TARGET$API-clang \
--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi-
make clean
make -j4
make install
cd ../../

!

cd ${basepath}/Eyer3rdpart/
chmod -R 777 ffmpeg-4.4

cd ${basepath}/Eyer3rdpart/ffmpeg-4.4/
./configure \
$COMMON_FF_CFG_FLAGS \
--prefix=./ffmpeg_install \
--enable-cross-compile \
--target-os=android \
--arch=arm \
--nm=$TOOLCHAIN/bin/arm-linux-androideabi-nm \
--cc=$TOOLCHAIN/bin/$TARGET$API-clang \
--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi-

make clean
make -j4
make install


:<<!
export CC=$TARGET$API-clang
export PATH=$TOOLCHAIN"/bin":$PATH
cd ${basepath}/Eyer3rdpart/openssl-1.1.1g/
./Configure \
android-arm -D__ANDROID_API__=$API no-asm no-ssl2 no-ssl3 no-comp no-hw no-engine --prefix=${basepath}/Eyer3rdpart/openssl-1.1.1g/openssl_install

make clean
make -j4
make install

cd ${basepath}/Eyer3rdpart/openssl-1.1.1g/openssl_install/lib
rm libcrypto.so
rm libcrypto.so.1.1
rm libssl.so
rm libssl.so.1.1





export CC=$TOOLCHAIN/bin/$TARGET$API-clang
cd ${basepath}/Eyer3rdpart/curl-7.72.0/
./configure \
--enable-static \
--disable-shared \
--prefix=${basepath}/Eyer3rdpart/curl-7.72.0/curl_install \
--host=arm-linux-androideabi \
--with-ssl=${basepath}/Eyer3rdpart/openssl-1.1.1g/openssl_install

make clean
make -j4
make install






cd ${basepath}/Eyer3rdpart/platform_external_libxml2/
$NDK/ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk
!

cd ${basepath}

if [ -d ./Lib ];then
    rm -rf Lib
fi

mkdir Lib

:<<!
cd ${basepath}/Lib/
mkdir libxml2_install
cd libxml2_install
mkdir include
cd include
mkdir libxml2
cd ${basepath}/Lib/
cp -r ${basepath}/Eyer3rdpart/platform_external_libxml2/include/libxml ${basepath}/Lib/libxml2_install/include/libxml2
cd ${basepath}/Lib/libxml2_install
mkdir lib
cp ${basepath}/Eyer3rdpart/platform_external_libxml2/obj/local/armeabi-v7a/libxml2.a ${basepath}/Lib/libxml2_install/lib/libxml2.a
!


cd ${basepath}
cp -r Eyer3rdpart/ffmpeg-4.4/ffmpeg_install Lib/ffmpeg_install
# cp -r Eyer3rdpart/openssl-1.1.1g/openssl_install Lib/openssl_install
# cp -r Eyer3rdpart/curl-7.72.0/curl_install Lib/curl_install




