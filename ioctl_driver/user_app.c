#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

int main() {
    int fd;
    int32_t val = 0;

    fd = open("/dev/etx_device", O_RDWR);
    if(fd < 0) {
        printf("Cannot open device\n");
        return 0;
    }

    printf("Enter value to send: ");
    scanf("%d", &val);
    ioctl(fd, WR_VALUE, (int32_t*) &val);

    ioctl(fd, RD_VALUE, (int32_t*) &val);
    printf("Value read = %d\n", val);

    close(fd);
    return 0;
}

