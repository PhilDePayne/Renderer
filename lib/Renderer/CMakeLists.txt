set(RASTERIZER_SOURCE_FILES 
	"include/Buffer.h" "src/Buffer.cpp" 
	"include/Writer.h" "src/Writer.cpp"
	"include/Rasterizer.h" "src/Rasterizer.cpp"
)

add_library(Rasterizer ${RASTERIZER_SOURCE_FILES})

target_include_directories(Rasterizer PUBLIC include)

target_include_directories(Rasterizer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Rasterizer Math)