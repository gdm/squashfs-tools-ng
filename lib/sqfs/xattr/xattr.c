/* SPDX-License-Identifier: LGPL-3.0-or-later */
/*
 * write_xattr.c
 *
 * Copyright (C) 2019 David Oberhollenzer <goliath@infraroot.at>
 */
#define SQFS_BUILDING_DLL
#include "config.h"
#include "sqfs/xattr.h"
#include "sqfs/error.h"

#include <string.h>

static const struct {
	const char *prefix;
	SQFS_XATTR_TYPE type;
} xattr_types[] = {
	{ "user.", SQFS_XATTR_USER },
	{ "trusted.", SQFS_XATTR_TRUSTED },
	{ "security.", SQFS_XATTR_SECURITY },
};

int sqfs_get_xattr_prefix_id(const char *key)
{
	size_t i, len;

	for (i = 0; i < sizeof(xattr_types) / sizeof(xattr_types[0]); ++i) {
		len = strlen(xattr_types[i].prefix);

		if (strncmp(key, xattr_types[i].prefix, len) == 0 &&
		    strlen(key) > len) {
			return xattr_types[i].type;
		}
	}

	return SQFS_ERROR_UNSUPPORTED;
}

const char *sqfs_get_xattr_prefix(SQFS_XATTR_TYPE id)
{
	size_t i;

	for (i = 0; i < sizeof(xattr_types) / sizeof(xattr_types[0]); ++i) {
		if (xattr_types[i].type == id)
			return xattr_types[i].prefix;
	}

	return NULL;
}
