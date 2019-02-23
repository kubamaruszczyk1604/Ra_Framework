#pragma once
//Uniform parameters send by the engine to currently bound shader program:

#define ENABLE__uWORLD			// World Matrix 4x4   id = "uWORLD"
#define ENABLE__uWORLD_INVERSE  // Matrix 4x4         id = "uWORLD_INVERSE"
#define ENABLE__uVIEW			// View Matrix 4x4    id = "uView" 
#define ENABLE__uMVP			// MVP Matrix 4x4     id = "uMVP"
#define ENABLE__uCameraPosition // Vector3            id = "uCameraPosition" 
#define ENABLE__uTime			// Single Float       id = "uTime"

/* 
  NOTE:
  Thr "uMVP" matrix is essential for the camera system to work and is best left enabled.
  In your vertex shader multiply the position attribute by this matrix:
  -> gl_Position =  uMVP*vec4(vertex_position, 1.0); <-
*/