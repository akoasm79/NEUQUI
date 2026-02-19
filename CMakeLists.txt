cmake_minimum_required(VERSION 3.19)
project(neuqui LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

# ====================== 库源文件 ======================
file(GLOB NEUQUI_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/header/*.h")
file(GLOB NEUQUI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

add_library(neuqui STATIC
    ${NEUQUI_HEADERS}
    ${NEUQUI_SOURCES}
)

# 包含 Qt 库
target_link_libraries(neuqui
    PUBLIC Qt6::Widgets
)

# 包含头文件目录
target_include_directories(neuqui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header
)

# 自动启用 moc（QObject 信号槽）
set_target_properties(neuqui PROPERTIES AUTOMOC ON)
