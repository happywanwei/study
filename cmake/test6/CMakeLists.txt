SET(INCLUDE_PATH /home/wwan001/code/cmake/include/hello
								 /home/wwan001/code/cmake/include/src1_hello
								 /home/wwan001/code/cmake/include/src2_hello)
ADD_SUBDIRECTORY(src1)
ADD_SUBDIRECTORY(src2)
SET(INCLUDE_PATH /home/wwan001/code/cmake/include/hello
								 /home/wwan001/code/cmake/test6/src1
								 /home/wwan001/code/cmake/test6/src2)
SET(LINK_PATH /home/wwan001/code/cmake/lib
							src1
							src2)
SET(LIB_LIST hello
						 src1_hello
						 src2_hello)		
INCLUDE_DIRECTORIES(${INCLUDE_PATH})
LINK_DIRECTORIES(${LINK_PATH})
ADD_EXECUTABLE(main main.c)
TARGET_LINK_LIBRARIES(main ${LIB_LIST})
