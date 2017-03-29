#include "deploy.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;
using std::map;

class network
{

private:
    int node_num;
    int path_num;
    int consumer_num;
    int server_cost;

    int (*consumer_node)[3];

    typedef struct linked_node
    {
        int target_id;
        int width;
        int cost;
    } linked_node;

    map<int , vector<linked_node *> > node_map;

    // get a integer from a char * , the param num mean which number to choice
    int get_int(char *data, int num)
    {
        int black = 0;
        int ret_num = 0;
        int index = 0;

        while(black < num)
        {
            if(data[index] == ' ') black ++;
            index ++;
        }

        while((data[index] >= '0') && (data[index] <= '9'))
        {
            ret_num = ret_num*10 + data[index] - '0' ;
            index ++;
        }
        return ret_num;
    }

    // read a normal node information to vector
    void read_node(char * data)
    {
        int node_id;
        linked_node * pln = new linked_node;
        int index = 0;
        int num = 0;
        while((data[index] != '\r') && (data[index] != '\n'))
        {
            while(data[index] != ' ')
                num = num * 10 + data[index++] - '0';
            node_id = num;
            index ++, num = 0;

            while(data[index] != ' ')
                num = num * 10 + data[index++] - '0';
            pln->target_id = num;
            index ++, num = 0;

            while(data[index] != ' ')
                num = num * 10 + data[index++] - '0';
            pln->width = num;
            index ++, num = 0;

            while((data[index] != ' ') && (data[index] != '\n') && (data[index] != '\r'))
                num = num * 10 + data[index++] - '0';
            pln->cost = num;
        }
        map<int, vector<linked_node *> >::iterator pi;
        pi = node_map.find(node_id);
        if(pi == node_map.end())
        {
            vector<linked_node *> vtmp;
            vtmp.push_back(pln);
            node_map.insert(map<int, vector<linked_node *> >::value_type(node_id, vtmp));
        }
        else
            pi->second.push_back(pln);
    }

    void read_consumer(char * data, int count_i)
    {
        int num = 0;
        int index = 0;

        while(data[index] != ' ')
            num = num * 10 + data[index++] - '0';
        (*(consumer_node + count_i))[0] = num;
        index ++, num = 0;

        while(data[index] != ' ')
            num = num * 10 + data[index++] - '0';
        (*(consumer_node + count_i))[1] = num;
        index ++, num = 0;

        while((data[index] != ' ') && (data[index] != '\r') && (data[index] != '\n'))
            num = num * 10 + data[index++] - '0';
        (*(consumer_node + count_i))[2] = num;
    }

public:

    network(): node_num(0), path_num(0), consumer_num(0), server_cost(0)
    {
        consumer_node = new int [consumer_num][3];
    }

    void init_network(char *topo[MAX_EDGE_NUM], int line_num)
    {
        node_num = get_int(topo[0], 0);
        path_num = get_int(topo[0], 1);
        consumer_num = get_int(topo[0], 2);
        server_cost = get_int(topo[2], 0);

        int step1 = path_num + 4;
        for(int i = 4; i < step1 ; i++)
        {
            read_node(topo[i]);
        }

        int step2 = step1 + consumer_num + 1;

        for(int i = step1 + 1, j =0; i < step2; i++, j++)
        {
            read_consumer(topo[i], j);
        }
    }
};

//你要完成的功能总入口
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename)
{
    network net_a ;

    net_a.init_network(topo, line_num);

    // 需要输出的内容
    //char * topo_file = (char *)"17\n\n0 8 0 20\n21 8 0 20\n9 11 1 13\n21 22 2 20\n23 22 2 8\n1 3 3 11\n24 3 3 17\n27 3 3 26\n24 3 3 10\n18 17 4 11\n1 19 5 26\n1 16 6 15\n15 13 7 13\n4 5 8 18\n2 25 9 15\n0 7 10 10\n23 24 11 23";

    // 直接调用输出文件的方法输出到指定文件中(ps请注意格式的正确性，如果有解，第一行只有一个数据；第二行为空；第三行开始才是具体的数据，数据之间用一个空格分隔开)
    //write_result(topo_file, filename);
    for(int i=0; i< line_num; i++)
    {
        cout << topo[i] << endl;
    }
}

