enable_testing()
find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CHECK_LIBRARIES})
include_directories(. ..)
add_executable(test_corc_str str_test.c ../str.c)
target_link_libraries(test_corc_str ${LIBS})
add_test(test_corc_str ${CMAKE_CURRENT_BINARY_DIR}/test_corc_str)

