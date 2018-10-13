/* libfat : A FAT file system library written in C.
 *
 * Copyright (C) 2018 Taylor Holberton
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <fat/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arg-iterator.h"
#include "common-opts.h"
#include "mkfs.h"
#include "mkdir.h"

static fat_bool
at_nonopt(const struct arg_iterator *iterator)
{
	const char *arg = arg_iterator_get_current(iterator);
	if (arg == NULL)
	{
		return FAT_FALSE;
	}

	if (arg[0] == '-')
	{
		return FAT_FALSE;
	}

	return FAT_TRUE;
}

static int
invalid_opt(const struct arg_iterator *iterator)
{
	const char *opt = arg_iterator_get_current(iterator);

	fprintf(stderr, "Invalid option '%s'.\n", opt);

	return EXIT_FAILURE;
}

static int
parse_disk_path(struct common_opts *opts,
                struct arg_iterator *iterator)
{
	const char *key = arg_iterator_get_current(iterator);
	if (key == NULL)
	{
		return 0;
	}

	if ((strcmp(key, "--disk") != 0)
	 && (strcmp(key, "-d") != 0))
	{
		return 0;
	}

	arg_iterator_next(iterator);

	if (arg_iterator_at_end(iterator))
	{
		fprintf(stderr, "The '%s' option requires a disk path.\n", key);
		return -1;
	}

	opts->disk_path = arg_iterator_get_current(iterator);

	arg_iterator_next(iterator);

	return 1;
}

static void
init_common_opts(struct common_opts *opts)
{
	opts->disk_path = "fat.img";
}

static void
print_help(void)
{
	fprintf(stderr, "Usage: ffutil [options] <command>\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Options\n");
	fprintf(stderr, "	-h, --help      : Print this help message.\n");
	fprintf(stderr, "	-d, --disk PATH : Specify the path of the disk file.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Commands\n");
	fprintf(stderr, "	mkfs  : Create a new FAT file system.\n");
	fprintf(stderr, "	mkdir : Create a new directory.\n");
}

static int
parse_help(struct arg_iterator *iterator)
{
	const char *opt = arg_iterator_get_current(iterator);
	if ((strcmp(opt, "-h") != 0)
	 && (strcmp(opt, "--help") != 0)) {
		return 0;
	}

	print_help();

	return -1;
}

static int
parse_common_opts(struct common_opts *opts,
                  struct arg_iterator *iterator)
{
	int result = 0;

	while (!arg_iterator_at_end(iterator)) {

		result = parse_disk_path(opts, iterator);
		if (result < 0)
		{
			return EXIT_FAILURE;
		}
		else if (result > 0)
		{
			continue;
		}

		result = parse_help(iterator);
		if (result < 0)
		{
			return EXIT_FAILURE;
		}
		else if (result > 0)
		{
			continue;
		}

		if (at_nonopt(iterator)) {
			break;
		} else {
			return invalid_opt(iterator);
		}
	}

	return EXIT_SUCCESS;
}

enum ffutil_cmd
{
	FFUTIL_CMD_UNKNOWN,
	FFUTIL_CMD_MKFS,
	FFUTIL_CMD_MKDIR
};

static enum ffutil_cmd
parse_cmd(struct arg_iterator *iterator)
{
	const char *arg = arg_iterator_get_current(iterator);
	if (arg == NULL) {
		return FFUTIL_CMD_UNKNOWN;
	}

	if (strcmp(arg, "mkfs") == 0)
	{
		return FFUTIL_CMD_MKFS;
	}
	else if (strcmp(arg, "mkdir") == 0)
	{
		return FFUTIL_CMD_MKDIR;
	}

	return FFUTIL_CMD_UNKNOWN;
}

static int
unknown_cmd(const struct arg_iterator *iterator)
{
	const char *cmd = arg_iterator_get_current(iterator);

	fprintf(stderr, "Unknown command '%s'.\n", cmd);
	fprintf(stderr, "\n");
	fprintf(stderr, "See -h or --help for assistance.\n");

	return EXIT_FAILURE;
}

static int
missing_cmd(void)
{
	fprintf(stderr, "Missing command.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "See -h or --help for assistance.\n");
	return EXIT_FAILURE;
}

int
main (int argc, const char **argv)
{
	(void) argc;
	(void) argv;

	struct common_opts opts;
	init_common_opts(&opts);

	struct arg_iterator arg_iterator;
	arg_iterator_init(&arg_iterator, argc, argv);
	arg_iterator_next(&arg_iterator);

	int err = parse_common_opts(&opts, &arg_iterator);
	if (err != 0) {
		return EXIT_FAILURE;
	}

	if (arg_iterator_at_end(&arg_iterator))
	{
		return missing_cmd();
	}

	enum ffutil_cmd cmd = parse_cmd(&arg_iterator);
	switch (cmd)
	{
	case FFUTIL_CMD_UNKNOWN:
		return unknown_cmd(&arg_iterator);
	case FFUTIL_CMD_MKFS:
		return ffutil_mkfs(&opts, &arg_iterator);
	case FFUTIL_CMD_MKDIR:
		return ffutil_mkdir(&opts, &arg_iterator);
	}

	/* unreachable */

	return EXIT_SUCCESS;
}
