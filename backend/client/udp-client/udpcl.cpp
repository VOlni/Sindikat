#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <map>
#include <unistd.h>
#include <stdint.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>


#define BUF_SIZE 512
#define SRV_ADDR "127.0.0.1"
#define SRV_PORT "9022"

#define DATAGR_SIZE 9

int main(){

  int sfd, s;
  char buf[BUF_SIZE];
  memset(&buf, 0, BUF_SIZE);
  ssize_t nread;
  //socklen_t peer_addrlen;
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  //struct sockaddr_in peer_addr;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = 0;
  hints.ai_protocol = IPPROTO_IP;
  
  s = getaddrinfo(SRV_ADDR, SRV_PORT, &hints, &result);
  if (s != 0) {
    printf("error.\n");
    return 500;
  }
  
  for (rp = result; rp != nullptr; rp = rp->ai_next){
    sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sfd == -1)
      continue;

    if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
      break;
    close(sfd);
  }
  freeaddrinfo(result);
  
  if (rp == nullptr) {
    printf("no connection\n");
    return 0;
  } else {
    printf("some connection\n");
    FILE *drachtlogfd;
    drachtlogfd = fopen("/var/log/drachtio/drachtio.log", "r");
    fseek(drachtlogfd, 0L, SEEK_SET);
    int8_t * buf;
    buf = (int8_t *) malloc(BUF_SIZE);
    memset(buf, 0, BUF_SIZE);
    nread = fread(buf, 1, (size_t) BUF_SIZE, drachtlogfd);
    printf("%s\n", buf);
  }
  
  /*
                                        
                  0      7 8     15 16    23 24    31  
                 +--------+--------+--------+--------+ 
                 |     Source      |   Destination   | 
                 |      Port       |      Port       | 
                 +--------+--------+--------+--------+ 
                 |                 |                 | 
                 |     Length      |    Checksum     | 
                 +--------+--------+--------+--------+ 
                 |                                     
                 |          data octets ...            
                 +---------------- ...                 

                      User Datagram Header Format

  */
  std::string request;
  request.append("abcdef");
  
  if((write(sfd, "abcdef", request.length())) != (ssize_t) request.length()){
    printf("bad write");
  }
  
  nread = read(sfd, buf, DATAGR_SIZE);
  if (nread == -1) {
    //perror("read");
  } else {
    std::string response;
    response.append(buf);
    printf("%s\n", response.c_str());

  }
  
  return 0;
}
