#include <stdio.h>
#include <stdint.h>
#include <linux/random.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
 
int main( int argc, const char* argv[] )
{
    // This program poses a potential security issue since it does not actally increase the entropy in the pool! USE AT YOUR OWN RISK!
    if (argc != 2) {
	printf("Usage: entropyIncreaser <Amount of bits added to the entropy count>\n");
    }
    int addEntropyAmount;
    addEntropyAmount = strtol(argv[1], NULL, 10);
    if (errno == ERANGE) {
	printf("The first parameter has to be an integer!\n");
	return -1;
    }
    int devRandomDevice = open("/dev/urandom", O_RDONLY);
    if (devRandomDevice == -1) {
        printf("Error while opening /dev/urandom\n");
        return devRandomDevice;
    }
    int storedEntropyCount;
    ioctl(devRandomDevice, RNDGETENTCNT, &storedEntropyCount);
    printf("Stored entropy: %d\n", storedEntropyCount);

    printf("Increasing entropy count by %d bits\n", addEntropyAmount);
    int result = ioctl(devRandomDevice, RNDADDTOENTCNT, &addEntropyAmount);
    // printf("Increment entropy count result: %d\n", result);
    if (result == -1) {
	printf("Failed to increase entropy count, maybe you forgot sudo?\n");
    }
    int storedEntropyLater;
    ioctl(devRandomDevice, RNDGETENTCNT, &storedEntropyLater);
    printf("Increased entropy count by %d bits\n", (storedEntropyLater - storedEntropyCount));
    if (close(devRandomDevice) == -1) {
        printf("Failed to close filedescriptor! Continuing anyways...");
	return -1;
    }
    return 0;
}
