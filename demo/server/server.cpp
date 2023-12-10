// server.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <uv.h>
#include <util/uv_assert.h>


void connection_cb(uv_stream_t* server, int status)
{
    ASSERT(status  == 0);
}

void start_server(uv_loop_t* loop)
{
    uv_tcp_t handle;
    uv_tcp_init(loop, &handle);

    struct sockaddr_in bind_addr;
    int r;
    r = uv_ip4_addr("0.0.0.0", 8081, &bind_addr);
    ASSERT(r == 0);

    r = uv_tcp_bind(&handle, (const struct sockaddr*)&bind_addr, 0);
    ASSERT(r == 0);

    r = uv_listen((uv_stream_t*)&handle, 128, connection_cb);
    ASSERT(r == 0);

    uv_unref((uv_handle_t*)&handle);
}

int main()
{
    std::cout << "server start!\n";

    uv_loop_t* loop = uv_default_loop();

    start_server(loop);

    int r;
    r = uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    std::cout << "server end!\n";
}
