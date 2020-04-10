basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ./FFmpeg-QuQi-Analyzer ];then 
    rm -rf FFmpeg-QuQi-Analyzer
fi

git clone https://gitee.com/redknot/FFmpeg-QuQi-Analyzer

cd ${basepath}/FFmpeg-QuQi-Analyzer
./configure --enable-static --enable-shared --prefix=./ffmpeg_install --enable-videotoolbox

make clean
make -j4
make install

cd ${basepath}

if [ -d ./Lib3rd ];then
    rm -rf Lib3rd
fi

mkdir Lib3rd
cp -r FFmpeg-QuQi-Analyzer/ffmpeg_install Lib3rd/ffmpeg_install