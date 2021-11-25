cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

# 下载代码

if [ -d ./Eyer3rdpart ];then 
    rm -rf Eyer3rdpart
fi

git clone https://gitee.com/redknot/Eyer3rdpart

cd ${basepath}/Eyer3rdpart/
chmod -R 777 ffmpeg-4.4

# 配置 NDK
if [ -z $NDK ]; then
    echo ""
    echo ""
    echo ""
    echo "==========Please set NDK path first=========="
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

    TARGET=$2
    ARCH=$3

    export TOOLCHAIN=$NDK/toolchains/llvm/prebuilt/$HOST_TAG

    # export TARGET=aarch64-linux-android
    # export TARGET=armv7a-linux-androideabi
    # export TARGET=i686-linux-android
    # export TARGET=x86_64-linux-android
    

    echo 'TARGET: '$TARGET

    export API=21

    # export CC=$TOOLCHAIN/bin/$TARGET$API-clang
    # export CXX=$TOOLCHAIN/bin/$TARGET$API-clang++

    # export AR=$TOOLCHAIN/bin/$TARGET-ar
    export AR=$TOOLCHAIN/bin/arm-linux-androideabi-ar
    export AS=$TOOLCHAIN/bin/arm-linux-androideabi-as
    export LD=$TOOLCHAIN/bin/arm-linux-androideabi-ld
    export RANLIB=$TOOLCHAIN/bin/arm-linux-androideabi-ranlib
    export STRIP=$TOOLCHAIN/bin/arm-linux-androideabi-strip

    # 配置 FFmpeg 选项 

    export COMMON_FF_CFG_FLAGS=
    . ${basepath}/tools/configs/module.sh

    ## x86 的 asm 编译不过去，直接干掉
    if [ $1 == "i686" ];then 
        export COMMON_FF_CFG_FLAGS="$COMMON_FF_CFG_FLAGS --disable-asm"
    fi
    
    if [ $1 == "x86_64" ];then 
        export COMMON_FF_CFG_FLAGS="$COMMON_FF_CFG_FLAGS --disable-asm"
    fi

    cd ${basepath}/Eyer3rdpart/ffmpeg-4.4/

    make clean
    make distclean

    ./configure \
    $COMMON_FF_CFG_FLAGS \
    --prefix=${basepath}/Eyer3rdpart/ffmpeg-4.4/ffmpeg_install \
    --enable-cross-compile \
    --arch=$ARCH \
    --target-os=android \
    --nm=$TOOLCHAIN/bin/arm-linux-androideabi-nm \
    --cc=$TOOLCHAIN/bin/$TARGET$API-clang \
    --cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi-

    make clean
    make -j8
    make install

    cd ${basepath}
    cp -r Eyer3rdpart/ffmpeg-4.4/ffmpeg_install Lib/ffmpeg/$1
}

cd ${basepath}

if [ -d ./Lib ];then
    rm -rf Lib
fi

mkdir Lib

cd Lib
mkdir ffmpeg

cd ${basepath}

ffmpeg_compile armv7a armv7a-linux-androideabi arm
ffmpeg_compile aarch64 aarch64-linux-android arm64
ffmpeg_compile i686 i686-linux-android x86
ffmpeg_compile x86_64 x86_64-linux-android x86_64