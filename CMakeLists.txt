cmake_minimum_required(VERSION 3.5)

project(image_proccesing LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_MODULE_PATH}")
find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
find_package(OpenCV REQUIRED)
find_package (Threads)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
# then make sure to link to Charts when building your app
include_directories( ${OpenCV_INCLUDE_DIRS} )



if(ANDROID)
  add_library(image_proccesing SHARED
    src/main.cpp
    src/image_proccesing.cpp
    src/image_proccesing.h
    src/image_proccesing.ui
    src/image_adjustments.cpp
    src/image_adjustments.h

  )
else()
  add_executable(image_proccesing
    src/main.cpp
    src/image_proccesing.cpp
    src/image_proccesing.h
    src/image_proccesing.ui
    src/image_adjustments.cpp
    src/image_adjustments.h

  )

endif()

target_link_libraries(image_proccesing PRIVATE Qt5::Widgets ${OpenCV_LIBS} qcustomplot Threads::Threads)
