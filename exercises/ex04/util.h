#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define MAXLINE 4096

typedef struct sockaddr Sockaddr;

typedef	void Sigfunc (int);

void err_doit (int errnoflag, int level, char *fmt, va_list ap);
void err_sys (char *fmt, ...);
void err_quit (char *fmt, ...);
char *sock_ntop_host (const struct sockaddr *sa, socklen_t salen);
char *Sock_ntop_host (const struct sockaddr *sa, socklen_t salen);
void sock_set_port (struct sockaddr *sa, socklen_t salen, int port);
int sock_cmp_addr (const struct sockaddr *sa1,
    const struct sockaddr *sa2, socklen_t salen);
void tv_sub (struct timeval *out, struct timeval *in);
char *icmpcode_v4 (int code);
Sigfunc *signal (int signo, Sigfunc *func);
Sigfunc *Signal (int signo, Sigfunc *func);
void *Malloc (size_t size);
void *Calloc (size_t n, size_t size);
void Gettimeofday (struct timeval *tv, void *foo);
void Pipe (int *fds);
void Bind (int fd, const struct sockaddr *sa, socklen_t salen);
void Setsockopt (int fd, int level, int optname, const void *optval,
    socklen_t optlen);
struct addrinfo * host_serv (char *host, char *serv, int family,
    int socktype);
struct addrinfo * Host_serv (const char *host, const char *serv,
    int family, int socktype);
ssize_t Read (int fd, void *ptr, size_t nbytes);
void Write (int fd, void *ptr, size_t nbytes);
ssize_t Recvfrom (int fd, void *ptr, size_t nbytes, int flags,
    struct sockaddr *sa, socklen_t *salenptr);
