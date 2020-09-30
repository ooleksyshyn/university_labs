cmake_minimum_required(VERSION 3.17)
project(lab1 C)

set(CMAKE_C_STANDARD 99)

SET(OBJS ${CMAKE_CURRENT_SOURCE_DIR}/lib/x86_64-linux/liblab1.so)

ADD_EXECUTABLE(lab1 ${OBJS} main.c)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(lab1 PRIVATE Threads::Threads)

SET_SOURCE_FILES_PROPERTIES(
        ${OBJS}
        PROPERTIES
        EXTERNAL_OBJECT true
        GENERATED true
)