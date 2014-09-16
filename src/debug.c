/**
 *  This file is part of ebtables-dhcpsnoopingd.
 *
 *  Ebtables-dhcpsnoopingd is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Ebtables-dhcpsnoopingd is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ebtables-dhcpsnoopingd.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 *  (C) 2013, Michael Braun <michael-dev@fami-braun.de>
 */

#include "config.h"
#include "debug.h"
#include "cmdline.h"
#include <unistd.h>
#include <syslog.h>
#include <stdio.h>
#include <string.h>

static int debug = DEBUG_ERROR;

void set_debug_flag(int c) {
	debug |= c;
}

void edprint(const int level, const char* msg, const char* file, const int line, const char* fnc)
{
#ifdef DEBUG
	char syslogbuf[4096];
	const char *bname;
	static int open = 0;
	if (!open) {
		openlog ("dhcpsnoopingd", LOG_CONS | LOG_PID | LOG_NDELAY | LOG_PERROR, LOG_DAEMON);
		open = 1;
	}
	if (level & debug) {
		bname = (strrchr(file, '/') ? strrchr(file, '/') + 1 : file);
		snprintf(syslogbuf, sizeof(syslogbuf), "%s (%s:%d): %s", fnc, bname, line, msg);
		syslog(LOG_INFO, syslogbuf, strlen(syslogbuf));
	};
#endif
}

static __attribute__((constructor)) void debug_init()
{
	{
		struct option long_option = {"debug", no_argument, 0, DEBUG_GENERAL};
		add_option_cb(long_option, set_debug_flag);
	}
	{
		struct option long_option = {"debug-udp", no_argument, 0, DEBUG_UDP};
		add_option_cb(long_option, set_debug_flag);
	}
	{
		struct option long_option = {"debug-nflog", no_argument, 0, DEBUG_NFLOG};
		add_option_cb(long_option, set_debug_flag);
	}
	{
		struct option long_option = {"debug-neigh", no_argument, 0, DEBUG_NEIGH};
		add_option_cb(long_option, set_debug_flag);
	}
	{
		struct option long_option = {"debug-dhcp", no_argument, 0, DEBUG_DHCP};
		add_option_cb(long_option, set_debug_flag);
	}
	{
		struct option long_option = {"debug-all",  no_argument, 0, DEBUG_ALL};
		add_option_cb(long_option, set_debug_flag);
	}
	{
		struct option long_option = {"verbose",  no_argument, 0, DEBUG_VERBOSE};
		add_option_cb(long_option, set_debug_flag);
	}
}

