cmake_minimum_required(VERSION 3.1)

project(FOLDER_2_MP3)

# Build specifics
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "-O2 -Wall" )


# Find and enable doxygen
find_package(Doxygen)
set(DOXYGEN_EXTRACT_ALL          "YES")
set(DOXYGEN_CLASS_DIAGRAMS       "YES")
set(DOXYGEN_HIDE_UNDOC_RELATIONS "NO")
set(DOXYGEN_HAVE_DOT             "YES")
set(DOXYGEN_CLASS_GRAPH          "YES")
set(DOXYGEN_COLLABORATION_GRAPH  "YES")
set(DOXYGEN_UML_LOOK             "YES")
set(DOXYGEN_UML_LIMIT_NUM_FIELDS "50")
set(DOXYGEN_TEMPLATE_RELATIONS   "YES")
set(DOXYGEN_DOT_GRAPH_MAX_NODES  "100")
set(DOXYGEN_MAX_DOT_GRAPH_DEPTH  "0")
set(DOXYGEN_DOT_TRANSPARENT      "YES")

doxygen_add_docs(documentation
    ../project
)


# Include subprojects
add_subdirectory(project)
