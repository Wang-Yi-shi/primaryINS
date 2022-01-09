# tests/CMakeLists.txt


add_executable(mechanization mechanization.cpp)
target_link_libraries(mechanization primaryINS)
install (TARGETS mechanization DESTINATION bin)




