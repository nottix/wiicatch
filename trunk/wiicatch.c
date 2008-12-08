#include <stdio.h>
#include <cwiid.h>
#include <unistd.h>
#include <stdlib.h>

#include <libnotify/notify.h>
#include <libnotify/notification.h>

#define WIIMOTE_ADDR	"00:19:1D:B7:0E:2F"

#define POLLING 200000

#define AMIXER		"amixer"
#define VOL_UP_BUT	2048
#define VOL_DOWN_BUT	1024
#define VOL_UP		1
#define VOL_DOWN	2

void show_mesg(char *mesg) {
	notify_init("wiimote");
	NotifyNotification* notf = notify_notification_new("Volume", mesg, NULL, NULL);
	//notify_notification_set_timeout(notf, 1500);
	notify_notification_show(notf, NULL);
}

void run_event(int type) {
	int pid=fork();
	if(pid==0) {
		if(type==VOL_UP) {
			if(execl("/usr/bin/amixer", "amixer", "-q", "-c", "0", "sset", "Master", "10+", (char*)0)<0)
				perror("Err\n");
			show_mesg("+10");
		}
		else if(type==VOL_DOWN) {
			if(execl("/usr/bin/amixer", "amixer", "-q", "-c", "0", "sset", "Master", "10-", (char*)0)<0)
				perror("Err\n");
			show_mesg("-10");
		}
		exit(0);
	}
}

int main(int argc, char **argv) {
	
	printf("Connecting to %s\n", WIIMOTE_ADDR);
	
	cwiid_wiimote_t *wiimote = cwiid_connect(BDADDR_ANY, 0);
	if(wiimote==NULL) {
		printf("Error while connecting\n");
		return -1;
	}
	printf("Connected to %s\n", WIIMOTE_ADDR);

	if(cwiid_command(wiimote, CWIID_CMD_RPT_MODE, CWIID_RPT_STATUS | CWIID_RPT_BTN)!=0) {
		printf("Error while setting command\n");
		return -2;
	}

	struct cwiid_state *state = (struct cwiid_state*)malloc(sizeof(struct cwiid_state));
	if(cwiid_get_state(wiimote, state)!=0) {
		printf("Error while retrieving state\n");
		return -2;
	}

	
	while(state->buttons!=128) {
		usleep(POLLING);
		if(cwiid_get_state(wiimote, state)!=0) {
			printf("Error while retrieving state\n");
			return -2;
		}
		printf("Buttons state: %d\n", (int)state->buttons);
		printf("Battery state: %d\n", (int)state->battery);
		printf("Led state: %d\n", (int)state->led);
		printf("Rumble state: %d\n", (int)state->rumble);
		if(state->buttons==VOL_UP_BUT) {
			printf("Executing %s\n", AMIXER);
			run_event(VOL_UP);
		}
		else if(state->buttons==VOL_DOWN_BUT) {
			printf("Executing %s\n", AMIXER);
			run_event(VOL_DOWN);
		}

	}

	cwiid_disconnect(wiimote);
	printf("Wiimote %s disconnected\n", WIIMOTE_ADDR);
	return 0;
}
