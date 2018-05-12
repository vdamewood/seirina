# Copyright 2016, 2018 Vincent Damewood
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

set(LIBNAME  Seirina)
set(LIBPHDRS OutputStream.h WaveFile.h Timbre.h Note.h)
set(LIBHDRS  ${LIBPHDRS})
set(LIBSRCS  OutputStream.cc WaveFile.cc Timbre.cc Note.cc Mpc.cc)

add_library(${LIBNAME} ${LIBHDRS} ${LIBSRCS})
set_target_properties(${LIBNAME}
  PROPERTIES
    FRAMEWORK     TRUE
    PUBLIC_HEADER "${LIBPHDRS}")
install(TARGETS ${LIBNAME}
  RUNTIME       DESTINATION ${RUNTIME_INSTALL_PATH}
  ARCHIVE       DESTINATION ${ARCHIVE_INSTALL_PATH}
  LIBRARY       DESTINATION ${LIBRARY_INSTALL_PATH}
  FRAMEWORK     DESTINATION ${FRAMEWORK_INSTALL_PATH}
  PUBLIC_HEADER DESTINATION ${HEADER_INSTALL_PATH}/${LIBNAME})

add_executable(genwav ${LIBPHDRS} InputParser.cc genwav.cc)
target_link_libraries(genwav ${LIBNAME})
