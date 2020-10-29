#ifndef EYERLIB_EYERMP4_HPP
#define EYERLIB_EYERMP4_HPP

#include "MP4Box.hpp"
#include "MP4BoxFTYP.hpp"
#include "MP4BoxMVHD.hpp"
#include "MP4BoxTKHD.hpp"
#include "MP4BoxELST.hpp"
#include "MP4BoxHDLR.hpp"
#include "MP4BoxDREF.hpp"
#include "MP4BoxTREX.hpp"
#include "MP4BoxMEHD.hpp"
#include "MP4BoxSTSD.hpp"
#include "MP4BoxSTTS.hpp"
#include "MP4BoxSTSC.hpp"
#include "MP4BoxSTCO.hpp"

/*
 *
 * 该模块主要用于解析 MP4 文件和 Buffer
 *
 * MP4 文件由 Box 组成，先读 4 个字节，这四个字节表示这个 Box 的大小，在读 4 个字节，这四个字节表示这个 Box 的类型。Box 可以嵌套
 *
 * 增加一种 Box 类型的流程：
 * 1，首先查看这种 Box 的名称是否已经添加（在 BoxType.hpp 里面枚举了所有类型）
 * 2，如果没有的话，添加一个 BoxType，并且在 BoxType::GetType 函数中返回
 * 3，如果这个 Box 没有详细内容，只是一个父容器，添加好类型就可以了
 * 4，如果这个类型有详细内容，就要新建一个类，这个类叫做 MP4BoxXXXX（XXXX 表示类型名称的大写名称）
 * 5，这个类根据情况继承自 MP4Box 或者 MP4FullBox
 * 6，需要覆写   EyerBuffer SerializeParam();
 *             int ParseParam(EyerBuffer & buffer, int offset);
 *             int PrintInfo(int level = 0);
 * 7，int ParseParam(EyerBuffer & buffer, int offset); 为解析函数，buffer 是这个 Box 的二进制内容，offset是需要跳过的长度（处理Box 头已经在父类中做了）
 * 8，EyerBuffer SerializeParam(); 为序列化，将这个 Box 的参数序列化成一个 Buffer
 * 9，int PrintInfo(int level = 0); 为打印这个类的信息
 * 10，测试用例，在 EyerMP4Test 里面，新建一个头文件，名称为你要测试的 Box 名称，编写测试用例：先新建一个Box 对象，为其设置一些假数据，然后将其序列化，然后再讲序列化之后的 Buffer 反序列化，对比序列化前后是否相等
 *
 */

#endif //EYERLIB_EYERMP4_HPP
