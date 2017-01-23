/*
  Copyright (c) 2016 Red Hat, Inc. <http://www.redhat.com>
  This file is part of gluster-block.

  This file is licensed to you under your choice of the GNU Lesser
  General Public License, version 3 or any later version (LGPLv3 or
  later), or the GNU General Public License, version 2 (GPLv2), in all
  cases as published by the Free Software Foundation.
*/


# ifndef   _UTILS_H
# define   _UTILS_H   1

# include  <stdio.h>
# include  <stdlib.h>
# include  <stdbool.h>
# include  <string.h>
# include  <errno.h>


/* Target Create */
# define  FAILED_CREATE             "failed in create"
# define  FAILED_CREATING_FILE      "failed while creating block file in gluster volume"
# define  FAILED_CREATING_BACKEND   "failed while creating glfs backend"
# define  FAILED_CREATING_IQN       "failed while creating IQN"
# define  FAILED_CREATING_LUN       "failed while creating LUN"
# define  FAILED_SETTING_ATTRIBUTES "failed while setting attributes"
# define  FAILED_SAVEING_CONFIG     "failed while saving configuration"

/* Target List */
# define  FAILED_LIST               "failed in list"
# define  FAILED_LIST_BACKEND       "failed while listing glfs backends"

/* Target Info */
# define  FAILED_INFO               "failed in info"
# define  FAILED_GATHERING_INFO     "failed while gathering target info"

/* Target get cfgstring */
# define  FAILED_GATHERING_CFGSTR   "failed while gathering backend cfgstring"

/* Target Delete */
# define  FAILED_DELETE             "failed in delete"
# define  FAILED_DELETING_BACKEND   "failed while deleting glfs backend"
# define  FAILED_DELETING_IQN       "failed while deleting IQN"
# define  FAILED_DELETING_FILE      "failed while deleting block file from gluster volume"


# define ERROR(fmt, ...) \
         fprintf(stderr, "Error: " fmt " [at %s+%d :<%s>]\n", \
                 __VA_ARGS__, __FILE__, __LINE__, __FUNCTION__)

# define MSG(fmt, ...) \
         fprintf(stdout, fmt "\n", __VA_ARGS__)


# define CALLOC(x)    calloc(1, x)

# define GB_ALLOC_N(ptr, count) gbAllocN(&(ptr), sizeof(*(ptr)), (count), \
                                         __FILE__, __FUNCTION__, __LINE__)

# define GB_ALLOC(ptr) gbAlloc(&(ptr), sizeof(*(ptr)), \
                               __FILE__, __FUNCTION__, __LINE__)

# define GB_STRDUP(dst, src) gbStrdup(&(dst), src, \
                                      __FILE__, __FUNCTION__, __LINE__)

# define GB_FREE(ptr) gbFree(1 ? (void *) &(ptr) : (ptr))



int gbAlloc(void *ptrptr, size_t size,
            const char *filename, const char *funcname, size_t linenr);

int gbAllocN(void *ptrptr, size_t size, size_t count,
             const char *filename, const char *funcname, size_t linenr);

int gbStrdup(char **dest, const char *src,
             const char *filename, const char *funcname, size_t linenr);

void gbFree(void *ptrptr);

#endif  /* _UTILS_H */