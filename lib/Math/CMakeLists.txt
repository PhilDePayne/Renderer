set(MATH_SOURCE_FILES
	 
 "include/Triangle.h" "src/Triangle.cpp" "include/Vec3.h" "src/Vec3.cpp")

add_library(Math ${MATH_SOURCE_FILES})

target_include_directories(Math PUBLIC include)

target_include_directories(Math PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})