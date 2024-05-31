#pragma once

#include <unistd.h>
#include <sys/param.h>


#define MFSTYPENAMELEN  16 /* length of fs type name including null */
//#define MAXPATHLEN      1024
#define MNAMELEN        MAXPATHLEN

typedef struct { int32_t val[2]; } fsid_t;

struct statfs { /* when _DARWIN_FEATURE_64_BIT_INODE is defined */
    uint32_t    f_bsize;        /* fundamental file system block size */
    int32_t     f_iosize;       /* optimal transfer block size */
    uint64_t    f_blocks;       /* total data blocks in file system */
    uint64_t    f_bfree;        /* free blocks in fs */
    uint64_t    f_bavail;       /* free blocks avail to non-superuser */
    uint64_t    f_files;        /* total file nodes in file system */
    uint64_t    f_ffree;        /* free file nodes in fs */
    fsid_t      f_fsid;         /* file system id */
    uid_t       f_owner;        /* user that mounted the filesystem */
    uint32_t    f_type;         /* type of filesystem */
    uint32_t    f_flags;        /* copy of mount exported flags */
    uint32_t    f_fssubtype;    /* fs sub-type (flavor) */
    char        f_fstypename[MFSTYPENAMELEN];   /* fs type name */
    char        f_mntonname[MAXPATHLEN];        /* directory on which mounted */
    char        f_mntfromname[MAXPATHLEN];      /* mounted filesystem */
    uint32_t    f_reserved[8];  /* For future use */
};
