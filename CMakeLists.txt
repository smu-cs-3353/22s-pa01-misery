cmake_minimum_required(VERSION 3.16)
project(22s_pa01_misery)
set(EXE_NAME theArtGallery)

set(input 01 "input/PictureInfo.txt")

foreach(file IN LISTS input01)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 14)

add_executable(22s_pa01_misery src/main.cpp src/BruteForceAlgo.h src/BruteForceAlgo.cpp src/MostExpensiveFirstAlgo.h src/MostExpensiveFirstAlgo.cpp src/CustomAlgo.h src/CustomAlgo.cpp)
