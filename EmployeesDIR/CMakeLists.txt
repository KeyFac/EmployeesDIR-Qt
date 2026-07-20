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

# Copy config.ini and .qm files to build directory
configure_file(${CMAKE_SOURCE_DIR}/config.ini ${CMAKE_CURRENT_BINARY_DIR}/config.ini COPYONLY)

# ---- Custom targets for translation workflow ----
# Usage:
#   cmake --build . --target lupdate   (scan sources, update .ts)
#   cmake --build . --target lrelease  (compile .ts → .qm, copy to i18n/)
find_program(QT_LUPDATE NAMES lupdate lupdate-pro lupdate-qt6 REQUIRED)
find_program(QT_LRELEASE NAMES lrelease lrelease-pro lrelease-qt6 REQUIRED)

add_custom_target(lupdate
    COMMAND ${QT_LUPDATE} -tr-function-alias tr=tr -tr-function-alias qsTr=tr
            ${CMAKE_SOURCE_DIR} -ts ${TS_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Updating translation source files (.ts) from source code"
)

add_custom_target(lrelease
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/i18n
    COMMAND ${QT_LRELEASE} ${CMAKE_SOURCE_DIR}/EmployeesDIR_en_US.ts -qm ${CMAKE_CURRENT_BINARY_DIR}/i18n/EmployeesDIR_en_US.qm
    COMMAND ${QT_LRELEASE} ${CMAKE_SOURCE_DIR}/EmployeesDIR_zh_CN.ts -qm ${CMAKE_CURRENT_BINARY_DIR}/i18n/EmployeesDIR_zh_CN.qm
    COMMENT "Compiling translation files (.ts → .qm) to i18n/"
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(EmployeesDIR
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    # Run lrelease at configure time to ensure .qm files exist
    find_program(QT_LRELEASE_CMD NAMES lrelease lrelease-pro lrelease-qt6 REQUIRED)
    execute_process(COMMAND ${QT_LRELEASE_CMD} ${CMAKE_SOURCE_DIR}/EmployeesDIR_en_US.ts
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                    OUTPUT_QUIET ERROR_QUIET)
    execute_process(COMMAND ${QT_LRELEASE_CMD} ${CMAKE_SOURCE_DIR}/EmployeesDIR_zh_CN.ts
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                    OUTPUT_QUIET ERROR_QUIET)

    # Copy .qm into i18n/ next to the executable
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/i18n)
    file(COPY ${CMAKE_SOURCE_DIR}/EmployeesDIR_en_US.qm ${CMAKE_SOURCE_DIR}/EmployeesDIR_zh_CN.qm
         DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/i18n)
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