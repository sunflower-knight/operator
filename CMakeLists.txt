cmake_minimum_required(VERSION 3.28)
project(operator
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# libc++ or libstdc++&clang

#add_compile_options(-nostdinc++ -nostdlib++ )
#include_directories(SYSTEM /usr/lib/llvm-18/include/c++/v1)
#link_directories(/usr/lib/llvm-18/lib)
#add_link_options(-fuse-ld=lld -lc++)

# force use lld if your compiler is clang
add_executable(main main.cpp MinxinOperator.h)



