
#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <bits/types/struct_timeval.h>
# include <stddef.h>
# include <stdint.h>
# include <sysexits.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <float.h>

# include <signal.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/ioctl.h>

# include <net/if.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <errno.h>
# include <error.h>
# include <ifaddrs.h>

//# include "libft_extended/libft.h"
//
typedef enum e_error_code {
    _ERC_STD,
    _ERC_GAI,
}   e_errcode;

typedef struct  s_recv_buff {
    struct msghdr       header;
    char                *buffer;
    size_t              buffer_size;
    struct iovec        iov[1];
}               t_recv_buff;

typedef struct  s_host {
    char                *addr_orig;
    struct addrinfo     *addr_info;
    char                addr_str[INET_ADDRSTRLEN];
}               t_host;

typedef struct s_session {
    size_t          hops_max;
    size_t          probes_nb;
    int             sockfd;
    struct addrinfo sockinfo;
    struct iphdr    header;
}   t_sum;

typedef struct s_packet_param {
    size_t          ttl;
    struct timeval  time_begin;
    char            *data;
}   t_packet;


#endif //////////////////////////////////////////////////////////////// FT_TRACEROUTE_H
