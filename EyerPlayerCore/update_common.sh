basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ./EyerLibTemp ];then 
    rm -rf EyerLibTemp
fi

mkdir EyerLibTemp
cd ${basepath}/EyerLibTemp
git clone https://gitee.com/redknot/EyerLib
cd ${basepath}/EyerLibTemp/EyerLib
git checkout -b dev origin/dev

cd ${basepath}
if [ -d ./EyerCore ];then 
    rm -rf EyerCore
fi
cp -r ${basepath}/EyerLibTemp/EyerLib/Lib/EyerCore ./EyerCore




cd ${basepath}
if [ -d ./EyerThread ];then 
    rm -rf EyerThread
fi
cp -r ${basepath}/EyerLibTemp/EyerLib/Lib/EyerThread ./EyerThread




cd ${basepath}
if [ -d ./EyerDASH ];then 
    rm -rf EyerDASH
fi
cp -r ${basepath}/EyerLibTemp/EyerLib/Lib/EyerDASH ./EyerDASH




cd ${basepath}
if [ -d ./EyerAV ];then 
    rm -rf EyerAV
fi
cp -r ${basepath}/EyerLibTemp/EyerLib/Lib/EyerAV ./EyerAV




cd ${basepath}
if [ -d ./EyerNet ];then 
    rm -rf EyerNet
fi
cp -r ${basepath}/EyerLibTemp/EyerLib/Lib/EyerNet ./EyerNet





cd ${basepath}
if [ -d ./EyerMP4 ];then 
    rm -rf EyerMP4
fi
cp -r ${basepath}/EyerLibTemp/EyerLib/Lib/EyerMP4 ./EyerMP4





cd ${basepath}
if [ -d ./EyerLibTemp ];then 
    rm -rf EyerLibTemp
fi