/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef BACKENDS_MODULAR_BACKEND_H
#define BACKENDS_MODULAR_BACKEND_H

#include "common/system.h"

class GraphicsManager;
class MutexManager;

/**
 * Base class for modular backends.
 *
 * It wraps most functions to their manager equivalent, but not
 * all OSystem functions are implemented here.
 *
 * A backend derivated from this class, will need to implement
 * these functions on its own:
 *   OSystem::pollEvent()
 *   OSystem::getMillis()
 *   OSystem::delayMillis()
 *   OSystem::getTimeAndDate()
 *
 * And, it should also initialize all the managers variables
 * declared in this class, or override their related functions.
 */
class ModularBackend : public OSystem {
public:
	ModularBackend() {};
	virtual ~ModularBackend() {};

	//@}

	/** @name Miscellaneous */
	//@{
	virtual void initBackend();
	virtual void quit();

	//@}

protected:
};

#endif
