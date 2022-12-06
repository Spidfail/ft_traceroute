#include "ft_traceroute.h"

void    error_handle(char *input, int8_t ec, e_errcode type) {
    if (type == _ERC_GAI) {
        fprintf(stderr, "traceroute: %s: %s\n", input, gai_strerror(ec));
    }
    else {
        fprintf(stderr, "traceroute: %s: %s\n", input, strerror(errno));
    }
    exit(ec);
}

void    set_socket_informations(struct addrinfo *sockinfo, int protocol, bool v6, int flags) {
    sockinfo->ai_protocol = protocol;
    sockinfo->ai_family = v6 ? AF_INET6 : AF_INET;
    sockinfo->ai_flags = flags;
    // The first one is the default one.
    if (protocol == IPPROTO_UDP)
        sockinfo->ai_socktype = SOCK_DGRAM;
    else if (protocol == IPPROTO_TCP)
        sockinfo->ai_socktype = SOCK_STREAM;
    else if (protocol == IPPROTO_ICMP)
        sockinfo->ai_socktype = SOCK_DGRAM;
}

void     host_lookup(const struct addrinfo *sockinfo, t_host *host, char *raw_addr) {
    uint8_t     rtn_gai = 0;
    
    host->addr_orig = raw_addr;
    rtn_gai = getaddrinfo(raw_addr, NULL, sockinfo, &host->addr_info);
    if (rtn_gai != EXIT_SUCCESS)
        error_handle(raw_addr, rtn_gai, _ERC_GAI);
    // Transform the recovered internet address to a 'human readable' string form.
    inet_ntop(sockinfo->ai_family,
        &((struct sockaddr_in *)host->addr_info->ai_addr)->sin_addr,
        host->addr_str,
        INET_ADDRSTRLEN);
}

void    set_header_base(struct iphdr *dst, const struct addrinfo *info) {
    (void) dst;
    (void) info;
    // TODO
    // Header params -> 
}

void    init_socket(int *sockfd, const struct addrinfo *info) {
    *sockfd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (*sockfd == -1)
        error_handle("Failed to open socket.", errno, _ERC_STD);
    // TODO for TTL and Options
    // else if (init_socket_options() != EXIT_SUCCESS)
    //     error_handle("Failed to open socket [AF_INET, SOCK_RAW, IPPROTO_ICMP]", errno, _ERC_STD);
}

int     main(int ac, char *av[]) {
    t_sum   session = {0};
    t_host  destination = {0};
    
    if (ac < 2)
        return -1;
   
    // TODO BONUS
    // UDP, ipv4 and cannonical for now.int flags
    set_socket_informations(&session.sockinfo, IPPROTO_UDP, false, AI_CANONNAME);
    host_lookup(&session.sockinfo, &destination, av[1]);
    init_socket(&session.sockfd, &session.sockinfo);
    fprintf(stderr, "Sockfd = %i, address = %s\n", session.sockfd, destination.addr_str);
}