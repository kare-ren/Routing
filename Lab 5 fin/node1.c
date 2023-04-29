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

int connectcosts1[4] = { 1,  0,  1, 999 };

struct distance_table 
{
  int costs[4][4];
} dt1;


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

rtinit1() 
{
  struct rtpkt pkt;
  printf("In rtinit1();");
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
        dt1.costs[i][j] = 999;
    }
  }
  //initials
  dt1.costs[0][0] = 1;
	dt1.costs[0][1] = 1;
	dt1.costs[1][1] = 0;
	dt1.costs[2][1] = 1;
	dt1.costs[2][2] = 1;

for(int i = 0; i < 4; i++)
{
  pkt.mincost[i] = dt1.costs[i][1];
}
pkt.sourceid = 1;
  pkt.destid = 0;
  tolayer2(pkt);
  pkt.destid = 2;
  tolayer2(pkt);
  //print info
  printf("sent from node 1 to neighbors 0,2 with cost: %d, %d, %d, %d \n", pkt.mincost[0], pkt.mincost[1], pkt.mincost[2], pkt.mincost[3]);
}


rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  printf("rtupdate1 started at %f", clocktime);
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
   if(dt1.costs[i][s_id] > dt1.costs[s_id][1] + rcvdpkt->mincost[i])
   {
      dt1.costs[i][s_id] = dt1.costs[s_id][1] + rcvdpkt->mincost[i];
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
      pkt.mincost[i] = min(dt1.costs[i][0], dt1.costs[i][2], dt1.costs[i][3]);
    }
    printf(" distance table for node 0 changed");
    printdt0(&dt1);
    pkt.sourceid = 1;
    pkt.destid = 0;
    tolayer2(pkt);
    pkt.destid = 2;
    tolayer2(pkt);
   //print info
   printf("sent from node 0 to neighbors with cost: %d, %d, %d, %d \n", pkt.mincost[0], pkt.mincost[1], pkt.mincost[2], pkt.mincost[3]);
  }
}


printdt1(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



linkhandler1(linkid, newcost)   
int linkid, newcost;   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}


