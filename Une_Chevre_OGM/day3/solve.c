#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <assert.h>

int main(int argc, char* argv[]){
    FILE* fp = fopen("input", "r");
    fseek(fp, 0L, SEEK_END);
    uint32_t sz = ftell(fp);
    rewind(fp);

    char* line = NULL;
    size_t len = 0;
    uint32_t sum = 0;

    getline(&line, &len, fp);
    uint32_t glen = strlen(line) - 1;
    uint32_t glines = sz / (glen + 1);
    uint32_t buffsize = glen * glines;
    char* buff = malloc(buffsize);
    char* print = calloc(buffsize, 1);
    memcpy(buff, line, glen);

    uint32_t i = 1;
    while (getline(&line, &len, fp) != -1){
        memcpy(buff + i*glen, line, glen);
        i++;
    }
    int32_t j, k;

    for (int32_t i = 0; i < buffsize; i++){
        if (buff[i] != '.' && (buff[i] > '9' || buff[i] < '0')){
            if (i % glen)
                print[i - 1] = 1;
            if (i % glen != glen - 1)
                print[i + 1] = 1;

            j = i - (int32_t)glen;
            if (j >= 0){
                print[j] = 1;

                if (j % glen)
                    print[j - 1] = 1;
                if (j % glen != glen - 1)
                    print[j + 1] = 1;
            }
            
            j = i + glen;
            if (j < buffsize){
                print[j] = 1;

                if (j % glen)
                    print[j - 1] = 1;
                if (j % glen != glen - 1)
                    print[j + 1] = 1;
            }
        }
    }
    uint32_t num = 0;
    uint8_t ok = 0;
    for (int32_t i = 0; i < buffsize; i++){
        if(isdigit(buff[i])){
            num = 10*num + buff[i] - '0';
            ok |= print[i];

            if (i % glen == glen - 1){
                if (num){
                    if (ok)
                        sum += num;
                    num = 0;
                }
                ok = 0;
            }
        }
        else{
            if (num){
                if (ok)
                    sum += num;
                num = 0;
            }
            ok = 0;
        }
    }

    printf("SUM : %d\n", sum);
    fclose(fp);
    return 0;
}