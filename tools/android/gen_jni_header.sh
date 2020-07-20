cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

javac -h ./ ${basepath}/EyerPlayerAndroid/eyerplayer_lib/src/main/java/com/eyer/eyerplayer/EyerPlayerJNI.java

mv ${basepath}/com_eyer_eyerplayer_EyerPlayerJNI.h ${basepath}/EyerPlayerCore/EyerPlayerJNI/com_eyer_eyerplayer_EyerPlayerJNI.h

cd ${basepath}/EyerPlayerAndroid/eyerplayer_lib/src/main/java/com/eyer/eyerplayer/