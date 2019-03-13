#pragma once
#include <iostream>
#include "portable.h"

namespace Phantom {
	ENUM(IndexDataType) {
		kIndexDataTypeInt8 = "I8  "_i32,
			kIndexDataTypeInt16 = "I16 "_i32,
			kIndexDataTypeInt32 = "I32 "_i32,
			kIndexDataTypeInt64 = "I64 "_i32,
	};

	//std::ostream& operator<<(std::ostream& out, IndexDataType type);

	ENUM(VertexDataType) {
		kVertexDataTypeFloat1 = "FLT1"_i32,
			kVertexDataTypeFloat2 = "FLT2"_i32,
			kVertexDataTypeFloat3 = "FLT3"_i32,
			kVertexDataTypeFloat4 = "FLT4"_i32,
			kVertexDataTypeDouble1 = "DUB1"_i32,
			kVertexDataTypeDouble2 = "DUB2"_i32,
			kVertexDataTypeDouble3 = "DUB3"_i32,
			kVertexDataTypeDouble4 = "DUB4"_i32
	};

	//std::ostream& operator<<(std::ostream& out, VertexDataType type);

}