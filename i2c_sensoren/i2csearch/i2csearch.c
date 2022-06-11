#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Von: http://www.netzmafia.de/skripten/hardware/RasPi/RasPi_I2C.html */

/* Installiert haben: libi2c-dev lm-sensors libsensors-dev */
/* Kompilieren mit:  "gcc i2csearch.c -o i2csearch -li2c" */
/* Bus Nummer passend zu: i2cdetect -l */
/* Installiert haben: libi2c-dev lm-sensors libsensors-dev */
/* Mehr dazu: https://www.kernel.org/doc/Documentation/i2c/dev-interface */

/* Suche nach I2C-Adressen */
void scan_i2c_bus(int device)
  {
  int port, res;

  for (port = 0; port < 127; port++)
    {
    if (ioctl(device, I2C_SLAVE, port) < 0)
      perror("ioctl() I2C_SLAVE failed\n");
    else
      {
      res = i2c_smbus_read_byte(device);
      if (res >= 0)
        printf("i2c chip found at: %x, val = %d\n", port, res);
      }
    }
  }


int main(void)
  {
  int device;
  unsigned long funcs;

  printf("Opening device...");
  if ((device = open("/dev/i2c-10", O_RDWR)) < 0)
    {
    perror("open() failed");
    exit (1);
    }
  printf(" OK\n");

  if (ioctl(device,I2C_FUNCS,&funcs) < 0)
    {
    perror("ioctl() I2C_FUNCS failed");
    exit (1);
    }

  if (funcs & I2C_FUNC_I2C)
    printf("I2C\n");
  if (funcs & (I2C_FUNC_SMBUS_BYTE))
    printf("I2C_FUNC_SMBUS_BYTE\n");

  scan_i2c_bus(device);

  return 0;
  }
