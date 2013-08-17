/*
 * api.c
 *
 * Copyright (C) 2012, 2013 James Booth <boothj5@gmail.com>
 *
 * This file is part of Profanity.
 *
 * Profanity is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Profanity is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Profanity.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdlib.h>

#include <glib.h>

#include "plugins/callbacks.h"
#include "profanity.h"
#include "ui/notifier.h"
#include "ui/ui.h"

void
api_cons_alert(void)
{
    cons_alert();
}

void
api_cons_show(const char * const message)
{
    if (message != NULL) {
        cons_show("%s", message);
        ui_current_page_off();
        ui_refresh();
    }
}

void
api_register_command(const char *command_name, int min_args, int max_args,
    const char *usage, const char *short_help, const char *long_help, void *callback)
{
    PluginCommand *command = malloc(sizeof(PluginCommand));
    command->command_name = command_name;
    command->min_args = min_args;
    command->max_args = max_args;
    command->usage = usage;
    command->short_help = short_help;
    command->long_help = long_help;
    command->callback = callback;

    callbacks_add_command(command);
}

void
api_register_timed(void *callback, int interval_seconds)
{
    PluginTimedFunction *timed_function = malloc(sizeof(PluginTimedFunction));
    timed_function->callback = callback;
    timed_function->interval_seconds = interval_seconds;
    timed_function->timer = g_timer_new();

    callbacks_add_timed(timed_function);
}

void
api_notify(const char *message, const char *category, int timeout_ms)
{
    notify(message, timeout_ms, category);
}

void
api_send_line(char *line)
{
    prof_process_input(line);
}

char *
api_get_current_recipient(void)
{
    win_type_t win_type = ui_current_win_type();
    if (win_type == WIN_CHAT) {
        char *recipient = ui_current_recipient();
        return recipient;
    } else {
        return NULL;
    }
}
