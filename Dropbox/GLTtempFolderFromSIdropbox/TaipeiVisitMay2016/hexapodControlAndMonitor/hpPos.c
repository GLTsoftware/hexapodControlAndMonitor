/* Set Absolute Position command */
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <zmq.h>
/*
#include "HPData.h"
#include "HPCommands.h"
*/

#include "hpParameters.h"

short checkSum (char *buff, int size);

int main(int argc, char *argv[]) {
  int msgLength = 512; 
  int lengthSendMsg;
  char recvBuffer[msgLength];
  char sendBuffer[msgLength];
  char sentCmdCode[10];
  int timestamp,exitCode;

/*
  HPStatus HPStatusResp;
  HPCmd HPCommand;
  HPXYZCmd HPXYZCommand;
*/

  char PMAChost[40];

  float cmdXum,cmdYum,cmdZum,cmdTipArcsec,cmdTiltArcsec,cmdSpinArcsec;
  void *context = zmq_ctx_new ();
  void *requester = zmq_socket (context, ZMQ_REQ);

  /* check validity of requested positions */
 
  if(argc!=8) {
  printf("Usage: setAbsPos <x micron> <y micron> <z micron> <tip arcsec>\n");
  printf("              <tilt arcsec> <spin arcsec> \n");
  printf("E.g.: setAbsPos 1000.0 2000. 2200. 0.0 0.0 0.0\n");
  exit(0);
  }

  sprintf(PMAChost,"tcp://%s:%d",PMAC_HOST_IP,PMAC_HOST_PORT);

  cmdXum = atof(argv[2]);
  cmdYum = atof(argv[3]);
  cmdZum = atof(argv[4]);
  cmdTipArcsec = atof(argv[5]);
  cmdTiltArcsec = atof(argv[6]);
  cmdSpinArcsec = atof(argv[7]);

  if((cmdXum<XNEGLIM)||(cmdXum>XPOSLIM)) {
  printf("Invalid commanded X; should be between XNEGLIM and XPOSLIM.\n");
  exit(0);
  }
  if((cmdYum<YNEGLIM)||(cmdYum>YPOSLIM)) {
  printf("Invalid commanded Y; should be between YNEGLIM and YPOSLIM.\n");
  exit(0);
  }
  if((cmdZum<ZNEGLIM)||(cmdZum>ZPOSLIM)) {
  printf("Invalid commanded Z; should be between ZNEGLIM and ZPOSLIM.\n");
  exit(0);
  }
  if((cmdTipArcsec<TIPNEGLIM)||(cmdTipArcsec>TIPPOSLIM)) {
  printf("Invalid commanded Tip; should be between TIPNEGLIM and TIPOSLIM.\n");
  exit(0);
  }
  if((cmdTiltArcsec<TILTNEGLIM)||(cmdTiltArcsec>TILTPOSLIM)) {
  printf("Invalid commanded Tip; should be between TIPNEGLIM and TIPOSLIM.\n");
  exit(0);
  }
  if(cmdSpinArcsec!=0.0) {
  printf("Invalid commanded Spin should be 0.0\n");
  exit(0);
  }
 
  sprintf(sendBuffer,"m %+f %+f %+f %+f %+f %+f",
           cmdXum,cmdYum,cmdZum,cmdTipArcsec,cmdTiltArcsec,cmdSpinArcsec);

  zmq_connect (requester, PMAChost);
  lengthSendMsg=strlen(sendBuffer);
  zmq_send(requester,sendBuffer,lengthSendMsg,0);
  zmq_recv (requester, recvBuffer, msgLength, 0);
  printf("PMAC response: %s\n",recvBuffer);
  sscanf(recvBuffer,"%s %d %d",sentCmdCode,&timestamp,&exitCode);
  switch (exitCode) {
       case 0:
       printf("Command parsed OK\n");
       break;
   
       case -1:
       printf("System error. Fix error before issuing another command.\n");
       break;
 
       case -2:
       printf("Command cannot be sent in the actual status\n");
       break;

       case -3: 
       printf("Target position outside boundaries\n");
       break;

       case -4:
       printf("Chopping target position outside boundaries\n");
       break;

       case -5:
       printf("Chopping target frequency too high\n");
       break;

       case -6:
       printf("Command not recognized\n");
       break;
  }
  zmq_close(requester);
  zmq_ctx_destroy(context);
  return 0;
}
