#pragma once

#include <array>

#include "Render/Mesh/MeshDataTypes.h"

namespace PEngine
{
	constexpr const int TotalVertexValuesPlane = 12;
	constexpr const int TotalIndexValuesPlane = 6;

	class Plane
	{
	public:
		enum Direction
		{
			First	= 0,
			North	= First,
			South	= 1,
			East	= 2,
			West	= 3,
			Up		= 4,
			Down	= 5,
			Last	= Down + 1
		};

		static constexpr std::array<Vertex::Position::ValueType, TotalVertexValuesPlane> GetPositions(Direction direction)
		{
			switch (direction)
			{
			case Direction::North:
			{
				constexpr std::array<Vertex::Position::ValueType, TotalVertexValuesPlane> positions =
				{
					 0.5f,  0.5f, 0.5f,
					 0.5f, -0.5f, 0.5f,
					-0.5f, -0.5f, 0.5f,
					-0.5f,  0.5f, 0.5f
				};

				return positions;
			}
			case Direction::South:
			{
				constexpr std::array<Vertex::Position::ValueType, TotalVertexValuesPlane> positions =
				{
					 0.5f,  0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,
					-0.5f,  0.5f, -0.5f
				};

				return positions;
			}
			case Direction::East:
			{
				constexpr std::array<Vertex::Position::ValueType, TotalVertexValuesPlane> positions =
				{
					0.5f,  0.5f,  0.5f,
					0.5f,  0.5f, -0.5f,
					0.5f, -0.5f, -0.5f,
					0.5f, -0.5f,  0.5f
				};

				return positions;
			}
			case Direction::West:
			{
				constexpr std::array<Vertex::Position::ValueType, TotalVertexValuesPlane> positions =
				{
					-0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,
					-0.5f, -0.5f,  0.5f
				};

				return positions;
			}
			case Direction::Up:
			{
				constexpr std::array<Vertex::Position::ValueType, TotalVertexValuesPlane> positions =
				{
					 0.5f,  0.5f,  0.5f,
					 0.5f,  0.5f, -0.5f,
					-0.5f,  0.5f, -0.5f,
					-0.5f,  0.5f,  0.5f
				};

				return positions;
			}
			case Direction::Down:
			{
				constexpr std::array<Vertex::Position::ValueType, TotalVertexValuesPlane> positions =
				{
					 0.5f, -0.5f,  0.5f,
					 0.5f, -0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,
					-0.5f, -0.5f,  0.5f
				};

				return positions;
			}
			}

			constexpr std::array<Vertex::Position::ValueType, TotalVertexValuesPlane> positions =
			{
				 0.5f, -0.5f,  0.5f,
				 0.5f, -0.5f, -0.5f,
				-0.5f, -0.5f, -0.5f,
				-0.5f, -0.5f,  0.5f
			};

			return positions;
		}

		static constexpr std::array<Vertex::Colour::ValueType, TotalVertexValuesPlane> GetColours()
		{
			constexpr std::array<Vertex::Colour::ValueType, TotalVertexValuesPlane> colours =
			{
				0.0f, 0.0f, 1.0f,
				1.0f, 0.0f, 1.0f,
				0.0f, 1.0f, 0.0f,
				1.0f, 1.0f, 1.0f
			};

			return colours;
		}

		static constexpr std::array<Vertex::Index::ValueType, TotalIndexValuesPlane> GetIndices(Direction direction)
		{
			switch (direction)
			{
			case Direction::North:
			{
				constexpr std::array<Vertex::Index::ValueType, TotalIndexValuesPlane> indices =
				{
					1, 0, 3,
					2, 1, 3
				};

				return indices;
			}
			case Direction::South:
			{
				constexpr std::array<Vertex::Index::ValueType, TotalIndexValuesPlane> indices =
				{
					0, 1, 3,
					1, 2, 3
				};

				return indices;
			}
			case Direction::East:
			{
				constexpr std::array<Vertex::Index::ValueType, TotalIndexValuesPlane> indices =
				{
					1, 0, 3,
					2, 1, 3
				};

				return indices;
			}
			case Direction::West:
			{
				constexpr std::array<Vertex::Index::ValueType, TotalIndexValuesPlane> indices =
				{
					0, 1, 3,
					1, 2, 3
				};

				return indices;
			}
			case Direction::Up:
			{
				constexpr std::array<Vertex::Index::ValueType, TotalIndexValuesPlane> indices =
				{
					0, 1, 3,
					1, 2, 3
				};

				return indices;
			}
			case Direction::Down:
			{
				constexpr std::array<Vertex::Index::ValueType, TotalIndexValuesPlane> indices =
				{
					1, 0, 3,
					2, 1, 3
				};

				return indices;
			}
			}

			constexpr std::array<Vertex::Index::ValueType, TotalIndexValuesPlane> indices =
			{
				0, 1, 3,
				1, 2, 3
			};

			return indices;
		}
	};
}

