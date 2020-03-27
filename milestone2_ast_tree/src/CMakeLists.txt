project(Project)
set(
    HEADERS
    ${Project_SOURCE_DIR}/driver.hh
    ${Project_SOURCE_DIR}/parser.hh
    )

BISON_TARGET(
    MyParser
    parser.y
    ${Project_SOURCE_DIR}/parser.cpp
    DEFINES_FILE ${Project_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    MyScanner
    scanner.l
    ${Project_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_executable(
    Project
    main.cpp
    driver.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
)
target_include_directories(Project PRIVATE ${Project_SOURCE_DIR})



