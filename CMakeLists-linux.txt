# The minimum version required to use Qt5 is CMake 2.8.3, but 2.8.11 is recommended.
cmake_minimum_required(VERSION 2.8.11)

set(QT_INSTALL_PATH "D:/Qt/Qt5.12.12/5.12.12/msvc2017_64")
#set(QT_INSTALL_PATH "D:/qt5.5.0/qtbase/bin")
set(OpenCV_DIR "E:/study/opencv/opencv-4.5.5/build")
message("qt: ${QT_INSTALL_PATH}" )
message("qt: ${QT_DIR_PATH}" )
project(testQT)

set(CMAKE_PREFIX_PATH ${QT_INSTALL_PATH})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core ${QT_VERSION_REQ} REQUIRED)
find_package(Qt5Widgets ${QT_VERSION_REQ} REQUIRED)
find_package(Qt5Gui ${QT_VERSION_REQ} REQUIRED)
find_package(Qt5Sql ${QT_VERSION_REQ} REQUIRED)
find_package(Qt5Multimedia ${QT_VERSION_REQ} REQUIRED)
find_package(Qt5MultimediaWidgets ${QT_VERSION_REQ} REQUIRED)
message("qt: ${QT_VERSION_REQ}" )
find_package(OpenCV REQUIRED)
message("opencv: ${OpenCV_LIBS}" )
#message("qt: ${QT_INSTALL_PATH}" )

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
link_directories(${OpenCV_LIBRARY_DIRS})
target_link_libraries(testQT
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Gui
                      Qt5::Sql
                      Qt5::Multimedia
                      Qt5::MultimediaWidgets
		      ${OpenCV_LIBS})

target_include_directories(testQT PUBLIC
                           /home/xujl/Qt5.8.0/5.8/Src/qtmultimedia/include/QtMultimedia
                          ${OpenCV_INCLUDE_DIRS})
# Add workflow header file
