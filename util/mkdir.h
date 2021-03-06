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

#ifndef FATFS_UTIL_MKDIR_H
#define FATFS_UTIL_MKDIR_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

struct arg_iterator;
struct common_opts;

int
ffutil_mkdir(const struct common_opts *common_opts,
             struct arg_iterator *arg_iterator);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FATFS_UTIL_MKDIR_H */
