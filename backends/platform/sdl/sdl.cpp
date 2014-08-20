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

#define FORBIDDEN_SYMBOL_ALLOW_ALL

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef ARRAYSIZE // winnt.h defines ARRAYSIZE, but we want our own one...
#endif

#include "backends/platform/sdl/sdl.h"
#include "common/textconsole.h"

#include <time.h>	// for getTimeAndDate()

#ifdef USE_DETECTLANG
#ifndef WIN32
#include <locale.h>
#endif // !WIN32
#endif

OSystem_SDL::OSystem_SDL()
	:
	_inited(false) {}

void OSystem_SDL::init() {}

void OSystem_SDL::initBackend() {
	// Check if backend has not been initialized
	assert(!_inited);

	_inited = true;

	ModularBackend::initBackend();
}


void OSystem_SDL::addSysArchivesToSearchSet(Common::SearchSet &s, int priority) {

#ifdef DATA_PATH
	// Add the global DATA_PATH to the directory search list
	// FIXME: We use depth = 4 for now, to match the old code. May want to change that
	Common::FSNode dataNode(DATA_PATH);
	if (dataNode.exists() && dataNode.isDirectory()) {
		s.add(DATA_PATH, new Common::FSDirectory(dataNode, 4), priority);
	}
#endif

}

void OSystem_SDL::quit() {
	delete this;
	exit(0);
}

void OSystem_SDL::fatalError() {
	delete this;
	exit(1);
}

void OSystem_SDL::logMessage(LogMessageType::Type type, const char *message) {
	// First log to stdout/stderr
	FILE *output = 0;

	if (type == LogMessageType::kInfo || type == LogMessageType::kDebug)
		output = stdout;
	else
		output = stderr;

	fputs(message, output);
	fflush(output);

	// Finally, some Windows / WinCE specific logging code.
#if defined( USE_WINDBG )
#if defined( _WIN32_WCE )
	TCHAR buf_unicode[1024];
	MultiByteToWideChar(CP_ACP, 0, message, strlen(message) + 1, buf_unicode, sizeof(buf_unicode));
	OutputDebugString(buf_unicode);

	if (type == LogMessageType::kError) {
#ifndef DEBUG
		drawError(message);
#else
		int cmon_break_into_the_debugger_if_you_please = *(int *)(message + 1);	// bus error
		printf("%d", cmon_break_into_the_debugger_if_you_please);			// don't optimize the int out
#endif
	}

#else
	OutputDebugString(message);
#endif
#endif
}

uint32 OSystem_SDL::getMillis(bool skipRecord) {
	uint32 millis = 0;//SDL_GetTicks();

	return millis;
}

void OSystem_SDL::delayMillis(uint msecs) {
//	SDL_Delay(msecs);
}

void OSystem_SDL::getTimeAndDate(TimeDate &td) const {
	time_t curTime = time(0);
	struct tm t = *localtime(&curTime);
	td.tm_sec = t.tm_sec;
	td.tm_min = t.tm_min;
	td.tm_hour = t.tm_hour;
	td.tm_mday = t.tm_mday;
	td.tm_mon = t.tm_mon;
	td.tm_year = t.tm_year;
	td.tm_wday = t.tm_wday;
}

