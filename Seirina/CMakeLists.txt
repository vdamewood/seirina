# Copyright 2018, 2019 Vincent Damewood
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
# implied. See the License for the specific language governing
# permissions and limitations under the License.

set(TARGET Seirina)
set(PUBLIC_HEADERS
	Adsr.h
	AdsrTransform.h
	AudioFrame.h
	AudioSample.h
	Frequency.h
	Note.h
	Octave.h
	OutputStream.h
	Phase.h
	PitchClass.h
	PlayedNote.h
	SampleRate.h
	Silence.h
	SonicEvent.h
	Tempo.h
	Timbre.h
	WaveFile.h
)
set(SOURCES
	${PUBLIC_HEADERS}
	Adsr.cc
	AdsrTransform.cc
	AudioFrame.cc
	AudioSample.cc
	Frequency.cc
	Note.cc
	Octave.cc
	Phase.cc
	PitchClass.cc
	PlayedNote.cc
	SampleRate.cc
	Silence.cc
	Tempo.cc
	Timbre.cc
	WaveFile.cc
)
set(DOXY_SOURCES
	${PUBLIC_HEADERS}
	Doxygen.dox
)

find_package(Doxygen)
if(DOXYGEN_FOUND)
	set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
	set(DOXYGEN_HTML_OUTPUT Docs)
	set(DOXYGEN_REPEAT_BRIEF No)
	set(DOXYGEN_QT_AUTOBRIEF Yes)
	doxygen_add_docs(Docs ALL ${DOXY_SOURCES})
endif()

add_library(${TARGET} SHARED ${SOURCES})
set_target_properties(${TARGET} PROPERTIES
	FRAMEWORK      TRUE
	PUBLIC_HEADER  "${PUBLIC_HEADERS}"
	VERSION        ${PROJECT_VERSION}
	SOVERSION      ${PROJECT_VERSION_MAJOR}
)
install(TARGETS ${TARGET}
	RUNTIME       DESTINATION ${RUNTIME_INSTALL_PATH}
	ARCHIVE       DESTINATION ${ARCHIVE_INSTALL_PATH}
	LIBRARY       DESTINATION ${LIBRARY_INSTALL_PATH}
	FRAMEWORK     DESTINATION ${FRAMEWORK_INSTALL_PATH}
	PUBLIC_HEADER DESTINATION ${HEADER_INSTALL_PATH}/${TARGET}
)
