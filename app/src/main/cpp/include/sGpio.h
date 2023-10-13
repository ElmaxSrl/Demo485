
#ifndef __SGPIO_H__
#define __SGPIO_H__

#include "types.h"

enum pin_config_param {
	PIN_CONFIG_BIAS_DISABLE,
	PIN_CONFIG_BIAS_HIGH_IMPEDANCE,
	PIN_CONFIG_BIAS_BUS_HOLD,
	PIN_CONFIG_BIAS_PULL_UP,
	PIN_CONFIG_BIAS_PULL_DOWN,
	PIN_CONFIG_BIAS_PULL_PIN_DEFAULT,
	PIN_CONFIG_DRIVE_PUSH_PULL,
	PIN_CONFIG_DRIVE_OPEN_DRAIN,
	PIN_CONFIG_DRIVE_OPEN_SOURCE,
	PIN_CONFIG_DRIVE_STRENGTH,
	PIN_CONFIG_INPUT_ENABLE,
	PIN_CONFIG_INPUT_SCHMITT_ENABLE,
	PIN_CONFIG_INPUT_SCHMITT,
	PIN_CONFIG_INPUT_DEBOUNCE,
	PIN_CONFIG_POWER_SOURCE,
	PIN_CONFIG_SLEW_RATE,
	PIN_CONFIG_LOW_POWER_MODE,
	PIN_CONFIG_OUTPUT,
	PIN_CONFIG_END = 0x7FFF,
};

class sGpio {
public:
	sGpio();
	~sGpio();

	int start(const char *main, const char *sub);
	int stop(const char *main, const char *sub);

	int dir(const char *main, const char *sub, int val);
	int set(const char *main, const char *sub, int val);
	int pull(const char *main, const char *sub, int pull);
	int get(const char *main, const char *sub);
	int ldo(const char *name, int val);

private:
	int m_fd;
};

#endif
