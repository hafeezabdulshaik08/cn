//Write a program for congestion control using leaky bucket algorithm.
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
