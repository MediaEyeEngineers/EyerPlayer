cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

# 配置 NDK
if [ -z $NDK ]; then
    echo ""
    echo ""
    echo ""
    echo "==========Please set NDK path first=========="
    echo "export NDK=......"
    echo ""
    echo ""
    echo ""
    exit 1;
fi

files=$(ls $NDK/toolchains/llvm/prebuilt/)
HOST_TAG=$""
for filename in $files
do
    echo $filename
    HOST_TAG=$filename
done

echo "HOST_TAG:"$HOST_TAG

PATH=$NDK/toolchains/llvm/prebuilt/$HOST_TAG/bin:$PATH
export ANDROID_NDK_HOME=$NDK




# 下载代码

if [ -d ./Eyer3rdpart ];then 
    rm -rf Eyer3rdpart
fi

git clone https://gitee.com/redknot/Eyer3rdpart

cd ${basepath}/Eyer3rdpart/
chmod -R 777 ffmpeg-4.4




ffmpeg_compile() {

    echo ""
    echo ""
    echo ""
    echo "Lets build FFmpeg for Android $1 !!!!"
    echo ""
    echo ""
    echo ""

    cd ${basepath}/Eyer3rdpart/ffmpeg-4.4/

    if [ -d ./ffmpeg_install ];then 
        rm -rf ffmpeg_install
    fi

    export TOOLCHAIN=$NDK/toolchains/llvm/prebuilt/$HOST_TAG    

    export API=21

    # export CC=$TOOLCHAIN/bin/$TARGET$API-clang
    # export CXX=$TOOLCHAIN/bin/$TARGET$API-clang++

    if [ $1 == "armeabi-v7a" ];then 
        export CROSS_PREFIX="arm-linux-androideabi-"
        export ARCH="arm"
        export CC=$TOOLCHAIN/bin/armv7a-linux-androideabi$API-clang
        export CXX=$TOOLCHAIN/bin/armv7a-linux-androideabi$API-clang++
        export AR=$TOOLCHAIN/bin/arm-linux-androideabi-ar
        export AS=$TOOLCHAIN/bin/arm-linux-androideabi-as
        export LD=$TOOLCHAIN/bin/arm-linux-androideabi-ld
        export NM=$TOOLCHAIN/bin/arm-linux-androideabi-nm
        export RANLIB=$TOOLCHAIN/bin/arm-linux-androideabi-ranlib
        export STRIP=$TOOLCHAIN/bin/arm-linux-androideabi-strip
    fi
    
    if [ $1 == "arm64-v8a" ];then 
        export CROSS_PREFIX="aarch64-linux-android-"
        export ARCH="arm64"
        export CC=$TOOLCHAIN/bin/aarch64-linux-android$API-clang
        export CXX=$TOOLCHAIN/bin/aarch64-linux-android$API-clang++
        export AR=$TOOLCHAIN/bin/aarch64-linux-android-ar
        export AS=$TOOLCHAIN/bin/aarch64-linux-android-as
        export LD=$TOOLCHAIN/bin/aarch64-linux-android-ld
        export NM=$TOOLCHAIN/bin/aarch64-linux-android-nm
        export RANLIB=$TOOLCHAIN/bin/aarch64-linux-android-ranlib
        export STRIP=$TOOLCHAIN/bin/aarch64-linux-android-strip
    fi

    if [ $1 == "x86" ];then 
        export CROSS_PREFIX="i686-linux-android-"
        export ARCH="x86"
        export CC=$TOOLCHAIN/bin/i686-linux-android$API-clang
        export CXX=$TOOLCHAIN/bin/i686-linux-android$API-clang++
        export AR=$TOOLCHAIN/bin/i686-linux-android-ar
        export AS=$TOOLCHAIN/bin/i686-linux-android-as
        export LD=$TOOLCHAIN/bin/i686-linux-android-ld
        export NM=$TOOLCHAIN/bin/i686-linux-android-nm
        export RANLIB=$TOOLCHAIN/bin/i686-linux-android-ranlib
        export STRIP=$TOOLCHAIN/bin/i686-linux-android-strip
    fi
    
    if [ $1 == "x86_64" ];then 
        export CROSS_PREFIX="x86_64-linux-android-"
        export ARCH="x86_64" 
        export CC=$TOOLCHAIN/bin/x86_64-linux-android$API-clang
        export CXX=$TOOLCHAIN/bin/x86_64-linux-android$API-clang++
        export AR=$TOOLCHAIN/bin/x86_64-linux-android-ar
        export AS=$TOOLCHAIN/bin/x86_64-linux-android-as
        export LD=$TOOLCHAIN/bin/x86_64-linux-android-ld
        export NM=$TOOLCHAIN/bin/x86_64-linux-android-nm
        export RANLIB=$TOOLCHAIN/bin/x86_64-linux-android-ranlib
        export STRIP=$TOOLCHAIN/bin/x86_64-linux-android-strip
    fi

    # 配置 FFmpeg 选项 

    export COMMON_FF_CFG_FLAGS=
    . ${basepath}/tools/configs/module.sh
    
    ## x86 的 asm 编译不过去，直接干掉
    if [ $1 == "x86" ];then 
        export COMMON_FF_CFG_FLAGS="$COMMON_FF_CFG_FLAGS --disable-asm"
    fi
    
    if [ $1 == "x86_64" ];then 
        export COMMON_FF_CFG_FLAGS="$COMMON_FF_CFG_FLAGS --disable-asm"
    fi

    cd ${basepath}/Eyer3rdpart/ffmpeg-4.4/

    make clean
    make distclean

    echo "-I${basepath}/Lib/android/openssl_install/$1/include/"
    echo "-L${basepath}/Lib/android/openssl_install/$1/lib/"

    echo $COMMON_FF_CFG_FLAGS

    echo ""
    echo ""
    echo ""
    echo "ARCH: $ARCH"
    echo "NM: $NM"
    echo "CC: $CC"
    echo "STRIP: $STRIP"
    echo ""
    echo ""
    echo ""

    ./configure \
    $COMMON_FF_CFG_FLAGS \
    --prefix=${basepath}/Eyer3rdpart/ffmpeg-4.4/ffmpeg_install \
    --enable-cross-compile \
    --arch=$ARCH \
    --target-os=android \
    --nm=$NM \
    --cc=$CC \
    --strip=$STRIP \
    --cross-prefix=$TOOLCHAIN/bin/$CROSS_PREFIX \
    --extra-cflags="-I${basepath}/Lib/android/openssl_install/$1/include/" \
    --extra-ldflags="-L${basepath}/Lib/android/openssl_install/$1/lib/"

    make clean
    make -j8
    make install

    cd ${basepath}
    cp -r Eyer3rdpart/ffmpeg-4.4/ffmpeg_install Lib/android/ffmpeg_install/$1
}

openssl_compile() {
    echo ""
    echo ""
    echo ""
    echo "Lets build OpenSSL for Android $1 !!!!"
    echo ""
    echo ""
    echo ""

    export CC=""
    export CXX=""
    export AR=""
    export AS=""
    export LD=""
    export NM=""
    export RANLIB=""
    export STRIP=""

    cd ${basepath}/Eyer3rdpart/openssl-1.1.1k/
    make clean
    make distclean

    CC=clang

    if [ $1 == "armeabi-v7a" ];then 
        export OPENSSL_ARCH="android-arm"
    fi

    if [ $1 == "arm64-v8a" ];then 
        export OPENSSL_ARCH="android-arm64"
    fi

    if [ $1 == "x86" ];then 
        export OPENSSL_ARCH="android-x86 no-asm"
    fi

    if [ $1 == "x86_64" ];then 
        export OPENSSL_ARCH="android-x86_64 no-asm"
    fi

    ./Configure \
    no-shared \
    --prefix=${basepath}/Eyer3rdpart/openssl-1.1.1k/openssl_install \
    ${OPENSSL_ARCH} \
    -D__ANDROID_API__=21

    make clean
    make -j8
    make install

    cd ${basepath}
    cp -r Eyer3rdpart/openssl-1.1.1k/openssl_install Lib/android/openssl_install/$1
}

cd ${basepath}

if [ -d ./Lib ];then
    rm -rf Lib
fi

mkdir Lib

cd Lib
mkdir android

cd android
mkdir ffmpeg_install
mkdir openssl_install

cd ${basepath}


openssl_compile armeabi-v7a
openssl_compile arm64-v8a
openssl_compile x86
openssl_compile x86_64

ffmpeg_compile armeabi-v7a
ffmpeg_compile arm64-v8a
ffmpeg_compile x86
ffmpeg_compile x86_64