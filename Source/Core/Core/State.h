// Copyright 2008 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.


// Emulator state saving support.

#pragma once

#include <string>
#include <vector>

#include "Common/CommonTypes.h"

namespace State
{

// number of states
constexpr u32 QUICK_STATE_FIRST = 1;
constexpr u32 QUICK_STATE_NUM = 10;
constexpr u32 QUICK_STATE_LAST = QUICK_STATE_FIRST + QUICK_STATE_NUM - 1;
constexpr u32 ON_EXIT_STATE = QUICK_STATE_LAST + 1;
constexpr u32 AUTOSAVE_STATE_FIRST = ON_EXIT_STATE + 1;
constexpr u32 AUTOSAVE_STATE_NUM = 0; //not implemented yet, so don't even look for them
constexpr u32 AUTOSAVE_STATE_LAST = AUTOSAVE_STATE_FIRST + AUTOSAVE_STATE_NUM - 1;
constexpr u32 ALL_STATES_LAST = AUTOSAVE_STATE_LAST;

struct StateHeader
{
	u8 gameID[6];
	u32 size;
	double time;
};

void Init();

void Shutdown();

void EnableCompression(bool compression);

bool ReadHeader(const std::string& filename, StateHeader& header);

// These don't happen instantly - they get scheduled as events.
// ...But only if we're not in the main CPU thread.
//    If we're in the main CPU thread then they run immediately instead
//    because some things (like Lua) need them to run immediately.
// Slots from 0-99.
void Save(int slot, bool wait = false);
void Load(int slot);
void Verify(int slot);

void SaveAs(const std::string &filename, bool wait = false);
void LoadAs(const std::string &filename);
void VerifyAt(const std::string &filename);

void SaveToBuffer(std::vector<u8>& buffer);
void LoadFromBuffer(std::vector<u8>& buffer);
void VerifyBuffer(std::vector<u8>& buffer);

void LoadLastSaved(int i = 1, bool silent = true);
void SaveFirstSaved();
void UndoSaveState();
void UndoLoadState();

// wait until previously scheduled savestate event (if any) is done
void Flush();

// for calling back into UI code without introducing a dependency on it in core
typedef void(*CallbackFunc)(void);
void SetOnAfterLoadCallback(CallbackFunc callback);

}
