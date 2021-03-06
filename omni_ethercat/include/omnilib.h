/*
 * This file is part of the libomnidrive project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 *                    Ingo Kresse <kresse@in.tum.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef OMNIDRIVE_H 
#define OMNIDRIVE_H 

#define NUM_DRIVES_ 5
#define TORSO_DRIVE_SEQ 4 // Drives 0-3 are the wheels, 4 is the torso

typedef struct {
  int slave_state[NUM_DRIVES_];
  int slave_online[NUM_DRIVES_];
  int slave_operational[NUM_DRIVES_];
  int master_link;
  int master_al_states;
  int master_slaves_responding;
  int working_counter;
  int working_counter_state;
} commstatus_t;

int omnidrive_init(void);
int omnidrive_drive(double x, double y, double a, double torso_vel);
void omnidrive_set_correction(double drift);
int omnidrive_odometry(double *x, double *y, double *a, double *torso_pos);
int omnidrive_shutdown(void);

void omnidrive_status(char *drive0, char *drive1, char *drive2, char *drive3, char *drive4, int *estop); //added torso

commstatus_t omnidrive_commstatus();

void omnidrive_poweron();
void omnidrive_poweroff();
void omnidrive_recover();

//void omnidrive_get_motor_currents(double *currents);

#endif  // OMNIDRIVE_H
