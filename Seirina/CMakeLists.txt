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
	include/Seirina/Adsr.h
	include/Seirina/AdsrTransform.h
	include/Seirina/AudioEvent.h
	include/Seirina/AudioFrame.h
	include/Seirina/AudioSample.h
	include/Seirina/Duration.h
	include/Seirina/Frequency.h
	include/Seirina/Note.h
	include/Seirina/Octave.h
	include/Seirina/Output.h
	include/Seirina/Phase.h
	include/Seirina/PitchClass.h
	include/Seirina/Rest.h
	include/Seirina/SampleDuration.h
	include/Seirina/SampleIndex.h
	include/Seirina/SampleRate.h
	include/Seirina/Silence.h
	include/Seirina/SimpleWaves.h
	include/Seirina/SynthNote.h
	include/Seirina/Tempo.h
	include/Seirina/Tuning.h
	include/Seirina/WaveForm.h
)

set(SOURCES
	${PUBLIC_HEADERS}
	src/Adsr.cc
	src/AdsrTransform.cc
	src/AudioFrame.cc
	src/AudioSample.cc
	src/Duration.cc
	src/Frequency.cc
	src/Note.cc
	src/Octave.cc
	src/Phase.cc
	src/PitchClass.cc
	src/Rest.cc
	src/SampleDuration.cc
	src/SampleIndex.cc
	src/SampleRate.cc
	src/Silence.cc
	src/SimpleWaves.cc
	src/SynthNote.cc
	src/Tempo.cc
	src/Tuning.cc
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
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
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
