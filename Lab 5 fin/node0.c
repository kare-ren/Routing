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
} dt0;


/* students to write the following two routines, and maybe some others */
float clocktime;

int min(int a, int b, int c) {
    int smallest = a;
    if (b < smallest) {
        smallest = b;
    }
    if (c < smallest) {
        smallest = c;
    }
    return smallest;
}

void rtinit0() 
{
  struct rtpkt pkt;
  printf("In rtinit0();");
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
        dt0.costs[i][j] = 999;
    }
  }
  //initials
  dt0.costs[0][0] = 0;
	dt0.costs[1][0] = 1;
	dt0.costs[1][1] = 1;
	dt0.costs[2][0] = 3;
	dt0.costs[2][2] = 3;
	dt0.costs[3][0] = 7;
	dt0.costs[3][3] = 7;
  
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      pkt.mincost[i] = dt0.costs[i][0];
    }
  }
  //send to neighbors
  pkt.sourceid = 0;
  pkt.destid = 1;
  tolayer2(pkt);
  pkt.destid = 2;
  tolayer2(pkt);
  pkt.destid = 3;
  tolayer2(pkt);
  //print info
  printf("sent from node 0 to neighbors 1,2,3 with cost: %d, %d, %d, %d \n", pkt.mincost[0], pkt.mincost[1], pkt.mincost[2], pkt.mincost[3]);
  printdt0(&dt0);
  

}


void rtupdate0(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  printf("rtupdate0 started at %f", clocktime);
  //get struct vars
  int s_id = rcvdpkt->sourceid;
  int dest = rcvdpkt->destid;
  int cost[4];
  for(int i = 0; i < 4; i++)
  {
    cost[i] = rcvdpkt->mincost;
  }

  int flip = 0;
  //distance table comparison
  for(int i = 0; i < 4; i++)
  {
   if(dt0.costs[i][s_id] > dt0.costs[s_id][0] + rcvdpkt->mincost[i])
   {
      dt0.costs[i][s_id] = dt0.costs[s_id][0] + rcvdpkt->mincost[i];
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
      pkt.mincost[i] = min(dt0.costs[i][1], dt0.costs[i][2], dt0.costs[i][3]);
    }
    printf(" distance table for node 0");
    printdt0(&dt0);
    pkt.sourceid = 0;
    pkt.destid = 1;
    tolayer2(pkt);
    pkt.destid = 2;
    tolayer2(pkt);
    pkt.destid = 3;
    tolayer2(pkt);
   //print info
   printf("sent from node 0 to neighbors 0,1,2,3 with cost: %d, %d, %d, %d \n", pkt.mincost[0], pkt.mincost[1], pkt.mincost[2], pkt.mincost[3]);
  }
 


}


printdt0(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

linkhandler0(linkid, newcost)   
  int linkid, newcost;

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}

