// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT

#pragma once

#include "cheri.hh"
#include <stdint.h>

using namespace CHERI;

template<typename T>
struct HeapOffset
{
	uint16_t value = 0;

	/**
	 * Return true if the underlying value is 0, that is, if this offset
	 * represents a nullpointer.
	 */
	[[nodiscard]] bool is_null() const
	{
		return value == 0;
	}

	/**
	 * Decode this offset and return a pointer to T, or `nullptr` if null.
	 */
	[[nodiscard]] T *get() const;

	/**
	 * Encode a pointer to a heap-allocated T as a HeapOffset.
	 * Asserts that `ptr` is non-null, correctly aligned, and is within the
	 * representable range of 16 bits.
	 *
	 * Use HeapOffset{} to represent a nullptr.
	 */
	[[nodiscard]] static HeapOffset<T> from(T *ptr);

	/**
	 * Comparison operators compare the underlying compressed pointer value.
	 */
	bool operator==(const HeapOffset &other) const
	{
		return value == other.value;
	}

	bool operator!=(const HeapOffset &other) const
	{
		return value != other.value;
	}

	/**
	 * Dereference operators allow this to be used as any other pointer.
	 */
	T *operator->() const
	{
		return get();
	}

	T &operator*() const
	{
		return *get();
	}
};
