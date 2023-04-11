#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    const char * filePath = "genesis.txt";
    const char * copyPath = "genesis_copy.txt";
    FILE * inputStream = fopen(filePath, "rb");
    FILE * outputStream = fopen(copyPath, "wb+");

    int f_size = 0;
    fseek(inputStream, 0 , SEEK_END);
    f_size = ftell(inputStream);
    int end = 0;
    end = f_size / 2;

    int p_id = fork();

    //child process
    if (p_id == 0){
        fseek(inputStream, 0, SEEK_SET);
        char buffer[end];
        fread(inputStream, end, 1, outputStream);
        fwrite(buffer, end, 1, outputStream);
        fflush(outputStream);
        fclose(inputStream);
        fclose(outputStream);
    }

    //parent process
    else {
        fseek(inputStream, end + 1, SEEK_SET);
        char buffer[f_size - end];
        fread(inputStream, (f_size - end), 1, outputStream);
        fseek(outputStream, end + 1, SEEK_SET);

        //force second process to wait for first process to write
        sleep(1);
        fwrite(buffer, end, 1, outputStream);
        fflush(outputStream);
        fclose(inputStream);
        fclose(outputStream);
    }

    return 0;
}