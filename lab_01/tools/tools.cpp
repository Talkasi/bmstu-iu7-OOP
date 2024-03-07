#include "tools.h"
#include <unistd.h>

err_t clear_file(FILE *f)
{
    if (f == NULL)
        return WRONG_FILE_PTR_ERR;

    err_t rc = SUCCESS;
    int fd = fileno(f);
    if (fd == -1)
        rc = FILE_DESC_OBTAIN_ERR;

    if (ftruncate(fd, 0) != 0)
        rc = FTRUNCATE_ERR;

    return rc;
}
