#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netdb.h>
#include <signal.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLINE 4096
#define BUFSIZE 1500

typedef struct rec {
  u_short seq;
} Rec;

typedef struct timeval Timeval;
typedef struct sockaddr Sockaddr;

int max_ttl;
int datalen;

Sockaddr *sasend;
Sockaddr *sarecv;
Sockaddr *salast;
Sockaddr *sabind;

socklen_t salen;

typedef	void Sigfunc (int);

#define max(a,b) ((a) > (b) ? (a) : (b))

void sig_alrm (int signo);
int process_ip (struct ip *ip, int len);
int recv_dgram ();
void sub_tv (Timeval *plus, Timeval *minus, Timeval *res);
double time_to_double (Timeval *time);
void print_report ();
void send_dgram (int ttl);
int send_probes (int ttl);
void loop_ttl ();

void err_sys (char *fmt, ...);
void Write (int fd, void *ptr, size_t nbytes);
void Gettimeofday (struct timeval *tv, void *foo);
ssize_t Read (int fd, void *ptr, size_t nbytes);
int sock_cmp_addr (const struct sockaddr *sa1,
    const struct sockaddr *sa2, socklen_t salen);
char *Sock_ntop_host (const struct sockaddr *sa, socklen_t salen);
void sock_set_port (struct sockaddr *sa, socklen_t salen, int port);
void Setsockopt (int fd, int level, int optname, const void *optval,
    socklen_t optlen);
void Pipe (int *fds);
void Bind (int fd, const struct sockaddr *sa, socklen_t salen);
Sigfunc *Signal (int signo, Sigfunc *func);
