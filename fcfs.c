#include<stdio.h>
#include<stdlib.h>


void main(){
    int total_block,num_req,current_head;
    int total_head_movement=0;

    printf("Enter the total no of disk block: ");
    scanf("%d",&total_block);

    printf("enter the no of disk reques: ");
    scanf("%d",&num_req);

    int requests[num_req];

    printf("Enter the disk request (space-separsted): ");
    for(int i=0;i<num_req;i++)
    scanf("%d",&requests[i]);

    printf("Enter the current possion: ");
    scanf("%d",&current_head);

    for(int i=0;i<num_req;i++){
        printf("\t%d",requests[i]);
        total_head_movement +=abs(current_head-requests[i]);
        current_head=requests[i];
    }
    printf("\nTotal no of head movements: %d\n",total_head_movement);
}