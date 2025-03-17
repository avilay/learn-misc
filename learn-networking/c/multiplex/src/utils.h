//
// Created by avilay on 11/15/24.
//

#pragma once

#include <netdb.h>


#define iferr_continue(status, msg_prefix) if (status == -1) {perror(msg_prefix); continue;}

#define iferr_break(status, msg_prefix) if (status == -1) {perror(msg_prefix); break;}

void iferr_log(const int status, const char* msg_prefix, const char* msg);
void iferr_die(int status, const char* msg_prefix, const char* msg);
void print_connx_details(const struct sockaddr* addr, const char* msg);
