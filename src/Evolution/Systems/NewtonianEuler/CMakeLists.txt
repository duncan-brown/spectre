# Distributed under the MIT License.
# See LICENSE.txt for details.

set(LIBRARY NewtonianEuler)

set(LIBRARY_SOURCES
    PrimitiveFromConservative.cpp
    )

add_library(${LIBRARY} ${LIBRARY_SOURCES})

target_link_libraries(
  ${LIBRARY}
  INTERFACE DataStructures
  INTERFACE ErrorHandling
  )
