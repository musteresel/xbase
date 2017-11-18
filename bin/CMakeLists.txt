set(
	BINS
		checkndx
		copydbf
		dbfxtrct
		dbfutil1
		deletall
		dumpdbt
		dumphdr
		dumprecs
		packdbf
		reindex
		undelall
		zap
)
foreach(BIN ${BINS})
	add_executable(${BIN} ${BIN}.cpp)
	target_link_libraries(${BIN} xbase64_shared)
	install(
		TARGETS ${BIN}
		RUNTIME DESTINATION usr/bin
	)
endforeach()
