add_executable (Renderer main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} Rasterizer)
target_link_libraries(${PROJECT_NAME} Math)