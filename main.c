#include "api.h"

ip_prefix_node_t ip_prefix_node = {{0, NO_PREFIXES}, NULL};
ip_prefix_list_t ip_prefix_list = {NULL, 0};

int main(void)
{

  int result = add(0x2040800, 20);
  printf("%d\n", result);
  printf("Number of nodes is  %ld\n", ip_prefix_list.num_of_el);

  result = add(0x2040800, 16);
  printf("%d\n", result);
  printf("Number of nodes is  %ld\n", ip_prefix_list.num_of_el);

  result = add(0x2040800, 15);
  printf("%d\n", result);
  printf("Number of nodes is  %ld\n", ip_prefix_list.num_of_el);

  result = del(0x2040800, 17);
  printf("%d\n", result);
  printf("Number of nodes is  %ld\n", ip_prefix_list.num_of_el);

  result = del(0x2040800, 16);
  printf("%d\n", result);
  printf("Number of nodes is  %ld\n", ip_prefix_list.num_of_el);

  result = del(0x2040800, 16);
  printf("%d\n", result);

  result = del(0x2040800, 15);
  printf("%d\n", result);
  return 0;
}
