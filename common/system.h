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

#ifndef COMMON_SYSTEM_H
#define COMMON_SYSTEM_H

#include "common/scummsys.h"
#include "common/noncopyable.h"
#include "graphics/pixelformat.h"

namespace Audio {
class Mixer;
}

namespace Graphics {
struct Surface;
//ResidualVM specific:
class PixelBuffer;
}

namespace Common {
class EventManager;
struct Rect;
class SaveFileManager;
class SearchSet;
class String;

class TimerManager;
class SeekableReadStream;
class WriteStream;
}

class AudioCDManager;
class FilesystemFactory;
class PaletteManager;

/**
 * A structure describing time and date. This is a clone of struct tm
 * from time.h. We roll our own since not all systems provide time.h.
 * We also do not imitate all files of struct tm, only those we
 * actually need.
 *
 * @note For now, the members are named exactly as in struct tm to ease
 * the transition.
 */
struct TimeDate {
	int tm_sec;     ///< seconds (0 - 60)
	int tm_min;     ///< minutes (0 - 59)
	int tm_hour;    ///< hours (0 - 23)
	int tm_mday;    ///< day of month (1 - 31)
	int tm_mon;     ///< month of year (0 - 11)
	int tm_year;    ///< year - 1900
	int tm_wday;    ///< days since Sunday (0 - 6)
};

namespace LogMessageType {

enum Type {
	kInfo,
	kError,
	kWarning,
	kDebug
};

} // End of namespace LogMessageType

/**
 * Interface for ScummVM backends. If you want to port ScummVM to a system
 * which is not currently covered by any of our backends, this is the place
 * to start. ScummVM will create an instance of a subclass of this interface
 * and use it to interact with the system.
 *
 * In particular, a backend provides a video surface for ScummVM to draw in;
 * methods to create timers, to handle user input events,
 * control audio CD playback, and sound output.
 */
class OSystem : Common::NonCopyable {
protected:
	OSystem();
	virtual ~OSystem();

protected:
	/**
	 * @name Module slots
	 *
	 * For backend authors only, the following pointers (= "slots) to various
	 * subsystem managers / factories / etc. can and should be set to
	 * a suitable instance of the respective type.
	 *
	 * For some of the slots, a default instance is set if your backend
	 * does not do so. For details, please look at the documentation of
	 * each slot.
	 *
	 * A backend may setup slot values in its initBackend() method,
	 * its constructor or somewhere in between. But it must a slot's value
	 * no later than in its initBackend() implementation, because
	 * OSystem::initBackend() will create any default instances if
	 * none has been set yet (and for other slots, will verify that
	 * one has been set; if not, an error may be generated).
	 */
	//@{

	
	/**
	 * No default value is provided for _fsFactory by OSystem.
	 *
	 * Note that _fsFactory is typically required very early on,
	 * so it usually should be set in the backends constructor or shortly
	 * thereafter, and before initBackend() is called.
	 *
	 * @note _fsFactory is deleted by the OSystem destructor.
	 */
	FilesystemFactory *_fsFactory;

	//@}

public:

	/**
	 * The following method is called once, from main.cpp, after all
	 * config data (including command line params etc.) are fully loaded.
	 *
	 * @note Subclasses should always invoke the implementation of their
	 *       parent class. They should do so near the end of their own
	 *       implementation.
	 */
	virtual void initBackend();

	/**
	 * Allows the backend to perform engine specific init.
	 * Called just before the engine is run.
	 */
	virtual void engineInit() { }

	/**
	 * Allows the backend to perform engine specific de-init.
	 * Called after the engine finishes.
	 */
	virtual void engineDone() { }

	/** @name Miscellaneous */
	//@{
	/** Quit (exit) the application. */
	virtual void quit() = 0;

	/**
	 * Signals that a fatal error inside the client code has happened.
	 *
	 * This should quit the application.
	 */
	virtual void fatalError();


	/**
	 * Returns the FilesystemFactory object, depending on the current architecture.
	 *
	 * @return the FSNode factory for the current architecture
	 */
	virtual FilesystemFactory *getFilesystemFactory();

	/**
	 * Add system specific Common::Archive objects to the given SearchSet.
	 * E.g. on Unix the dir corresponding to DATA_PATH (if set), or on
	 * Mac OS X the 'Resource' dir in the app bundle.
	 *
	 * @todo Come up with a better name. This one sucks.
	 *
	 * @param s		the SearchSet to which the system specific dirs, if any, are added
	 * @param priority	the priority with which those dirs are added
	 */
	virtual void addSysArchivesToSearchSet(Common::SearchSet &s, int priority = 0) {}


	/**
	 * Logs a given message.
	 *
	 * It is up to the backend where to log the different messages.
	 * The backend should aim at using a non-buffered output for it
	 * so that no log data is lost in case of a crash.
	 *
	 * The default implementation outputs them on stdout/stderr.
	 *
	 * @param type    the type of the message
	 * @param message the message itself
	 */
	virtual void logMessage(LogMessageType::Type type, const char *message) = 0;

	//@}
};


/** The global OSystem instance. Initialized in main(). */
extern OSystem *g_system;

#endif
