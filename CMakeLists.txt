# 编译该软件时使用的cmake版本
cmake_minimum_required(VERSION 3.16.3)

# 项目名称
project(primaryINS)

set(CMAKE_CXX_STANDARD 14)

# 递归搜索库头文件
file(GLOB_RECURSE HEADERS   "lib/*.h"     )
file(GLOB_RECURSE HEADERS2  "lib/*.hpp"   )

# 寻找lib的子目录
set (INCLUDE_DIRS "")
foreach (_headerFile ${HEADERS})
    # 将_headerFile转换为_dir，类型为PATH，也就是把文件名转换为路径
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND INCLUDE_DIRS ${_dir})
endforeach()

foreach (_headerFile ${HEADERS2})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND INCLUDE_DIRS ${_dir})
endforeach()

# 删除重复子目录
list(REMOVE_DUPLICATES INCLUDE_DIRS)

# 添加头文件的路径
include_directories(${INCLUDE_DIRS})


# 递归搜索源文件
file(GLOB_RECURSE SOURCES   "lib/*.c"     )
file(GLOB_RECURSE SOURCES2  "lib/*.cpp"   )

# 根据源文件创建库文件
#add_library(primaryINS SHARED ${SOURCES}   ${SOURCES2} lib/files/IMUData.hpp)
add_library(primaryINS SHARED ${SOURCES}   ${SOURCES2} )


# Install the primaryINS library and headers
install(TARGETS primaryINS DESTINATION lib)
install(FILES ${HEADERS}   ${HEADERS2}  DESTINATION include/primaryINS )


# 可执行程序子目录
add_subdirectory(apps)


