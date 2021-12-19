file(GLOB_RECURSE SOURCEFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
add_library(day_04_lib ${SOURCEFILES})
target_include_directories(day_04_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(day_04_lib PUBLIC ${CMAKE_SOURCE_DIR}/ext/strutils)

file(GLOB_RECURSE UNITTESTFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test/*)
add_executable(day_04_test ${UNITTESTFILES})

target_link_libraries(day_04_test gtest_main)
target_link_libraries(day_04_test gmock)
target_link_libraries(day_04_test day_04_lib)
