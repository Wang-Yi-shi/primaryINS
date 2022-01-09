# tests/CMakeLists.txt


add_executable(initialization initialization.cpp)
target_link_libraries(initialization primaryINS)
install (TARGETS initialization DESTINATION bin)




