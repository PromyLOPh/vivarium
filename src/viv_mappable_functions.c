#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <wayland-server-core.h>
#include <wlr/util/log.h>

#include "viv_mappable_functions.h"

#include "viv_types.h"
#include "viv_workspace.h"

void viv_mappable_do_exec(struct viv_workspace *workspace, union viv_mappable_payload payload) {
    printf("Executing %s\n", payload.do_exec.executable);

    pid_t p;
    if ((p = fork()) == 0) {
        setsid();
        freopen("/dev/null", "w", stdout);
        freopen("/dev/null", "w", stderr);
        execvp(payload.do_exec.executable, payload.do_exec.args);
        _exit(EXIT_FAILURE);
    }
}

void viv_mappable_increment_divide(struct viv_workspace *workspace, union viv_mappable_payload payload) {
    viv_workspace_increment_divide(workspace, payload.increment_divide.increment);
}

void viv_mappable_terminate(struct viv_workspace *workspace, union viv_mappable_payload payload) {
    wl_display_terminate(workspace->output->server->wl_display);
}

void viv_mappable_swap_out(struct viv_workspace *workspace, union viv_mappable_payload payload) {
    printf("Attempting swap-out\n");
    viv_workspace_swap_out(workspace->output, &workspace->output->server->workspaces);
}

void viv_mappable_next_window(struct viv_workspace *workspace, union viv_mappable_payload payload) {
    wlr_log(WLR_DEBUG, "Mappable next_window");
}

void viv_mappable_prev_window(struct viv_workspace *workspace, union viv_mappable_payload payload) {
}

void viv_mappable_tile_window(struct viv_workspace *workspace, union viv_mappable_payload payload) {
}