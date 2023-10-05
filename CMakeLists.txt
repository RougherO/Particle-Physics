cmake_minimum_required(VERSION 3.21.0)
project(Particles LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.89.9)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(ImGui-SFML)

set(BOX2D_BUILD_TESTBED OFF)
FetchContent_Declare(Box2D
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG 411acc3)
FetchContent_MakeAvailable(Box2D)


add_executable(Particles "src/main.cpp" "src/App/App.cpp" "src/Physics/Physics.cpp" "src/UI/UI.cpp" "src/Transform/Transform.cpp" "src/Shooter/Shooter.cpp")
target_link_libraries(Particles PRIVATE sfml-graphics sfml-window sfml-system ImGui-SFML box2d)

if (WIN32) 
    add_custom_command(
        TARGET Particles
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}
        extlibs/bin/$<IF:$<BOOL:${ARCH_64BITS}>,x64,x86>/openal32.dll
        $<TARGET_FILE_DIR:Particles>
        VERBATIM
    )
    add_custom_command(
        TARGET Particles
        COMMENT "Copy SFML DLL"
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_BUILD_DIR}
        lib/*.dll $<TARGET_FILE_DIR:Particles>
        VERBATIM
    )
endif()