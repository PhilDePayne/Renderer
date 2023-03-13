set(MATH_SOURCE_FILES
	 
 "include/Triangle.h" "src/Triangle.cpp" 
 "include/Vec3.h" "src/Vec3.cpp" 
 "include/Ray.h" "src/Ray.cpp"
 "include/Sphere.h" "src/Sphere.cpp"
 "include/Plane.h" "src/Plane.cpp"
 "include/Vec4.h" "src/Vec4.cpp"
 "include/Mat4x4.h" "src/Mat4x4.cpp")

add_library(Math ${MATH_SOURCE_FILES})

target_include_directories(Math PUBLIC include)

target_include_directories(Math PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})