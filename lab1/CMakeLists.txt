project(AsiaPiotrekCompany)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

include_directories(src)

add_subdirectory(src)

add_executable(AsiaPiotrekCompany_run main_lab1.cpp)
add_executable(AsiaPiotrekResults_run results_lab1.cpp)

add_executable(AsiaPiotrekTeam_run main_lab2.cpp)

target_link_libraries(AsiaPiotrekCompany_run PUBLIC Algorithm_lib)
target_link_libraries(AsiaPiotrekResults_run PUBLIC Algorithm_lib)