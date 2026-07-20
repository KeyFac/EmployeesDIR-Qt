cmake_minimum_required(VERSION 3.16)

project(EmployeesDIR VERSION 3.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES
    EmployeesDIR_en_US.ts
    EmployeesDIR_zh_CN.ts
)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    employee.h
    employee.cpp
    employeelist.h
    employeelist.cpp
    config.h
    config.cpp
    logger.h
    logger.cpp
    errorform.h
    errorform.cpp
    errorform.ui
    dbconnectform.h
    dbconnectform.cpp
    dbconnectform.ui
    settingsform.h
    settingsform.cpp
    settingsform.ui
    config.ini
    ${TS_FILES}
)

# Copy config.ini to build directory
configure_file(${CMAKE_SOURCE_DIR}/config.ini ${CMAKE_CURRENT_BINARY_DIR}/config.ini COPYONLY)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(EmployeesDIR
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        errorform.ui
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(EmployeesDIR SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(EmployeesDIR
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_compile_definitions(EmployeesDIR PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_link_libraries(EmployeesDIR PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.EmployeesDIR)
endif()
set_target_properties(EmployeesDIR PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS EmployeesDIR
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(EmployeesDIR)
endif()