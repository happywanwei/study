

1 Test 1(�ڲ�����)
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
��ʽ�Ķ���������cmake���� 
	<projectname>_BINARY_DIR
	<projectname>_SOURCE_DIR

Ϊ��ͳһ����������Ժ�ֱ��ʹ��PROJECT_BINARY_DIR��PROJECT_SOURCE_DIR

2.SET �﷨������ָ������ļ�
SET(SRC_LIST main.c)��SET(SRC_LIST main.c t1.c t2.c)��
SET(SRC_LIST ��main.c��)

3. MESSAG�﷨�����ն�����û��������Ϣ
MESSAGE(STATUS "This is BINARY dir " ${HELLO_BINARY_DIR})
��MESSAGE(STATUS ��This is BINARY dir ${HELLO_BINARY_DIR}��)

?	SEND_ERROR�������������ɹ��̱�������
?	SATUS�����ǰ׺Ϊ������Ϣ��
?	FATAL_ERROR��������ֹ����cmake����.

4. ADD_EXECUTABLE�﷨
ADD_EXECUTABLE(hello ${SRC_LIST})
������������̻�����һ���ļ���Ϊhello�Ŀ�ִ���ļ�����ص�Դ�ļ���SRC_LIST��
�����Դ�ļ��б�

5.${}�﷨
�������ã�IF������䣬������ֱ��ʹ�ñ���������




�����﷨������
1������ʹ��${}��ʽȡֵ��������IF�����������ֱ��ʹ�ñ�����
2��ָ��(����1 ����2...)
����ʹ���������𣬲���֮��ʹ�ÿո��ֺŷֿ���
�������ADD_EXECUTABLEָ��Ϊ���������������һ��func.cԴ�ļ�����Ҫд�ɣ�
ADD_EXECUTABLE(hello main.c func.c)����
ADD_EXECUTABLE(hello main.c;func.c)
3��ָ���Ǵ�Сд�޹صģ������ͱ����Ǵ�Сд��صġ������Ƽ���ȫ��ʹ�ô�дָ�


������ make clean, ���ǲ�֧��make distclean, û��ɾ�����ɵ��м��ļ���check in��ʱ�������⣿��


�ڲ����룺��������ʽ�������ɺܶ��޷��Զ�ɾ������ʱ�ļ�
�ⲿ���룺
1�����ȣ������t1Ŀ¼�г�main.c CmakeLists.txt֮��������м��ļ�
2����t1Ŀ¼�н���build Ŀ¼����Ȼ��Ҳ�������κεط�����buildĿ¼����һ�������ڹ���Ŀ¼�С�
3������buildĿ¼������cmake ..( cmake <���̵�ȫ·��>)
4������make��������

 
2 Test2(�ⲿ����)
����ڲ����������Ը�����ʵ���ļ�����

ʹ���ⲿ���빹��һ�����Ӻ���Ĺ��̣�camke_test2��
1��Ϊ�������һ����Ŀ¼src���������ù���Դ����;
2�����һ����Ŀ¼doc����������������̵��ĵ�hello.txt
3���ڹ���Ŀ¼����ı��ļ�COPYRIGHT, README��
4���ڹ���Ŀ¼���һ��runhello.sh�ű�����������hello������
4�����������Ŀ���ļ����빹��Ŀ¼��bin��Ŀ¼��
5�����հ�װ��Щ�ļ�����hello��������runhello.sh��װ��/usr/bin����docĿ¼�������Լ�COPYRIGHT/README��װ��/usr/share/doc/cmake/t2


ADD_SUBDIRECTORY�﷨
ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
���ָ��������ǰ������Ӵ��Դ�ļ�����Ŀ¼��������ָ���м�����ƺ�Ŀ������ƴ�ŵ�λ��

SUBDIRS�﷨
SUBDIRS(dir1 dir2...) �������ָ���Ѿ����Ƽ�ʹ�á�������һ����Ӷ����Ŀ¼�����ң���ʹ�ⲿ���룬��Ŀ¼��ϵ��Ȼ�ᱻ����

���ط�����������ļ�����
�����������⣬������ͨ��SET EXECUTABLE_OUTPUT_PATH��LIBRARY_OUTPUT_PATH��ָ�������ļ��Ĵ��·��
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
������ADD_EXECUTABLE��ADD_LIBRARY�������Ҫ�ı�Ŀ����·��������������������Ķ���
��װ����

1.�ֹ��޸�makefile, ��make install ��make install DESTDIR=/tmp/test
DESTDIR = /home/wwan001/code
install :
#	mkdir -p $(DESTDIR)/usr/bin
	install -m 755 hello $(DESTDIR)/usr/bin
2.����cmakeֱ�Ӱ�װ
?	��װCOPYRIGHT/README��ֱ���޸��������ļ�CMakelists.txt����������ָ�
	INSTALL(FILES COPYRIGHT README DESTINATION share/doc/cmake/t2)
?	��װrunhello.sh��ֱ���޸��������ļ�CMakeLists.txt����������ָ�
	INSTALL(PROGRAMS runhello.sh DESTINATION bin)
?	��װdoc�е�hello.txt�����������ַ�ʽ��һ��ͨ����docĿ¼����CMakeLists.txt����docĿ¼ͨ��ADD_SUBDIRECTORY���빤������ɡ���һ�ַ�����ֱ���ڹ���Ŀ¼ͨ��INSTALL(DIRECTORY�����)��ǰ�߱Ƚϼ򵥣�
   INSTALL(DIRECTORY doc/ DESTINATION share/doc/cmake/t2)
?	cmake -D CMAKE_INSTALL_PREFIX=/home/wwan001/code/usr ..
?	make & make install


 
3 Test 3(��̬���붯̬�⹹��)
 	����һ����̬��Ͷ�̬�⣬�ṩHelloFunc����������������ʹ�ã�HelloFunc ���ն����Hello World�ַ�����
 	��װͷ�ļ��빲��⡣


?	��libĿ¼���½�hello.c��hello.h��CMakeLists.txt
/****************hello.c*****************/
#include ��hello.h��
void HelloFunc()
{
printf(��Hello World\n��);
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



?	��cmake_test3Ŀ¼���½�CMakeLists.txt
cmake_minimum_required(VERSION 2.6)
PROJECT(HELLOLIB)
ADD_SUBDIRECTORY(lib)

?	Cmake .. & make �����빲��⣩
�����ı�*.so������λ�ã�
1. ���������ļ�CMakeLists.txt���޸�ADD_SUBDIRECTORY(lib)
ע��libĿ¼�������Ե�ļ���Ȼ����bldĿ¼�»�����ͬ���ļ��д��so�ļ�
2. lib/CMakeLists.txt�����SET(LIBRARY_OUTPUT_PATH <·��>)��ָ��һ���µ�λ�á�


ADD_LIBRARY�﷨
ADD_LIBRARY(libname [SHARED|STATIC|MODULE] 
						[EXCLUDE_FROM_ALL] 
							source1 source2 ... sourceN)
�㲻��Ҫдȫlibhello.so��ֻ��Ҫ��дhello���ɣ�cmakeϵͳ���Զ�Ϊ������libhello.X

SHARED����̬��
STATIC����̬��
MODULE����ʹ��dyld��ϵͳ��Ч�������֧��dyld���򱻵���SHARED�Դ���

EXCLUDE_FROM_ALL��������˼������ⲻ�ᱻĬ�Ϲ������������������������������
��������

?	ͬʱ������̬���ļ���*.a��
1. ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})---��ȡһ������hello_static
2. ����lib/CMakeLists.txt����ӣ�
SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")
SET_TARGET_PROPERTIES(hello PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

SET_TARGET_PROPERTIES�﷨��
SET_TARGET_PROPERTIES(target1 target2 ...
PROPERTIES prop1 value1
prop2 value2 ...)
����ָ���������������������ƣ����ڶ�̬�⣬����������ָ����̬��汾��API�汾��

?	Ϊ��̬����Ӱ汾�ţ���libhello.so.1.2
SET_TARGET_PROPERTIES(hello PROPERTIES VERSION 1.2 SOVERSION 1)
VERSIONָ����̬��汾��SOVERSIONָ��API�汾��
������ָ�����lib/CMakeLists.txt��

?	��װ�����ͷ�ļ�
������Ҫ��libhello.a, libhello.so.x�Լ�hello.h��װ��ϵͳĿ¼�����������������˿���ʹ��
��lib/CMakeLists.txt���������ָ�
INSTALL(TARGETS hello hello_static
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib)
INSTALL(FILES hello.h DESTINATION include/hello)

��hello.so ��װ����${CMAKE_INSTALL_PREFIX}/libĿ¼
��hello.o ��װ����${CMAKE_INSTALL_PREFIX}/libĿ¼
��hello.h��װ����${CMAKE_INSTALL_PREFIX}/ include/helloĿ¼
ע�⣬��̬��Ҫʹ��ARCHIVE�ؼ���
����ǰ�װ��ִ���ļ��������ű���
INSTALL(TARGETS��.)

ͨ��:
cmake -D CMAKE_INSTALL_PREFIX=/home/wwan001/code/usr ..
make
make install
���ǾͿ��Խ�ͷ�ļ��͹���ⰲװ��ϵͳĿ¼/home/wwan001/code /usr/lib��/home/wwan001/code /usr/include/hello���ˡ�

 
4 Test 4(���ʹ���ⲿ������ͷ�ļ�)
��Ŀ¼�����CMakeLists.txt
/*****************CMakeLists.txt***********/
PROJECT(NEWHELLO)
ADD_SUBDIRECTORY(src)

��srcĿ¼�����main.c��CMakeLists.txt
/*****************main.c***********/
#include <hello.h>
int main()
{
    HelloFunc();
    return 0;
}
/*****************src/CMakeLists.txt***********/
INCLUDE_DIRECTORIES(/home/wwan001/code/usr/include/hello) #����ͷ�ļ�·��
LINK_DIRECTORIES(/home/wwan001/code/usr/lib)            #��ӹ����
ADD_EXECUTABLE(main src/main.c)
TARGET_LINK_LIBRARIES(main hello)


LINK_DIRECTORIES�﷨
LINK_DIRECTORIES(directory1 directory2 ...)   ��ӷǱ�׼�Ĺ��������·��

TARGET_LINK_LIBRARIES�﷨
TARGET_LINK_LIBRARIES(target library1
<debug | optimized> library2
...)
���ָ���������Ϊtarget�����Ҫ���ӵĹ����


�������þ�̬��
TARGET_LINK_LIBRARIES(main libhello.a)
