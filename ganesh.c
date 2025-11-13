//2a
#include <stdio.h> 
#include <string.h> 
int main() { 
    char input[30], stuffed[80] = ""; 
    char start_delim, end_delim; 
    char temp[3], double_start[3], double_end[3]; 
    int i; 
    
    printf("Enter the data to be stuffed: "); 
    scanf("%s", input); 
    printf("Enter the starting delimiter character: "); 
    scanf(" %c", &start_delim); 
    printf("Enter the ending delimiter character: "); 
    scanf(" %c", &end_delim); 
    
    double_start[0] = double_start[1] = start_delim; 
    double_start[2] = '\0'; 
    double_end[0] = double_end[1] = end_delim; 
    double_end[2] = '\0'; 
   
    strcat(stuffed, double_start); 
    
    for(i = 0; i < strlen(input); i++) { 
        temp[0] = input[i]; 
        temp[1] = '\0'; 
        if(input[i] == start_delim) 
            strcat(stuffed, double_start); 
        else if(input[i] == end_delim) 
            strcat(stuffed, double_end);
        else 
            strcat(stuffed, temp); 
    } 
   
    strcat(stuffed, double_end); 
 
    printf("Data after character stuffing: %s\n", stuffed); 
 
    return 0; 
} 

//2bWrite a program for congestion control using leaky bucket algorithm.
#include <stdio.h>
int main() {
 int bucket_capacity, output_rate, n, i;
 int input_packets[50], current_bucket = 0;
 printf("Enter bucket capacity: ");
 scanf("%d", &bucket_capacity);
 printf("Enter output rate: ");
 scanf("%d", &output_rate);
 printf("Enter number of time intervals: ");
 scanf("%d", &n);
 printf("Enter number of packets arriving at each interval:\n");
 for(i = 0; i < n; i++) {
 scanf("%d", &input_packets[i]);
 }
 printf("\nTime\tPackets Incoming\tPackets Sent\tPackets Left\tPackets Dropped\n");
 for(i = 0; i < n; i++) {
 printf("%d\t\t%d\t", i+1, input_packets[i]);
 if(input_packets[i] + current_bucket > bucket_capacity) {
 // Incoming packets overflow bucket
 int dropped = (input_packets[i] + current_bucket) - bucket_capacity;
 current_bucket = bucket_capacity;
 printf("%d\t\t%d\t\t%d\n", output_rate, current_bucket-output_rate, dropped);
 } else {
 current_bucket += input_packets[i];
 printf("%d\t\t%d\t\t0\n", output_rate, (current_bucket-output_rate > 0) ?
current_bucket-output_rate : 0);
 }
 if(current_bucket < output_rate)
 current_bucket = 0;
 
else
 current_bucket -= output_rate;
 }
 return 0;
}
//4
#include <stdio.h> 
#define MAX 100 
#define INFINITY 9999 
 
void dijkstra(int n, int graph[MAX][MAX], int start) { 
    int distance[MAX], visited[MAX], i, j, count, min_dist, next_node; 
 
    // Initialization 
    for (i = 0; i < n; i++) { 
        distance[i] = graph[start][i]; 
        visited[i] = 0; 
    } 
    distance[start] = 0; 
    visited[start] = 1; 
    count = 1; 
 
    while (count < n) { 
        min_dist = INFINITY; 
        next_node = -1; 
        for (i = 0; i < n; i++) { 
            if (!visited[i] && distance[i] < min_dist) { 
                min_dist = distance[i]; 
                next_node = i; 
            } 
        } 
        if (next_node == -1) break; 
 
        visited[next_node] = 1; 
        for (i = 0; i < n; i++) { 
            if (!visited[i] && graph[next_node][i] != INFINITY &&  
                distance[next_node] + graph[next_node][i] < distance[i]) { 
                distance[i] = distance[next_node] + graph[next_node][i]; 
            } 
        } 
        count++; 
    } 
    // Output shortest distances 
    printf("\nShortest distances from source vertex %d:\n", start); 
    for (i = 0; i < n; i++) { 
        printf("To vertex %d : %d\n", i, distance[i]); 
    } 
} 
int main() { 
    int n, graph[MAX][MAX], i, j, start; 
    printf("Enter number of vertices: "); 
    scanf("%d", &n); 
    printf("Enter the adjacency matrix (use %d for infinity/no edge):\n", INFINITY); 
    for (i = 0; i < n; i++) 
        for (j = 0; j < n; j++) 
            scanf("%d", &graph[i][j]); 
     
    printf("Enter the source vertex (0 to %d): ", n - 1); 
    scanf("%d", &start); 
 
    dijkstra(n, graph, start); 
    return 0; 
} 
//7
#include <stdio.h> 
#include <string.h> 
 
// Function to calculate checksum (simple byte-sum modulo 256) 
unsigned char calculate_checksum(const char *data) { 
    unsigned int sum = 0; 
    for (int i = 0; data[i] != '\0'; i++) { 
        sum += (unsigned char)data[i]; 
    } 
    return (unsigned char)(sum % 256); // Modulo 256 for one-byte checksum 
} 
 
// Function to simulate transmission (framing and checksum) 
void send_frame(const char *data, unsigned char *frame, int *frame_len) { 
    unsigned char checksum = calculate_checksum(data); 
    int data_len = strlen(data); 
 
    // Frame format: | SOF (Start of Frame) | DATA | CHECKSUM | EOF (End of Frame) | 
    frame[0] = 0x7E; // SOF byte (01111110 in HDLC) 
    memcpy(&frame[1], data, data_len); 
    frame[1 + data_len] = checksum; 
    frame[2 + data_len] = 0x7F; // EOF byte (arbitrary choice) 
    *frame_len = 3 + data_len; 
} 
 
// Function to simulate receiver frame check 
int receive_frame(const unsigned char *frame, int frame_len, char *out_data) { 
    if (frame[0] != 0x7E || frame[frame_len - 1] != 0x7F) { 
        printf("Frame error: Invalid framing bytes.\n"); 
        return 0; 
    } 
    int data_len = frame_len - 3; 
    memcpy(out_data, &frame[1], data_len); 
    out_data[data_len] = '\0'; 
    unsigned char received_checksum = frame[1 + data_len]; 
    unsigned char calc_checksum = calculate_checksum(out_data); 
    if (received_checksum != calc_checksum) { 
        printf("Checksum error!\n"); 
        return 0; 
    } 
    return 1; 
} 
 
int main() { 
    char data[100]; 
    unsigned char frame[110]; 
    char received_data[100]; 
    int frame_len; 
 
    // Sender Side 
    printf("Enter data to send: "); 
    scanf("%s", data); 
    send_frame(data, frame, &frame_len); 
 
    printf("Transmitted Frame (in hex): "); 
    for (int i = 0; i < frame_len; i++) 
        printf("%02X ", frame[i]); 
    printf("\n"); 
 // (Change third character in data) 
//frame[3] = 0x4D; 
    // Receiver Side 
    if (receive_frame(frame, frame_len, received_data)) { 
        printf("Received data: %s\n", received_data); 
        printf("No error detected in frame.\n"); 
    } 
    return 0; 
}
