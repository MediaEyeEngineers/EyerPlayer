cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ./Eyer3rdpart ];then 
    rm -rf Eyer3rdpart
fi

git clone https://gitee.com/redknot/Eyer3rdpart

cd ${basepath}/Eyer3rdpart/
chmod -R 777 ffmpeg-4.4

export COMMON_FF_CFG_FLAGS=
. ${basepath}/tools/configs/module.sh

cd ${basepath}/Eyer3rdpart/ffmpeg-4.4/
./configure \
$COMMON_FF_CFG_FLAGS \
--prefix=./ffmpeg_install

make clean
make -j8
make install









cd ${basepath}

if [ -d ./Lib ];then
    rm -rf Lib
fi

mkdir Lib

cd ${basepath}
cp -r Eyer3rdpart/ffmpeg-4.4/ffmpeg_install Lib/ffmpeg_install

cd ${basepath}/Lib
mkdir QtLib
cd QtLib
QT_LIB_PATH=/Users/yuqiaomiao/Qt/5.15.2/clang_64/lib/
ln -s ${QT_LIB_PATH}/QtCore.framework/Versions/5/Headers/ QtCore
ln -s ${QT_LIB_PATH}/QtGui.framework/Versions/5/Headers/ QtGui