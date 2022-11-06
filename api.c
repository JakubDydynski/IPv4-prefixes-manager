#include "api.h"
extern ip_prefix_node_t ip_prefix_node;
extern ip_prefix_list_t ip_prefix_list;

static ip_prefix_node_t *check_if_prefix_exist(unsigned int base, char mask);
static ip_prefix_node_t *check_if_prefix_exist_to_del(unsigned int base, char mask);
static void *check_malloc(void *wsk);

int add(unsigned int base, char mask)
{
  if (sizeof(base) != sizeof(unsigned int) && sizeof(mask) != sizeof(char))
    return -1;

  if (ip_prefix_node.ip.mask == NO_PREFIXES)
  {
    ip_prefix_node.ip.mask = mask;
    ip_prefix_node.ip.base = base;
    ip_prefix_list.head = &ip_prefix_node;
    ip_prefix_list.num_of_el++;
    return 0;
  }

  ip_prefix_node_t *result = check_if_prefix_exist(base, mask);
  if (result != NULL)
    return -1;

  ip_prefix_list.head->next = check_malloc(malloc(sizeof(ip_prefix_node_t)));
  ip_prefix_list.head->next->ip.base = base;
  ip_prefix_list.head->next->ip.mask = mask;
  ip_prefix_list.head->next->next = NULL;
  ip_prefix_list.head = (ip_prefix_list.head)->next;
  ip_prefix_list.num_of_el++;

  return 0;
}

int del(unsigned int base, char mask)
{
  if (sizeof(base) != sizeof(unsigned int) && sizeof(mask) != sizeof(char))
    return -1;

  ip_prefix_node_t *previous = check_if_prefix_exist_to_del(base, mask);
  if (previous == NULL)
    return -1;

  ip_prefix_list.num_of_el--;

  ip_prefix_node_t *to_del = previous->next;
  previous->next = (previous->next)->next;

  ip_prefix_list.head = previous;

  free(to_del);
  return 0;
}

char check(unsigned int ip)
{
  ip_prefix_node_t *prefix_iterator = &ip_prefix_node;
  char highest_mask;

  while (prefix_iterator != NULL)
  {
    if ((prefix_iterator->ip.base >> (32 - prefix_iterator->ip.mask)) == (ip >> (32 - prefix_iterator->ip.mask))) // check if bases are the same
    {
      if (ip - prefix_iterator->ip.base < (32 - prefix_iterator->ip.mask) * (32 - prefix_iterator->ip.mask))
      {
        highest_mask = prefix_iterator->ip.mask;
      }
      else
      {
        return -1;
      }
    }
    else
    {
      return -1;
    }

    prefix_iterator = prefix_iterator->next;
  }
  return highest_mask;
}

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

static ip_prefix_node_t *check_if_prefix_exist(unsigned int base, char mask)
{
  ip_prefix_node_t *prefix_iterator = &ip_prefix_node;
  while (prefix_iterator != NULL)
  {
    if (base == prefix_iterator->ip.base && mask == prefix_iterator->ip.mask)
      return prefix_iterator;

    prefix_iterator = prefix_iterator->next;
  }
  return NULL;
}

static ip_prefix_node_t *check_if_prefix_exist_to_del(unsigned int base, char mask)
{
  if (base == ip_prefix_node.ip.base && mask == ip_prefix_node.ip.mask)
    return &ip_prefix_node;

  ip_prefix_node_t *prefix_iterator = &ip_prefix_node;
  do
  {
    ip_prefix_node_t *to_ret = prefix_iterator;
    prefix_iterator = prefix_iterator->next;
    if (prefix_iterator == NULL)
      return NULL;
    if (base == prefix_iterator->ip.base && mask == prefix_iterator->ip.mask)
      return to_ret;

  } while (prefix_iterator != NULL);
  return NULL;
}

static void *check_malloc(void *wsk)
{
  if (!wsk)
  {
    fputs("Lack of memory\n", stderr);
    exit(EXIT_FAILURE);
  }

  return wsk;
}