cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

cd ${basepath}/EyerPlayerCore

if [ -d ./ios_build ];then 
    rm -rf ios_build
fi

if [ -d ./ios_install ];then 
    rm -rf ios_install
fi

mkdir ios_build

cd ios_build

cmake ../ \
-G Xcode \
-DCMAKE_TOOLCHAIN_FILE=${basepath}/tools/ios-cmake/ios.toolchain.cmake \
-DPLATFORM=OS64COMBINED

cmake --build . --config Release
cmake --install . --config Release