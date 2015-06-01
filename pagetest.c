#include "types.h"
#include "stat.h"
#include "user.h"


int rec() {
  printf(1,".");
  rec();
  return 0;
}

int
main(int argc, char *argv[])
{
  
  int npages = 10000;
  int i;
  int fork_res = fork();
  
  if (fork_res)
    wait(); //wait for child to finish run
  
  printf(1,"fork:%d\t allocating %d pages\n", fork_res, npages);
  char * p = malloc(npages * 4096);
  printf(1,"fork:%d\t allocated %d pages at: 0x%p\n", fork_res, npages, p);

  printf(1,"fork:%d\t start writing to few pages\n", fork_res);
  for(i = 0; i < 10; i++)
    *(p+i*100000) = 1;
  
  printf(1,"fork:%d\t malloc until reached to kernel\n", fork_res);
  while(malloc(4096 * 4096) > 0);
  printf(1,"fork:%d\t reached kernel\n", fork_res);
      
  printf(1,"fork:%d\t try to stack overflow\n", fork_res);
  rec();
  
  exit();
}
