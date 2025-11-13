//3a
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
 
#define MAX_FRAMES 50 
#define WINDOW_SIZE 4 

int is_frame_lost() { 
    // 20% loss chance 
    return (rand() % 5) == 0; 
} 
 
int main() { 
    int total_frames, sent = 0, ack = 0, to_send, i; 
 
    srand((unsigned)time(NULL)); 
    printf("Enter total number of frames to send (max %d): ", MAX_FRAMES); 
    scanf("%d", &total_frames); 
 
    printf("\n--- Sending frames using Go-Back-N with window size %d ---\n", 
WINDOW_SIZE); 
 
    while (ack < total_frames) { 
        // Determine how many frames can be sent in this window 
        to_send = 0; 
        for (i = 0; i < WINDOW_SIZE && sent + i < total_frames; i++) 
            to_send++; 
 
        printf("\nSender window: ["); 
        for (i = 0; i < to_send; i++) 
            printf("%d ", sent + i + 1); 
        printf("]\n"); 
 
        int error_index = -1; 
        for (i = 0; i < to_send; i++) { 
            if (is_frame_lost()) { 
                printf("Frame %d lost or corrupted!\n", sent + i + 1); 
                error_index = i; 
                break; 
            } else { 
                printf("Frame %d sent successfully.\n", sent + i + 1); 
            } 
        } 

        if (error_index == -1) { 
            // All frames received correctly, ACK all 
            printf("Receiver: ACK for all %d frames.\n", to_send); 
            sent += to_send; 
            ack += to_send; 
        } else { 
          
            printf("Receiver: NACK for frame %d. Go-Back-N triggered.\n", sent + error_index + 
1); 
            printf("Receiver: Discards all frames after and incl. frame %d.\n", sent + error_index + 
1); 
          
            sent += error_index; 
            ack += error_index; 
        } 
    } 
 
    printf("\nAll frames sent and acknowledged successfully!\n"); 
    return 0; 
}

//3b
#include <stdio.h> 
#define MAX 20 
#define INF 9999 
 
int main() { 
    int n, i, j, u, v, min, total_cost = 0; 
    int graph[MAX][MAX], visited[MAX] = {0}, edges = 0; 
 
    printf("Enter the number of hosts (nodes): "); 
    scanf("%d", &n); 
 
    printf("Enter the adjacency matrix (cost 0 for self, %d for no direct link):\n", INF); 
    for(i = 0; i < n; i++) 
        for(j = 0; j < n; j++) 
            scanf("%d", &graph[i][j]); 
 
    visited[0] = 1; // Start from host 0 
 
    printf("\nEdges in the broadcast (spanning) tree:\n"); 
    while(edges < n - 1) { 
        min = INF; 
        for(i = 0; i < n; i++) { 
            if(visited[i]) { 
                for(j = 0; j < n; j++) { 
                    if(!visited[j] && graph[i][j] < min && graph[i][j] != 0) { 
                        min = graph[i][j]; 
                        u = i; 
                        v = j; 
                    } 
                } 
            } 
        } 
        printf("Host %d - Host %d : Cost = %d\n", u, v, min); 
        total_cost += min; 
        visited[v] = 1; 
        edges++; 
    } 
    printf("Total cost of Broadcast Tree: %d\n", total_cost); 
    return 0; 
} 
//6a
#include <stdio.h> 
#include <stdlib.h> 
 
#define MAX_FRAMES 10 
 
// Simulating frame transmission 
typedef struct { 
    int frame_no; 
    int acked; // 0: not acked, 1: acked 
} Frame; 
 
void send_frame(int frame_no) { 
    printf("Sender: Sent frame %d\n", frame_no); 
} 
 
void receive_frame(int frame_no) { 
    printf("Receiver: Received frame %d\n", frame_no); 
} 
 
void send_ack(int frame_no) { 
    printf("Receiver: Ack sent for frame %d\n", frame_no); 
} 
 
void receive_ack(int frame_no) { 
    printf("Sender: Ack received for frame %d\n", frame_no); 
} 
 
int main() { 
    int total_frames, window_size; 
    int sender_base = 0; 
    int next_frame_to_send = 0; 
    int receiver_expected = 0; 
    int ack[MAX_FRAMES] = {0}; 
    Frame window[MAX_FRAMES]; 
 
    printf("Enter total number of frames to send: "); 
    scanf("%d", &total_frames); 
    printf("Enter window size: "); 
    scanf("%d", &window_size); 
 
    // Initialize window 
    for(int i=0; i<total_frames; ++i) { 
        window[i].frame_no = i; 
        window[i].acked = 0; 
    } 
 
    // Sender side 
    while (sender_base < total_frames) { 
        // Send frames in window 
        while (next_frame_to_send < sender_base + window_size && next_frame_to_send < 
total_frames) { 
            if (window[next_frame_to_send].acked == 0) { 
                send_frame(window[next_frame_to_send].frame_no); 
            } 
            next_frame_to_send++; 
        } 
 
        // Simulate receiver randomly dropping some frames 
        int recv; 
        printf("Enter received frame number (or -1 if lost): "); 
        scanf("%d", &recv); 
 
        if (recv >= 0 && recv < total_frames && window[recv].acked == 0) { 
            receive_frame(recv); 
            send_ack(recv); 
            window[recv].acked = 1; 
        } 
         
        // Simulate sender receiving acks (all acks up to and including the last in-order acked frame) 
        printf("Enter ack number received by sender (-1 if none): "); 
        int ack_no; 
        scanf("%d", &ack_no); 
        if (ack_no >= 0 && ack_no < total_frames && window[ack_no].acked == 1) { 
            receive_ack(ack_no); 
        } 
 
        // Slide the window for every in-order ack 
        while (sender_base < total_frames && window[sender_base].acked == 1) { 
            sender_base++; 
        } 
    } 
 
    printf("All frames sent and acknowledged!\n"); 
    return 0; 
}
//8a
#include <stdio.h> 
#define MAX 10 
#define INF 9999 
int main() { 
    int nodes, i, j, k, count = 0; 
    int distance[MAX][MAX], via[MAX][MAX], updated[MAX][MAX]; 
     
    printf("Enter the number of nodes: "); 
    scanf("%d", &nodes); 
 
    printf("Enter the cost/delay adjacency matrix (%d for no link/infinite delay):\n", INF); 
    for(i = 0; i < nodes; i++) { 
        for(j = 0; j < nodes; j++) { 
            scanf("%d", &distance[i][j]); 
            if(i != j && distance[i][j] == 0) distance[i][j] = INF; 
            via[i][j] = j; 
        } 
    } 
 
    // Distance Vector Algorithm 
    do { 
        count = 0; 
        for(i = 0; i < nodes; i++) { 
            for(j = 0; j < nodes; j++) { 
                for(k = 0; k < nodes; k++) { 
                    if(distance[i][j] > distance[i][k] + distance[k][j]) { 
                        distance[i][j] = distance[i][k] + distance[k][j]; 
                        via[i][j] = k; 
                        count++; 
                    } 
                } 
            } 
        } 
    } while(count != 0); 
    // Display routing tables 
    for(i = 0; i < nodes; i++) { 
        printf("\nRouting table for node %d:\n", i); 
        printf("Destination\tNext Hop\tTotal Cost\n"); 
        for(j = 0; j < nodes; j++) { 
            if (i == j) 
                printf("%d\t\t-\t\t0\n", j); 
            else 
                printf("%d\t\t%d\t\t%d\n", j, via[i][j], distance[i][j]); 
        } 
    } 
    return 0; 
} 
 
