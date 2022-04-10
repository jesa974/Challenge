struct tcp_flow* gather_flows(char** file_content, int* nb_packet); // Separate the TCP flows
struct counter* count_len(struct tcp_flow* flows, int nb_flow); // Count the length of each TCP flow
void sort_by_len(struct counter* total, int nb_flow, char* mode); // Sort the TCP flows by length

struct counter {
    int index;
    int length;
};