cmake_minimum_required(VERSION 3.5)
project("dai_core_template")

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(depthai_DIR depthai-core-lib)

find_package(OpenCV REQUIRED)
find_package(depthai CONFIG REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})


# set compile target -------------------------------------------------------
set(TARGET stereo_hconcat)

add_executable(${TARGET} examples/${TARGET}.cpp)

target_include_directories(${TARGET} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(
  ${TARGET}
  ${OpenCV_LIBS}
  depthai::opencv
)
# ---------------------------------------------------------------------------
