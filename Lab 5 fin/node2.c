#include <stdio.h>

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table 
{
  int costs[4][4];
} dt2;


/* students to write the following two routines, and maybe some others */
float clocktime;

/*
int min(int a, int b, int c) {
    int smallest = a;
    if (b < smallest) {
        smallest = b;
    }
    if (c < smallest) {
        smallest = c;
    }
    return smallest;
}*/

void rtinit2() 
{
  printf("In rtinit2();");
  struct rtpkt pkt;
  for(int i = 0; i < 4; i++)
  {
    //default
    pkt.mincost[i] = 999;
  }

  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
        //high value of infinite to start
        dt2.costs[i][j] = 999;
    }
  }
  //initials
  dt2.costs[0][0] = 3;
	dt2.costs[0][2] = 3;
	dt2.costs[1][1] = 1;
	dt2.costs[1][2] = 1;
	dt2.costs[2][2] = 0;
	dt2.costs[3][2] = 2;
	dt2.costs[3][3] = 2;

for(int i = 0; i < 4; i++)
{
  pkt.mincost[i] = dt2.costs[i][2];
}
pkt.sourceid = 2;
  pkt.destid = 0;
  tolayer2(pkt);
  pkt.destid = 1;
  tolayer2(pkt);
   pkt.destid = 3;
  tolayer2(pkt);
  //print info
  printf("sent from node 2 to neighbors 0,1,3 with cost: %d, %d, %d, %d \n", pkt.mincost[0], pkt.mincost[1], pkt.mincost[2], pkt.mincost[3]);
}


void rtupdate2(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  printf("rtupdate2 started at %f", clocktime);

  int s_id = rcvdpkt->sourceid;
  int dest = rcvdpkt->destid;
  int cost[4];
  for(int i = 0; i < 4; i++)
  {
    cost[i] = rcvdpkt->mincost;
  }

  int flip = 0;
  for(int i = 0; i < 4; i++)
  {
   if(dt2.costs[i][s_id] > dt2.costs[s_id][2] + rcvdpkt->mincost[i])
   {
      dt2.costs[i][s_id] = dt2.costs[s_id][2] + rcvdpkt->mincost[i];
      if(i != 0)
      {
        flip = 1;
      }
   }
  }

  //change in table
  if(flip == 1)
  {
    struct rtpkt pkt;
    for(int i = 1; i < 4; i++)
    {
      pkt.mincost[i] = min(dt2.costs[i][0], dt2.costs[i][1], dt2.costs[i][3]);
    }
    printf(" distance table for node 0 changed");
    printdt0(&dt2);
    pkt.sourceid = 2;
    pkt.destid = 0;
    tolayer2(pkt);
    pkt.destid = 1;
    tolayer2(pkt);
    pkt.destid = 3;
    tolayer2(pkt);
    //print info
    printf("sent from node 2 to neighbors 0,1,3 with cost: %d, %d, %d, %d \n", pkt.mincost[0], pkt.mincost[1], pkt.mincost[2], pkt.mincost[3]);
  }

}


printdt2(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}







