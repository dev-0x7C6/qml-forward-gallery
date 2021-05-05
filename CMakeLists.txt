cmake_minimum_required(VERSION 3.14)

project(qml-forward-gallery LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/qml.qrc
        src/database.cpp
        src/database.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable(qml-forward-gallery
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
		add_library(qml-forward-gallery SHARED
            ${PROJECT_SOURCES}
        )
    else()
		add_executable(qml-forward-gallery
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(qml-forward-gallery
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(qml-forward-gallery
  PRIVATE Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::Network
)

install(TARGETS qml-forward-gallery RUNTIME DESTINATION bin)
