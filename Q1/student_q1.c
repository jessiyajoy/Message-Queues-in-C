#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct buffer
{
    long mtype;
    float data[10];
} message;

int main()
{
    int i = 0;
    key_t key;
    int msgid;

    float marks[5];
    float avg = 0;

    key = ftok(".", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    for (i = 0; i < 5; i += 1)
    {
        // Each Student Recieves their marks based on their ID which is passed as Message Type
        msgrcv(msgid, &message, sizeof(message), i + 1, 0);                       // Type is ID of Student
        printf("Mark of Student with ID: %d is : %f \n", i + 1, message.data[0]); // Marks for that Particular student
        marks[i] = message.data[0];
    }
}