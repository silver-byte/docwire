cmake_minimum_required(VERSION 3.7)
project(Unzip)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
set(UNZIP_SRC ioapi.c unzip.c)
add_library(unzip STATIC ${UNZIP_SRC})
find_path(zlib_incdir zlib.h REQUIRED)
target_include_directories(unzip PUBLIC ${zlib_incdir})
install(FILES unzip.h ioapi.h DESTINATION include)
install(TARGETS unzip DESTINATION lib)
target_compile_options(unzip PRIVATE -fPIC)
