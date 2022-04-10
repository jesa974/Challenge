#include <stdio.h>
#include <stdlib.h>
#include "../include/chaine.h"
#include "../include/file.h"
#include "../include/manage.h"
#include "../include/tcp_packet.h"

int main(void)
{
	int max = 0;

	char** files = list_files();

	char* file_name = (char*)malloc(sizeof(char) * number_of_files(files) + 1);

	file_name = ask_file(files);

	char** file_content = import_file(file_name, &max);

	// Check the content of the file
	if (file_content == NULL)
	{
		printf("Error while importing the file\n");
		return 1;
	} else if (max == 0)
	{
		printf("The file is empty\n");
		return 1;
	} else
	{
		struct tcp_flow* flow_array = (struct tcp_flow*)malloc(sizeof(struct tcp_flow) * max);

		flow_array = gather_flows(file_content, &max);

		for (int i = 0; i < max; i++) {
			printf("%s:%d -> %s:%d\n", flow_array[i].src_ip, flow_array[i].src_port, flow_array[i].dst_ip, flow_array[i].dst_port);
			printf("NB: %d\n", flow_array[i].nb_packet);
			for (int j = 0; j < flow_array[i].nb_packet; j++) {
				printf("Seq %d : %d\n", j, flow_array[i].seq[j]);
			}
		}

		printf("NB flow: %d\n", max);

		struct counter* length_array = (struct counter*)malloc(sizeof(struct counter) * max);
		
		length_array = count_len(flow_array, max);

		printf("Classic sort\n");
		for (int i = 0; i < max; i++) {
			printf("%s:%d -> %s:%d = %d\n", flow_array[length_array[i].index].src_ip, flow_array[length_array[i].index].src_port, flow_array[length_array[i].index].dst_ip, flow_array[length_array[i].index].dst_port, length_array[i].length);
		}
		printf("\n\n\n");

		printf("ASC sort\n");
		sort_by_len(length_array, max, "asc");

		for (int i = 0; i < max; i++) {
			printf("%s:%d -> %s:%d = %d\n", flow_array[length_array[i].index].src_ip, flow_array[length_array[i].index].src_port, flow_array[length_array[i].index].dst_ip, flow_array[length_array[i].index].dst_port, length_array[i].length);
		}
		printf("\n\n\n");

		printf("DESC sort\n");
		sort_by_len(length_array, max, "desc");

		for (int i = 0; i < max; i++) {
			printf("%s:%d -> %s:%d = %d\n", flow_array[length_array[i].index].src_ip, flow_array[length_array[i].index].src_port, flow_array[length_array[i].index].dst_ip, flow_array[length_array[i].index].dst_port, length_array[i].length);
		}
	}
	
	return 0;
}
