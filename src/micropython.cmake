add_library(usermod_cexample INTERFACE)

target_sources(usermod_cexample INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/examplemodule.c

  ${CMAKE_CURRENT_LIST_DIR}/../libffi/src/prep_cif.c
  ${CMAKE_CURRENT_LIST_DIR}/../libffi/src/types.c
  ${CMAKE_CURRENT_LIST_DIR}/../libffi/src/xtensa/ffi.c
  ${CMAKE_CURRENT_LIST_DIR}/../libffi/src/xtensa/sysv.S
)

target_include_directories(usermod_cexample INTERFACE
	${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/../libffi/include
	${CMAKE_CURRENT_LIST_DIR}/../libffi/include/xtensa
)

target_link_libraries(usermod INTERFACE usermod_cexample)
