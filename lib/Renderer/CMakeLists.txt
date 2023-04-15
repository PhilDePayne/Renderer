set(RASTERIZER_SOURCE_FILES 
	"include/Buffer.h" "src/Buffer.cpp" 
	"include/Writer.h" "src/Writer.cpp"
	"include/Rasterizer.h" "src/Rasterizer.cpp"
	"include/VertexProcessor.h" "src/VertexProcessor.cpp" 
	"include/OrthoCamera.h" "src/OrthoCamera.cpp" 
	"include/LightIntensity.h" "src/LightIntensity.cpp" 
	"include/PerspectiveCamera.h" "src/PerspectiveCamera.cpp"
	"include/Scene.h" "src/Scene.cpp"
	"include/Light.h" "src/Light.cpp" 
	"include/PointLight.h" "src/PointLight.cpp")

add_library(Rasterizer ${RASTERIZER_SOURCE_FILES})

target_include_directories(Rasterizer PUBLIC include)

target_include_directories(Rasterizer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Rasterizer Math)