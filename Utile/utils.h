#pragma once

#include "lst_timer.h"


/* 工具类
 * 包含定时器和常用网络编程的函数
 */

class util_timer;
class sort_timer_lst;

class Utils
{
public:
    Utils() {}
    ~Utils() {}

    void init(sort_timer_lst timer_lst, int timeslot);

    //bind+listen port
    int socket_bind(int port);

    //对文件描述符设置非阻塞
    int setnonblocking(int fd);

    //关闭Nagle算法，不要延迟ack
    int setSocketNodelay(int fd);

    //将内核事件表注册读事件，ET模式，选择开启EPOLLONESHOT
    void addfd(int epollfd, int fd, bool one_shot, int TRIGMode);

    //信号处理函数
    static void sig_handler(int sig);

    //设置信号函数
    void addsig(int sig, void(handler)(int), bool restart = true);

    //定时处理任务，重新定时以不断触发SIGALRM信号
    void timer_handler();

    void show_error(int connfd, const char *info);

public:
    static int *u_pipefd;
    sort_timer_lst m_timer_lst;
    static int u_epollfd;
    int m_TIMESLOT;
};
