cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

cd src/

if [ -d ./player_core_build ];then 
    rm -rf player_core_build
fi
mkdir player_core_build

cd player_core_build
cmake ../

make clean
make -j4
make install

cd ${basepath}/

cp -r ${basepath}/src/install/ ${basepath}/Lib/EyerPlayer_install/
