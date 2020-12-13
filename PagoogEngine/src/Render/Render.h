#pragma once

#define PG_FRONT_AND_BACK                0x0408 
#define PG_FRONT                         0x0404 
#define PG_BACK                          0x0405 
									     
#define PG_FILL                          0x1B02
#define PG_LINE                          0x1B01
#define PG_POINT                         0x1B00
									     
#define PG_POINTS					     0x0000
#define PG_LINE_STRIP				     0x0003
#define PG_LINE_LOOP				     0x0002
#define PG_LINES					     0x0001
#define PG_LINE_STRIP_ADJACENCY	         0x000B
#define PG_LINES_ADJACENCY			     0x000A
#define PG_TRIANGLE_STRIP			     0x0005
#define PG_TRIANGLE_FAN			         0x0006
#define PG_TRIANGLES				     0x0004
#define PG_TRIANGLE_STRIP_ADJACENCY      0x000D
#define PG_TRIANGLES_ADJACENCY 	         0x000C 
#define PG_PATCHES					     0x000E
									     
#define PG_BYTE                          0x1400
#define PG_UNSIGNED_BYTE                 0x1401
#define PG_SHORT                         0x1402
#define PG_UNSIGNED_SHORT                0x1403
#define PG_INT                           0x1404
#define PG_HALF_FLOAT                    0x140B
#define PG_FLOAT                         0x1406
#define PG_DOUBLE                        0x140A
#define PG_FIXED                         0x140C
#define PG_INT_2_10_10_10_REV            0x8D9F
#define PG_UNSIGNED_INT_2_10_10_10_REV   0x8368 
#define PG_UNSIGNED_INT_10F_11F_11F_REV  0x8C3B  

namespace PEngine
{
	class Render
	{
	public:
		typedef unsigned int RenderingOption;

		static void Init();

		static void APIENTRY ErrorCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam);

		static void EnableDepthTest(bool enable);

		static void SetPolygonMode(RenderingOption face, RenderingOption type);

		static void RenderArrays(RenderingOption type, unsigned int first, unsigned int count);
		static void RenderElements(RenderingOption type, unsigned int first, unsigned int count);

		static void RenderTrianglesFromArrays(unsigned int first, unsigned int count);
		static void RenderTrianglesFromElements(unsigned int first, unsigned int count);

		static unsigned int GetError();
	};
}

