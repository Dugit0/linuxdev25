cmake_minimum_required(VERSION 3.10)

project(GuessTheNumber C)

add_executable(guess src/main.c)
find_package(Gettext REQUIRED)
find_package(Intl REQUIRED)
find_package(Doxygen REQUIRED)

add_library(roman SHARED src/roman.c)
set_target_properties(roman PROPERTIES
    PUBLIC_HEADER include/roman.h
)
target_include_directories(roman PUBLIC include)
target_link_libraries(guess roman)


# -------- Tests --------
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest) # Включает функционал add_test
    add_subdirectory(tests)
endif()


# -------- i18n --------
if(Intl_FOUND)
    target_include_directories(guess PRIVATE ${Intl_INCLUDE_DIRS})
    target_link_libraries(guess PRIVATE ${Intl_LIBRARIES})
else()
    message(WARNING "Intl not found.")
endif()

if(GETTEXT_FOUND)
    message(STATUS "Gettext found")

    set(GETTEXT_DOMAIN "guess")
    set(POT_FILE "${CMAKE_CURRENT_BINARY_DIR}/${GETTEXT_DOMAIN}.pot")
    set(PO_DIR "${CMAKE_SOURCE_DIR}/po")
    set(LOCALE_DIR "${CMAKE_CURRENT_BINARY_DIR}/locale")


    add_custom_command(
        OUTPUT ${POT_FILE}
        COMMAND xgettext --keyword=_ --from-code=UTF-8 -o ${POT_FILE} ${CMAKE_SOURCE_DIR}/src/main.c
        COMMENT "Generating POT file"
    )

    add_custom_target(
        pot
        ALL
        DEPENDS src/main.c
    )

    set(LANGUAGES ru_RU.UTF-8)

    foreach(LANG ${LANGUAGES})
        set(PO_FILE ${PO_DIR}/${LANG}.po)
        set(MO_DIR ${LOCALE_DIR}/${LANG}/LC_MESSAGES)
        set(MO_FILE ${MO_DIR}/${GETTEXT_DOMAIN}.mo)

        file(MAKE_DIRECTORY ${MO_DIR})

        add_custom_command(
            OUTPUT ${PO_FILE}
            COMMAND ${GETTEXT_MSGMERGE_EXECUTABLE} --update ${PO_FILE} ${POT_FILE}
            DEPENDS ${POT_FILE}
            COMMENT "Updating ${POT_FILE}"
        )

        add_custom_command(
            OUTPUT ${MO_FILE}
            COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} -o ${MO_FILE} ${PO_FILE}
            DEPENDS src/main.c ${POT_FILE} ${PO_FILE}
            COMMENT "Compiling ${LANG}.po to ${MO_FILE}"
        )

        add_custom_target(
            mo_${LANG}
            ALL
            DEPENDS ${MO_FILE} ${PO_FILE}
        )
        add_dependencies(guess mo_${LANG})

    endforeach()

    install(
        DIRECTORY ${LOCALE_DIR}/
        DESTINATION share/locale
    )

    add_custom_target(clean_locale
        COMMAND ${CMAKE_COMMAND} -E remove -f ${PO_DIR}/${GETTEXT_DOMAIN}.pot
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${LOCALE_DIR}
        COMMENT "Cleaning generated locale files"
    )

else()
    message(WARNING "Gettext not found. Building without localization support.")
endif()


# -------- Docs --------
if(Doxygen_FOUND)
    set(DOXYFILE "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    set(DOXYFILEIN "${CMAKE_SOURCE_DIR}/Doxyfile.in")
    set(TOP_SRC_DIR ${CMAKE_SOURCE_DIR})
    set(DOCS "${CMAKE_CURRENT_BINARY_DIR}/docs")

    configure_file(
        "${DOXYFILEIN}"
        "${DOXYFILE}"
    )

    add_custom_command(
        OUTPUT ${DOCS}
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
        COMMENT "Compile docs"
    )
    add_custom_target(
        docs
        ALL
        DEPENDS ${DOCS}
    )
    add_dependencies(guess docs)

else()
    message(WARNING "Doxygen not found. Building without docs.")
endif()

# -------- Install --------
install(
    TARGETS guess
    RUNTIME
)
install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/roman
)
install(
    TARGETS roman
    LIBRARY
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/roman
)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/man/
        DESTINATION share/man
        OPTIONAL)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/html/
        DESTINATION share/doc/${CMAKE_PROJECT_NAME}/html
        OPTIONAL)


# -------- Uninstall --------
# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
