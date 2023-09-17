/**
 * @author climatex
 * @date 2023-Sep-15
 * @version 1.0.1
 * @file cfile.h
*/

#ifndef __CFILE_H__
#define __CFILE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * fread_all(char *fpath);
void fwrite_all(char *fpath, char *data);

#ifdef __cplusplus
}
#endif

#endif  // __CFILE_H__