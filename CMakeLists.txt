cmake_minimum_required(VERSION 3.16)

project(pomodoro_qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickWidgets QuickControls2)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(apppomodoro_qml
    main.cpp
)

qt_add_qml_module(apppomodoro_qml
    URI pomodoro_qml
    VERSION 1.0

    QML_FILES
        Main.qml
        CustomTitleBar.qml
        GlassButton.qml

    SOURCES
        pomodoro.h
        pomodoro.cpp

    RESOURCES
        icons/tomatoes.png
        icons/tomatoes_2.png
        icons/tomatoes_2_32x32.png
        SOURCES Settings.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apppomodoro_qml PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apppomodoro_qml
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apppomodoro_qml
    PRIVATE Qt6::Quick Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS apppomodoro_qml
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
