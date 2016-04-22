/*
 *| libmapuid - map random OpenShift 3 container UIDs to well-known UID
 *| Copyright (C) 2016  Daniel Tschan
 *|
 *| This program is free software; you can redistribute it and/or
 *| modify it under the terms of the GNU General Public License
 *| Version 2 as published by the Free Software Foundation.
 *|
 *| This program is distributed in the hope that it will be useful,
 *| but WITHOUT ANY WARRANTY; without even the implied warranty of
 *| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *| GNU General Public License for more details.
 *|
 *| You should have received a copy of the GNU General Public License
 *| along with this program; if not, write to the Free Software
 *| Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#define _GNU_SOURCE

#include <sys/types.h>
#include <pwd.h>
#include <dlfcn.h>

static struct passwd* (*next_getpwuid)(uid_t uid);
static int (*next_getpwuid_r)(uid_t uid, struct passwd *pwd, char *buf, size_t buflen, struct passwd **result);

void libmapuid_init (void) __attribute__((constructor));
void libmapuid_init (void)
{
	next_getpwuid = dlsym(RTLD_NEXT, "getpwuid");
	next_getpwuid_r = dlsym(RTLD_NEXT, "getpwuid_r");
}

struct passwd *getpwuid(uid_t uid) {
  if (uid >= 1000000000) {
    uid = 1001;
  }

  return next_getpwuid(uid);
}

int getpwuid_r(uid_t uid, struct passwd *pwd, char *buf, size_t buflen, struct passwd **result) {
  if (uid >= 1000000000) {
    uid = 1001;
  }

  return next_getpwuid_r(uid, pwd, buf, buflen, result);
}
