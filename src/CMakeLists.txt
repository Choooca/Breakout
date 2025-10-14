set(PROJECT_SOURCES "")

add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(entity)
add_subdirectory(utility)
add_subdirectory(state)

list(APPEND PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE
	PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
	ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets"
	TEXTURES_PATH="${CMAKE_SOURCE_DIR}/assets/textures")

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 stb)