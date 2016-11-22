cmake_minimum_required(VERSION 2.8)  
SET(LIBHELLO1_SRC src2_hello.c)
ADD_LIBRARY(src2_hello SHARED ${LIBHELLO1_SRC})
INSTALL(TARGETS src2_hello
LIBRARY DESTINATION lib)
INSTALL(FILES src2_hello.h DESTINATION include/src2_hello)
