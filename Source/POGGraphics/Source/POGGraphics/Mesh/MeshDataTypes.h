#pragma once

namespace POG::Graphics
{
	class VertexAttribute
	{
	public:
		VertexAttribute()
			: dataArray(nullptr)
		{
		}

		VertexAttribute(const VertexAttribute&) = delete;
		VertexAttribute(VertexAttribute&&) = delete;

		virtual ~VertexAttribute()
		{
			delete[] dataArray;
		}

		const char* GetData()
		{
			return dataArray;
		}

		void SetData(const void* dataToBeCopied, int size)
		{
			// Delete the old data array if it exists
			delete[] dataArray;

			// Allocate a new array the size of the data being passed in
			dataArray = new char[size];

			// Copy the given data to the new array
			memcpy(dataArray, dataToBeCopied, size);
		}

		// Returns the number of values per vertex e.g 3 for position, 2 for tex coords
		virtual constexpr int Count() const = 0;

		// Returns the size of an entire vertex's worth of data e.g. 12 bytes for a position, 8 bytes for a tex coord
		virtual constexpr int Size() const = 0;

	private:
		char* dataArray;
	};

	struct Position : public VertexAttribute
	{
		using ValueType = float;
		constexpr int Count() const override { return 3; }
		constexpr int Size() const override { return sizeof(ValueType) * Count(); }
	};

	struct Colour : public VertexAttribute
	{
		using ValueType = float;
		constexpr int Count() const override { return 3; }
		constexpr int Size() const override { return sizeof(ValueType) * Count(); }
	};

	struct TexCoords : public VertexAttribute
	{
		using ValueType = float;
		constexpr int Count() const override { return 2; }
		constexpr int Size() const override { return sizeof(ValueType) * Count(); }
	};

	struct Index : public VertexAttribute
	{
		using ValueType = unsigned int;
		constexpr int Count() const override { return 1; }
		constexpr int Size() const override { return sizeof(ValueType) * Count(); }
	};
}