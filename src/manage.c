#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tcp_packet.h"
#include "../include/chaine.h"

struct counter {
    int index;
    int length;
};

// Verify if the TCP flow is already registered
int is_in_array(char* ip_src, char* ip_dst, struct tcp_flow* array, int nb) {
    for (int i = 0; i < nb; i++) {
        if (strcmp(ip_src, array[i].src_ip) == 0 && strcmp(ip_dst, array[i].dst_ip) == 0)
        {
            return i;
        }
    }

    return -1;
}

// Separate the TCP flows
struct tcp_flow* gather_flows(char** file_content, int* nb_packet) {
    // Allocate memory for the array of flows
    struct tcp_flow* flows = NULL;
    flows = (struct tcp_flow*)malloc(sizeof(struct tcp_flow) * (*nb_packet));

    // Declare separator variables for the parser
    int nb = 0;
    char sep = ',';
    char new_sep = ':';
    
    // Declare the result array of the parser
    char **R = NULL;
    
    // Declare the temporary variables for the parser
    char* src = NULL;
    char* dst = NULL;
    char* ip_src = NULL;
    char* ip_dst = NULL;
    int src_port = 0;
    int dst_port = 0;
    int seq = 0;

    // Declare the counters
    int nb_flow = 0;
    
    for (int i = 0; i < (*nb_packet); i++) {
        // Allocate memory for the result array of the parser
        R = (char**)malloc(sizeof(char*) * (*nb_packet));

        // Parse the TCP packet
        fonct(file_content[i], &R, &nb, sep);

        // Get the source & the destination
        src = (char*)malloc(sizeof(char) * strlen(R[0]));
        dst = (char*)malloc(sizeof(char) * strlen(R[1]));
        strcpy(src, R[0]);
        strcpy(dst, R[1]);

        // Save the TCP sequence in the array
        seq = atoi(R[2]);

        // Parse the source IP & the source port
        fonct(src, &R, &nb, new_sep);

        // Get the source IP & the source port
        ip_src = (char*)malloc(sizeof(char) * strlen(R[0]));
        strcpy(ip_src, R[0]);
        src_port = atoi(R[1]);
        
        // Parse the destination IP & the destination port
        fonct(dst, &R, &nb, new_sep);

        // Get the destination IP & the destination port
        ip_dst = (char*)malloc(sizeof(char) * strlen(R[0]));
        strcpy(ip_dst, R[0]);
        dst_port = atoi(R[1]);
        
        // Check if the flow is already registered
        int index = is_in_array(ip_src, ip_dst, flows, nb_flow);

        // The flow is not registered
        if (index == -1)
        {
            // Set the number of packets
            flows[nb_flow].nb_packet = 0;

            // Save the source IP & the source port in the array
            flows[nb_flow].src_ip = (char*)malloc(sizeof(char) * strlen(ip_src));
            strcpy(flows[nb_flow].src_ip, ip_src);
            flows[nb_flow].src_port = src_port;

            // Save the destination IP & the destination port in the array
            flows[nb_flow].dst_ip = (char*)malloc(sizeof(char) * strlen(ip_dst));
            strcpy(flows[nb_flow].dst_ip, ip_dst);
            flows[nb_flow].dst_port = dst_port;

            // Save the sequence number in the array
            flows[nb_flow].seq = (int*)malloc(sizeof(int) * (*nb_packet));
            flows[nb_flow].seq[flows[nb_flow].nb_packet] = seq;

            // Increase the number of flow
            flows[nb_flow].nb_packet++;
            nb_flow++;
        } else // The flow is already registered
        {
            // Add the sequence number in the array
            flows[index].seq[flows[index].nb_packet] = seq;
            
            // Increase the number of packets
            flows[index].nb_packet++;
        }

        // Free memory
        free(R);
        R = NULL;
    }
    
    // Register the number of flows
    *nb_packet = nb_flow;

    return flows;
}

// Count the length of each TCP flow
struct counter* count_len(struct tcp_flow* flows, int nb_flow) {
    // Allocate memory for the array of counters
    struct counter* total = NULL;
    total = (struct counter*)malloc(sizeof(struct counter) * nb_flow);

    // Count the len of each TCP flow
    for (int i = 0; i < nb_flow; i++) {
        // Register the index of the TCP flow
        total[i].index = i;

        // Register the length of the TCP flow
        if (flows[i].nb_packet <= 1)
        {
            total[i].length = 0;
        } else
        {
            total[i].length = flows[i].seq[flows[i].nb_packet - 1] - flows[i].seq[0];
        }
    }

    return total;
}

// Sort the TCP flows by length
void sort_by_len(struct counter* total, int nb_flow, char* mode) {
    // Declare the temporary variables
    struct counter temp;

    if (strcmp(mode, "asc") == 0)
    {
        // Sort the TCP flows by length in ascending order
        for (int i = 0; i < nb_flow - 1; i++) {
            for (int j = 0; j < nb_flow - i - 1; j++) {
                if (total[j].length > total[j + 1].length)
                {
                    temp = total[j];
                    total[j] = total[j + 1];
                    total[j + 1] = temp;
                }
            }
        }
    } else if (strcmp(mode, "desc") == 0)
    {
        // Sort the TCP flows by length in descending order
        for (int i = 0; i < nb_flow - 1; i++) {
            for (int j = 0; j < nb_flow - i - 1; j++) {
                if (total[j].length < total[j + 1].length)
                {
                    temp = total[j];
                    total[j] = total[j + 1];
                    total[j + 1] = temp;
                }
            }
        }
    }
}
