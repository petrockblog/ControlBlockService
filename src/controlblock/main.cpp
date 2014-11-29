#include <stdio.h>
#include <chrono>
#include <thread>
#include <signal.h>

#include "ControlBlock.h"
#include "PowerSwitch.h"

static volatile sig_atomic_t doRun = 1;

extern "C" {
	void sig_handler(int signo) {
		// int16_t ctr = 0;

		if ((signo == SIGINT) | (signo == SIGQUIT) | (signo == SIGABRT) | (signo =
				SIGTERM)) {
			printf("[ControlBlockService] Releasing input devices.\n");
			// pollButton = 0;
			// pollPads = 0;
			// uinput_kbd_close(&uinp_kbd);
			// for (ctr = 0; ctr < GPADSNUM; ctr++) {
			// 	uinput_gpad_close(&uinp_gpads[ctr]);
			// }
		    // cfg_free(cfg);
		    // free(confres.gamepad1_type);
		    // free(confres.gamepad2_type);

			doRun = 0;
		}
	}
}

void register_signalhandlers() {
	/* Register signal handlers  */
	if (signal(SIGINT, sig_handler) == SIG_ERR )
		printf("\n[ControlBlockService] Cannot catch SIGINT\n");
	if (signal(SIGQUIT, sig_handler) == SIG_ERR )
		printf("\n[ControlBlockService] Cannot catch SIGQUIT\n");
	if (signal(SIGABRT, sig_handler) == SIG_ERR )
		printf("\n[ControlBlockService] Cannot catch SIGABRT\n");
	if (signal(SIGTERM, sig_handler) == SIG_ERR )
		printf("\n[ControlBlockService] Cannot catch SIGTERM\n");
}

int main(int argc, char **argv)
{
	register_signalhandlers();

	ControlBlock controlBlock = ControlBlock();

	while (doRun) {
		controlBlock.update();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}
