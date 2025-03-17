//
// Created by avilay on 11/14/24.
//
#pragma once
#include <netdb.h>

char* stringify_ai_protocol(const int proto);
char* stringify_ai_socktype(const int socktype);
char* stringify_ai_family(const int family);
char* stringify_ai_flags(const int flags);
char* stringify_ai_addr(const struct sockaddr* addr);
char* stringify_addrinfo(const struct addrinfo* res);
