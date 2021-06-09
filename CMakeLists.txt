# The minimum version required to use Qt5 is CMake 2.8.3, but 2.8.11 is recommended.
cmake_minimum_required(VERSION 2.8.11)

set(QT_INSTALL_PATH "/home/xujl/Qt5.8.0/5.8/gcc_64")
message("qt: ${QT_INSTALL_PATH}" )
project(testQT)

set(CMAKE_PREFIX_PATH ${QT_INSTALL_PATH})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core ${QT_VERSION_REQ} REQUIRED)
find_package(Qt5Widgets ${QT_VERSION_REQ} REQUIRED)
find_package(Qt5Gui ${QT_VERSION_REQ} REQUIRED)
find_package(Qt5Sql ${QT_VERSION_REQ} REQUIRED)
find_package(Qt5Multimedia ${QT_VERSION_REQ} REQUIRED)
find_package(Qt5MultimediaWidgets ${QT_VERSION_REQ} REQUIRED)

message("config types: ${CMAKE_CONFIGURATION_TYPES}")
set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")

FILE(GLOB_RECURSE MOCS "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.h")
FILE(GLOB_RECURSE FORMS "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui")
FILE(GLOB_RECURSE RES "${CMAKE_CURRENT_SOURCE_DIR}/ui/qss/*.qrc")
FILE(GLOB_RECURSE RES "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.qrc")
FILE(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.cpp")


SOURCE_GROUP("Form Files" FILES ${FORMS})

# QT : Link .ui files
QT5_WRAP_CPP(HEADERS_MOC ${MOCS})
QT5_WRAP_UI(FORMS_UIC ${FORMS})
QT5_ADD_RESOURCES(RES_RCC ${RES})

SOURCE_GROUP("Generated Files" FILES ${HEADERS_MOC} ${FORMS_UIC})

add_executable(testQT
               ${SRC}
               ${HEADERS_MOC}
               ${FORMS_UIC}
               ${RES_RCC})

target_link_libraries(testQT
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Gui
                      Qt5::Sql
                      Qt5::Multimedia
                      Qt5::MultimediaWidgets)

# Add workflow header file

