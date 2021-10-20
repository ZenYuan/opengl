# Install script for directory: F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/build/code/Debug/assimp-vc142-mtd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/build/code/Release/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/build/code/MinSizeRel/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/build/code/RelWithDebInfo/assimp-vc142-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/build/code/Debug/assimp-vc142-mtd.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/build/code/Release/assimp-vc142-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/build/code/MinSizeRel/assimp-vc142-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/build/code/RelWithDebInfo/assimp-vc142-mt.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/anim.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/aabb.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/ai_assert.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/camera.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/color4.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/color4.inl"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/build/code/../include/assimp/config.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/defs.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Defines.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/cfileio.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/light.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/material.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/material.inl"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/matrix3x3.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/matrix3x3.inl"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/matrix4x4.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/matrix4x4.inl"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/mesh.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/pbrmaterial.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/postprocess.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/quaternion.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/quaternion.inl"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/scene.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/metadata.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/texture.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/types.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/vector2.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/vector2.inl"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/vector3.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/vector3.inl"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/version.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/cimport.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/importerdesc.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Importer.hpp"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/DefaultLogger.hpp"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/ProgressHandler.hpp"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/IOStream.hpp"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/IOSystem.hpp"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Logger.hpp"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/LogStream.hpp"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/NullLogger.hpp"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/cexport.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Exporter.hpp"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/DefaultIOStream.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/DefaultIOSystem.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/ZipArchiveIOSystem.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/SceneCombiner.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/fast_atof.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/qnan.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/BaseImporter.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Hash.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/MemoryIOWrapper.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/ParsingUtils.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/StreamReader.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/StreamWriter.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/StringComparison.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/StringUtils.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/SGSpatialSort.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/GenericProperty.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/SpatialSort.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/SkeletonMeshBuilder.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/SmoothingGroups.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/SmoothingGroups.inl"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/StandardShapes.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/RemoveComments.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Subdivision.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Vertex.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/LineSplitter.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/TinyFormatter.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Profiler.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/LogAux.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Bitmap.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/XMLTools.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/IOStreamBuffer.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/CreateAnimMesh.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/irrXMLWrapper.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/BlobIOSystem.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/MathFunctions.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Macros.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Exceptional.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Compiler/pushpack1.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Compiler/poppack1.h"
    "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/build/code/Debug/assimp-vc142-mtd.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "F:/Project/code/CG/opengl/opengl/thirdParty/assimp-5.0.1/build/code/RelWithDebInfo/assimp-vc142-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

