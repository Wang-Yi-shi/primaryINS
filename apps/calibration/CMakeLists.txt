# tests/CMakeLists.txt


add_executable(calibration calibration.cpp)
target_link_libraries(calibration primaryINS)
install (TARGETS calibration DESTINATION bin)




