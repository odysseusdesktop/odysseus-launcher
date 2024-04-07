cmake_minimum_required(VERSION 3.16)

project(odysseus-launcher VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Quick DBus REQUIRED)
find_package(KF5Config REQUIRED)

qt5_add_resources(RESOURCES
    resources.qrc
)

add_executable(odysseus-launcher
    main.cpp
    launcherviewmanager.h
    launcherviewmanager.cpp
    desktopentryreader.h
    desktopentryreader.cpp
    iconimageprovider.h
    iconimageprovider.cpp
    processhelper.h
    processhelper.cpp
    applicationmodel.h
    applicationmodel.cpp
    ${RESOURCES}
)

set_target_properties(odysseus-launcher PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(odysseus-launcher
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(odysseus-launcher
    PRIVATE Qt5::Quick Qt5::DBus KF5::ConfigCore)

install(TARGETS odysseus-launcher RUNTIME DESTINATION /usr/bin)
