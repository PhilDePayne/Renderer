set(RASTERIZE_SOURCE_FILES 
	"include/Buffer.h" "src/Buffer.cpp" 
	"include/Writer.h" "src/Writer.cpp")

add_library(Rasterizer ${RASTERIZE_SOURCE_FILES})

target_include_directories(Rasterizer PUBLIC include)

target_include_directories(Rasterizer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})