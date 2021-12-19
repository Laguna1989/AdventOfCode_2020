file(GLOB_RECURSE SOURCEFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
add_library(day_09_lib ${SOURCEFILES})
target_include_directories(day_09_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(day_09_lib PUBLIC ${CMAKE_SOURCE_DIR}/ext/strutils)

file(GLOB_RECURSE UNITTESTFILES CONFIGURE_DEPENDS  ${CMAKE_CURRENT_SOURCE_DIR}/test/*)
add_executable(day_09_test ${UNITTESTFILES})

target_link_libraries(day_09_test gtest_main)
target_link_libraries(day_09_test gmock)
target_link_libraries(day_09_test day_09_lib)
