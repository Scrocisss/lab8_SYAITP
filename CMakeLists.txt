cmake_minimum_required(VERSION 3.16)

project(poehali_v2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(apppoehali_v2
    main.cpp
)

qt_add_qml_module(apppoehali_v2
    URI poehali_v2
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES
    QML_FILES
    SOURCES
    QML_FILES
    SOURCES mainimagedownloader.h mainimagedownloader.cpp
    QML_FILES
    SOURCES



)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apppoehali_v2 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apppoehali_v2
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apppoehali_v2
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS apppoehali_v2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
