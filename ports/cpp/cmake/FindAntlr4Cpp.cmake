set(ANTLR4_TAG 4.13.1)
set(ANTLR4_ZIP_REPOSITORY https://github.com/antlr/antlr4/archive/refs/tags/${ANTLR4_TAG}.zip)

if(NOT TARGET antlr4_static)
  set(ANTLR4_STATIC antlr4_static)

  set(ANTLR4_WITH_STATIC_CRT OFF)
  add_definitions(-DANTLR4CPP_STATIC)
  include(ExternalAntlr4Cpp)

else()
  set(ANTLR4_STATIC existing_antlr4_static)

  add_library(${ANTLR4_STATIC} STATIC IMPORTED)

  add_dependencies(${ANTLR4_STATIC} antlr4_static)

  set_target_properties(
    ${ANTLR4_STATIC} PROPERTIES
    IMPORTED_LOCATION ${ANTLR4_STATIC_LIBRARIES}
  )

  target_include_directories(
    ${ANTLR4_STATIC}
    INTERFACE ${ANTLR4_INCLUDE_DIRS}
  )

endif()
