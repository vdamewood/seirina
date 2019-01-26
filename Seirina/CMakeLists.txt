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
	Audio/Adsr.h
	Audio/AdsrTransform.h
	Audio/AudioEvent.h
	Audio/AudioFrame.h
	Audio/AudioSample.h
	Notation/Duration.h
	Audio/Frequency.h
	Notation/Note.h
	Notation/Octave.h
	Audio/Output.h
	Audio/Phase.h
	Notation/PitchClass.h
	Notation/Rest.h
	Audio/SampleDuration.h
	Audio/SampleIndex.h
	Audio/SampleRate.h
	Audio/Silence.h
	Audio/SimpleWaves.h
	Audio/SynthNote.h
	Notation/Tempo.h
	Notation/Tuning.h
	Audio/WaveForm.h
)
set(SOURCES
	${PUBLIC_HEADERS}
	Audio/Adsr.cc
	Audio/AdsrTransform.cc
	Audio/AudioFrame.cc
	Audio/AudioSample.cc
	Notation/Duration.cc
	Audio/Frequency.cc
	Notation/Note.cc
	Notation/Octave.cc
	Audio/Phase.cc
	Notation/PitchClass.cc
	Notation/Rest.cc
	Audio/SampleDuration.cc
	Audio/SampleIndex.cc
	Audio/SampleRate.cc
	Audio/Silence.cc
	Audio/SimpleWaves.cc
	Audio/SynthNote.cc
	Notation/Tempo.cc
	Notation/Tuning.cc
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
