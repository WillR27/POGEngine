#pragma once

#include "POGCommon.h"

#define POG_FRONT_AND_BACK					0x0408 
#define POG_FRONT							0x0404 
#define POG_BACK							0x0405 

#define POG_CW								0x0900
#define POG_CCW								0x0901

#define POG_FILL							0x1B02
#define POG_LINE							0x1B01
#define POG_POINT							0x1B00

#define POG_POINTS							0x0000
#define POG_LINE_STRIP						0x0003
#define POG_LINE_LOOP						0x0002
#define POG_LINES							0x0001
#define POG_LINE_STRIP_ADJACENCY	        0x000B
#define POG_LINES_ADJACENCY					0x000A
#define POG_TRIANGLE_STRIP					0x0005
#define POG_TRIANGLE_FAN			        0x0006
#define POG_TRIANGLES						0x0004
#define POG_TRIANGLE_STRIP_ADJACENCY		0x000D
#define POG_TRIANGLES_ADJACENCY 	        0x000C 
#define POG_PATCHES							0x000E

#define POG_BYTE							0x1400
#define POG_UNSIGNED_BYTE					0x1401
#define POG_SHORT							0x1402
#define POG_UNSIGNED_SHORT					0x1403
#define POG_INT								0x1404
#define POG_HALF_FLOAT						0x140B
#define POG_FLOAT							0x1406
#define POG_DOUBLE							0x140A
#define POG_FIXED							0x140C
#define POG_INT_2_10_10_10_REV				0x8D9F
#define POG_UNSIGNED_INT_2_10_10_10_REV		0x8368 
#define POG_UNSIGNED_INT_10F_11F_11F_REV	0x8C3B  

namespace POG::Graphics
{
	using RenderingOption = unsigned int;

	void ErrorCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam);

	void Init();

	void ClearColour(float r, float g, float b, float a);

	void ClearColourBuffer();
	void ClearDepthBuffer();

	void DepthTest(bool enable);
	void FaceCulling(bool enable);

	void SetPolygonMode(RenderingOption face, RenderingOption type);
	void CullFace(RenderingOption face);
	void SetFrontFace(RenderingOption face);

	void Blend(bool enable);

	void SetViewport(int x, int y, int width, int height);

	void BindDefaultFrameBuffer();

	void RenderArrays(RenderingOption type, unsigned int first, unsigned int count);
	void RenderElements(RenderingOption type, unsigned int first, unsigned int count);

	void RenderTrianglesFromArrays(unsigned int first, unsigned int count);
	void RenderTrianglesFromElements(unsigned int first, unsigned int count);

	void SetContextAddressFunc(ContextAddressFunc func);
}

