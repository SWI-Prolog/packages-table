cmake_minimum_required(VERSION 2.8.12)
project(swipl-table)

include("../cmake/PrologPackage.cmake")

AC_CHECK_HEADERS(malloc.h unistd.h ctype.h sys/time.h fcntl.h floatingpoint.h)
AC_CHECK_FUNCS(mmap strerror)

configure_file(config.h.cmake config.h)

swipl_plugin(
    table
    C_SOURCES table.c order.c error.c
    PL_LIBS table.pl table_util.pl)

pkg_doc(table
        SECTION
        SOURCE table.doc)
