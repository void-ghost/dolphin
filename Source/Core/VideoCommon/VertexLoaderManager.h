// Copyright 2008 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <string>

#include "Common/CommonTypes.h"
#include "VideoCommon/DataReader.h"
#include "VideoCommon/NativeVertexFormat.h"

namespace VertexLoaderManager
{
	void Init();
	void Shutdown();

	void MarkAllDirty();

	// Returns -1 if buf_size is insufficient, else the amount of bytes consumed
	int RunVertices(int vtx_attr_group, int primitive, int count, DataReader src, bool skip_drawing, bool is_preprocess);

	// For debugging
	void AppendListToString(std::string *dest);

	NativeVertexFormat* GetCurrentVertexFormat();

	// Resolved pointers to array bases. Used by vertex loaders.
	extern u8 *cached_arraybases[12];
	void UpdateVertexArrayPointers();

	// Position cache for zfreeze (3 vertices, 4 floats each to allow SIMD overwrite).
	// These arrays are in reverse order.
	extern float position_cache[3][4];
	extern u32 position_matrix_index[3];
}

