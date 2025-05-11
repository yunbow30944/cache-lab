#include "cachelab.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

//数据结构
//1行cache
typedef struct cache_line_t{
    unsigned tag;
    int valid;
    //int data;
    int lru;//时间戳
}cache_line;

//1组cache
typedef struct cache_set_t{
    cache_line *lines;
}cache_set;

//计数
typedef struct count_t{
    int hit_count;
    int miss_count;
    int eviction_count;
}count;

//处理操作
void handle_op(char op, unsigned address, int s, int E, int b, count *c, cache_set *cache, long long* clock)
{
    //计算索引和标记
    unsigned index = (address >> b)&((1<<s)-1);
    unsigned tag = address >> (s+b);
    cache_line* lines = cache[index].lines;//某一组的lines
    
    //查找命中
    for(int i=0; i<E; i++){
        if(lines[i].valid && lines[i].tag == tag){
            c->hit_count++;
            lines[i].lru = (*clock)++;//更新LRU
            return;
        }
    }
    
    //未命中
    c->miss_count++;
    
    //查找空行
    long long min_clock;//最小时间戳
    int min_index = -1;
    for(int i=0; i<E; i++){
        if(!lines[i].valid){//找到空行
            lines[i].valid = 1;
            lines[i].tag = tag;
            lines[i].lru = (*clock)++;
            return;
        }
        else{//有效行
            if(lines[i].lru < min_clock || min_index == -1){
                min_index = i;
                min_clock = lines[i].lru;
            }
        }
    }
    
    //没有空了，替换行
    c->eviction_count++;
    lines[min_index].tag = tag;
    lines[min_index].lru = (*clock)++;
}


int main(int argc, char** argv)
{   
    int opt,s,E,b;
    char *t;
    while(-1 != (opt = getopt(argc, argv, "s:E:b:t:"))){
        /* 解析命令行参数 */
        switch(opt) {
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                t = optarg;
               
                break;
            default:
                printf("wrong argument\n");
                break;
        }
    }
    FILE *fp = fopen(t, "r");//打开文件
    if(fp == NULL){
        printf("File open error\n");
        return 0;
    }
    
    //初始化计数
    count *c = (count*)malloc(sizeof(count));//计数
    c->hit_count = 0;
    c->miss_count = 0;
    c->eviction_count = 0;

    long long clock=0;//时间戳
    //初始化cache
    cache_set *cache = (cache_set*)malloc(sizeof(cache_set)*((1<<s)));
    for(int i=0; i<(1<<s); i++){
        cache[i].lines = (cache_line*)malloc(sizeof(cache_line)*E);
        for(int j=0; j<E; j++){
            cache[i].lines[j].valid = 0;
            cache[i].lines[j].lru = 0;
        }
    }

    char op;
    unsigned address;
    int size;
    // 例如读取行 " M 20,1" or " L 19,3"
    while(fscanf(fp," %c %x,%d", &op, &address, &size)>0)
    {
        if(op == 'I') continue;
        else if(op == 'L'|| op == 'S'){
            handle_op(op, address, s, E, b, c, cache, &clock);
        }
        else if(op == 'M'){
            handle_op('L', address, s, E, b, c, cache, &clock);
            handle_op('S', address, s, E, b, c, cache, &clock);
        }
        else{
            printf("wrong operation\n");
            return 0;
        }
    }
    fclose(fp);
    printSummary(c->hit_count, c->miss_count, c->eviction_count);
    free(c);
    for(int i=0; i<(1<<s); i++){
        free(cache[i].lines);
    }
    free(cache);
    
    return 0;
}