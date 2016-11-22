cmake_minimum_required(VERSION 2.8)  
SET(LIBHELLO1_SRC src1_hello.c)
ADD_LIBRARY(src1_hello SHARED ${LIBHELLO1_SRC})
INSTALL(TARGETS src1_hello
LIBRARY DESTINATION lib)
INSTALL(FILES src1_hello.h DESTINATION include/src1_hello)
