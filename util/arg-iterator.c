/* FatFS : A FAT file system library written in C.
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

#include "arg-iterator.h"

void
arg_iterator_init(struct arg_iterator *iterator,
                  int argc,
                  const char **argv)
{
	iterator->argc = argc;
	iterator->argv = argv;
	iterator->pos = 0;
}

fatfs_bool
arg_iterator_at_end(const struct arg_iterator *iterator)
{
	if (iterator->pos >= iterator->argc) {
		return FATFS_TRUE;
	}

	return FATFS_FALSE;
}

const char *
arg_iterator_get_current(const struct arg_iterator *iterator)
{
	if (arg_iterator_at_end(iterator)) {
		return "";
	}

	return iterator->argv[iterator->pos];
}

void
arg_iterator_next(struct arg_iterator *iterator)
{
	if (!arg_iterator_at_end(iterator)) {
		iterator->pos++;
	}
}
