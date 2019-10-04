set(NODE_VERSION_URL "https://nodejs.org/dist/v12.10.0")

if (WIN32)
    set(NODE_FILE_NAME          "node-v12.10.0-win-x64")
    set(NODE_FILE_EXTENSION     ".zip")
elseif (APPLE)
    set(NODE_FILE_NAME          "node-v12.10.0-darwin-x64")
    set(NODE_FILE_EXTENSION     ".tar.gz")
elseif (UNIX)
    set(NODE_FILE_NAME          "node-v12.10.0-linux-x64")
    set(NODE_FILE_EXTENSION     ".tar.xz")
else ()
    message(FATAL "Platform is not supported")
endif ()

set(NODE_FILE_URL "${NODE_VERSION_URL}/${NODE_FILE_NAME}${NODE_FILE_EXTENSION}")
set(NODE_FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tmp/${NODE_FILE_NAME}${NODE_FILE_EXTENSION}")
set(NODE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/dist/${NODE_FILE_NAME}")

if (WIN32)
    set(NODE_BIN_ROOT ${NODE_ROOT})
elseif (UNIX)
    set(NODE_BIN_ROOT "${NODE_ROOT}/bin")
endif ()

set(NODE_COMMAND "${NODE_BIN_ROOT}/node")
set(NPM_COMMAND "${NODE_BIN_ROOT}/npm")
set(NPX_COMMAND "${NODE_BIN_ROOT}/npx")

if (UNIX)
    set(NPM_COMMAND export PATH=$PATH:${NODE_BIN_ROOT} && ${NPM_COMMAND})
    set(NPX_COMMAND export PATH=$PATH:${NODE_BIN_ROOT} && ${NPX_COMMAND})
endif ()

set(NODE_COMMAND ${NODE_COMMAND} PARENT_SCOPE)
set(NPM_COMMAND ${NPM_COMMAND} PARENT_SCOPE)
set(NPX_COMMAND ${NPX_COMMAND} PARENT_SCOPE)

if (NOT EXISTS "${NODE_ROOT}")
    message(STATUS "Downloading ${NODE_FILE_NAME}...")
    file(DOWNLOAD ${NODE_FILE_URL} ${NODE_FILE_PATH} SHOW_PROGRESS)

    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dist")
    message(STATUS "Extracting ${NODE_FILE_NAME}...")
    if (WIN32)
        execute_process(COMMAND powershell -Command Expand-Archive ${NODE_FILE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/dist")
    elseif (UNIX)
        execute_process(COMMAND tar -xJf ${NODE_FILE_PATH} -C "${CMAKE_CURRENT_SOURCE_DIR}/dist")
        # TODO add extraction strategy for macos
    endif ()

    message(STATUS "Setting prefix for ${NODE_FILE_NAME}...")
    execute_process(COMMAND ${NPM_COMMAND} config set prefix "${NODE_ROOT}")
endif ()

set(PACKAGE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/package.json")
file(TIMESTAMP ${PACKAGE_FILE} PACKAGE_FILE_TIMESTAMP)

if (NOT PACKAGE_FILE_TIMESTAMP STREQUAL PACKAGE_FILE_TIMESTAMP_CACHE)
    set(PACKAGE_FILE_TIMESTAMP_CACHE ${PACKAGE_FILE_TIMESTAMP} CACHE STRING "" FORCE)

    # install needed packages
    message(STATUS "Installing required packages for ${NODE_FILE_NAME}...")
    execute_process(COMMAND ${NPM_COMMAND} i -g)
endif ()