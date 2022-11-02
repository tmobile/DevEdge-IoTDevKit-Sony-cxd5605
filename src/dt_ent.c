#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <stdio.h>
#include <stdlib.h>

const struct device *cxd5605_i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c1));
