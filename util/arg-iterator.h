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

#ifndef FATFS_UTIL_ARG_ITERATOR_H
#define FATFS_UTIL_ARG_ITERATOR_H

#include <fat/types.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** Used to iterate command line arguments.
 * */

struct arg_iterator
{
	/** The position of the iterator
	 * within the argument array. */
	int pos;
	/** The number of command line
	 * arguments in the argument array. */
	int argc;
	/** The argument array. */
	const char **argv;
};

void
arg_iterator_init(struct arg_iterator *iterator,
                  int argc,
                  const char **argv);

fat_bool
arg_iterator_at_end(const struct arg_iterator *iterator);

void
arg_iterator_next(struct arg_iterator *iterator);

const char *
arg_iterator_get_current(const struct arg_iterator *iterator);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FATFS_UTIL_ARG_ITERATOR_H */
