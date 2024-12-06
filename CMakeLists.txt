cmake_minimum_required(VERSION 3.16)

project(school_management_system_linkedlist LANGUAGES C)

add_executable(school_management_system_linkedlist main.c
    admin.h
    admin.c
    student.h
    faculty.h
    section.h
    fees.h
    main1.h
    student.c
    faculty.c
    fees.c
    section.c
    main1.c
    fileoperation.h
    fileoperation.c)

include(GNUInstallDirs)
install(TARGETS school_management_system_linkedlist
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
