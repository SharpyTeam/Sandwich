if (NOT DEFINED NODE_COMMAND)
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
    set(NODE_FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../tmp/${NODE_FILE_NAME}${NODE_FILE_EXTENSION}")
    set(NODE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/dist/${NODE_FILE_NAME}")

    set(NODE_COMMAND "${NODE_ROOT}/bin/node" PARENT_SCOPE)
    set(NPM_COMMAND "${NODE_ROOT}/bin/npm" PARENT_SCOPE)
    set(NPX_COMMAND "${NODE_ROOT}/bin/npx" PARENT_SCOPE)

    set(NODE_COMMAND "${NODE_ROOT}/bin/node")
    set(NPM_COMMAND "${NODE_ROOT}/bin/npm")
    set(NPX_COMMAND "${NODE_ROOT}/bin/npx")

    if (NOT EXISTS "${NODE_ROOT}")
        message(STATUS "Downloading ${NODE_FILE_NAME}...")
        file(DOWNLOAD ${NODE_FILE_URL} ${NODE_FILE_PATH} SHOW_PROGRESS)

        file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dist")
        if (UNIX)
            message(STATUS "Extracting ${NODE_FILE_NAME}...")
            execute_process(COMMAND tar -xJf ${NODE_FILE_PATH} -C "${CMAKE_CURRENT_SOURCE_DIR}/dist")
            # TODO add extraction strategy for macos and win
        endif ()

        message(STATUS "Setting prefix for ${NODE_FILE_NAME}...")
        execute_process(COMMAND "${NODE_ROOT}/bin/npm" config set prefix "${NODE_ROOT}")

        # install needed packages
        message(STATUS "Installing required packages for ${NODE_FILE_NAME}...")
        include(package.cmake)
    endif ()
endif ()