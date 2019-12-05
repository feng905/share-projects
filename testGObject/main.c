/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>


#include <glib.h>
#include <gtk/gtk.h>

#include "src/spice-obj.h"

#include "header.h"

#include "src/vcd-msg-box.h"

static  void spice_created(SpiceObj* obj,int width,int height,gpointer data,gpointer user_priv){
    LOGD("spice_created w:%d,h:%d,data:%p",width,height,data);
}


void testGobject(){
  //  gtk_init(0,0);

   SpiceObj* so = g_object_new(SPICE_TYPE_OBJ, NULL);


   LOGD("connect 'spice-created'");
   g_signal_connect(so,"spice-created",G_CALLBACK(spice_created),so);

   //
   LOGD("begin emit");
   emit_spice_created(so);
   LOGD("end emit");

   //g_object_ref(so);
}

void testGSocket(){
    LOGD("testGSocket");

    const char* host = "192.168.199.249";
    int port = 3389;

    GError*  err = NULL;

#if 0
    GSocketClient * client = g_socket_client_new();
    int timeout = g_socket_client_get_timeout(client);
    LOGD("g_socket_client_get_timeout :%d",timeout);
    g_socket_client_set_timeout(client,1);

    LOGD("g_socket_client_connect_to_host begin");
    GSocketConnection *conn = g_socket_client_connect_to_host(client,host,port,NULL,&err);
    LOGD("g_socket_client_connect_to_host end conn:%p,err:%p,msg:%s",conn,err,err?err->message:"null");
#else
    GSocket *socket = g_socket_new(G_SOCKET_FAMILY_IPV4, G_SOCKET_TYPE_STREAM,G_SOCKET_PROTOCOL_TCP,&err);
    LOGD("g_socket_new socket:%p",socket);

    GSocketAddress *addr = g_inet_socket_address_new_from_string(host,port);
    LOGD("g_inet_socket_address_new_from_string addr:%p",addr);
    if(!addr) return;

    //g_socket_set_timeout(socket,1);
    g_socket_set_blocking(socket,0);

    LOGD("g_socket_connect begin");
    err = NULL;
    gboolean b =  g_socket_connect(socket,addr,NULL,&err);
    //LOGD("g_socket_connect end b:%d,err:%s",b,err?err->message:"null");

    err = NULL;
    b = g_socket_condition_timed_wait(socket,G_IO_IN | G_IO_OUT | G_IO_NVAL | G_IO_ERR | G_IO_HUP, 1000*200,NULL,&err);
    LOGD("g_socket_condition_timed_wait end b:%d,err:%s",b,err? err->message: "null");
    if(err) return;

    err = NULL;
    b = g_socket_check_connect_result(socket,&err);
    LOGD("g_socket_check_connect_result b:%d,err:%s",b,err ? err->message : "null");
#endif
}


int main(int arg0,char** arg1){
   
#if 0
        //1.gtk环境初始化
        gtk_init(&arg0, &arg1);
 
        //2.创建一个窗口
        GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 
        //3.创建一个固定布局容器fixed
        GtkWidget *fixed = gtk_fixed_new();
        //将fixed添加到window中
        gtk_container_add(GTK_CONTAINER(window), fixed);
 
        //4.创建一个button按钮
        GtkWidget *button1 = gtk_button_new_with_label("button1");
        //将button1添加到固定容器fixed中
        gtk_fixed_put(GTK_FIXED(fixed), button1, 0,0);
 
        GtkWidget *button2 = gtk_button_new_with_label("button2");
        //将button1添加到固定容器fixed中
        gtk_fixed_put(GTK_FIXED(fixed), button2, 0, 0);
 
        //5.移动button2到(150,150)的位置
        gtk_fixed_move(GTK_FIXED(fixed), button2, 150, 150);
 
        //6.设置button2的大小
        gtk_widget_set_size_request(button2,100, 50);
 
        //7.显示所有窗口
        gtk_widget_show_all(window);
 
        //8.主事件循环
        gtk_main();
#elif 0
        testGobject();
#elif 1
        testGSocket();
#elif 0 
        gtk_init(&arg0, &arg1);
        message_box("sfasgasfwef");
        gtk_main();
#else
#endif


   return 0;
}
