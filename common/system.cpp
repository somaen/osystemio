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

#define FORBIDDEN_SYMBOL_EXCEPTION_exit

#include "common/system.h"
#include "common/fs.h"
#include "common/str.h"
#include "common/textconsole.h"
#include "backends/fs/fs-factory.h"

OSystem *g_system = 0;

OSystem::OSystem() {
	_fsFactory = 0;
}

OSystem::~OSystem() {
	delete _fsFactory;
	_fsFactory = 0;
}

void OSystem::initBackend() {
}

void OSystem::fatalError() {
	quit();
	exit(1);
}

FilesystemFactory *OSystem::getFilesystemFactory() {
	assert(_fsFactory);
	return _fsFactory;
}


