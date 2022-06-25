#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <libevdev/libevdev-uinput.h>

struct s_enabling_key_table {
	unsigned int type;
	unsigned int code; 
};

struct s_enabling_key_table enabling_key_table[] = {
	{ EV_KEY , KEY_EQUAL },
	{ EV_KEY , KEY_TAB },
	{ EV_KEY , KEY_AUDIO },
	{ EV_KEY , KEY_MODE },
	{ EV_KEY , KEY_PREVIOUS },
};

int main(int argc, char *argv[])
{
	int err;
	struct libevdev *dev = NULL;
	struct libevdev_uinput *uidev = NULL;

	dev = libevdev_new();
	if (dev == NULL)
		goto errorend;

	libevdev_set_name(dev, "automotive devices");
	libevdev_set_id_bustype(dev, BUS_HOST);
	libevdev_enable_event_type(dev, EV_KEY);
	for (int i=0; i < (sizeof(enabling_key_table)/sizeof(struct s_enabling_key_table)); i++) {
		libevdev_enable_event_code(dev, enabling_key_table[i].type, enabling_key_table[i].code, NULL);
	}

	err = libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &uidev);
	if (err != 0)
		goto errorend;
	
	for(int i=0;i<100;i++)
	{
		unsigned int type = enabling_key_table[3].type;
		unsigned int code = enabling_key_table[3].code;

		sleep(1);
		
		fprintf(stderr,"writekey : type=%x  code =%04x\n", type, code);

		err = libevdev_uinput_write_event(uidev, type, code, i%2);
		if (err != 0)
			fprintf(stderr,"error write\n");
		err = libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
		if (err != 0)
			fprintf(stderr,"error write\n");
	}

	libevdev_uinput_destroy(uidev);
	libevdev_free(dev);
	
	return 0;
	
errorend:
	if (uidev != NULL)
		libevdev_uinput_destroy(uidev);

	if (dev != NULL)
		libevdev_free(dev);

	return -1;
}


