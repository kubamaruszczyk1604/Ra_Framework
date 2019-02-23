#pragma once
//Uniform parameters send by the engine to bound shader program
#define ENABLE__uWORLD			// World Matrix 4x4   id = "uWORLD"
#define ENABLE__uWORLD_INVERSE  // Matrix 4x4         id = "uWORLD_INVERSE"
#define ENABLE__uVIEW			// View Matrix 4x4    id = "uView" 
#define ENABLE__uCameraPosition // Vector3            id = "uCameraPosition" 
#define ENABLE__uTime			// Single Float       id = "uTime"