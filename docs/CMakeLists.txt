option(MAKE_DOCS "Run doxygen documentation generator" OFF)

if(MAKE_DOCS)
	set(DOXYGEN_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../xbase64)
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/doxygen.cfg.in
		${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg
	)
	add_custom_target(
		doc ALL
		COMMAND doxygen ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg
		COMMENT "Generation API documentation using Doxygen"
		VERBATIM
	)
endif()
