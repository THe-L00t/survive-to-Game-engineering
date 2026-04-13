cmake_minimum_required(VERSION 3.10.0)
project(DinoRun VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 26)

# 헤더 및 라이브러리 경로 설정
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include/Framework)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 소스 파일 추가 (src 폴더 안의 모든 .cpp와 glad.c 포함)
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/DinoRun/*.cpp" "src/Framework/glad.c" "src/Framework/*.cpp")

# 실행 파일 출력 디렉토리 설정 (프로젝트 루트)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(COPY ${CMAKE_SOURCE_DIR}/assets
     DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CMAKE_SOURCE_DIR}/shaders
     DESTINATION ${CMAKE_BINARY_DIR}/bin)

# 실행 파일 생성
add_executable(DinoRun ${SOURCES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(DinoRun PUBLIC DEBUG)
endif()

# 라이브러리 링크
target_link_libraries(DinoRun glfw3 opengl32 gdi32 user32)
