

1 Test 1(内部构建)
Main.c
/************/
#include <stdio.h>
int main()
{
	printf ("hello world!\n");
	return 0;
}
/****************/
CMakeLists.txt

/************/
PROJECT (HELLO)
SET(SRC_MAIN main.c)
MESSAGE(STATUS "This is BINARY dir " ${HELLO_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir "${HELLO_SOURCE_DIR})
ADD_EXECUTABLE(hello ${SRC_MAIN})
/****************/
1.
隐式的定义了两个cmake变量 
	<projectname>_BINARY_DIR
	<projectname>_SOURCE_DIR

为了统一起见，建议以后直接使用PROJECT_BINARY_DIR，PROJECT_SOURCE_DIR

2.SET 语法，可以指定多个文件
SET(SRC_LIST main.c)或SET(SRC_LIST main.c t1.c t2.c)。
SET(SRC_LIST “main.c”)

3. MESSAG语法，向终端输出用户定义的信息
MESSAGE(STATUS "This is BINARY dir " ${HELLO_BINARY_DIR})
或MESSAGE(STATUS “This is BINARY dir ${HELLO_BINARY_DIR}”)

?	SEND_ERROR，产生错误，生成过程被跳过。
?	SATUS，输出前缀为—的信息。
?	FATAL_ERROR，立即终止所有cmake过程.

4. ADD_EXECUTABLE语法
ADD_EXECUTABLE(hello ${SRC_LIST})
定义了这个工程会生成一个文件名为hello的可执行文件，相关的源文件是SRC_LIST中
定义的源文件列表

5.${}语法
变量引用，IF控制语句，变量是直接使用变量名引用




基本语法描述：
1，变量使用${}方式取值，但是在IF控制语句中是直接使用变量名
2，指令(参数1 参数2...)
参数使用括弧括起，参数之间使用空格或分号分开。
以上面的ADD_EXECUTABLE指令为例，如果存在另外一个func.c源文件，就要写成：
ADD_EXECUTABLE(hello main.c func.c)或者
ADD_EXECUTABLE(hello main.c;func.c)
3，指令是大小写无关的，参数和变量是大小写相关的。但，推荐你全部使用大写指令。


清理工程 make clean, 但是不支持make distclean, 没法删除生成的中间文件，check in的时候有问题？？


内部编译：如上述方式，会生成很多无法自动删除的临时文件
外部编译：
1，首先，请清除t1目录中除main.c CmakeLists.txt之外的所有中间文件
2，在t1目录中建立build 目录，当然你也可以在任何地方建立build目录，不一定必须在工程目录中。
3，进入build目录，运行cmake ..( cmake <工程的全路径>)
4，运行make构建工程

 
2 Test2(外部构建)
相比内部构建，可以更容易实现文件清理

使用外部编译构建一个更加合理的工程（camke_test2）
1，为工程添加一个子目录src，用来放置工程源代码;
2，添加一个子目录doc，用来放置这个工程的文档hello.txt
3，在工程目录添加文本文件COPYRIGHT, README；
4，在工程目录添加一个runhello.sh脚本，用来调用hello二进制
4，将构建后的目标文件放入构建目录的bin子目录；
5，最终安装这些文件：将hello二进制与runhello.sh安装至/usr/bin，将doc目录的内容以及COPYRIGHT/README安装到/usr/share/doc/cmake/t2


ADD_SUBDIRECTORY语法
ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
这个指令用于向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置

SUBDIRS语法
SUBDIRS(dir1 dir2...) 但是这个指令已经不推荐使用。它可以一次添加多个子目录，并且，即使外部编译，子目录体系仍然会被保存

换地方保存二进制文件方法
除上述方法外，还可以通过SET EXECUTABLE_OUTPUT_PATH和LIBRARY_OUTPUT_PATH来指定生成文件的存放路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
在哪里ADD_EXECUTABLE或ADD_LIBRARY，如果需要改变目标存放路径，就在哪里加入上述的定义
安装方法

1.手工修改makefile, 再make install 或make install DESTDIR=/tmp/test
DESTDIR = /home/wwan001/code
install :
#	mkdir -p $(DESTDIR)/usr/bin
	install -m 755 hello $(DESTDIR)/usr/bin
2.利用cmake直接安装
?	安装COPYRIGHT/README，直接修改主工程文件CMakelists.txt，加入以下指令：
	INSTALL(FILES COPYRIGHT README DESTINATION share/doc/cmake/t2)
?	安装runhello.sh，直接修改主工程文件CMakeLists.txt，加入如下指令：
	INSTALL(PROGRAMS runhello.sh DESTINATION bin)
?	安装doc中的hello.txt，这里有两种方式：一是通过在doc目录建立CMakeLists.txt并将doc目录通过ADD_SUBDIRECTORY加入工程来完成。另一种方法是直接在工程目录通过INSTALL(DIRECTORY来完成)，前者比较简单，
   INSTALL(DIRECTORY doc/ DESTINATION share/doc/cmake/t2)
?	cmake -D CMAKE_INSTALL_PREFIX=/home/wwan001/code/usr ..
?	make & make install


 
3 Test 3(静态库与动态库构建)
 	建立一个静态库和动态库，提供HelloFunc函数供其他程序编程使用，HelloFunc 向终端输出Hello World字符串。
 	安装头文件与共享库。


?	在lib目录下新建hello.c，hello.h和CMakeLists.txt
/****************hello.c*****************/
#include “hello.h”
void HelloFunc()
{
printf(“Hello World\n”);
}
/****************hello.h*****************/
#ifndef HELLO_H
#define HELLO_H
#include <stdio.h>
void HelloFunc();
#endif
/**************** CMakeLists.txt*****************/
SET(LIBHELLO_SRC hello.c)
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})



?	在cmake_test3目录下新建CMakeLists.txt
cmake_minimum_required(VERSION 2.6)
PROJECT(HELLOLIB)
ADD_SUBDIRECTORY(lib)

?	Cmake .. & make （编译共享库）
如果想改变*.so的生成位置：
1. 在主工程文件CMakeLists.txt中修改ADD_SUBDIRECTORY(lib)
注：lib目录必须包括缘文件，然后在bld目录下会生成同名文件夹存放so文件
2. lib/CMakeLists.txt中添加SET(LIBRARY_OUTPUT_PATH <路径>)来指定一个新的位置。


ADD_LIBRARY语法
ADD_LIBRARY(libname [SHARED|STATIC|MODULE] 
						[EXCLUDE_FROM_ALL] 
							source1 source2 ... sourceN)
你不需要写全libhello.so，只需要填写hello即可，cmake系统会自动为你生成libhello.X

SHARED，动态库
STATIC，静态库
MODULE，在使用dyld的系统有效，如果不支持dyld，则被当作SHARED对待。

EXCLUDE_FROM_ALL参数的意思是这个库不会被默认构建，除非有其他的组件依赖或者手
工构建。

?	同时产生静态库文件（*.a）
1. ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})---需取一个别名hello_static
2. 是向lib/CMakeLists.txt中添加：
SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")
SET_TARGET_PROPERTIES(hello PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

SET_TARGET_PROPERTIES语法：
SET_TARGET_PROPERTIES(target1 target2 ...
PROPERTIES prop1 value1
prop2 value2 ...)
这条指令可以用来设置输出的名称，对于动态库，还可以用来指定动态库版本和API版本。

?	为动态库添加版本号，如libhello.so.1.2
SET_TARGET_PROPERTIES(hello PROPERTIES VERSION 1.2 SOVERSION 1)
VERSION指代动态库版本，SOVERSION指代API版本。
将上述指令加入lib/CMakeLists.txt中

?	安装共享库头文件
我们需要将libhello.a, libhello.so.x以及hello.h安装到系统目录，才能真正让其他人开发使用
向lib/CMakeLists.txt中添加如下指令：
INSTALL(TARGETS hello hello_static
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib)
INSTALL(FILES hello.h DESTINATION include/hello)

将hello.so 安装到到${CMAKE_INSTALL_PREFIX}/lib目录
将hello.o 安装到到${CMAKE_INSTALL_PREFIX}/lib目录
将hello.h安装到到${CMAKE_INSTALL_PREFIX}/ include/hello目录
注意，静态库要使用ARCHIVE关键字
如果是安装可执行文件（包括脚本）
INSTALL(TARGETS….)

通过:
cmake -D CMAKE_INSTALL_PREFIX=/home/wwan001/code/usr ..
make
make install
我们就可以将头文件和共享库安装到系统目录/home/wwan001/code /usr/lib和/home/wwan001/code /usr/include/hello中了。

 
4 Test 4(如何使用外部共享库和头文件)
主目录下添加CMakeLists.txt
/*****************CMakeLists.txt***********/
PROJECT(NEWHELLO)
ADD_SUBDIRECTORY(src)

在src目录下添加main.c和CMakeLists.txt
/*****************main.c***********/
#include <hello.h>
int main()
{
    HelloFunc();
    return 0;
}
/*****************src/CMakeLists.txt***********/
INCLUDE_DIRECTORIES(/home/wwan001/code/usr/include/hello) #设置头文件路径
LINK_DIRECTORIES(/home/wwan001/code/usr/lib)            #添加共享库
ADD_EXECUTABLE(main src/main.c)
TARGET_LINK_LIBRARIES(main hello)


LINK_DIRECTORIES语法
LINK_DIRECTORIES(directory1 directory2 ...)   添加非标准的共享库搜索路径

TARGET_LINK_LIBRARIES语法
TARGET_LINK_LIBRARIES(target library1
<debug | optimized> library2
...)
这个指令可以用来为target添加需要链接的共享库


如果想调用静态库
TARGET_LINK_LIBRARIES(main libhello.a)
