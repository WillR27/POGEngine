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

#define POG_BLEND							0x0BE2
#define POG_CULL_FACE						0x0B44
#define POG_DEPTH_TEST						0x0B71

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

#define POG_UNPACK_ALIGNMENT				0x0CF5
#define POG_PACK_ALIGNMENT					0x0D05

namespace POG::Graphics
{
	using RenderingOption = unsigned int;

	enum class Capability : unsigned int
	{
		Blend			= POG_BLEND,
		CullFace		= POG_CULL_FACE,
		DepthTest		= POG_DEPTH_TEST,
	};

	enum class PolygonFace : unsigned int
	{
		FrontAndBack	= POG_FRONT_AND_BACK,
		Front			= POG_FRONT,
		Back			= POG_BACK,
	};

	enum class PolygonMode : unsigned int
	{
		Point			= POG_POINT,
		Line			= POG_LINE,
		Fill			= POG_FILL,
	};

	enum class PolygonFaceDirection : unsigned int
	{
		Clockwise			= POG_CW,
		CounterClockwise	= POG_CCW,
	};

	enum class Alignment : unsigned int
	{
		Unpack	= POG_UNPACK_ALIGNMENT,
		Pack	= POG_PACK_ALIGNMENT,
	};

	void ErrorCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam);

	void Enable(Capability capability);
	void Disable(Capability capability);
	bool IsEnabled(Capability capability);

	void ClearColour(float r, float g, float b, float a);

	void ClearColourBuffer();
	void ClearDepthBuffer();

	PolygonMode GetPolygonMode(PolygonFace face);
	void SetPolygonMode(PolygonFace face, PolygonMode mode);

	PolygonFaceDirection GetFrontFaceDirection();
	void SetFrontFaceDirection(PolygonFaceDirection face);

	PolygonFace GetCullFace();
	void SetCullFace(PolygonFace face);

	void RenderArrays(RenderingOption type, unsigned int first, unsigned int count);
	void RenderElements(RenderingOption type, unsigned int first, unsigned int count);

	void RenderTrianglesFromArrays(unsigned int first, unsigned int count);
	void RenderTrianglesFromElements(unsigned int first, unsigned int count);

	void SetPixelStorei(Alignment alignment, int value);
	void SetPixelStoref(Alignment alignment, float value);

	void SetViewport(int x, int y, int width, int height);

	void BindDefaultFrameBuffer();

	void SetContextAddressFunc(ContextAddressFunc func);

	void Init();
}

