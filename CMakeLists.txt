# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MyCppRestProject)

    set(CMAKE_CXX_STANDARD 20)

add_executable(prueba_2_proyecto_p3 src/main.cpp
        include/MovieDatabase.h
        include/utils.h
        src/MovieDatabase.cpp
        src/utils.cpp)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/Usuario/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(Crow CONFIG REQUIRED)
target_link_libraries(prueba_2_proyecto_p3 PRIVATE Crow::Crow asio::asio ws2_32 mswsock)
