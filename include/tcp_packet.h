struct tcp_flow {
    char* src_ip;
    char* dst_ip;
    int src_port;
    int dst_port;
    int* seq;
    int nb_packet;
};