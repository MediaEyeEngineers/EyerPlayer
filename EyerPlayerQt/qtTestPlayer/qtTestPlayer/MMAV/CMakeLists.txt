cmake_minimum_required (VERSION 3.8)

include_directories(../3rdpart/ffmpge/include)

add_library (
	MMAV
	"MMAVReader.cpp"
	"MMAVPacket.cpp"
	"MMAVDecoder.cpp"
	"MMAVStream.cpp" 
	"MMAVFream.cpp"
	"MMAVTime.cpp"
	 
)



