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

#ifndef FAT_FILE_INFO_H
#define FAT_FILE_INFO_H

#include <fat/tchar.h>
#include <fat/types.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** Contains information about
 * a single file.
 * */

struct fat_file_info {
	/* File size */
	FSIZE_t fsize;
	/* Modified date */
	fat_uint_least16 fdate;
	/* Modified time */
	fat_uint_least16 ftime;
	/* File attribute */
	fat_uint8 fattrib;
#if FF_USE_LFN
	/* Altenative file name */
	TCHAR altname[FF_SFN_BUF + 1];
	/* Primary file name */
	TCHAR fname[FF_LFN_BUF + 1];
#else
	/* File name */
	TCHAR fname[12 + 1];
#endif
};

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FAT_FILE_INFO_H */
