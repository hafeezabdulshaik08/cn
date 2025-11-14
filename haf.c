3a//
  Enter total number of frames to send (max 50): 3 
 --- Sending frames using Go-Back-N with window size 4 --- 
 
Sender window: [1 2 3 ] 
Frame 1 sent successfully. 
Frame 2 sent successfully. 
Frame 3 sent successfully. 
Receiver: ACK for all 3 frames. 
 
//3bAll frames sent and acknowledged successfully!
Enter the number of hosts (nodes): 4 
Enter the adjacency matrix (cost 0 for self, 9999 for no direct link): 
0 2 9999 6 
2 0 3 8 
9999 3 0 5 
6 8 5 0 
Edges in the broadcast (spanning) tree: 
Host 0 - Host 1 : Cost = 2 
Host 1 - Host 2 : Cost = 3 
Host 2 - Host 3 : Cost = 5 
Total cost of Broadcast Tree: 10

//slw select
Enter total number of frames to send: 5 
Enter window size: 3 
Sender: Sent frame 0 
Sender: Sent frame 1 
Sender: Sent frame 2 
Enter received frame number (or -1 if lost): 0 
Receiver: Received frame 0 
Receiver: Ack sent for frame 0 
Enter ack number received by sender (-1 if none): 0 
Sender: Ack received for frame 0 
Sender: Sent frame 3 
Enter received frame number (or -1 if lost): 2 
Receiver: Received frame 2 
Receiver: Ack sent for frame 2 
Enter ack number received by sender (-1 if none): 2 
Sender: Ack received for frame 2 
Enter received frame number (or -1 if lost): 3 
Receiver: Received frame 3 
Receiver: Ack sent for frame 3 
Enter ack number received by sender (-1 if none): -1 
Enter received frame number (or -1 if lost): 1 
Receiver: Received frame 1 
Receiver: Ack sent for frame 1 
Enter ack number received by sender (-1 if none): 1 
Sender: Ack received for frame 1 
Sender: Sent frame 4 
Enter received frame number (or -1 if lost): 4 
Receiver: Received frame 4 
Receiver: Ack sent for frame 4 
Enter ack number received by sender (-1 if none): 4 
Sender: Ack received for frame 4 
All frames sent and acknowledged! 
// algorithum
  Output:  
1. Input: Enter the number of nodes (e.g., 4). 
2. Matrix: Enter an adjacency matrix (use 0 for self, actual delay for link, 9999 for 
no link). 
● Example for 4 nodes: 
● 0 3 9999 7 
● 8 0 2 9999 
● 5 9999 0 1 
● 2 9999 9999 0 
 
Routing table for node 0: 
Destination Next Hop Total Cost 
0  -  0 
1  1  3 
2  1  5 
3  2  6 
 
Routing table for node 1: 
Destination Next Hop Total Cost 
1  -  0 
0  0  8 
2  2  2 
3  2  3 
