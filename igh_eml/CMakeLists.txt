cmake_minimum_required(VERSION 2.8.3)
project(igh_eml)

find_package(catkin REQUIRED)

include(ExternalProject)
ExternalProject_Add(upstream_igh_eml    # Name for custom target
# #--Download step--------------
  #HG_REPOSITORY http://hg.code.sf.net/p/etherlabmaster/code         # URL of mercurial repo
  #HG_TAG 792892ab4806                # Mercurial branch name, commit id or tag
  #Switch to a UniBremen mirror of the upstream igh code (faster than sourceforge)
  GIT_REPOSITORY https://gitlab.informatik.uni-bremen.de/amaldo/igh_eml_upstream_clone.git
  #The following TAG should correspond to the same version as your installed kernel modules
  GIT_TAG d598ab86741cc7b60b3a169a1cee06b24dd83f89
  TIMEOUT 30           # Time allowed for file download operations
# #--Update/Patch step----------
  UPDATE_COMMAND touch <SOURCE_DIR>/config.h COMMAND mkdir -p <SOURCE_DIR>/include <SOURCE_DIR>/lib    # Source work-tree update command
# #--Configure step-------------
  CONFIGURE_COMMAND touch <SOURCE_DIR>/ChangeLog COMMAND autoreconf -i <SOURCE_DIR> COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR> --disable-kernel --enable-hrtimer --enable-tool  # Build tree configuration command
# #--Build step-----------------
  BUILD_IN_SOURCE 1         # Use source dir for build dir
# #--Install step---------------
  INSTALL_DIR ${CATKIN_DEVEL_PREFIX}           # Installation prefix
  )

add_library(ethercat SHARED IMPORTED)
set_target_properties(ethercat PROPERTIES IMPORTED_LOCATION ${CATKIN_DEVEL_PREFIX}/lib/libethercat.so)
add_dependencies(ethercat upstream_igh_eml)

catkin_package(
  LIBRARIES ethercat
)
