#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct ip_prefix_t
{
  unsigned int base;
  char mask;
};

struct ip_prefix_node_t
{
  struct ip_prefix_t ip;
  struct ip_prefix_node_t *next;
};
struct ip_prefix_list_t
{
  struct ip_prefix_node_t *head;
  size_t num_of_el;
};

typedef struct ip_prefix_t ip_prefix_t;
typedef struct ip_prefix_node_t ip_prefix_node_t;
typedef struct ip_prefix_list_t ip_prefix_list_t;

enum
{
  NO_PREFIXES = -1
};

// API
int add(unsigned int base, char mask);
int del(unsigned int base, char mask);
char check(unsigned int ip);
