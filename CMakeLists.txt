# Copyright 2016, 2019 Vincent Damewood
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

cmake_minimum_required(VERSION 3.1.0)

project(Seirina)
set(Seirina_VERSION_MAJOR 0)
set(Seirina_VERSION_MINOR 0)
set(Seirina_VERSION_PATCH 0)

set (CMAKE_CXX_STANDARD 11)

###########################
# System-dependent Values #
###########################

if(WIN32)
  set(RUNTIME_INSTALL_PATH   .)
  set(ARCHIVE_INSTALL_PATH   .)
  set(LIBRARY_INSTALL_PATH   .)
  set(BUNDLE_INSTALL_PATH    Error)
  set(FRAMEWORK_INSTALL_PATH Error)
  set(HEADER_INSTALL_PATH    ./include)
  set(SHARE_INSTALL_PATH     .)
  set(DOC_INSTALL_PATH       .)
elseif(APPLE)
  set(RUNTIME_INSTALL_PATH   bin)
  set(ARCHIVE_INSTALL_PATH   Error)
  set(LIBRARY_INSTALL_PATH   Error)
  set(BUNDLE_INSTALL_PATH    .)
  set(FRAMEWORK_INSTALL_PATH .)
  set(HEADER_INSTALL_PATH    Error)
  set(SHARE_INSTALL_PATH     Error)
  set(DOC_INSTALL_PATH       .)
elseif(UNIX)
  set(RUNTIME_INSTALL_PATH   bin)
  set(ARCHIVE_INSTALL_PATH   lib)
  set(LIBRARY_INSTALL_PATH   lib)
  set(BUNDLE_INSTALL_PATH    share/Seirina/error)
  set(FRAMEWORK_INSTALL_PATH share/Seirina/error)
  set(HEADER_INSTALL_PATH    include)
  set(SHARE_INSTALL_PATH     share/Seirina)
  set(DOC_INSTALL_PATH       share/Seirina/docs)
endif()

###########################
# Subdirectory Inclusions #
###########################

add_subdirectory(library)
add_subdirectory(genwav)
