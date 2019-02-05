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
#include <stdlib.h>

static struct passwd* (*next_getpwuid)(uid_t uid);
static uid_t (*next_getpwuid_r)(uid_t uid, struct passwd *pwd, char *buf, size_t buflen, struct passwd **result);

static int target_user = 1001;

void libmapuid_init (void) __attribute__((constructor));
void libmapuid_init (void)
{
  char* mapuid_target_user;

	next_getpwuid = dlsym(RTLD_NEXT, "getpwuid");
	next_getpwuid_r = dlsym(RTLD_NEXT, "getpwuid_r");
  mapuid_target_user = getenv("MAPUID_TARGET_USER");
  if (mapuid_target_user) {
    target_user = atoi(mapuid_target_user);
  }
}

struct passwd *getpwuid(uid_t uid) {
  if (uid >= 1000000000) {
    uid = target_user;
  }

  return next_getpwuid(uid);
}

int getpwuid_r(uid_t uid, struct passwd *pwd, char *buf, size_t buflen, struct passwd **result) {
  if (uid >= 1000000000) {
    uid = target_user;
  }

  return next_getpwuid_r(uid, pwd, buf, buflen, result);
}
