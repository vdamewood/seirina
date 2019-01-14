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
  AudioFrame.h
  OutputStream.h
  WaveFile.h
  Timbre.h
  Note.h
  PlayedNote.h
  Adsr.h
  SonicEvent.h
  Silence.h
)
set(SOURCES
  ${PUBLIC_HEADERS}
  AudioFrame.cc
  OutputStream.cc
  WaveFile.cc
  Timbre.cc
  Note.cc
  PlayedNote.cc
  Adsr.cc
  Silence.cc
)

add_library(${TARGET} SHARED ${SOURCES})
set_target_properties(${TARGET}
  PROPERTIES
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
