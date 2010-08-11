#ifndef FIO_OS_AIX_H
#define FIO_OS_AIX_H

#include <errno.h>
#include <unistd.h>
#include <sys/devinfo.h>
#include <sys/ioctl.h>

#define FIO_HAVE_POSIXAIO
#define FIO_HAVE_ODIRECT
#define FIO_USE_GENERIC_RAND

#define FIO_HAVE_PSHARED_MUTEX

#define OS_MAP_ANON		MAP_ANON

static inline int blockdev_invalidate_cache(int fd)
{
	return EINVAL;
}

static inline int blockdev_size(int fd, unsigned long long *bytes)
{
	struct devinfo info;

	if (!ioctl(fd, IOCINFO, &info)) {
        	*bytes = (unsigned long long)info.un.scdk.numblks *
				info.un.scdk.blksize;
		return 0;
	}

	return errno;
}

static inline unsigned long long os_phys_mem(void)
{
	long mem = sysconf(_SC_AIX_REALMEM);

	if (mem == -1)
		return 0;

	return (unsigned long long) mem * 1024;
}

#endif