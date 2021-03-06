if(NOT INSIDE_DOCKER)
    if("${USE_IDE}" STREQUAL "eclipse")
        message("Generating project files for Eclipse IDE...")
        message(WARNING "Eclipse IDE currently not supported!")
        # TODO: Debug Configuration
    elseif("${USE_IDE}" STREQUAL "vscode")
        message(STATUS "Generating project files for VSCode...")
        configure_file(${CMAKE_CONFIG_DIR}/vscode/launch.local.json.in ${PROJECT_SOURCE_DIR}/.vscode/launch.json @ONLY)
        configure_file(${CMAKE_CONFIG_DIR}/vscode/extensions.local.json.in ${PROJECT_SOURCE_DIR}/.vscode/extensions.json @ONLY)
        configure_file(${CMAKE_CONFIG_DIR}/vscode/tasks.local.json.in ${PROJECT_SOURCE_DIR}/.vscode/tasks.json @ONLY)
        configure_file(${CMAKE_CONFIG_DIR}/vscode/c_cpp_properties.local.json.in ${PROJECT_SOURCE_DIR}/.vscode/c_cpp_properties.json @ONLY)
    else()
        message(STATUS "No IDE projects generated.")
    endif()
else()
    message(STATUS "Running inside a docker container!")
    add_definitions(-DHOST_OS=${CMAKE_SYSTEM_NAME} -DDOCKER)
endif()
