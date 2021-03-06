# - Try to find voikko
# Once done this will define
#
#  VOIKKO_FOUND - system has VOIKKO
#  VOIKKO_INCLUDE_DIR - the VOIKKO include directory
#  VOIKKO_LIBRARIES - The libraries needed to use VOIKKO
#  VOIKKO_DEFINITIONS - Compiler switches required for using VOIKKO


IF (VOIKKO_INCLUDE_DIR AND VOIKKO_LIBRARIES)
  # Already in cache, be silent
  SET(VOIKKO_FIND_QUIETLY TRUE)
ENDIF (VOIKKO_INCLUDE_DIR AND VOIKKO_LIBRARIES)

FIND_PATH(VOIKKO_INCLUDE_DIR libvoikko/voikko.h)
FIND_LIBRARY(VOIKKO_LIBRARIES NAMES voikko)

# handle the QUIETLY and REQUIRED arguments and set VOIKKO_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VOIKKO DEFAULT_MSG VOIKKO_LIBRARIES VOIKKO_INCLUDE_DIR)

MARK_AS_ADVANCED(VOIKKO_INCLUDE_DIR VOIKKO_LIBRARIES)
